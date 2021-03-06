 /************************************************************ 
  Copyright (C),Chigoo Tech. Co., Ltd. 
  FileName: cpu_to_mcu.c  
      <author>  <time>   <version >   <desc>  
***********************************************************/ 
#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/syscalls.h>
#include <linux/kthread.h>
#include <linux/mm.h>
#include <linux/string.h>
#include <linux/semaphore.h>
#include <linux/poll.h>
#include<linux/cdev.h> 
#include <linux/delay.h>

#define ERR(fmt, args...) printk("<0>TIOINFO_ERROR:" fmt, ##args)

#define TINTERFACE_NUM           168
#define TINTERFACE_DEVNAME	    "mcu_dev"

static struct cdev char_dev_devs;// 定义一个cdev结构

static	int mcu_major;
static  int mcu_IRQ;

typedef struct lOCATIONDATA
{
	 unsigned char   CMD;
	 unsigned	 long int  Val;                   
}lOCATIONDATA;


static struct class *mcu_gpio_dev_class; 
static unsigned int queue_flag;
DECLARE_WAIT_QUEUE_HEAD(location_queue);
#define MCU_DATA0	GPIO_PC(26)
#define MCU_DATA1	GPIO_PC(27)
//#define MCU_DATA	GPIO_PD(00)
#define MCU_ACK     GPIO_PD(03)
#define MCU_ENA     GPIO_PD(01)
#define MCU_CLK     GPIO_PD(02)
#define SMCU_PWREN	GPIO_PB(20)
#define MasterSendCommType         0x0A
#define MasterRecvCommType         0x05

static int      IrqCount		= 0;
static int      CommType		= 0;
static int      SendType			= 0;
static lOCATIONDATA RecvFormMcuData;
static lOCATIONDATA SendToMcuData;
static char     AckStatues      = 0; 
static long int		 location_ir		= 0;
static long int		 location_angle		= 0;
static long int		 locationInfo		= 0;
static long	int		 location_temp_ir 	= 0;
static long	int		 locationTempInfo	= 0;
static char			 angleFlag			= 0;
#define INITANGLE	360
static void ReposeACK(void)
{
  if (AckStatues)
         gpio_set_value(MCU_ACK,0);
  else   gpio_set_value(MCU_ACK,1);
  AckStatues=!AckStatues; 
}

static void char_dev_setup_cdev(struct cdev *dev, int minor, struct file_operations *fops)
{
    int err, devno = MKDEV(mcu_major, minor);
    
    cdev_init(dev, fops);
    dev->owner = THIS_MODULE;
    dev->ops = fops;
    
    err = cdev_add(dev, devno, 1);
    if( err )
    {
        printk(KERN_NOTICE "Error %d adding char_dev %d\n", err, minor);
    }
}

static void mcu_gpio_init(void)
{  
	gpio_request(MCU_DATA1, "mcu_data1"); 
	gpio_request(MCU_DATA0, "mcu_data1"); 
	gpio_request(MCU_ACK, "mcu_ack"); 
	gpio_request(MCU_ENA,"mcu_ena"); 
	gpio_request(MCU_CLK, "mcu_clk"); 
	gpio_request(SMCU_PWREN,"smcu_pwren");
	
	gpio_direction_input(MCU_DATA0);
	gpio_direction_input(MCU_DATA1);
	gpio_direction_output(MCU_ACK,0);
	AckStatues=0;
	gpio_direction_input(MCU_ENA);
	gpio_direction_input(MCU_CLK);
	gpio_direction_output(SMCU_PWREN,0);
	printk("mcu_interface_gpio_init\n");
}

static int mcu_open(struct inode *inode, struct file *filp)
{
    printk("mcu devive open\n");
    return 0;
}

static ssize_t mcu_read(struct file * file,char * buf,size_t count,loff_t * f_ops) 
{ 
    wait_event_interruptible(location_queue,queue_flag);
	copy_to_user(buf, &locationInfo,sizeof(long int));
    queue_flag 		= 0;
	locationInfo		= 0;
	location_ir		= 0;
	location_angle	= INITANGLE;
    return 0; 
} 
 
