#include <mbed.h>
#include "QSPI_FLASH.h"

QSPI_FLASH::QSPI_FLASH(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName d2, PinName d3)
    :
    _spi(mosi, miso, sclk, cs),
    _d2(d2),
    _d3(d3)
{
    QSPI_FLASH_Begin();
}

QSPI_FLASH::~QSPI_FLASH() {
}

void QSPI_FLASH::QSPI_FLASH_Begin() {
    _spi.format(8, 0);
    _spi.frequency(2000000);  //SPI Clock = 2MHz
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_D2D3_SwitchToNormalMode() {
    SYS->GPC_MFPL =  SYS->GPC_MFPL & ~(SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk);
    _d2.output();
    _d3.output();
    _d2.write(1);
    _d3.write(1);

}

void QSPI_FLASH::QSPI_D2D3_SwitchToQuadMode() {
    SYS->GPC_MFPL =  (SYS->GPC_MFPL & ~(SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk)) | (0x04UL<<SYS_GPC_MFPL_PC4MFP_Pos) | (0x04UL<<SYS_GPC_MFPL_PC5MFP_Pos);
}

void QSPI_FLASH::QSPI_WriteEnable() {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_WRITE_ENABLE);
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_WriteDisable() {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_WRITE_DISABLE);
    _spi.QSPI_SET_SS_HIGH();
}

uint8_t QSPI_FLASH::QSPI_NAND_ReadStatusReg1() {
    uint8_t rc;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_STATUS_REG);
    _spi.write(ADR_STATUS_REG_1);
    rc = _spi.write(0xFF);
    _spi.QSPI_SET_SS_HIGH();
    return rc;
}

uint8_t QSPI_FLASH::QSPI_NAND_ReadStatusReg2() {
    uint8_t rc;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_STATUS_REG);
    _spi.write(ADR_STATUS_REG_2);
    rc = _spi.write(0xFF);
    _spi.QSPI_SET_SS_HIGH();
    return rc;
}

uint8_t QSPI_FLASH::QSPI_NAND_ReadStatusReg3() {
    uint8_t rc;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_STATUS_REG);
    _spi.write(ADR_STATUS_REG_3);
    rc = _spi.write(0xFF);
    _spi.QSPI_SET_SS_HIGH();
    return rc;
}

void QSPI_FLASH::QSPI_NAND_WriteStatusReg1(uint8_t rc) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_WRITE_STATUS_REG);
    _spi.write(ADR_STATUS_REG_1);
    _spi.write(rc);
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_NAND_WriteStatusReg2(uint8_t rc) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_WRITE_STATUS_REG);
    _spi.write(ADR_STATUS_REG_2);
    _spi.write(rc);
    _spi.QSPI_SET_SS_HIGH();
}

bool QSPI_FLASH::QSPI_NAND_IsBusy() {
    uint8_t r1;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_STATUS_REG);
    _spi.write(ADR_STATUS_REG_3);
    r1 = _spi.write(0xFF);
    _spi.QSPI_SET_SS_HIGH();
    if(r1 & SR3_BUSY_MASK)
        return true;
    return false;
}

void QSPI_FLASH::QSPI_NAND_ReadJEDECID(uint8_t* d) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_JEDEC_ID);
    _spi.write(0x00);
    for (uint8_t i=0; i<3; i++) {
        d[i] = _spi.write(0x00);
    }
    _spi.QSPI_SET_SS_HIGH();
}

bool QSPI_FLASH::QSPI_NAND_PageDataRead(uint16_t addr) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_PAGE_DATA_READ);
    _spi.write(0x00);           // Dummy
    _spi.write(addr>>8);        // PA15-PA08
    _spi.write(addr & 0xFF);    // PA07-PA00
    _spi.QSPI_SET_SS_HIGH();
    //wait(0.1);
    while( _spi.QSPI_IS_BUSY());
    while(QSPI_NAND_IsBusy());

    return true;
}

uint16_t QSPI_FLASH::QSPI_NAND_ReadData(uint16_t addr, uint8_t *buf) { 
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_DATA);
    _spi.write(addr>>8);        // PA15-PA08
    _spi.write(addr & 0xFF);    // PA07-PA00
    _spi.write(0x00);           // Dummy
    uint16_t i;
    for(i=0; i<(PAGE_SIZE_QSPI_NAND); i++) {
        buf[i] = _spi.write(0x00);
    }
    _spi.QSPI_SET_SS_HIGH();
    wait(0.1);
    return i;
}

