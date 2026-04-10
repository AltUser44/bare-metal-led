#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

/*
 * STM32F401RE memory map (RM0368)
 */
#define PERIPH_BASE            (0x40000000UL)
#define AHB1PERIPH_BASE        (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE        (PERIPH_BASE + 0x00000000UL)

#define RCC_BASE               (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOA_BASE             (AHB1PERIPH_BASE + 0x0000UL)
#define TIM2_BASE              (APB1PERIPH_BASE + 0x0000UL)

#define NVIC_ISER_BASE         (0xE000E100UL)
#define NVIC_ICER_BASE         (0xE000E180UL)
#define NVIC_ICPR_BASE         (0xE000E280UL)

typedef struct
{
    volatile uint32_t MODER;      /* 0x00 */
    volatile uint32_t OTYPER;     /* 0x04 */
    volatile uint32_t OSPEEDR;    /* 0x08 */
    volatile uint32_t PUPDR;      /* 0x0C */
    volatile uint32_t IDR;        /* 0x10 */
    volatile uint32_t ODR;        /* 0x14 */
    volatile uint32_t BSRR;       /* 0x18 */
    volatile uint32_t LCKR;       /* 0x1C */
    volatile uint32_t AFR[2];     /* 0x20, 0x24 */
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t CR;         /* 0x00 */
    volatile uint32_t PLLCFGR;    /* 0x04 */
    volatile uint32_t CFGR;       /* 0x08 */
    volatile uint32_t CIR;        /* 0x0C */
    volatile uint32_t AHB1RSTR;   /* 0x10 */
    volatile uint32_t AHB2RSTR;   /* 0x14 */
    volatile uint32_t RESERVED0[2];
    volatile uint32_t APB1RSTR;   /* 0x20 */
    volatile uint32_t APB2RSTR;   /* 0x24 */
    volatile uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;    /* 0x30 */
    volatile uint32_t AHB2ENR;    /* 0x34 */
    volatile uint32_t RESERVED2[2];
    volatile uint32_t APB1ENR;    /* 0x40 */
    volatile uint32_t APB2ENR;    /* 0x44 */
    volatile uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;  /* 0x50 */
    volatile uint32_t AHB2LPENR;  /* 0x54 */
    volatile uint32_t RESERVED4[2];
    volatile uint32_t APB1LPENR;  /* 0x60 */
    volatile uint32_t APB2LPENR;  /* 0x64 */
    volatile uint32_t RESERVED5[2];
    volatile uint32_t BDCR;       /* 0x70 */
    volatile uint32_t CSR;        /* 0x74 */
    volatile uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;      /* 0x80 */
    volatile uint32_t PLLI2SCFGR; /* 0x84 */
    volatile uint32_t RESERVED7;
    volatile uint32_t DCKCFGR;    /* 0x8C */
} RCC_TypeDef;

typedef struct
{
    volatile uint32_t CR1;        /* 0x00 */
    volatile uint32_t CR2;        /* 0x04 */
    volatile uint32_t SMCR;       /* 0x08 */
    volatile uint32_t DIER;       /* 0x0C */
    volatile uint32_t SR;         /* 0x10 */
    volatile uint32_t EGR;        /* 0x14 */
    volatile uint32_t CCMR1;      /* 0x18 */
    volatile uint32_t CCMR2;      /* 0x1C */
    volatile uint32_t CCER;       /* 0x20 */
    volatile uint32_t CNT;        /* 0x24 */
    volatile uint32_t PSC;        /* 0x28 */
    volatile uint32_t ARR;        /* 0x2C */
    volatile uint32_t RESERVED0;
    volatile uint32_t CCR1;       /* 0x34 */
    volatile uint32_t CCR2;       /* 0x38 */
    volatile uint32_t CCR3;       /* 0x3C */
    volatile uint32_t CCR4;       /* 0x40 */
    volatile uint32_t RESERVED1;
    volatile uint32_t DCR;        /* 0x48 */
    volatile uint32_t DMAR;       /* 0x4C */
    volatile uint32_t OR;         /* 0x50 */
} TIM_TypeDef;

#define RCC                    ((RCC_TypeDef *)RCC_BASE)
#define GPIOA                  ((GPIO_TypeDef *)GPIOA_BASE)
#define TIM2                   ((TIM_TypeDef *)TIM2_BASE)

#define NVIC_ISER0             (*(volatile uint32_t *)(NVIC_ISER_BASE + 0x00UL))
#define NVIC_ICER0             (*(volatile uint32_t *)(NVIC_ICER_BASE + 0x00UL))
#define NVIC_ICPR0             (*(volatile uint32_t *)(NVIC_ICPR_BASE + 0x00UL))

/* RCC bits */
#define RCC_AHB1ENR_GPIOAEN_Pos (0U)
#define RCC_AHB1ENR_GPIOAEN_Msk (1UL << RCC_AHB1ENR_GPIOAEN_Pos)
#define RCC_APB1ENR_TIM2EN_Pos  (0U)
#define RCC_APB1ENR_TIM2EN_Msk  (1UL << RCC_APB1ENR_TIM2EN_Pos)

/* GPIO */
#define GPIO_MODER_MODER5_Pos   (10U)
#define GPIO_MODER_MODER5_Msk   (3UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_OUTPUT       (1UL)
#define GPIO_ODR_OD5_Msk        (1UL << 5U)

/* TIM2 */
#define TIM_DIER_UIE_Msk        (1UL << 0U)
#define TIM_SR_UIF_Msk          (1UL << 0U)
#define TIM_EGR_UG_Msk          (1UL << 0U)
#define TIM_CR1_CEN_Msk         (1UL << 0U)

/* NVIC */
#define TIM2_IRQn               (28U)

#endif /* REGISTERS_H */
