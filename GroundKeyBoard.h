#ifndef __GROUNDKEYBOARD_H__
#define __GROUNDKEYBOARD_H__


/*
¶ÀÁ¢°´¼ü£º
J2:
	KEY1->Pin1->Å×Í¶->P24
	KEY2->Pin2->ÕÕÉä->P25
	KEY3->Pin3->Â¼Ïñ->P26
	KEY4->Pin4->ÅÄÕÕ->P27
	KEY5->Pin5->ÐüÍ£->P00
	KEY6->Pin6->·µº½->P01
	KEY7->Pin7->½µÂä->P02
	KEY8->Pin8->Æð·É->P03
*/


/*
KEY-LED:
	Pin1->LED1->P23
	Pin2->LED2->P22
	Pin3->LED3->P21
	Pin4->LED4->P20
	Pin5->LED5->P44
	Pin6->LED6->P43
	Pin7->LED7->P42
	Pin8->LED8->P41
*/

/*
Ò¡¸Ë:
	Pin1->ADC2->P12
	Pin2->ADC3->P13
	Pin3->ADC4->P14
*/
#define KEY1  P24
#define KEY2  P25
#define KEY3  P26
#define KEY4  P27
#define KEY5  P00
#define KEY6  P01
#define KEY7  P02
#define KEY8  P03



#define LED1  P23
#define LED2  P22
#define LED3  P21
#define LED4  P20
#define LED5  P44
#define LED6  P43
#define LED7  P42
#define LED8  P41

#define ADC2Pin P12
#define ADC3Pin P13
#define ADC4Pin P14

typedef enum
{
		KEY1Enum = 0x21,
		KEY2Enum,
		KEY3Enum,
		KEY4Enum,
		KEY5Enum = 0x41,
		KEY6Enum,
		KEY7Enum,
		KEY8Enum
}KEY_ENUM;

typedef enum
{
		ADC1Enum = 0x02,
		ADC2Enum,
		ADC3Enum
}ADC_Channel;

//#define UpAndDown_MIN  87
//#define UpAndDown_MID  70
//#define UpAndDown_MAX  0xA7

//#define LeftAndRight_MIN  87
//#define LeftAndRight_MID  70
//#define LeftAndRight_MAX  0xAA

//#define Round_MIN  87
//#define Round_MID  70
//#define Round_MAX  0xb4

//#define UpAndDown_MIN  90
//#define UpAndDown_MAX  163

//#define LeftAndRight_MIN  92
//#define LeftAndRight_MAX  162

//#define Round_MIN  77
//#define Round_MAX  181
////////////////////////////////////////////////
#define THROW_KEY     KEY1
#define LIGHT_KEY     KEY2
#define RECORD_KEY    KEY3
#define PHOTO_KEY     KEY4
#define HOVER_KEY     KEY5
#define HOME_KEY      KEY6
#define LANDING_KEY   KEY7
#define TAKEOFF_KEY   KEY8

#define THROW_LED     LED1
#define LIGHT_LED     LED2
#define RECORD_LED    LED3
#define PHOTO_LED     LED4
#define HOVER_LED     LED5
#define HOME_LED      LED6
#define LANDING_LED   LED7
#define TAKEOFF_LED   LED8

typedef enum
{
		THROWEnum = 0x21,
		LIGHTEnum,
		RECORDEnum,
		PHOTOEnum,
		HOVEREnum = 0x41,
		HOMEEnum,
		LANDINGEnum,
		TAKEOFFEnum
}KEY_NAME_ENUM;

#endif