static int mcu_close(struct inode *inode, struct file *filp)
{
    
	return 0;
}
static irqreturn_t mcu_isr(int irq, void *dev_id)
{
	int interrupt_num;
    int rCount = 0;
	interrupt_num = *(int*)dev_id;
	if (interrupt_num!=mcu_IRQ)
	{
	    printk("interrupt_num invalid\n");
		return IRQ_HANDLED;
	}     

    //接收数据
    if(gpio_get_value(MCU_ENA) == 1)
    {
        CommType = 0;
        IrqCount = 0;
        RecvFormMcuData.CMD = 0;
        RecvFormMcuData.Val = 0;
        ReposeACK();		
        return IRQ_HANDLED;
    }

    IrqCount++;
    if(IrqCount < 3)
    {
        rCount = (IrqCount-1)*2;
        if (gpio_get_value(MCU_DATA0)==1) CommType |=(0x1 <<(rCount+0));
        if (gpio_get_value(MCU_DATA1)==1) CommType |=(0x1 <<(rCount+1));
        if (IrqCount == 2)
        {
                if (CommType == MasterRecvCommType)
                    {
                        printk("RecvFromMcuData = %d\n",CommType);
                    }
        }
     }else 
     if (CommType == MasterSendCommType)
     {
        if (IrqCount < 7)
        {
            rCount=(IrqCount-3)*2;
            if (gpio_get_value(MCU_DATA0)==1) RecvFormMcuData.CMD|=(0x1 <<(rCount+0));    
            if (gpio_get_value(MCU_DATA1)==1) RecvFormMcuData.CMD |=(0x1 <<(rCount+1));    
        }else
        if(IrqCount < 23)
         {
            rCount=(IrqCount-7)*2;
            if (gpio_get_value(MCU_DATA0)==1) RecvFormMcuData.Val|=((long int)0x1 <<(rCount+0));    
            if (gpio_get_value(MCU_DATA1)==1) RecvFormMcuData.Val |=((long int)0x1 <<(rCount+1));    
            if (IrqCount == 22)
            {    
                if(RecvFormMcuData.CMD == 0xA0)
                {
					location_ir = (RecvFormMcuData.Val)*10000;
					location_temp_ir = location_ir;
				}else 
				if(RecvFormMcuData.CMD == 0xA1)
				{
						location_angle = RecvFormMcuData.Val;
				}
				locationTempInfo = location_ir + location_angle;
				if((locationInfo != locationTempInfo) && locationTempInfo != INITANGLE)
				{
					location_ir	 = location_temp_ir;										
					locationInfo = location_ir + location_angle;
					if(locationInfo > INITANGLE+1)
					{
						printk("RecvFormMcuData.CMD = %d,locationInfo=%ld\n",RecvFormMcuData.CMD,locationInfo);
						queue_flag = 1;
						wake_up_interruptible(&location_queue);//唤醒
					}
				}
            }
        }
     }else
     if(CommType == MasterSendCommType)
     {
         printk("line = %d RecvFromMcuData = %d\n",__LINE__,CommType);
     }else
     {
        printk("Recv ERROR CommType\n");
     }
    
  ReposeACK();
  return IRQ_HANDLED; 
}

unsigned int mcu_poll(struct file *file , struct poll_table_struct *wait)
{
    unsigned int mask;
    printk("will poll wait...\n");
    poll_wait(file,&location_queue,wait);
    printk("poll wait end...\n");
    //阻塞
    if(queue_flag)
        mask = POLLIN | POLLRDNORM; //有数据可以读
    return mask;
}

static struct file_operations mcu_fops = {
	.owner  =   THIS_MODULE,
//    .probe  =   mcu_probe,
	.open   =   mcu_open,
	.read   =   mcu_read,
 	.release=   mcu_close,
 	.poll   =   mcu_poll,
};

static int __init	mcu_dev_init(void)
{
	int    ret;
	mcu_major = register_chrdev(TINTERFACE_NUM, TINTERFACE_DEVNAME,&mcu_fops);                                                                                                                                                            
	if (mcu_major < 0) 
	{
        	ERR("Failed to allocate major number.\n");
	        return -ENODEV;
    }
    char_dev_setup_cdev(&char_dev_devs, 0, &mcu_fops);
    printk("The major of the char_dev device is %d\n", mcu_major);
	//sema_init(&sem1, 0);
	mcu_gpio_init();
	mcu_IRQ = gpio_to_irq(MCU_CLK);
	disable_irq(mcu_IRQ);
	irq_set_irq_type(mcu_IRQ,IRQF_TRIGGER_FALLING);//IRQF_TRIGGER_RISING);
	ret = request_irq(mcu_IRQ, mcu_isr,IRQF_DISABLED, TINTERFACE_DEVNAME,&mcu_IRQ);
	if(ret != 0)
	{
		return -ENODEV;
	}
	mcu_gpio_dev_class=class_create(THIS_MODULE, TINTERFACE_DEVNAME); 
	if (IS_ERR(mcu_gpio_dev_class)==0)
	    device_create(mcu_gpio_dev_class,NULL, MKDEV(TINTERFACE_NUM, 0), NULL,TINTERFACE_DEVNAME); 
	else   
        ERR("Failed to Create  Dev=%s\n",TINTERFACE_DEVNAME);	
	printk("Chigoo Comm Successfully initialized module IRQ=%d\n",mcu_IRQ);
	return 0;
}
static void __exit	mcu_dev_cleanup(void)
{
	  device_destroy(mcu_gpio_dev_class, MKDEV(TINTERFACE_NUM, 0)); 
  	  class_destroy(mcu_gpio_dev_class);
      cdev_del(&char_dev_devs);
  	  unregister_chrdev(mcu_major, TINTERFACE_DEVNAME);	
}

module_init(mcu_dev_init);
module_exit(mcu_dev_cleanup);
MODULE_DESCRIPTION("Chigoo mcu communication driver");
MODULE_AUTHOR("Ozil");
MODULE_LICENSE("GPL");



