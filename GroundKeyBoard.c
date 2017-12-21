/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F2K16S2 ϵ�� IO���Ծ���------------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����        */
/* ���Ҫ��������Ӧ�ô˴���,����������ע��ʹ����STC�����ϼ�����        */
/*---------------------------------------------------------------------*/

//��ʾ����Keil������������ѡ��Intel��8058оƬ�ͺŽ��б���
//�����ر�˵��,����Ƶ��һ��Ϊ11.0592MHz


#include "reg51.h"
#include "GroundkeyBoard.h"
#include "intrins.h"

#define FOSC 11059200L

#define T1MS (65536-FOSC/1000)      //1T??
//#define T1MS (65536-FOSC/12/1000) //12T??

typedef unsigned char BYTE;
typedef unsigned int WORD;

sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P1M1 = 0x91;    //PxM1.n,PxM0.n     =00--->Standard,    01--->push-pull
sfr P1M0 = 0x92;    //                  =10--->pure input,  11--->open drain
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xb1;
sfr P3M0 = 0xb2;
sfr P4M1 = 0xb3;
sfr P4M0 = 0xb4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;

sfr P4   = 0xC0;
sbit P40 = P4^0;
sbit P41 = P4^1;
sbit P42 = P4^2;
sbit P43 = P4^3;
sbit P44 = P4^4;
sbit P45 = P4^5;
sbit P46 = P4^6;
sbit P47 = P4^7;

sfr P5   = 0xC8;
sbit P50 = P5^0;
sbit P51 = P5^1;
sbit P52 = P5^2;
sbit P53 = P5^3;
sbit P54 = P5^4;
sbit P55 = P5^5;
sbit P56 = P5^6;
sbit P57 = P5^7;

sfr P6   = 0xE8;
sbit P60 = P6^0;
sbit P61 = P6^1;
sbit P62 = P6^2;
sbit P63 = P6^3;
sbit P64 = P6^4;
sbit P65 = P6^5;
sbit P66 = P6^6;
sbit P67 = P6^7;

sfr P7   = 0xF8;
sbit P70 = P7^0;
sbit P71 = P7^1;
sbit P72 = P7^2;
sbit P73 = P7^3;
sbit P74 = P7^4;
sbit P75 = P7^5;
sbit P76 = P7^6;
sbit P77 = P7^7;

sfr AUXR = 0x8e;                    //�����Ĵ���

sfr ADC_CONTR   =   0xBC;           //ADC������
sfr ADC_RES     =   0xBD;           //ADC��8���
sfr ADC_LOW2    =   0xBE;           //ADC��2���
sfr P1ASF       =   0x9D;           //P1�ڵ�2���ܿ��ƼĴ���



sfr IAP_DATA    =   0xC2;           //IAP?????
sfr IAP_ADDRH   =   0xC3;           //IAP????????
sfr IAP_ADDRL   =   0xC4;           //IAP????????
sfr IAP_CMD     =   0xC5;           //IAP?????
sfr IAP_TRIG    =   0xC6;           //IAP???????
sfr IAP_CONTR   =   0xC7;           //IAP?????

#define CMD_IDLE    0               //????
#define CMD_READ    1               //IAP?????
#define CMD_PROGRAM 2               //IAP??????
#define CMD_ERASE   3               //IAP??????
//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
//#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

//#define IAP_ADDRESS 0x1000
#define LeftRightMin_Addr  	0x10
#define LeftRightMax_Addr  	0x210
#define UpDownMin_Addr  		0x410
#define UpDownMax_Addr  		0x610
#define RoundMin_Addr  			0x810
#define RoundMax_Addr  			0x1210        //2017-12-21����EEPROM����

#define ADC_POWER   0x80            //ADC��Դ����λ
#define ADC_FLAG    0x10            //ADC��ɱ�־
#define ADC_START   0x08            //ADC��ʼ����λ
#define ADC_SPEEDLL 0x00            //540��ʱ��
#define ADC_SPEEDL  0x20            //360��ʱ��
#define ADC_SPEEDH  0x40            //180��ʱ��
#define ADC_SPEEDHH 0x60            //90��ʱ��

#define     URMD    0           //0:ʹ�ö�ʱ��2��Ϊ�����ʷ�����
                                //1:ʹ�ö�ʱ��1��ģʽ0(16λ�Զ�����ģʽ)��Ϊ�����ʷ�����
                                //2:ʹ�ö�ʱ��1��ģʽ2(8λ�Զ�����ģʽ)��Ϊ�����ʷ�����

