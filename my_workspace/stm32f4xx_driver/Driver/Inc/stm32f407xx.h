/*
 * stm32f4xx.h
 *
 *  Created on: 21 __Dec__ 2025
 *      Author: __Sayad__ __Hassan__
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>



/*
 * Simple qualifier
 */

#define _vo		volatile


/*
 * stm32f407xx main system base addreses
 */

#define FLASH_BASEADDR						0x08000000U			/* Base address of Main Memory (Flash memory)(up to 1MB) */
#define SRAM1_BASEADDR						0x20000000U			/* Base address of SRAM1 (112KB) */
#define SRAM2_BASEADDR						0x2001C000U			/* Base address of SRAM2 (16KB) - after SRAM1 */
#define SRAM_BASEADDR						SRAM1_BASEADDR		/* Default SRAM base address points to SRAM1 */
#define ROM_BASEADDR						0x1FFF0000U			/* Base address of System Memory (ROM) */


/*
 *  AHBx and APBx Bus Peripheral base addresses
 */

#define AHB1PERI_BASEADDR						0X40020000U
#define AHB2PERI_BASEADDR						0X50000000U
#define APB1PERI_BASEADDR						0X40000000U
#define APB2PERI_BASEADDR						0X40010000U


/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 */

#define GPIOAPERI_BASEADDR						0X40020000U
#define GPIOBPERI_BASEADDR						0X40020400U
#define GPIOCPERI_BASEADDR						0X40020800U
#define GPIODPERI_BASEADDR						0X40020C00U
#define GPIOEPERI_BASEADDR						0X40021000U
#define GPIOFPERI_BASEADDR						0X40021400U
#define GPIOGPERI_BASEADDR						0X40021800U
#define GPIOHPERI_BASEADDR						0X40021C00U
#define GPIOIPERI_BASEADDR						0X40022000U
#define GPIOJPERI_BASEADDR						0X40022400U
#define GPIOKPERI_BASEADDR						0X40022800U

#define RCCPERI_BASEADDR						0X40023800U


/*
 * Base addresses of peripherals which are hanging on APB1 bus
 */

#define SPI2PERI_BASEADDR						0X40003800U
#define SPI3PERI_BASEADDR						0X40003C00U

#define USART2PERI_BASEADDR						0X40004400U
#define USART3PERI_BASEADDR						0X40004800U

#define UART4PERI_BASEADDR						0X40004C00U
#define UART5PERI_BASEADDR						0X40005000U
#define UART7PERI_BASEADDR						0X40007800U
#define UART8PERI_BASEADDR						0X40007C00U

#define I2C1PERI_BASEADDR						0X40005400U
#define I2C2PERI_BASEADDR						0X40005800U
#define I2C35PERI_BASEADDR						0X40005C00U


/*
 * Base addresses of peripherals which are hanging on APB2 bus
 */

#define USART1PERI_BASEADDR						0X40011000U
#define USART6PERI_BASEADDR						0X40011400U

#define SPI1PERI_BASEADDR						0X40013400U
#define SPI4PERI_BASEADDR						0X40013000U

#define SYSCFGPERI_BASEADDR 					0x40013800U
#define EXTIPERI_BASEADDR						0X40013C00U



/***************** PERIPHERAL REGISTER DEFINITION STRUCTURES *****************/

/*
 * Note: Register of a peripheral are specific to MCU
 *
 * It is wise to use _vo keyword in structure members.
 * Because some of the members may be really _vo in nature.
 *
 */

/*
 * General Purpose Input Output Register Map
 */

typedef struct
{
	_vo uint32_t MODER;		/* GPIO port mode register,							Address Offset: 0x00 */
	_vo uint32_t OTYPER;		/* GPIO port output type register,					Address Offset: 0x04 */
	_vo uint32_t OSPEEDR;		/* GPIO port output speed register,					Address Offset: 0x08 */
	_vo uint32_t PUPDR;		/* GPIO port pull-up/pull-down register,			Address Offset: 0x0C */
	_vo uint32_t IDR;			/* GPIO port input data register,					Address Offset: 0x10 */
	_vo uint32_t ODR;			/* GPIO port output data register,					Address Offset: 0x14 */
	_vo uint32_t BSRR;			/* GPIO port bit set/reset register,				Address Offset: 0x18 */
	_vo uint32_t LCKR;			/* GPIO port configuration lock register,			Address Offset: 0x1C */
	_vo uint32_t AFR[2];		/* AFR[0] : GPIO alternate function low register, 	Address Offset: 0x20
							   	   	   AFR[1] : GPIO alternate function high register,  Address Offset: 0x24 */

} GPIO_RegDef_t;



/*
 * RCC Register Map
 */

