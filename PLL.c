// PLL.c
#include "stm32f10x.h"
#include "PLL.h"

void PLL_Init(void) {
    // 1. B?t HSE (High-Speed External oscillator)
    RCC->CR |= RCC_CR_HSEON; // Kích ho?t HSE
    while (!(RCC->CR & RCC_CR_HSERDY)); // Ch? cho HSE s?n sàng

    // 2. C?u hình b? PLL
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;      // Xóa nguon PLL
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSE;  // Ch?n HSE làm ngu?n PLL

    // C?u hình h? s? nhân PLL
    RCC->CFGR &= ~RCC_CFGR_PLLMULL;    // Xóa h? s? nhân PLL cu
    RCC->CFGR |= RCC_CFGR_PLLMULL5;  // H? s? nhân PLL = 10 (16 MHz * 10 = 160 MHz)

    // 3. B?t PLL
    RCC->CR |= RCC_CR_PLLON; // Kích ho?t PLL
    while (!(RCC->CR & RCC_CR_PLLRDY)); // Ch? cho PLL s?n sàng

    // 4. C?u hình Flash
    FLASH->ACR |= FLASH_ACR_PRFTBE;    // Kích hoat bo dem Prefetch
    //FLASH->ACR &= ~FLASH_ACR_LATENCY;  // Xóa do tre Flash
    //F//LASH->ACR |= FLASH_ACR_LATENCY_1; // Ðat do tre Flash (2 chu k?, phù hop voi 80 MHz)

    // 5. C?u hình bo chia (Prescaler)
    RCC->CFGR &= ~RCC_CFGR_HPRE; // Không chia AHB (HCLK = SYSCLK)
    RCC->CFGR &= ~RCC_CFGR_PPRE1; // Chia PCLK1 (APB1) = HCLK/2
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
    RCC->CFGR &= ~RCC_CFGR_PPRE2; // Không chia PCLK2 (APB2 = HCLK)

    // 6. Ch?n PLL làm ngu?n xung nh?p h? th?ng (SYSCLK)
    RCC->CFGR &= ~RCC_CFGR_SW; // Xóa ch?n SYSCLK
    RCC->CFGR |= RCC_CFGR_SW_PLL; // Ch?n PLL làm SYSCLK
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Ch? PLL du?c ch?n làm SYSCLK
}