sfr T2H   = 0xd6;               //��ʱ��2��8λ
sfr T2L   = 0xd7;               //��ʱ��2��8λ
sfr BRT		= 0x9C;
//-----------------------------------------------

/* Timer0 interrupt routine */

int T1Counter=0;
int KeyScanCounter=0;
int SendCounter=0;
int ADCSacnCounter = 0;
BYTE KeyFlag=0;
BYTE KEYSCANFLAG=0;
BYTE SendFLAG=0;
BYTE LEDFLAG=0;
BYTE ADCSCANFLAG=0;

BYTE LightKEYCouter=0;
BYTE LightKEYReleaseFlag=0;
int TAKEOFF_KEYCounter=0;
unsigned char  LED_Set = 0;
unsigned char  KEY_Value = 0x00;
static BYTE ADCNO=ADC1Enum;
BYTE ADCValue[5]={0x60,0x61,0x62,0x63,0x64};

BYTE rocker[3]={100,100,100};

unsigned char Package[8];

unsigned char ScanKey(void);
void LED_SET(unsigned char key);
BYTE GetADCResult(BYTE ch);
void InitADC(void);
void ScanADCChannel(void);
void UartInit(void);		//9600bps@11.0592MHz
void ShowResult(BYTE ch);
void ProcessData(void);


unsigned char UpAndDown_MIN  = 100;
unsigned char UpAndDown_MAX  = 100;

unsigned char LeftAndRight_MIN = 100;
unsigned char LeftAndRight_MAX  = 100;

unsigned char Round_MIN  = 100;
unsigned char Round_MAX  = 100;

void tm0_isr() interrupt 1 using 1
{
	T1Counter++;
	KeyScanCounter++;
	SendCounter++;
	ADCSacnCounter++;
	if(ADCSacnCounter>=20)
	{
		ADCSacnCounter = 0;
		ADCSCANFLAG = 1;
	}
	if(KeyScanCounter>=50)
	{
		KeyScanCounter=0;
		KEYSCANFLAG = 1;
		LEDFLAG = 1;
	}
	if(T1Counter>=1000)
	{
		T1Counter = 0;
		P54 = ! P54;                    //�����Կ�ȡ��
	}
	if(SendCounter>=100)
	{
		SendCounter = 0;
		SendFLAG = 1;
	}
}

/*----------------------------
�����ʱ
----------------------------*/
void Delay(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}

/*----------------------------
���ʹ�������
----------------------------*/
void SendData(BYTE dat)
{
    while (!TI);                    //�ȴ�ǰһ���������
    TI = 0;                         //������ͱ�־
    SBUF = dat;                     //���͵�ǰ����
}

//-----------------------------------------------


void BSP_Init(void)
{
	  P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;

    AUXR |= 0x80;                   //��ʱ��0Ϊ1Tģʽ
//  AUXR &= 0x7f;                   //��ʱ��0Ϊ12Tģʽ

    TMOD = 0x00;                    //���ö�ʱ��Ϊģʽ0(16λ�Զ�����)
    TL0 = T1MS;                     //��ʼ����ʱֵ
    TH0 = T1MS >> 8;
    TR0 = 1;                        //��ʱ��0��ʼ��ʱ
    ET0 = 1;                        //ʹ�ܶ�ʱ��0�ж�
    EA = 1;
		
		InitADC();
		
		UartInit();
}


unsigned char ScanKey(void)
{
	unsigned char KeyNO=0;
	/*ǰ�ĸ�*/
	if(!KEY1)
	{
		KeyNO = KEY1Enum;
		KEY_Value |=0x01;
	}
	else
		KEY_Value &=0xFE;
	/***************************/
	if(!KEY2)
	{
		KeyNO = KEY2Enum;
		if(LightKEYReleaseFlag==0)
		{
			LightKEYReleaseFlag = 1;
			LightKEYCouter++;
		}
		//KEY_Value |=0x02;
	}
	else
		LightKEYReleaseFlag = 0;
	/***************************/
	if(!KEY3)
	{
		KeyNO = KEY3Enum;
		KEY_Value |=0x04;
	}
	else
		KEY_Value &=0xFB;
	/***************************/
	if(!KEY4)
	{
		KeyNO = KEY4Enum;
		KEY_Value |=0x08;
	}
	else
		KEY_Value &=0xF7;
	/***************************/
	/*���ĸ�*/
	if(!KEY5&&(KeyFlag==0||KeyFlag==1))
	{
		KeyNO = KEY5Enum;
		KEY_Value |=0x10;
		KeyFlag = 1;
	}
	else 	if(!KEY6&&(KeyFlag==0||KeyFlag==2))
	{
		KeyNO = KEY6Enum;
		KEY_Value |=0x20;
		KeyFlag = 2;
	}
	else 	if(!KEY7&&(KeyFlag==0||KeyFlag==3))
	{
		KeyNO = KEY7Enum;
		KEY_Value |=0x40;
		KeyFlag = 3;
	}
	else 	if(!KEY8&&(KeyFlag==0||KeyFlag==4))
	{
		KeyNO = KEY8Enum;
		TAKEOFF_KEYCounter++;
		if(TAKEOFF_KEYCounter>40)
		{
			KEY_Value |=0x80;
			KeyFlag = 4;
		}
	}
	else 
	{
		KEY_Value &= 0x0f;
		TAKEOFF_KEYCounter = 0;
		KeyFlag = 0;
	}
	return KeyNO;
}