void QSPI_FLASH::QSPI_NAND_ReadData2(uint16_t addr, uint8_t *buf) { 
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_DATA);
    _spi.write(addr>>8);        // PA15-PA08
    _spi.write(addr & 0xFF);    // PA07-PA00
    _spi.write(0x00);           // Dummy
    buf[0] = _spi.write(0x00);
    _spi.QSPI_SET_SS_HIGH();
    while(QSPI_NAND_IsBusy());
}

void QSPI_FLASH::QSPI_NAND_BlockErase(uint16_t addr) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_BLOCK_ERASE);
    _spi.write(0x00);           // Dummy
    _spi.write(addr>>8);        // PA15-PA08
    _spi.write(addr & 0xFF);    // PA07-PA00
    _spi.QSPI_SET_SS_HIGH();
    //wait(2);
    while( _spi.QSPI_IS_BUSY());
}

uint16_t QSPI_FLASH::QSPI_NAND_ProgramDataLoad(uint16_t addr, uint8_t *buf) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_PGM_DATA_LOAD);
    _spi.write(addr>>8);        // CA15-PA08
    _spi.write(addr & 0xFF);    // CA07-PA00
    uint16_t i;
    for(i=0; i<(PAGE_SIZE_QSPI_NAND+SPARE_SIZE_QSPI_NAND); i++) {
        _spi.write(buf[i]);
    }
    _spi.QSPI_SET_SS_HIGH();
    wait(0.1);
    return i;
}

bool QSPI_FLASH::QSPI_NAND_ProgramExecute(uint16_t addr) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_PGM_EXECUTE);
    _spi.write(0x00);           // Dummy
    _spi.write(addr>>8);        // PA15-PA08
    _spi.write(addr & 0xFF);    // PA07-PA00
    _spi.QSPI_SET_SS_HIGH();
    while( _spi.QSPI_IS_BUSY());
    while(QSPI_NAND_IsBusy());

    return true;
}

uint16_t QSPI_FLASH::QSPI_NAND_QuadReadData(uint16_t addr, uint8_t *buf, uint8_t read_mode) { 
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_FAST_READ_QUAD_IO);       //0xEB
    while( _spi.QSPI_IS_BUSY());

    // enable QSPI quad IO mode and set direction to input
    QSPI_D2D3_SwitchToQuadMode();

    //QSPI_ENABLE_QUAD_OUTPUT_MODE(QSPI_FLASH_PORT);
    _spi.ENABLE_QUAD_OUTPUT_MODE();

    if(read_mode) {
        _spi.write(addr>>8);     // CA15-PA08
        _spi.write(addr & 0xFF); // CA07-PA00
        _spi.write(0xff);        // dummy BUF=1
        _spi.write(0xff);        // dummy
    } else {
        _spi.write(0xff);        // dummy BUF=0
        _spi.write(0xff);        // dummy
        _spi.write(0xff);        // dummy
        _spi.write(0xff);        // dummy
        _spi.write(0xff);        // dummy 
        _spi.write(0xff);        // dummy
    }
    
    _spi.ENABLE_QUAD_INPUT_MODE();

	// clear RX buffer
    _spi.CLEAR_RXFIFO();
    while( _spi.QSPI_IS_BUSY());

    uint16_t i;
    for(i=0; i<(PAGE_SIZE_QSPI_NAND); i++) {
        buf[i] = _spi.write(0x00);
    }

    // /CS: de-active
    _spi.QSPI_SET_SS_HIGH();
    _spi.DISABLE_QUAD_MODE();    
    QSPI_D2D3_SwitchToNormalMode();

    wait(0.1);
    return i;
}

uint16_t QSPI_FLASH::QSPI_NAND_QuadProgramDataLoad(uint16_t addr, uint8_t *buf) {

    // /CS: active
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_QUAD_DATA_LOAD);//0x32
    _spi.write(0x00);        // CA15-PA08
    _spi.write(0x00);        // CA07-PA00

    // enable QSPI quad IO mode and set direction to output
    QSPI_D2D3_SwitchToQuadMode();   //PORT C mfc setting
    _spi.ENABLE_QUAD_OUTPUT_MODE();

    uint16_t i;
    for(i=0; i<(PAGE_SIZE_QSPI_NAND+SPARE_SIZE_QSPI_NAND); i++) {
        _spi.write(buf[i]);
    }

    // /CS: de-active
    _spi.QSPI_SET_SS_HIGH();
    _spi.DISABLE_QUAD_MODE();

    // wait flash busy
    while(QSPI_NAND_IsBusy());

    // wait tx finish
    while(_spi.QSPI_IS_BUSY());

    //QSPI_ClearRxFIFO(QSPI_FLASH_PORT);}
    _spi.CLEAR_RXFIFO();

    QSPI_D2D3_SwitchToNormalMode();
    wait(0.1);
    return i;
}

