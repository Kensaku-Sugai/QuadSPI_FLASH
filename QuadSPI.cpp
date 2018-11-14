#include "QuadSPI.h"

QuadSPI::QuadSPI(PinName mosi, PinName miso, PinName sclk, PinName cs): SPI(mosi, miso, sclk, cs) {
	spi_base = (SPI_T *) NU_MODBASE(_spi.spi.spi);
}

QuadSPI::~QuadSPI() {
}

void QuadSPI::SPIEN_ENABLE() {
	spi_base->CTL |= QSPI_CTL_QSPIEN_Msk;
}

void QuadSPI::SPIEN_DISABLE() {
	spi_base->CTL &= ~QSPI_CTL_QSPIEN_Msk;
}

void QuadSPI::CLEAR_RXFIFO() {
	spi_base->FIFOCTL |= QSPI_FIFOCTL_RXFBCLR_Msk;
}

void QuadSPI::ENABLE_QUAD_OUTPUT_MODE(void) {
	spi_base->CTL |= QSPI_CTL_DATDIR_Msk | QSPI_CTL_QUADIOEN_Msk;
}

void QuadSPI::ENABLE_QUAD_INPUT_MODE(void) {
    spi_base->CTL =  ( spi_base->CTL & ~QSPI_CTL_DATDIR_Msk) | QSPI_CTL_QUADIOEN_Msk;
}

void QuadSPI::DISABLE_QUAD_MODE(void) {
	spi_base->CTL &= ~QSPI_CTL_QUADIOEN_Msk;
}

uint32_t QuadSPI::READ_STATUS() {
	return( spi_base->STATUS );
}

uint32_t QuadSPI::QSPI_IS_BUSY() {
	return( (spi_base->STATUS & QSPI_STATUS_BUSY_Msk)  >> QSPI_STATUS_BUSY_Pos );
}

uint32_t QuadSPI::GET_TX_FIFO_FULL_FLAG() {
	return( (spi_base->STATUS & QSPI_STATUS_TXFULL_Msk )  >> QSPI_STATUS_TXFULL_Pos );
}

void QuadSPI::QSPI_SET_SS_LOW() {
	spi_base->SSCTL = (spi_base->SSCTL & (~(QSPI_SSCTL_AUTOSS_Msk | QSPI_SSCTL_SSACTPOL_Msk))) | QSPI_SSCTL_SS_Msk;
}

void QuadSPI::QSPI_SET_SS_HIGH() {
    spi_base->SSCTL = (spi_base->SSCTL & (~QSPI_SSCTL_AUTOSS_Msk)) | (QSPI_SSCTL_SSACTPOL_Msk | QSPI_SSCTL_SS_Msk);
}

void QuadSPI::QSPI_WRITE_TX(uint32_t u32TxData) {
    spi_base->TX = (u32TxData);
}
uint32_t QuadSPI::QSPI_READ_RX() {
	return (spi_base->RX);
}

uint32_t QuadSPI::QSPI_WRITE_READ(uint32_t u32TxData) {
    spi_base->TX = (u32TxData);
    while( (spi_base->STATUS & QSPI_STATUS_BUSY_Msk)  >> QSPI_STATUS_BUSY_Pos );
	return (spi_base->RX);
}

void QuadSPI::QSPI_ENABLE() {
	spi_base->CTL |= QSPI_CTL_QSPIEN_Msk;
}

void QuadSPI::QSPI_DISABLE() {
    spi_base->CTL &= ~QSPI_CTL_QSPIEN_Msk;
}
