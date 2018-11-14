#include <mbed.h>
#include "QuadSPI.h"

#define CMD_DIE_SELECT            0xC2

#define PAGE_SIZE_QSPI_NOR         256       //256    bytes
#define SECTOR_SIZE_QSPI_NOR      0x1000     //4096 =4kbytes
#define MAX_BYTES_QSPI_NOR        0x2000000  // 32Mbytes =256 Mbits
#define MAX_PAGES_QSPI_NOR        0x20000    // 32Mbytes/256bytes=131072
#define MAX_SECTORS_QSPI_NOR      0x2000     // 32Mbytes/4Kbytes=8192

#define PAGE_SIZE_QSPI_NAND       2048
#define SPARE_SIZE_QSPI_NAND        64
#define MAX_PAGES_QSPI_NAND       65536
#define MAX_BLOCKS_QSPI_NAND      1024

#define CMD_NAND_DEVICE_RESET     0xFF
#define CMD_READ_JEDEC_ID         0x9F
#define CMD_READ_STATUS_REG       0x05
#define CMD_WRITE_STATUS_REG      0x01
#define CMD_WRITE_ENABLE          0x06
#define CMD_WRITE_DISABLE         0x04

#define CMD_BB_MANAGEMENT         0xA1  // not implemented yet
#define CMD_READ_BBM_LUT          0xA5  // not implemented yet
#define CMD_LAST_ECC_FPA          0xA9  // not implemented yet
#define CMD_BLOCK_ERASE           0xD8
#define CMD_PGM_DATA_LOAD         0x02
#define CMD_RPGM_DATA_LOAD        0x84  // not implemented yet
#define CMD_QUAD_DATA_LOAD        0x32  
#define CMD_RQUAD_DATA_LOAD       0x34  // not implemented yet
#define CMD_PGM_EXECUTE           0x10
#define CMD_PAGE_DATA_READ        0x13
#define CMD_READ_DATA             0x03  //NAND
#define CMD_FAST_READ             0x0B
#define CMD_FAST_READ_4B          0x0C  // not implemented yet
#define CMD_FAST_READ_DUAL        0x3B  // not implemented yet
#define CMD_FAST_READ_DUAL_4B     0x3C  // not implemented yet
#define CMD_FAST_READ_QUAD        0x6B  // not implemented yet
#define CMD_FAST_READ_QUAD_4B     0x6C  // not implemented yet
#define CMD_FAST_READ_DUAL_IO     0xBB  // not implemented yet
#define CMD_FAST_READ_DUAL_IO_4B  0xBC  // not implemented yet
#define CMD_FAST_READ_QUAD_IO     0xEB  
#define CMD_FAST_READ_QUAD_IO_4B  0xEC  // not implemented yet
#define ADR_STATUS_REG_1          0xAF
#define ADR_STATUS_REG_2          0xBF
#define ADR_STATUS_REG_3          0xCF
#define SR3_BUSY_MASK             0x01

#define CMD_NOR_ENABLE_RESET      0x66 // NOR only 
#define CMD_NOR_RESET_DEVICE      0x99 // NOR only 

#define CMD_NOR_READ_STATUS_REG2   0x35 // NOR only 
#define CMD_NOR_READ_STATUS_REG3   0x15 // NOR only
#define CMD_READ_MANUFACTUREDEV_ID 0x90 // NOR only
#define CMD_WRITE_STATUS_REG1      0x01 // NOR
#define CMD_WRITE_STATUS_REG2      0x31 //no use
#define CMD_WRITE_STATUS_REG3      0x51 //no use
#define NOR_EWIP_MASK              0x01 //no use

#define CMD_READ                   0x03  //NOR
#define CMD_PAGE_PROGRAM           0x02
#define CMD_SECTOR_ERASE           0x20 //NOR only

#define CMD_READ_4B                0x13 //NOR only
#define CMD_PAGE_PROGRAM_4B        0x12 
#define CMD_SECTOR_ERASE_4B        0x21 
#define CMD_QUAD_PAGE_PROGRAM      0x32  
#define CMD_QUAD_PAGE_PROGRAM_4B   0x34  
#define CMD_Enter_4B_Address_Mode  0xB7
#define CMD_Exit_4B_Address_Mode   0xE9

#define CMD_W74M                   0x9B
#define CMD_W74M_WRITE_ROOTKEY     0x00
#define CMD_W74M_UPDATE_HMACKEY    0x01
#define CMD_W74M_INC_MONOCOUNTER   0x02
#define CMD_W74M_REQ_MONOCOUNTER   0x03
#define CMD_W74M_STATUS_READ       0x96


