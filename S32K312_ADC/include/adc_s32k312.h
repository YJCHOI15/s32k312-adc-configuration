#ifndef ADC_S32K312_H
#define ADC_S32K312_H

#include <stdint.h>

/********************* MC_CGM *************************/
#define MC_CGM_BASE            (0x402D8000UL)
#define MC_CGM_MUX_0_CSC_OFF   (0x300UL)
#define MC_CGM_MUX_0_DC_0_OFF  (0x308UL)

#define MC_CGM_MUX_0_CSC       (*(volatile unsigned*)(MC_CGM_BASE+MC_CGM_MUX_0_CSC_OFF))
#define MC_CGM_MUX_0_DC_0      (*(volatile unsigned*)(MC_CGM_BASE+MC_CGM_MUX_0_DC_0_OFF))

/* MUX_0_CSC fields */
#define SELCTL_SBIT            24   /* [27:24] */

/* MUX_0_DC_0 fields */
#define DIV_SBIT               16   /* [18:16] */

/********************* MC_ME *************************/
#define MC_ME_BASE                   (0x402DC000UL)
#define MC_ME_PRTN0_PCONF_OFF        (0x100UL)
#define MC_ME_PRTN0_COFB1_CLKEN_OFF  (0x134UL)
#define MC_ME_PRTN0_PUPD_OFF         (0x104UL)
#define MC_ME_CTL_KEY_OFF            (0x0UL)

#define MC_ME_PRTN0_PCONF            (*(volatile unsigned*)(MC_ME_BASE+MC_ME_PRTN0_PCONF_OFF))
#define MC_ME_PRTN0_COFB1_CLKEN      (*(volatile unsigned*)(MC_ME_BASE+MC_ME_PRTN0_COFB1_CLKEN_OFF))
#define MC_ME_PRTN0_PUPD             (*(volatile unsigned*)(MC_ME_BASE+MC_ME_PRTN0_PUPD_OFF))
#define MC_ME_CTL_KEY                (*(volatile unsigned*)(MC_ME_BASE+MC_ME_CTL_KEY_OFF))

/* PRTN0_PCONF fields*/
#define PCE_BIT                      0

/* PRTN0_COFB1_CLKEN fields */
#define REQ40_BIT                    8

/* PRTN0_PUPD fields */
#define PCUD_BIT                     0

/* CTL_KEY fields */
#define CTL_KEY_VAL                  0x5AF0U
#define CTL_KEY_INV_VAL              0xA50FU

/********************* ADC0 *************************/
#define ADC0_BASE                   (0x400A0000UL)
#define ADC0_MCR_OFF                (0x000UL)
#define ADC0_NCMR0_OFF              (0x0A4UL)
#define ADC0_PCDR0_OFF              (0x100UL)
#define ADC0_CALBISTREG_OFF         (0x3A0UL)

#define ADC0_MCR (*(volatile unsigned*)(ADC0_BASE+ADC0_MCR_OFF)) 
#define ADC0_NCMR0 (*(volatile unsigned*)(ADC0_BASE+ADC0_NCMR0_OFF)) 
#define ADC0_PCDR0 (*(volatile unsigned*)(ADC0_BASE+ADC0_PCDR0_OFF)) 
#define ADC0_CALBISTREG (*(volatile unsigned*)(ADC0_BASE+ADC0_CALBISTREG_OFF))

/* MCR fields */
#define MODE_BIT                    29      
#define NSTART_BIT                  24      
#define ADCLKSEL_SBIT               1       /* [2:1] */
#define PWDN_BIT                    0

/* NCMR0 fields */
#define CH0_BIT                     0     

/* PCDR0 fields */
#define VALID_BIT                   19
#define OVERW_BIT                   18
#define RESULT_SBIT                 16      /* [17:16] */
#define CDATA_MASK                  (0xFFFFUL)

/* CALBISTREG fields */
#define RESN_SBIT                   29      /* [31:29] */
#define C_T_BUSY_BIT                15
#define TEST_FAIL_BIT               3
#define TEST_EN_BIT                 0

/********************함수 선언 *******************/
void ADC0_CLK_Enable(void);
void ADC0_Init(void);
void ADC0_Start_Conversion(void);
uint16_t ADC0_Get_Result(void);

#endif