//void LED_SET(unsigned char ledvalue)
//{
//	if(ledvalue==KEY1Enum)
//		LED1 = 0;
//	else 	if(ledvalue==KEY2Enum)
//		LED2 = 0;
//	else 	if(ledvalue==KEY3Enum)
//		LED3 = 0;
//	else 	if(ledvalue==KEY4Enum)
//		LED4 = 0;
//	else 	if(ledvalue==KEY5Enum)
//		LED5 = 0;
//	else 	if(ledvalue==KEY6Enum)
//		LED6 = 0;
//	else 	if(ledvalue==KEY7Enum)
//		LED7 = 0;
//	else 	if(ledvalue==KEY8Enum)
//		LED8 = 0;
//	else
//	{
//		LED1 = 1;
//		LED2 = 1;
//		LED3 = 1;
//		LED4 = 1;
//		LED5 = 1;
//		LED6 = 1;
//		LED7 = 1;
//		LED8 = 1;		
//	}
//}

void LED_SET(unsigned char ledvalue)
{
	if(ledvalue==THROWEnum)
		THROW_LED = 0;
	else 	if(ledvalue==LIGHTEnum)
		LIGHT_LED = ~LIGHT_LED;
	else 	if(ledvalue==RECORDEnum)
		RECORD_LED = 0;
	else 	if(ledvalue==PHOTOEnum)
		PHOTO_LED = 0;
	else 	if(ledvalue==HOVEREnum)
		HOVER_LED = 0;
	else 	if(ledvalue==HOMEEnum)
		HOME_LED = 0;
	else 	if(ledvalue==LANDINGEnum)
		LANDING_LED = 0;
	else 	if(ledvalue==TAKEOFFEnum)
		TAKEOFF_LED = 0;
	else
	{	
		THROW_LED = 1;
//		LIGHT_LED = 1;
		RECORD_LED = 1;
		PHOTO_LED = 1;
		HOVER_LED = 1;
		HOME_LED = 1;
		LANDING_LED = 1;
		TAKEOFF_LED = 1;
	}
}
                                                                                                
/*----------------------------
��ʼ��ADC
----------------------------*/
void InitADC(void)
{
    P1ASF = 0xff;                   //����P1��AD��
    ADC_RES = 0;                    //�������Ĵ���
    ADC_CONTR = ADC_POWER | ADC_SPEEDH;
    Delay(5);                       //ADC�ϵ粢��ʱ
}
/*----------------------------
��ȡADC���
----------------------------*/
BYTE GetADCResult(BYTE ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDH | ch | ADC_START;
    _nop_();                        //�ȴ�4��NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//�ȴ�ADCת�����
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    return ADC_RES;                 //����ADC���
}

///*----------------------------
//????
//----------------------------*/
//void Delay(BYTE n)
//{
//    WORD x;

//    while (n--)
//    {
//        x = 0;
//        while (++x);
//    }
//}

/*----------------------------
??IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //??IAP??
    IAP_CMD = 0;                    //???????
    IAP_TRIG = 0;                   //???????
    IAP_ADDRH = 0x80;               //???????IAP??
    IAP_ADDRL = 0;
}

/*----------------------------
?ISP/IAP/EEPROM???????
----------------------------*/
unsigned char IapReadByte(WORD addr)
{
    BYTE dat;                       //?????

    IAP_CONTR = ENABLE_IAP;         //??IAP
    IAP_CMD = CMD_READ;             //??IAP??
    IAP_ADDRL = addr;               //??IAP???
    IAP_ADDRH = addr >> 8;          //??IAP???
    IAP_TRIG = 0x5a;                //?????(0x5a)
    IAP_TRIG = 0xa5;                //?????(0xa5)
    _nop_();                        //??ISP/IAP/EEPROM????
    dat = IAP_DATA;                 //?ISP/IAP/EEPROM??
    IapIdle();                      //??IAP??

    return dat;                     //??
}