void QSPI_FLASH::QSPI_NAND_ReadBBMLUT(uint8_t *d) {
    uint8_t i;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_BBM_LUT);
    _spi.write(0x00);              // dummy
        for(i=0;i<(20*2*2);++i){   // 16bit x 20 x 2(LBA,PBA) 
        d[i] = _spi.write(0x00);
    }
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_NAND_DeviceReset() {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_NAND_DEVICE_RESET);
    _spi.QSPI_SET_SS_HIGH();

    wait(0.1);

}

//----------------
uint16_t QSPI_FLASH::QSPI_NOR_SpiFlash_ReadMidDid(void) {
    uint8_t u8RxData[6];

    // /CS: active
    _spi.QSPI_SET_SS_LOW();

    // send Command: 0x90, Read Manufacturer/Device ID
    u8RxData[0] = _spi.write(CMD_READ_MANUFACTUREDEV_ID);

    // send 24-bit '0', dummy
    u8RxData[1] = _spi.write(0x00);
    u8RxData[2] = _spi.write(0x00);
    u8RxData[3] = _spi.write(0x00);

    // receive 16-bit
    u8RxData[4] = _spi.write(0x00);
    u8RxData[5] = _spi.write(0x00);

    // wait tx finish
    while( _spi.QSPI_IS_BUSY());

    // /CS: de-active
    _spi.QSPI_SET_SS_HIGH();

    return ( (u8RxData[4]<<8) | u8RxData[5] );
}
	
bool QSPI_FLASH::QSPI_NOR_IsBusy() {
    uint8_t r1;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_STATUS_REG);
    r1 = _spi.write(0xFF);
    _spi.QSPI_SET_SS_HIGH();
    if(r1 & NOR_EWIP_MASK)
        return true;
    return false;
}

void QSPI_FLASH::QSPI_NOR_PageProgram(uint32_t StartAddress, uint8_t *u8DataBuffer, uint32_t mode_4B) {
    uint32_t i = 0;

    // /CS: active
    _spi.QSPI_SET_SS_LOW();

    // send Command: 0x06, Write enable
    _spi.write(CMD_WRITE_ENABLE);

    // wait tx finish
    while(_spi.QSPI_IS_BUSY());

    // /CS: de-active
    _spi.QSPI_SET_SS_HIGH();

    // /CS: active
    _spi.QSPI_SET_SS_LOW();

    // send Command: 0x02, Page program
    _spi.write(CMD_PAGE_PROGRAM);

	if(mode_4B==1) {
	    // send 32-bit start address
	    _spi.write((StartAddress>>24) & 0xFF);
	    _spi.write((StartAddress>>16) & 0xFF);
	    _spi.write((StartAddress>>8)  & 0xFF);
	    _spi.write( StartAddress      & 0xFF);
	}else{
    // send 24-bit start address
        _spi.write((StartAddress>>16) & 0xFF);
        _spi.write((StartAddress>>8)  & 0xFF);
        _spi.write( StartAddress      & 0xFF);
	}

    // write data
    while(1) {
        if( !( ( (_spi.READ_STATUS()) &  (0x1ul << (QSPI_STATUS_TXFULL_Pos)) )>> (QSPI_STATUS_TXFULL_Pos)) ) {
            _spi.write( u8DataBuffer[i++]);
            if(i >= PAGE_SIZE_QSPI_NOR) break;
        }
    }

    // wait tx finish
    while(_spi.QSPI_IS_BUSY());

    // /CS: de-active
    _spi.QSPI_SET_SS_HIGH();

    //QSPI_ClearRxFIFO(QSPI_FLASH_PORT);}
    _spi.CLEAR_RXFIFO();
}

void QSPI_FLASH::QSPI_NOR_EnableQEBit(void) {
    uint8_t u8Status1=QSPI_NOR_ReadStatusReg1();
    uint8_t u8Status2=QSPI_NOR_ReadStatusReg2();
    u8Status2 |= 0x2;
    QSPI_NOR_WriteStatusReg(u8Status1, u8Status2);
	while(QSPI_NOR_IsBusy());
}

