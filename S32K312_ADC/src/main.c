#include <stdio.h>
#include "adc_s32k312.h"

/************************ SIUL2 ****************************/
#define SIUL2_BASE           (0x40290000UL)
#define SIUL2_MSCR48_OFF     (0x300UL)
#define SIUL2_MSCR49_OFF     (0x304UL)
#define SIUL2_MSCR74_OFF     (0x368UL)
#define SIUL2_GPDO48_OFF     (0x1300UL+(48U+3U-2U*(48U%4U)))   /* PTB16 - Blue */
#define SIUL2_GPDO49_OFF     (0x1300UL+(49U+3U-2U*(49U%4U)))   /* PTB17 - Green */
#define SIUL2_GPDO74_OFF     (0x1300UL+(74U+3U-2U*(74U%4U)))   /* PTC10 - Red */

#define SIUL2_MSCR48         (*(volatile unsigned*)(SIUL2_BASE+SIUL2_MSCR48_OFF))
#define SIUL2_MSCR49         (*(volatile unsigned*)(SIUL2_BASE+SIUL2_MSCR49_OFF))
#define SIUL2_MSCR74         (*(volatile unsigned*)(SIUL2_BASE+SIUL2_MSCR74_OFF))

#define SIUL2_GPDO48         (*(volatile unsigned*)(SIUL2_BASE+SIUL2_GPDO48_OFF))
#define SIUL2_GPDO49         (*(volatile unsigned*)(SIUL2_BASE+SIUL2_GPDO49_OFF))
#define SIUL2_GPDO74         (*(volatile unsigned*)(SIUL2_BASE+SIUL2_GPDO74_OFF))

/* MSCRn fields */
#define SSS_SBIT             0   /* [2:0] */
#define OBE_BIT              21 

/* GPDOn fields */
#define PDO_BIT              0

#define RED_ON               (SIUL2_GPDO74 |= (1U << PDO_BIT))
#define RED_OFF              (SIUL2_GPDO74 &= ~(1U << PDO_BIT))
#define GREEN_ON             (SIUL2_GPDO49 |= (1U << PDO_BIT))
#define GREEN_OFF            (SIUL2_GPDO49 &= ~(1U << PDO_BIT))
#define BLUE_ON              (SIUL2_GPDO48 |= (1U << PDO_BIT))
#define BLUE_OFF             (SIUL2_GPDO48 &= ~(1U << PDO_BIT))

void Pin_Init(void) {

    // SSS 피드를 0으로 만들어 GPIO 기능으로 설정
    // OBE 비트를 1로 만들어 출력 모드로 설정

    // RED_LED
    SIUL2_MSCR74 &= ~(0b1111 << SSS_SBIT); 
    SIUL2_MSCR74 |= (1 << OBE_BIT);      

    // GREEN_LED
    SIUL2_MSCR49 &= ~(0b1111 << SSS_SBIT); 
    SIUL2_MSCR49 |= (1 << OBE_BIT);       

    // BLUE_LED
    SIUL2_MSCR48 &= ~(0b1111 << SSS_SBIT); 
    SIUL2_MSCR48 |= (1 << OBE_BIT);     
}

int main(void) {

    Pin_Init();          /* LED 핀들을 GPIO 출력으로 설정 */
    ADC0_CLK_Enable();   /* MC_CGM, MC_ME 설정으로 ADC0 클럭 활성화 */
    ADC0_Init();         /* ADC 모듈 초기화 */

    // 모든 LED를 끈 상태에서 시작
    RED_OFF;
    GREEN_OFF;
    BLUE_OFF;

    uint16_t adcResult = 0;

    while(1)
    {
        ADC0_Start_Conversion(); /* ADC0_P0 채널 변환 시작 (완료 대기 포함) */

        adcResult = ADC0_Get_Result(); // 0 ~ 4095 사이의 값을 읽어옴

        if (adcResult < 1024)
        {
            // 모든 LED 끄기
            RED_OFF;
            GREEN_OFF;
            BLUE_OFF;
        } else if (adcResult < 2048) {
            // RED LED만 켜기
            RED_ON;
            GREEN_OFF;
            BLUE_OFF;
        } else if (adcResult < 3072) {
            // GREEN LED만 켜기
            RED_OFF;
            GREEN_ON;
            BLUE_OFF;
        } else {
            // BLUE LED만 켜기
            RED_OFF;
            GREEN_OFF;
            BLUE_ON;
        }

    }

    return 0;
}