/*----------------------------
???????ISP/IAP/EEPROM??
----------------------------*/
void IapProgramByte(WORD addr, unsigned char dat)
{
    IAP_CONTR = ENABLE_IAP;         //??IAP
    IAP_CMD = CMD_PROGRAM;          //??IAP??
    IAP_ADDRL = addr;               //??IAP???
    IAP_ADDRH = addr >> 8;          //??IAP???
    IAP_DATA = dat;                 //?ISP/IAP/EEPROM??
    IAP_TRIG = 0x5a;                //?????(0x5a)
    IAP_TRIG = 0xa5;                //?????(0xa5)
    _nop_();                        //??ISP/IAP/EEPROM????
    IapIdle();
}

/*----------------------------
????
----------------------------*/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;         //??IAP
    IAP_CMD = CMD_ERASE;            //??IAP??
    IAP_ADDRL = addr;               //??IAP???
    IAP_ADDRH = addr >> 8;          //??IAP???
    IAP_TRIG = 0x5a;                //?????(0x5a)
    IAP_TRIG = 0xa5;                //?????(0xa5)
    _nop_();                        //??ISP/IAP/EEPROM????
    IapIdle();
}


void ReadParameter(void)
{
		LeftAndRight_MIN 	= IapReadByte(LeftRightMin_Addr); 
			if (LeftAndRight_MIN == 0xff)
					LeftAndRight_MIN = 128;
			
		LeftAndRight_MAX 	= IapReadByte(LeftRightMax_Addr); 
			if (LeftAndRight_MAX == 0xff)
					LeftAndRight_MAX = 128;
			
		UpAndDown_MIN 		= IapReadByte(UpDownMin_Addr);
			if (UpAndDown_MIN == 0xff)
					UpAndDown_MIN = 128;
			
		UpAndDown_MAX 		= IapReadByte(UpDownMax_Addr); 
			if (UpAndDown_MAX == 0xff)
					UpAndDown_MAX = 128;
			
		Round_MIN 				= IapReadByte(RoundMin_Addr); 
			if (Round_MIN == 0xff)
					Round_MIN = 128;
			
		Round_MAX		 			= IapReadByte(RoundMax_Addr); 
			if (Round_MAX == 0xff)
					Round_MAX = 128;
}

/* main program */
void main()
{
		BSP_Init();
		ReadParameter();
    while (1)
		{
			if(ADCSCANFLAG)
			{
				ADCSCANFLAG = 0;
				ScanADCChannel();
			}				
			if(KEYSCANFLAG)
			{
				KEYSCANFLAG = 0;
				ScanKey();
			}
			if(LEDFLAG)
			{
				LEDFLAG = 0;
				LED_SET(LED_Set);
			}
			if(SendFLAG)
			{
				SendFLAG = 0;
				ProcessData();
			}
		}
}


void SaveData(WORD addr,unsigned char  _data)
{
	IapEraseSector(addr);
	IapProgramByte(addr, _data);
}