void QSPI_FLASH::QSPI_NOR_DisableQEBit(void) {
    uint8_t u8Status1=QSPI_NOR_ReadStatusReg1();
    uint8_t u8Status2=QSPI_NOR_ReadStatusReg2();
    u8Status2 &= ~0x2;
    QSPI_NOR_WriteStatusReg(u8Status1, u8Status2);
	while(QSPI_NOR_IsBusy());
}

uint16_t QSPI_FLASH::QSPI_NOR_QuadFastRead(uint32_t StartAddress, uint8_t *u8DataBuffer, uint32_t mode_4B) {
    uint32_t i;
    
    // enable quad mode
    QSPI_NOR_EnableQEBit();
    
    // /CS: active
    _spi.QSPI_SET_SS_LOW();
    wait(0.1);
    
    // Command: 0xEB, Fast Read quad data
    _spi.write(CMD_FAST_READ_QUAD_IO);
    
    //while(QSPI_IS_BUSY(QSPI_FLASH_PORT));
    while(_spi.QSPI_IS_BUSY());

    // enable QSPI quad IO mode and set direction to input
    QSPI_D2D3_SwitchToQuadMode();

    //QSPI_ENABLE_QUAD_OUTPUT_MODE(QSPI_FLASH_PORT);
    _spi.ENABLE_QUAD_OUTPUT_MODE();

    if(mode_4B==1) {
        // send 24-bit start address
        _spi.write((StartAddress>>24) & 0xFF);       // A31-A24
        _spi.write((StartAddress>>16) & 0xFF);       // A23-A16
        _spi.write((StartAddress>>8)  & 0xFF);       // A15-A08
        _spi.write( StartAddress      & 0xFF);       // A07-A00
        // dummy byte
        _spi.write(0xFF); //<<<<<<<<<<<<<<<<<<<<<<<<
        _spi.write(0xFF); 
        _spi.write(0xFF); 
    } else {  //3-Byte Address Mode
        // send 24-bit start address
        _spi.write((StartAddress>>16) & 0xFF);       // A23-A16
        _spi.write((StartAddress>>8)  & 0xFF);       // A15-A08
        _spi.write( StartAddress      & 0xFF);       // A07-A00
        // dummy byte
        _spi.write(0xFF); 
        _spi.write(0xFF); 
        _spi.write(0xFF); 
    }

    //#define QSPI_IS_BUSY(qspi)   ( ((qspi)->STATUS & QSPI_STATUS_BUSY_Msk)>>QSPI_STATUS_BUSY_Pos )
    while( _spi.QSPI_IS_BUSY());

    _spi.ENABLE_QUAD_INPUT_MODE();
    
    // clear RX buffer
    _spi.CLEAR_RXFIFO();
    
    for(i=0; i<PAGE_SIZE_QSPI_NOR; i++) {
        u8DataBuffer[i] = _spi.write(0x00);
    }

    // wait tx finish
    while( _spi.QSPI_IS_BUSY());

    // /CS: de-active
    _spi.QSPI_SET_SS_HIGH();
    _spi.DISABLE_QUAD_MODE();
    
    QSPI_D2D3_SwitchToNormalMode();
    wait(0.1);

    QSPI_NOR_DisableQEBit();
    wait(0.1);
    return i;
}

uint8_t QSPI_FLASH::QSPI_NOR_ReadStatusReg1() {
    uint8_t rc;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_STATUS_REG);
    rc = _spi.write(0xFF);
    _spi.QSPI_SET_SS_HIGH();
    return rc;
}

uint8_t QSPI_FLASH::QSPI_NOR_ReadStatusReg2() {
    uint8_t rc;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_NOR_READ_STATUS_REG2);
    rc = _spi.write(0xFF);
    _spi.QSPI_SET_SS_HIGH();
    return rc;
}

uint8_t QSPI_FLASH::QSPI_NOR_ReadStatusReg3() {
    uint8_t rc;
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_NOR_READ_STATUS_REG3);
    rc = _spi.write(0xFF);
    _spi.QSPI_SET_SS_HIGH();
    return rc;
}

