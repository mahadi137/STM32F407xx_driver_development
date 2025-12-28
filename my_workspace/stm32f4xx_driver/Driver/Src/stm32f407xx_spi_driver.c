/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: 28 Dec 2025
 *      Author: sayad hassan
 */

// Helper function
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if (pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}



/*********************************************************************
 * @fn                 - SPI_PeriClockControl
 *
 * @brief              - Enables or disables clock for a given
 *                       SPI peripheral on APB bus.
 *
 * @param[pSPIx]       - Base address of SPI peripheral (SPI1–SPI4)
 *
 * @param[EnorDi]      - ENABLE  : Turn ON peripheral clock
 *                       DISABLE : Turn OFF peripheral clock
 *
 * @return             - None
 *
 * @note               - Uses RCC clock enable/disable macros.
 *********************************************************************/

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
	    if (pSPIx == SPI1)      SPI1_PERI_CLK_EN();
	    else if (pSPIx == SPI2) SPI2_PERI_CLK_EN();
	    else if (pSPIx == SPI3) SPI3_PERI_CLK_EN();
	    else if (pSPIx == SPI4) SPI4_PERI_CLK_EN();
	}
	else
	{
		if (pSPIx == SPI1)      SPI1_PERI_CLK_DI();
		else if (pSPIx == SPI2) SPI2_PERI_CLK_DI();
		else if (pSPIx == SPI3) SPI3_PERI_CLK_DI();
		else if (pSPIx == SPI4) SPI4_PERI_CLK_DI();
	}
}




/*********************************************************************
 * @fn                 - SPI_Init
 *
 * @brief              - Initializes SPI peripheral according to
 *                       configuration stored in SPI handle structure.
 *
 * @param[pSPIHandle]  - Pointer to SPI handle structure containing:
 *                         - pSPIx        : SPI base address
 *                         - DeviceMode   : Master/Slave mode
 *                         - BusConfig    : Full duplex / Half duplex /
 *                                         Simplex TX / Simplex RX
 *                         - CPHA / CPOL  : Clock phase & polarity
 *                         - DFF          : Data frame format
 *                         - SSM          : Software slave management
 *                         - BR           : Baud rate prescaler
 *
 * @return             - None
 *
 * @note               - Enables SPI peripheral clock internally
 *                       before writing configuration registers.
 *********************************************************************/

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//peripheral clock enable

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);



	uint32_t temp = 0;

	// Configure the device mode
	temp |= (pSPIHandle->SPIPinConfig.DeviceMode << SPI_CR1_MSTR);


	// Configure the bus config
	if(pSPIHandle->SPIPinConfig.BusConfig == SPI_DEVICE_BUS_MODE_FD)
	{
		temp &= ~(1 << SPI_CR1_BIDIMODE);
		temp &= ~(1 << SPI_CR1_RXONLY);
	}
	else if(pSPIHandle->SPIPinConfig.BusConfig == SPI_DEVICE_BUS_MODE_HD)
	{
		temp |= (1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIPinConfig.BusConfig == SPI_DEVICE_BUS_MODE_SIMPLEX_TXONLY)
	{
		temp |= (1 << SPI_CR1_BIDIOE);
	}
	else if(pSPIHandle->SPIPinConfig.BusConfig == SPI_DEVICE_BUS_MODE_SIMPLEX_RXONLY)
	{
		//BIDI mode should be cleared
		temp &= ~(1 << SPI_CR1_BIDIOE);
		//RXONLY bit must be set
		temp |= (1 << SPI_CR1_RXONLY);
	}


	// Configure the CPHA
	temp |= (pSPIHandle->SPIPinConfig.CPHA << SPI_CR1_CPHA);

	// Configure the CPOL
	temp |= (pSPIHandle->SPIPinConfig.CPOL << SPI_CR1_CPOL);

	// Configure the DFF
	temp |= (pSPIHandle->SPIPinConfig.DFF << SPI_CR1_DFF);

	// configure the SSM
	temp |= (pSPIHandle->SPIPinConfig.SSM << SPI_SSM_EN);

	// Configure the spi serial clock speed (baud rate)
	temp |= (pSPIHandle->SPIPinConfig.BR << SPI_CR1_BR);



	pSPIHandle->pSPIx->CR1 = temp;

}



/*********************************************************************
 * @fn                 - SPI_DeInit
 *
 * @brief              - Resets SPI peripheral registers to their
 *                       default reset values.
 *
 * @param[pSPIx]       - Base address of SPI peripheral (SPI1–SPI3)
 *
 * @return             - None
 *
 * @note               - Uses RCC peripheral reset macros.
 *********************************************************************/

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1) SPI1_REG_RESET();
	else if(pSPIx == SPI2) SPI2_REG_RESET();
	else if(pSPIx == SPI3) SPI3_REG_RESET();
}


uint8_t SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint8_t Len)
{
	while(Len > 0)
	{
		// wait until TXE is set
		while(SPI_GetFlag_Status(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// check DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit DFF
			pSPIx->DR =  *((uint16_t*) pTxBuffer);
			Len--;
			Len--;
			(uint16_t*) pTxBuffer++;
		} else
		{
			// 8 bit DFF
			pSPIx->DR =  *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}

}



