class QSPI_FLASH
{
public:
    // Create an SPI_NAND instance
    QSPI_FLASH(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName d2, PinName d3);

    // Destructor of SPI_NAND
    virtual ~QSPI_FLASH();
    void QSPI_FLASH_Begin();

    void QSPI_D2D3_SwitchToNormalMode();
    void QSPI_D2D3_SwitchToQuadMode();

    void QSPI_WriteEnable();
    void QSPI_WriteDisable();

    uint8_t QSPI_NAND_ReadStatusReg1();
    uint8_t QSPI_NAND_ReadStatusReg2();
    uint8_t QSPI_NAND_ReadStatusReg3();
    
    void QSPI_NAND_WriteStatusReg1(uint8_t rc);
    void QSPI_NAND_WriteStatusReg2(uint8_t rc);
    bool QSPI_NAND_IsBusy();
    void QSPI_NAND_ReadJEDECID(uint8_t* d);

    bool     QSPI_NAND_PageDataRead(uint16_t addr);
    uint16_t QSPI_NAND_ReadData(uint16_t addr, uint8_t *buf);
    void     QSPI_NAND_ReadData2(uint16_t addr, uint8_t *buf);
    void     QSPI_NAND_BlockErase(uint16_t addr);
    uint16_t QSPI_NAND_ProgramDataLoad(uint16_t addr, uint8_t *buf);
    bool     QSPI_NAND_ProgramExecute(uint16_t addr);

    uint16_t QSPI_NAND_QuadReadData(uint16_t addr, uint8_t *buf, uint8_t read_mode);
    uint16_t QSPI_NAND_QuadProgramDataLoad(uint16_t addr, uint8_t *buf);
    void     QSPI_NAND_ReadBBMLUT(uint8_t *d);
    void     QSPI_NAND_DeviceReset();


    uint16_t QSPI_NOR_SpiFlash_ReadMidDid(void);
    bool     QSPI_NOR_IsBusy();

    void     QSPI_NOR_PageProgram(uint32_t StartAddress, uint8_t *u8DataBuffer, uint32_t mode_4B);
    void     QSPI_NOR_EnableQEBit(void);
    void     QSPI_NOR_DisableQEBit(void);
    
    uint16_t QSPI_NOR_QuadFastRead(uint32_t StartAddress, uint8_t *u8DataBuffer, uint32_t mode_4B);
    void     QSPI_NOR_QuadInputPageProgram(uint32_t StartAddress, uint8_t *u8DataBuffer, uint32_t mode_4B);
    uint8_t  QSPI_NOR_ReadStatusReg1();
    uint8_t  QSPI_NOR_ReadStatusReg2();
    uint8_t  QSPI_NOR_ReadStatusReg3();

    void     QSPI_NOR_WriteStatusReg(uint8_t rc1,uint8_t rc2);
    void     QSPI_NOR_ReadJEDECID(uint8_t* d);
    uint16_t QSPI_NOR_Read(uint32_t addr, uint8_t *buf, uint32_t mode_4B);
    void     QSPI_NOR_Block_Erase(uint32_t addr);
    void     QSPI_NOR_Sector_Erase(uint32_t addr, uint32_t mode_4B);
    void     QSPI_NOR_DeviceReset();

    void     QSPI_NOR_Enter_4B_Address_Mode(void);
    void     QSPI_NOR_Exit_4B_Address_Mode(void);

    void     QSPI_STACK_Die_Select_NOR(void);
    void     QSPI_STACK_Die_Select_NAND(void);

    void     QSPI_W74M_WriteRootKey  (uint8_t cntaddr, uint8_t *rootkey, uint8_t *sign);
    void     QSPI_W74M_UpdateHMACKey (uint8_t cntaddr, uint8_t *seed,    uint8_t *sign);
    void     QSPI_W74M_IncrementMC   (uint8_t cntaddr, uint8_t *cntdata, uint8_t *sign);
    void     QSPI_W74M_RequestMC     (uint8_t cntaddr, uint8_t *tag,     uint8_t *sign);
    uint8_t  QSPI_W74M_StatusRead    (uint8_t *tag, uint8_t *cntdata, uint8_t *sign);

    private:
    QuadSPI _spi;

    DigitalInOut _d2;
    DigitalInOut _d3;
};
