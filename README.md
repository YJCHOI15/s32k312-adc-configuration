# S32K312 ADC Module

개요

가변저항 입력(ADC0_P0)을 읽어 값의 범위에 따라 OFF/Red/Green/Blue 중 하나를 선택해 PTC10/PTB17/PTB16 GPIO로 RGB LED를 구동하는 실습 레포임. 레지스터 기반으로 SIUL2, MC_CGM, MC_ME, ADC 설정을 순서대로 수행함.
또한 경북대 ACE( http://ace.knu.ac.kr/
 ) 프로그램에서 진행한 ‘S32K312 펌웨어 교재’ 개발에 참여했으며, 이 레포는 내가 맡은 ADC 파트의 예제와 설명을 담고 있음. 관련 회로/레지스터 캡처, 해설 문서, 강의 슬라이드 등은 docs/ 폴더에 정리해둠.

하드웨어

보드: S32K312EVB-Q172

쉴드: Easy Module Shield V1 (ROTATION=A0, RGB LED=D9/D10/D11)

전원: 5V/USB

참고 전압: ADC 입력은 0~3.3V 범위로 유지할 것임

핀 맵
기능	보드 핀	모듈/채널	비고
가변저항 입력	PTD1	ADC0_P0	A0 라인 매핑됨
RGB Red	PTC10	SIUL2.GPDO[74]	Active High
RGB Green	PTB17	SIUL2.GPDO[49]	Active High
RGB Blue	PTB16	SIUL2.GPDO[48]	Active High

MSCR 인덱스: PTC10=74, PTB17=49, PTB16=48 임


동작 요약 (레지스터 경로)

클럭 생성 (MC_CGM)

FIRC 48 MHz → DIV=1 설정으로 24 MHz CORE_CLK 생성함

클럭 적용 (MC_ME)

PRTN0_PCONF.PCE=1 → PRTN0_COFB1_CLKEN에서 ADC0 포함 블록 활성화 → PRTN0_PUPD 트리거 → CTL_KEY 2단계 키 입력 순서로 갱신함

핀 설정 (SIUL2)

MSCR[74,49,48]을 GPIO/출력(OBE=1)로 설정

GPDO[74,49,48]로 출력 제어함

ADC 설정/사용 (ADC_0)

MCR: PWDN 상태에서 ADCLKSEL 선택 → PWDN 해제 → MODE=single 변환 기준

NCMR0: CH0(ADC0_P0) 활성화

MCR.NSTART=1로 변환 개시 → PCDR0에서 VALID 확인 후 CDATA 읽음

참고

S32K3XXRM: SIUL2, Clocking(MC_CGM), MC_ME, ADC 챕터

S32K312_IO Signal Table: PTD1↔ADC0_P0 매핑 확인용임