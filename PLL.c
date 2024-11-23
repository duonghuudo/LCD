// PLL.c
#include "stm32f10x.h"
#include "PLL.h"

void PLL_Init(void) {
    // 1. B?t HSE (High-Speed External oscillator)
    RCC->CR |= RCC_CR_HSEON; // K�ch ho?t HSE
    while (!(RCC->CR & RCC_CR_HSERDY)); // Ch? cho HSE s?n s�ng

    // 2. C?u h�nh b? PLL
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;      // X�a nguon PLL
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSE;  // Ch?n HSE l�m ngu?n PLL

    // C?u h�nh h? s? nh�n PLL
    RCC->CFGR &= ~RCC_CFGR_PLLMULL;    // X�a h? s? nh�n PLL cu
    RCC->CFGR |= RCC_CFGR_PLLMULL5;  // H? s? nh�n PLL = 10 (16 MHz * 10 = 160 MHz)

    // 3. B?t PLL
    RCC->CR |= RCC_CR_PLLON; // K�ch ho?t PLL
    while (!(RCC->CR & RCC_CR_PLLRDY)); // Ch? cho PLL s?n s�ng

    // 4. C?u h�nh Flash
    FLASH->ACR |= FLASH_ACR_PRFTBE;    // K�ch hoat bo dem Prefetch
    //FLASH->ACR &= ~FLASH_ACR_LATENCY;  // X�a do tre Flash
    //F//LASH->ACR |= FLASH_ACR_LATENCY_1; // �at do tre Flash (2 chu k?, ph� hop voi 80 MHz)

    // 5. C?u h�nh bo chia (Prescaler)
    RCC->CFGR &= ~RCC_CFGR_HPRE; // Kh�ng chia AHB (HCLK = SYSCLK)
    RCC->CFGR &= ~RCC_CFGR_PPRE1; // Chia PCLK1 (APB1) = HCLK/2
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
    RCC->CFGR &= ~RCC_CFGR_PPRE2; // Kh�ng chia PCLK2 (APB2 = HCLK)

    // 6. Ch?n PLL l�m ngu?n xung nh?p h? th?ng (SYSCLK)
    RCC->CFGR &= ~RCC_CFGR_SW; // X�a ch?n SYSCLK
    RCC->CFGR |= RCC_CFGR_SW_PLL; // Ch?n PLL l�m SYSCLK
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Ch? PLL du?c ch?n l�m SYSCLK
}