/*----------------------------
ɨ��ADC���
ADC:93-128-163
����:0-100-200
----------------------------*/
void ScanADCChannel(void)
{
	ADCValue[ADCNO] = GetADCResult(ADCNO);
	if(ADCNO==ADC1Enum)
	{
		/*�������Сֵ*/
		if(ADCValue[ADCNO]<LeftAndRight_MIN)
		{
			LeftAndRight_MIN = ADCValue[ADCNO];
			SaveData(LeftRightMin_Addr, LeftAndRight_MIN);
		}
		if(ADCValue[ADCNO]>LeftAndRight_MAX)
		{
			LeftAndRight_MAX = ADCValue[ADCNO];
			SaveData(LeftRightMax_Addr, LeftAndRight_MAX);
		}
		rocker[0] = ((ADCValue[ADCNO] - LeftAndRight_MIN)*200)/(LeftAndRight_MAX-LeftAndRight_MIN);  //�Ѿ��޸ĺã����Ҹ����¿��Զ�Ӧ�� 20170927	
		//rocker[0] = ADCValue[ADCNO];
	}
	else 	if(ADCNO==ADC2Enum)
	{
				/*�������Сֵ*/
		if(ADCValue[ADCNO]<UpAndDown_MIN)
		{
			UpAndDown_MIN = ADCValue[ADCNO];
			SaveData(UpDownMin_Addr, UpAndDown_MIN);
		}
		if(ADCValue[ADCNO]>UpAndDown_MAX)
		{
			UpAndDown_MAX = ADCValue[ADCNO];
			SaveData(UpDownMax_Addr, UpAndDown_MAX);
		}
		
		rocker[1] = ((ADCValue[ADCNO] - UpAndDown_MIN)*200)/(UpAndDown_MAX-UpAndDown_MIN);
		//rocker[1] = ADCValue[ADCNO];
	}
	else	if(ADCNO==ADC3Enum)
	{
						/*�������Сֵ*/
		if(ADCValue[ADCNO]<Round_MIN)
		{
			Round_MIN = ADCValue[ADCNO];
			SaveData(RoundMin_Addr, Round_MIN);
		}
		if(ADCValue[ADCNO]>Round_MAX)
		{
			Round_MAX = ADCValue[ADCNO];
			SaveData(RoundMax_Addr, Round_MAX);
		}
		
		rocker[2] = ((ADCValue[ADCNO] - Round_MIN)*200)/(Round_MAX-Round_MIN);
		//rocker[2] = ADCValue[ADCNO];
	}
	ADCNO++;
	if(ADCNO>ADC3Enum)
		ADCNO = ADC1Enum;
}

/*----------------------------
��ʼ������
----------------------------*/
void UartInit(void)
{
    SCON = 0x5a;                //���ô���Ϊ8�ɱ䲨����
#if URMD == 0
    T2L = 0xe0;                 //���ò���������ֵ
    T2H = 0xfe;                 //115200 bps(65536-18432000/4/115200)
    AUXR |= 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
    AUXR |= 0x01;               //ѡ��ʱ��2Ϊ����1�Ĳ����ʷ�����
#elif URMD == 1
    AUXR = 0x40;                //��ʱ��1Ϊ1Tģʽ
    TMOD = 0x00;                //��ʱ��1Ϊģʽ0(16Ϊ�Զ�����ֵ)
    TL1 = 0xd8;                 //���ò���������ֵ
    TH1 = 0xff;                 //115200 bps(65536-18432000/4/115200)
    TR1 = 1;                    //��ʱ��1��ʼ����
#else
    TMOD = 0x20;                //���ö�ʱ��1Ϊ8Ϊ�Զ�����ֵģʽ
    AUXR = 0x40;                //��ʱ��1Ϊ1Tģʽ
    TH1 = TL1 = 0xfb;           //115200 bps(256 - 18432000/32/115200)
    TR1 = 1;										//��ʱ��1��ʼ����
#endif
}

/*----------------------------
��װ���ݰ���������
----------------------------*/
void ProcessData(void)
{
	int i=0;
	
	if(LightKEYCouter%2)
		KEY_Value |=0x02;
	else
		KEY_Value &=0xfd;
	
	Package[0] = 0xff;
	Package[1] =  rocker[0];
	Package[2] =	rocker[1];
	Package[3] =	rocker[2];
	Package[4] =	0x00;
	Package[5] =	KEY_Value;
	Package[6] = ~KEY_Value;
	//Package[7] =	0xAA;
	Package[7] = (Package[1]+Package[2]+Package[3]+Package[4]+Package[5]);
	
//		Package[0] = 0xff;
//	Package[1] =  0xc8;
//	Package[2] =	0xc8;
//	Package[3] =	0xc8;
//	Package[4] =	0x00;
//	Package[5] =	KEY_Value;
//	Package[6] = ~KEY_Value;
//	//Package[7] =	0xAA;
//	Package[7] = Package[1]+Package[2]+Package[3]+Package[4]+Package[5];
	
	for(i=0;i<8;i++)
		SendData(Package[i]);
}
//void ProcessData(void)
//{
//	int i=0;
//	
//	if(LightKEYCouter%2)
//		KEY_Value |=0x02;
//	else
//		KEY_Value &=0xfd;
//	
//	Package[0] = 	0xff;
//	Package[1] =  rocker[0];
//	Package[2] =	rocker[1];
//	Package[3] =	rocker[2];
//	Package[4] =	LeftAndRight_MIN;
//	Package[5] =	UpAndDown_MIN;
//	Package[6] =  Round_MIN;
//	Package[7] = 	0xff;
//	
//	for(i=0;i<8;i++)
//		SendData(Package[i]);
//}
