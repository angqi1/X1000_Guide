��    X      �     �      �  '   �     �     �  F   �  Z   *  �   �     ,	  
   F	  	   Q	     [	     k	     w	  .   �	     �	     �	     �	     �	     �	     �	     �	     �	     �	     �	  #   
     *
     /
     1
     7
     @
     I
     R
     [
  	   `
     j
     s
     |
     �
     �
     �
     �
     �
     �
     �
     �
     �
     �
     �
     �
     �
     �
     �
     �
     �
          
                    &  [   5     �     �     �  $   �               *  o  :     �     �     �     �     �     �     �     �     �     �     �     �     �     �     �     �          &     (  0  +     \     v     |  &   �  8   �     �     o  
   �  	   �     �     �     �  .   �     �     �                               '     .     3     <     \     a     c     h     q     z     �     �     �     �     �     �     �     �     �     �     �     �     �     �     �     �     �                              $     -     6     ;     D     I     R  [   ^     �     �     �             	   +  	   5  $  ?     d     f     h     j     l     s     |     ~     �     �     �     �     �     �     �     �     �     �     �            U       >                             3           T                        V   K               C       2   J       #      R      M   	   <       5                            .   =   )           *   N   1       Q   $          D               ,       G          H           X      0       8   B      /   &             O            %   I               L           W   6   
   F   E   P   4      9             A   7   @   "   !   S   '   ?   (   ;   -       +      :        
Press a key or mouse button to resume.         C:  specify color scheme
   I:  start in interactive mode after doing non-interactive functions
   L:  load settings
  q:  query all channels and print their settings
  S:  save settings
   d:  adjust a device besides /dev/mixer
  f:  specify file for saving and loading settings (defaults to
      ~/.aumixrc or /etc/aumixrc)
  h:  this helpful message
  [-C <color scheme file>]  [-dhILqS]  [-dhLqS]  [-f <rc file>] %i ms wait
 + - [ ] arrows digits
 ------------------------- -------------------- 0 100 Balance Bass     CD       Digital1 Digital2 Digital3 File Input    Key                       Function
 Keys L Level Line     Line 1   Line 2   Line 3   Load Load From Mic      Mix      Monitor  Mute Mute All Only Output   PCM      PCM 2    Phone In PhoneOut Quit R Radio    Rec Record   Save Save To Speaker  Synth    Treble   Undo Video    View Volume   adjust slider
 aumix %s usage: aumix [-<channel option>[[+|-][<amount>]]|<level>|
R[ecord]|P[lay]|q[uery]] aumix:  error opening mixer aumix:  mixer not open aumix:  no device found aumix:  unable to open settings file aumix:  unknown error %i center balance
 change channel
 channel options:
  v:  main volume           x:  mix monitor
  b:  bass                  W:  PCM 2
  t:  treble                r:  record
  s:  synthesizer           i:  input gain
  w:  PCM                   o:  output gain
  p:  PC speaker            1:  line 1
  l:  line                  2:  line 2
  m:  microphone            3:  line 3
  c:  CD

other options:
 f k l m muted not set o only  page arrows
 q s set to space
 t tab enter < > , .
 toggle level/balance
 toggle record/play
 u |
 Project-Id-Version: aumix
POT-Creation-Date: 2002-11-25 01:36+0000
PO-Revision-Date: 2001-11-28 22:04+0800
Last-Translator: Wang Jian <lark@linux.net.cn>
Language-Team: zh_CN <i18n-translation@lists.linux.net.cn>
MIME-Version: 1.0
Content-Type: text/plain; charset=gb2312
Content-Transfer-Encoding: 8bit
 
�����������갴ť������         C��ָ����ɫ����
   I������ɷǽ������ܺ�����������ģʽ
   L����������
  q����ѯ����ͨ�����ò���ӡ
  S����������
   d�������� /dev/mixer ���������豸
  f��ָ�����ڱ�����������õ��ļ�(Ĭ��Ϊ ~/.aumixrc �� /etc/aumixrc)
  h����ӡ�ð�����Ϣ
  [-C <color scheme file>]  [-dhILqS]  [-dhLqS]  [-f <rc file>] %i ms �ȴ�
 + - [ ] ��ͷ ����
 ------------------------- -------------------- 0 100 ƽ�� ����     CD       ���� 1 ���� 2 ���� 3 �ļ� ����     ��                        ����
 ���� L ���� ��·     ��· 1   ��· 2   ��· 3   ���� ������ ��Ͳ     ���     ������   ���� ȫ������ �� ���     PCM      PCM 2    ��Ͳ���� ��Ͳ��� �˳� R ������   ¼�� ¼��     ���� ���浽 ������   �ϳ�     ����     ���� ��Ƶ     �鿴 ����     ����������
 aumix %s �÷��� aumix [-<channel option>[[+|-][<amount>]]|<level>|
R[ecord]|P[lay]|q[uery]] aumix���򿪻�����ʱ�������� aumix��û�д򿪻����� aumix��û�з����豸 aumix���޷��������ļ� aumix��δ֪���� %i ��ȫƽ��
 �ı�ͨ��
 ͨ��ѡ�
  v��������           x������������
  b������             W��PCM 2
  t������             r��¼��
  s���ϳ���           i����������
  w��PCM              o���������
  p��PC ������        1����· 1
  l����·             2����· 2
  m����Ͳ             3����· 3
  c��CD

����ѡ�
 f k l m �Ѿ��� û������ o ��  ��ҳ��
 q s ����Ϊ �ո�
 t tab enter < > , .
 �л�����/ƽ��
 �л�¼��/����
 u |
 