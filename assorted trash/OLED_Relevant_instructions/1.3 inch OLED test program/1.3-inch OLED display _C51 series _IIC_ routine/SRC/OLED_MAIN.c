//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED IIC�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   P1^0��SCL��
//              D1   P1^1��SDA��
//              RES  �Ӹ�
//              DC   �ӵ�
//              CS   �ӵ�                
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/

#include "reg52.h"

#include "oled.h"

/*******************************Main*******************************/
void main(void)
{
	Initial_M096128x64_ssd1306();
	Delay_1ms(5);
	while(1)
	{
		fill_picture(0xff);//ȫ����ʾ
		Delay_50ms(25);
		fill_picture(0xf0);//����Ϩ�𣻳���һ��һ��������
		Delay_50ms(25);
		Picture();//��ʾһ��ͼƬ
		Delay_50ms(25);
	}
}
