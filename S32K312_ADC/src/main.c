#include <stdio.h>
#include "adc_s32k312.h"

/************************ SIUL2 ****************************/
#define SIUL2_BASE           (0x40290000UL)
#define SIUL2_GPDO_BASE      (SIUL2_BASE+0x1300)

#define SIUL2_MSCR48_OFF     (0x300)
#define SIUL2_MSCR49_OFF     (0x304)
#define SIUL2_MSCR74_OFF     (0x368)

#define SIUL2_MSCR48         (*(volatile uint32_t*)(SIUL2_BASE+SIUL2_MSCR48_OFF))
#define SIUL2_MSCR49         (*(volatile uint32_t*)(SIUL2_BASE+SIUL2_MSCR49_OFF))
#define SIUL2_MSCR74         (*(volatile uint32_t*)(SIUL2_BASE+SIUL2_MSCR74_OFF))

#define SIUL2_GPDO48         (*(volatile uint8_t*)(SIUL2_GPDO_BASE+0x33))  /* PTB16 (Blue) */
#define SIUL2_GPDO49         (*(volatile uint8_t*)(SIUL2_GPDO_BASE+0x32))  /* PTB17 (Green) */
#define SIUL2_GPDO74         (*(volatile uint8_t*)(SIUL2_GPDO_BASE+0x49))  /* PTC10 (Red) */

/* MSCRn fields */
#define OBE_BIT              21 
#define SSS_SBIT             0   /* [2:0] */

/* GPDOn fields */
#define PDO_BIT              0
/***********************************************************/

#define RED_ON               (SIUL2_GPDO74 |= (1 << PDO_BIT))
#define RED_OFF              (SIUL2_GPDO74 &= ~(1 << PDO_BIT))
#define GREEN_ON             (SIUL2_GPDO49 |= (1 << PDO_BIT))
#define GREEN_OFF            (SIUL2_GPDO49 &= ~(1 << PDO_BIT))
#define BLUE_ON              (SIUL2_GPDO48 |= (1 << PDO_BIT))
#define BLUE_OFF             (SIUL2_GPDO48 &= ~(1 << PDO_BIT))

void SIUL2_Init(void) {

    // SSS 필드를 0으로 만들어 GPIO 기능으로 설정
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
    
    SIUL2_Init();          /* LED 핀들을 GPIO 출력으로 설정 */
    ADC0_Clk_Enable();     /* ADC0 클럭 게이팅 */
    ADC0_Clk_Generate();   /* ADC0 클럭 (CORE_CLK) 생성 */
    ADC0_Init();           /* ADC 모듈 초기화 */

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

