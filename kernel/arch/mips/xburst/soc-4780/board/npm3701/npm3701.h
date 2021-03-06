#ifndef __NPM3701_H__
#define __NPM3701_H__
#include <gpio.h>

/**
 * mmc platform data
 **/
extern struct jzmmc_platform_data npm3701_inand_pdata;
extern struct jzmmc_platform_data npm3701_tf_pdata;
extern struct jzmmc_platform_data npm3701_sdio_pdata;

/**
 * lcd platform data
 **/
#ifdef CONFIG_FB_JZ4780_LCDC0
extern struct jzfb_platform_data jzfb0_hdmi_pdata;
#endif
#ifdef CONFIG_FB_JZ4780_LCDC1
extern struct jzfb_platform_data jzfb1_pdata;
#endif

/**
 * lcd platform device
 **/
#ifdef CONFIG_LCD_KR070LA0S_270
extern struct platform_device kr070la0s_270_device;
#endif
#ifdef CONFIG_LCD_EK070TN93
extern struct platform_device ek070tn93_device;
#endif
#ifdef CONFIG_LCD_KD50G2_40NM_A2
extern struct platform_device kd50g2_40nm_a2_device;
#endif

extern struct platform_device npm3701_backlight_device;

/**
 * sound platform data
 **/
extern struct snd_codec_data codec_data;

/**
 * audio gpio
 **/
#define GPIO_HP_MUTE		-1	//GPIO_PD(13)	/*hp mute gpio*/
#define GPIO_HP_MUTE_LEVEL	-1	//1		/*vaild level*/

#define GPIO_SPEAKER_EN		-1 //GPIO_PA(27)	//GPIO_PE(6)	/*speaker enable gpio*/
#define GPIO_SPEAKER_EN_LEVEL	1	//1

#define GPIO_HANDSET_EN		  -1		/*handset enable gpio*/
#define GPIO_HANDSET_EN_LEVEL -1

#define	GPIO_HP_DETECT		-1 //GPIO_PE(7)	/*hp detect gpio*/
#define GPIO_HP_INSERT_LEVEL	0

#define GPIO_MIC_DETECT		-1		/*mic detect gpio*/
#define GPIO_MIC_INSERT_LEVEL	-1

#define GPIO_MIC_SELECT		-1		/*mic select gpio*/
#define	GPIO_BUILDIN_MIC_LEVEL	-1		/*headset mic select level*/

#define GPIO_MIC_DETECT_EN		-1  /*mic detect enable gpio*/
#define GPIO_MIC_DETECT_EN_LEVEL	-1 /*mic detect enable gpio*/

/**
 * tsc gpio interface
 **/
#define GPIO_CTP_IRQ			-1 //GPIO_PF(19)
#define GPIO_CTP_WAKE_UP		-1 //GPIO_PF(18)

/**
 * g sensor gpio interface
 **/
#define GPIO_MMA8452_INT1		-1 //GPIO_PF(9)
#define GPIO_LIS3DH_INT1		-1 //GPIO_PF(9)

/**
 * keyboard gpio interface
 **/
//#define GPIO_BACK			GPIO_PF(9)
//#define ACTIVE_LOW_BACK			1

//#define GPIO_MENU			GPIO_PF(10)
//#define ACTIVE_LOW_MENU			1

#define GPIO_ENDCALL			GPIO_PA(30)
#define ACTIVE_LOW_ENDCALL		1

//#define GPIO_VOLUMEUP			GPIO_PD(17)
//#define ACTIVE_LOW_VOLUMEUP		0

//#define GPIO_VOLUMEDOWN		GPIO_PD(18)
//#define ACTIVE_LOW_VOLUMEDOWN		1
#define GPIO_KEY1			GPIO_PD(17)
#define ACTIVE_LOW_KEY1			0

#define GPIO_KEY4                       GPIO_PD(18)
#define ACTIVE_LOW_KEY4	                1

#define GPIO_SP0838_EN			-1 //GPIO_PB(18)
#define GPIO_SP0838_RST			-1 //GPIO_PB(26)

#define GPIO_OV3640_EN			-1 //GPIO_PF(15)
#define GPIO_OV3640_RST			-1 //GPIO_PF(11)

/**
 * usb detect pin
 **/
#define GPIO_USB_DETE			GPIO_PF(13)
/**
 * pmem information
 **/
#define JZ_PMEM_CAMERA_BASE	0x5f000000
#define JZ_PMEM_CAMERA_SIZE	0x01000000

/**
 * motor gpio
 */
#define GPIO_MOTOR_PIN			-1	//GPIO_PB(25) /* PB25 */


//#define GPIO_HOME			GPIO_PD(19)
//#define ACTIVE_LOW_HOME			1
// #define GPIO_CALL
// #define ACTIVE_LOW_CALL			1
#endif /* __NPM3701_H__ */