typedef struct
{
	_vo uint32_t CR;				/* Clock control register, 								Address Offset: 0x00 */
	_vo uint32_t PLLCFGR;			/* PLL configuration register, 							Address Offset: 0x04 */
	_vo uint32_t CFGR;				/* Clock configuration register, 						Address Offset: 0x08 */
	_vo uint32_t CIR;				/* Clock interrupt register, 							Address Offset: 0x0C */
	_vo uint32_t AHB1RSTR;			/* AHB1 peripheral reset register, 						Address Offset: 0x10 */
	_vo uint32_t AHB2RSTR;			/* AHB2 peripheral reset register, 						Address Offset: 0x14 */
	_vo uint32_t AHB3RSTR;			/* AHB3 peripheral reset register, 						Address Offset: 0x18 */

			 uint32_t RESERVED0;		/* Reserved, 											Address Offset: 0x1C */

	_vo uint32_t APB1RSTR;			/* APB1 peripheral reset register, 						Address Offset: 0x20 */
	_vo uint32_t APB2RSTR;			/* APB2 peripheral reset register, 						Address Offset: 0x24 */

	 	 	 uint32_t RESERVED1[2];		/* Reserved, 											Address Offset: 0x28, 0x2C */

	_vo uint32_t AHB1ENR;			/* AHB1 peripheral clock enable register, 				Address Offset: 0x30 */
	_vo uint32_t AHB2ENR;			/* AHB2 peripheral clock enable register, 				Address Offset: 0x34 */
	_vo uint32_t AHB3ENR;			/* AHB3 peripheral clock enable register, 				Address Offset: 0x38 */

	         uint32_t RESERVED2;		/* Reserved, 											Address Offset: 0x3C */

	_vo uint32_t APB1ENR;			/* APB1 peripheral clock enable register, 				Address Offset: 0x40 */
	_vo uint32_t APB2ENR;			/* APB2 peripheral clock enable register, 				Address Offset: 0x44 */

			 uint32_t RESERVED3[2];		/* Reserved, 											Address Offset: 0x48, 0x4C */

	_vo uint32_t AHB1LPENR;		/* AHB1 peripheral clock enable in low power mode register, Address Offset: 0x50 */
	_vo uint32_t AHB2LPENR;		/* AHB2 peripheral clock enable in low power mode register, Address Offset: 0x54 */
	_vo uint32_t AHB3LPENR;		/* AHB3 peripheral clock enable in low power mode register, Address Offset: 0x58 */

			 uint32_t RESERVED4;		/* Reserved, 											Address Offset: 0x5C */

	_vo uint32_t APB1LPENR;		/* APB1 peripheral clock enable in low power mode register, Address Offset: 0x60 */
	_vo uint32_t APB2LPENR;		/* APB2 peripheral clock enable in low power mode register, Address Offset: 0x64 */

			 uint32_t RESERVED5[2];		/* Reserved, 											Address Offset: 0x68, 0x6C */

	_vo uint32_t BDCR;				/* Backup domain control register, 						Address Offset: 0x70 */
	_vo uint32_t CSR;				/* Clock control & status register, 					Address Offset: 0x74 */

			 uint32_t RESERVED6[2];		/* Reserved, 											Address Offset: 0x78, 0x7C */

	_vo uint32_t SSCGR;			/* Spread spectrum clock generation register, 			Address Offset: 0x80 */
	_vo uint32_t PLLI2SCFGR;		/* PLLI2S configuration register, 						Address Offset: 0x84 */
	_vo uint32_t PLLSAICFGR;		/* PLLSAI configuration register, 						Address Offset: 0x88 */
	_vo uint32_t DCKCFGR;			/* Dedicated clocks configuration register, 			Address Offset: 0x8C */
} RCC_RegDef_t;


/*
 * Peripheral base addresses type casted to xxx_RegDef_t
 *
 * EXAMPLE: RCC_RegDef_t *pRCC = ( (RCC_RegDef_t*) RCC_BASEADDR)
 *
 * Now we can use: RCC_RegDef_t *pRCC = RCC
 */





/*
 *  Clock enable macros for GPIOx peripherals
 */





/*
 *  Clock enable macros for I2Cx peripherals
 */



/*
 *  Clock enable macros for SPIx peripherals
 */




/*
 *  Clock enable macros for USARTx peripherals
 */



/*
 *  Clock enable macros for SYSCFG peripherals
 */





/*
 *  Clock disable macros for GPIOx peripherals
 */





/*
 *  Clock disable macros for I2Cx peripherals
 */



/*
 *  Clock disable macros for SPIx peripherals
 */



/*
 *  Clock disable macros for USARTx peripherals
 */




/*
 *  Clock disable macros for SYSCFG peripherals
 */



/*
 * Macros to reset GPIOx peripherals
 */

// ref @RCC AHB1 peripheral clock register (RCC_AHB1ENR) in reference manual
// first: set to RESET, second: reset to previous to prevent continuous reset operation

#define GPIO_REG_RESET()			do{( RCC->AHB1ENR |= (1 << 0); ( RCC->AHB1ENR &= ~(1 << 0); )} while(0)
									// “do while condition is zero” loop
									// Keep looping while a variable equals 0
									// This runs only once






/*
 * Some generic macros
 */






#endif /* INC_STM32F407XX_H_ */