void QSPI_FLASH::QSPI_NOR_WriteStatusReg(uint8_t rc1, uint8_t rc2) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_WRITE_ENABLE);
    while( _spi.QSPI_IS_BUSY());
    _spi.QSPI_SET_SS_HIGH();

    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_WRITE_STATUS_REG1);
    _spi.write(rc1);
    _spi.write(rc2);

    while( _spi.QSPI_IS_BUSY());
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_NOR_ReadJEDECID(uint8_t* d) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ_JEDEC_ID);
    for (uint8_t i=0; i<3; i++) {
        d[i] = _spi.write(0x00);
    }
    _spi.QSPI_SET_SS_HIGH();
}

uint16_t QSPI_FLASH::QSPI_NOR_Read(uint32_t addr, uint8_t *buf, uint32_t mode_4B) { 
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_READ);
    if(mode_4B==1) {
      _spi.write(addr>>24);       // A31-A24
      _spi.write(addr>>16);       // A23-A16
      _spi.write(addr>>8);        // A15-A08
      _spi.write(addr & 0xFF);    // A07-A00
    } else {
      _spi.write(addr>>16);       // A23-A16
      _spi.write(addr>>8);        // A15-A08
      _spi.write(addr & 0xFF);    // A07-A00
    }

    uint16_t i;
    for(i=0; i<PAGE_SIZE_QSPI_NOR; i++) {
        buf[i] = _spi.write(0x00);
    }

    _spi.QSPI_SET_SS_HIGH();
    wait(0.1);
    return i;
}

void QSPI_FLASH::QSPI_NOR_Sector_Erase(uint32_t addr,uint32_t mode_4B) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_SECTOR_ERASE);
	if(mode_4B==1) {
	    _spi.write(addr>>24);       // A32-A24
	    _spi.write(addr>>16);       // A23-A16
	    _spi.write(addr>>8);        // A15-A08
	    _spi.write(addr & 0xFF);    // A07-A00
	} else {
	    _spi.write(addr>>16);       // A23-A16
	    _spi.write(addr>>8);        // A15-A08
	    _spi.write(addr & 0xFF);    // A07-A00
	}
    _spi.QSPI_SET_SS_HIGH();
	while(QSPI_NOR_IsBusy());
}

void QSPI_FLASH::QSPI_NOR_Block_Erase(uint32_t addr) {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_BLOCK_ERASE);
    _spi.write(addr>>16);       // A23-A16
    _spi.write(addr>>8);        // A15-A08
    _spi.write(addr & 0xFF);    // A07-A00
    _spi.QSPI_SET_SS_HIGH();
	while(QSPI_NOR_IsBusy());
}

void QSPI_FLASH::QSPI_NOR_QuadInputPageProgram(uint32_t StartAddress, uint8_t *u8DataBuffer, uint32_t mode_4B) {
    uint32_t i = 0;

    // enable quad mode
    QSPI_NOR_EnableQEBit();

    // /CS: active
    _spi.QSPI_SET_SS_LOW();

    // send Command: 0x06, Write enable
    _spi.write(CMD_WRITE_ENABLE);

    // wait tx finish
    while(_spi.QSPI_IS_BUSY());

    // /CS: de-active
    _spi.QSPI_SET_SS_HIGH();

    // /CS: active
    _spi.QSPI_SET_SS_LOW();

    // send Command: 0x32, Quad Input Page program
    _spi.write(CMD_QUAD_PAGE_PROGRAM);

	if(mode_4B==1) {
	    // send 32-bit start address
	    _spi.write((StartAddress>>24) & 0xFF);
	    _spi.write((StartAddress>>16) & 0xFF);
	    _spi.write((StartAddress>>8)  & 0xFF);
	    _spi.write( StartAddress      & 0xFF);
    } else {
	    // send 24-bit start address
	    _spi.write((StartAddress>>16) & 0xFF);
	    _spi.write((StartAddress>>8)  & 0xFF);
	    _spi.write( StartAddress      & 0xFF);
	}

    // enable QSPI quad IO mode and set direction to output
    QSPI_D2D3_SwitchToQuadMode();   //PORT C mfc setting
    _spi.ENABLE_QUAD_OUTPUT_MODE();

    // write data
    while(1) {
        if( !(_spi.GET_TX_FIFO_FULL_FLAG()) ) {
            _spi.write( u8DataBuffer[i++]);
            if(i >= PAGE_SIZE_QSPI_NOR) break;
        }
    }

     // /CS: de-active
    _spi.QSPI_SET_SS_HIGH();
    _spi.DISABLE_QUAD_MODE();

    //wait flash busy
	while(QSPI_NOR_IsBusy());

    // wait tx finish
    while(_spi.QSPI_IS_BUSY());

    _spi.CLEAR_RXFIFO(); 
    QSPI_D2D3_SwitchToNormalMode();
    wait(0.1);

    // disable quad mode
    QSPI_NOR_DisableQEBit();

    wait(0.1);
}

