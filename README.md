# S32K312 ADC Module

NXP S32K312 MCU의 ADC 모듈을 레지스터 직접 제어 방식으로 사용하여, 가변저항 값에 따라 RGB LED의 4가지 상태를 제어하는 Bare-metal 펌웨어 예제입니다.

---

## 프로젝트 배경

경북대학교 IT대학 전자공학부 ACELAB에서 진행한 'S32K312 펌웨어 교재 개발' 프로젝트의 일환으로 작성된 ADC 파트 예제 코드와 문서입니다.

S32 Design Studio의 SDK나 HAL에 의존하지 않고, 레퍼런스 매뉴얼을 기반으로 하드웨어 레지스터를 직접 설정하는 방법을 학습하는 것을 목표로 합니다.

---

## 개요

가변저항(ADC0_P0) 입력을 12비트 디지털 값으로 변환한 뒤, 결과 값의 범위에 따라 RGB LED를 OFF, Red, Green, Blue 상태로 점등합니다. 이를 위해 SIUL2, MC_CGM, MC_ME, ADC 모듈을 순서대로 초기화하고 제어합니다.

---

## 하드웨어 구성
보드: S32K312EVB-Q172

쉴드: Easy Module Shield V1

| 부품         | 쉴드 핀 | S32K312EVB 핀 | MCU 기능  |
|--------------|---------|---------------|-----------|
| 가변저항 (ROTATION) | A0      | PTD1          | ADC0_P0  |
| Red LED      | D11     | PTC10         | GPIO     |
| Green LED    | D10     | PTB17         | GPIO     |
| Blue LED     | D9      | PTB16         | GPIO     |

---

## 코드 구조

- **main.c**  
  메인 애플리케이션 로직을 포함, SIUL2 초기화 및 ADC 값에 따른 LED 상태를 제어

- **adc_s32k312.c**  
  ADC 및 클럭 모듈(MC_CGM, MC_ME) 초기화, 변환 시작, 결과 읽기 등 저수준 드라이버 함수를 구현

- **adc_s32k312.h**  
  ADC 및 관련 모듈의 레지스터 주소, 오프셋, 비트 필드 매크로를 정의

- **docs/**  
  ADC 모듈 상세 분석, 관련 회로 및 레지스터 데이터시트가 포함

---

## 참고 자료

- **S32K3XXRM.pdf** (Reference Manual)  
  - Chapter 10: SIUL2  
  - Chapter 24: Clocking (MC_CGM)  
  - Chapter 46: MC_ME  
  - Chapter 60: ADC  

- **S32K312_IO_Signal_Table.xlsx**  
  MCU 핀과 ADC 채널 매핑 관계를 확인
