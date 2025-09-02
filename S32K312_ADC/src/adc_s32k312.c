#include "adc_s32k312.h"

void ADC0_CLK_Enable(void) {
    /* MC_CGM 설정 */
    /* FIRC_CLK(48MHz)을 2분주해 CORE_CLK(24Mhz) 생성 */
    MC_CGM_MUX_0_CSC &= ~(0b1111 << SELCTL_SBIT);   /* CORE_CLK으로 FIRC 선택 */
    MC_CGM_MUX_0_DC_0 |= (3 << DIV_SBIT);           /* FIRC_CLK을 2로 분주 */
                                                    /* 출력 클럭 주기는 입력 클럭 주기의 (DIV + 1) 배*/

    /* MC_ME 설정 */
    /* CORE_CLK이 ADC0이 속한 파티션 0, COFB 1번 구역에 공급되도록 허가*/
    MC_ME_PRTN0_PCONF |= (1 << PCE_BIT);            /* 파티션0 클럭 활성화 */
    MC_ME_PRTN0_COFB1_CLKEN |= (1 << REQ40_BIT);    /* 파티션0 COFB1 클럭 게이트 요청 */
    MC_ME_PRTN0_PUPD |= (1 << PCUD_BIT);            /* 파티션0 설정 적용 트리거 */
    MC_ME_CTL_KEY = CTL_KEY_VAL;                    /* 안전키로 최종 실행 */
    MC_ME_CTL_KEY = CTL_KEY_INV_VAL;                /* 총 2회 수행 */

    while(MC_ME_PRTN0_PUPD & (1 << PCUD_BIT));      /* 파티션0 설정 완료 대기 */
}

void ADC0_Init(void) {

    ADC0_CALBISTREG &= ~(0b111 << RESN_SBIT);
    ADC0_CALBISTREG |= (0b001 << RESN_SBIT);        /* 해상도 12비트 설정 */
    ADC0_CALBISTREG |= (1 << TEST_EN_BIT);          /* 최초 1회 캘리브레이션 진행 */
    while(ADC0_CALBISTREG & (1 << C_T_BUSY_BIT));   /* 캘리브레이션 완료 대기 */

    ADC0_MCR |= (1 << PWDN_BIT);  /* ADC0 MCR 레지스터 설정을 위한 파워 다운 진입 */
    ADC0_MCR &= ~(1 << MODE_BIT); /* Single conversion Mode */
    ADC0_MCR &= ~(0b11 << ADCLKSEL_SBIT); /* CORE_CLK을 1분주 -> AD_CLK(24Mhz) 생성 */
    ADC0_MCR &= ~(1 << PWDN_BIT); /* ADC0 파워 다운 해제 */

    ADC0_NCMR0 |= (1 << CH0_BIT); /* 일반 변환 채널 선택: Precision 0 */

}

void ADC0_Start_Conversion(void) {
    ADC0_MCR |= (1 << NSTART_BIT);             /* 일반 변환 시작 */
    
    while(ADC0_MCR & (1 << NSTART_BIT));       /* 변환 후 NSTART 값은 자동으로 0이 됨 */
}

uint16_t ADC0_Get_Result(void) {
    while(!(ADC0_PCDR0 & (1 << VALID_BIT)));   /* 아직 읽지 않은 새로운 데이터 확인 */
    
    return (uint16_t)(ADC0_PCDR0 & CDATA_MASK);
}