void QSPI_FLASH::QSPI_NOR_DeviceReset() {
	while(QSPI_NOR_IsBusy());

    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_NOR_ENABLE_RESET);
    _spi.QSPI_SET_SS_HIGH();

    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_NOR_RESET_DEVICE);
    _spi.QSPI_SET_SS_HIGH();
    wait_us(50); //more than 30us
}

void QSPI_FLASH::QSPI_NOR_Enter_4B_Address_Mode(){
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_Enter_4B_Address_Mode);
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_NOR_Exit_4B_Address_Mode(){
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_Exit_4B_Address_Mode);
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_STACK_Die_Select_NOR() {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_DIE_SELECT);
    _spi.write(0x00);             //DIE #0 NOR
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_STACK_Die_Select_NAND() {
    _spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_DIE_SELECT);
    _spi.write(0x01);             //DIE #1 NAND
    _spi.QSPI_SET_SS_HIGH();
}

void QSPI_FLASH::QSPI_W74M_WriteRootKey  (uint8_t cntaddr, uint8_t *rootkey, uint8_t *sign) {
    uint8_t i;
	_spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_W74M);
    _spi.write(CMD_W74M_WRITE_ROOTKEY);
    _spi.write(cntaddr);
    _spi.write(0x00);    //dummy

    for(i=0; i<32; i++) {
        _spi.write(rootkey[i]);
    }

    for(i=0; i<28; i++) {
        _spi.write(sign[i]);
    }

    _spi.QSPI_SET_SS_HIGH();
    wait(0.1);
}

void QSPI_FLASH::QSPI_W74M_UpdateHMACKey (uint8_t cntaddr, uint8_t *seed,    uint8_t *sign) {
    uint8_t i;
	_spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_W74M);
    _spi.write(CMD_W74M_UPDATE_HMACKEY);
    _spi.write(cntaddr);
    _spi.write(0x00);    //dummy

    for(i=0; i<4; i++) {
        _spi.write(seed[i]);
    }

    for(i=0; i<32; i++) {
        _spi.write(sign[i]);
    }

    _spi.QSPI_SET_SS_HIGH();
    wait(0.1);
}

void QSPI_FLASH::QSPI_W74M_IncrementMC(uint8_t cntaddr, uint8_t *cntdata, uint8_t *sign) {
    uint8_t i;
	_spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_W74M);
    _spi.write(CMD_W74M_INC_MONOCOUNTER);
    _spi.write(cntaddr);
    _spi.write(0x00);    //dummy

    for(i=0; i<4; i++) {
        _spi.write(cntdata[i]);
    }

    for(i=0; i<32; i++) {
        _spi.write(sign[i]);
    }

    _spi.QSPI_SET_SS_HIGH();
    wait(0.1);
}

void QSPI_FLASH::QSPI_W74M_RequestMC(uint8_t cntaddr, uint8_t *tag,     uint8_t *sign) {
    uint8_t i;
	_spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_W74M);
    _spi.write(CMD_W74M_REQ_MONOCOUNTER);
    _spi.write(cntaddr);
    _spi.write(0x00);    //dummy

    for(i=0; i<12; i++) {
        _spi.write(tag[i]);
    }

    for(i=0; i<32; i++) {
        _spi.write(sign[i]);
    }

    _spi.QSPI_SET_SS_HIGH();
    wait(0.1);
}
uint8_t QSPI_FLASH::QSPI_W74M_StatusRead(uint8_t *tag, uint8_t *cntdata, uint8_t *sign) {
    uint8_t i,mc;
	_spi.QSPI_SET_SS_LOW();
    _spi.write(CMD_W74M_STATUS_READ);
    _spi.write(0x00);  //dummy

	mc=_spi.write(0x00);

    for(i=0; i<(12); i++) {
        tag[i]=_spi.write(0x00);
    }

    for(i=0; i<(4); i++) {
        cntdata[i]=_spi.write(0x00);
    }

    for(i=0; i<(32); i++) {
        sign[i]=_spi.write(0x00);
    }

    _spi.QSPI_SET_SS_HIGH();
    return(mc);
}
