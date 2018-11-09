#include <mbed.h>
#ifndef __MBED_QUADSPI__
#define __MBED_QUADSPI__



#define QSPI_CTL_QSPIEN_Pos               (0)                                                /*!< QSPI_T::CTL: QSPIEN Position             */
#define QSPI_CTL_QSPIEN_Msk               (0x1ul << QSPI_CTL_QSPIEN_Pos)                     /*!< QSPI_T::CTL: QSPIEN Mask                 */

#define QSPI_CTL_RXNEG_Pos                (1)                                                /*!< QSPI_T::CTL: RXNEG Position             */
#define QSPI_CTL_RXNEG_Msk                (0x1ul << QSPI_CTL_RXNEG_Pos)                      /*!< QSPI_T::CTL: RXNEG Mask                 */

#define QSPI_CTL_TXNEG_Pos                (2)                                                /*!< QSPI_T::CTL: TXNEG Position             */
#define QSPI_CTL_TXNEG_Msk                (0x1ul << QSPI_CTL_TXNEG_Pos)                      /*!< QSPI_T::CTL: TXNEG Mask                 */

#define QSPI_CTL_CLKPOL_Pos               (3)                                                /*!< QSPI_T::CTL: CLKPOL Position            */
#define QSPI_CTL_CLKPOL_Msk               (0x1ul << QSPI_CTL_CLKPOL_Pos)                     /*!< QSPI_T::CTL: CLKPOL Mask                */

#define QSPI_CTL_SUSPITV_Pos              (4)                                                /*!< QSPI_T::CTL: SUSPITV Position           */
#define QSPI_CTL_SUSPITV_Msk              (0xful << QSPI_CTL_SUSPITV_Pos)                    /*!< QSPI_T::CTL: SUSPITV Mask               */

#define QSPI_CTL_DWIDTH_Pos               (8)                                                /*!< QSPI_T::CTL: DWIDTH Position            */
#define QSPI_CTL_DWIDTH_Msk               (0x1ful << QSPI_CTL_DWIDTH_Pos)                    /*!< QSPI_T::CTL: DWIDTH Mask                */

#define QSPI_CTL_LSB_Pos                  (13)                                               /*!< QSPI_T::CTL: LSB Position               */
#define QSPI_CTL_LSB_Msk                  (0x1ul << QSPI_CTL_LSB_Pos)                        /*!< QSPI_T::CTL: LSB Mask                   */

#define QSPI_CTL_HALFDPX_Pos              (14)                                               /*!< QSPI_T::CTL: HALFDPX Position           */
#define QSPI_CTL_HALFDPX_Msk              (0x1ul << QSPI_CTL_HALFDPX_Pos)                    /*!< QSPI_T::CTL: HALFDPX Mask               */

#define QSPI_CTL_RXONLY_Pos               (15)                                               /*!< QSPI_T::CTL: RXONLY Position            */
#define QSPI_CTL_RXONLY_Msk               (0x1ul << QSPI_CTL_RXONLY_Pos)                     /*!< QSPI_T::CTL: RXONLY Mask                */

#define QSPI_CTL_TWOBIT_Pos               (16)                                               /*!< QSPI_T::CTL: TWOBIT Position            */
#define QSPI_CTL_TWOBIT_Msk               (0x1ul << QSPI_CTL_TWOBIT_Pos)                     /*!< QSPI_T::CTL: TWOBIT Mask                */

#define QSPI_CTL_UNITIEN_Pos              (17)                                               /*!< QSPI_T::CTL: UNITIEN Position           */
#define QSPI_CTL_UNITIEN_Msk              (0x1ul << QSPI_CTL_UNITIEN_Pos)                    /*!< QSPI_T::CTL: UNITIEN Mask               */

#define QSPI_CTL_SLAVE_Pos                (18)                                               /*!< QSPI_T::CTL: SLAVE Position             */
#define QSPI_CTL_SLAVE_Msk                (0x1ul << QSPI_CTL_SLAVE_Pos)                      /*!< QSPI_T::CTL: SLAVE Mask                 */

#define QSPI_CTL_REORDER_Pos              (19)                                               /*!< QSPI_T::CTL: REORDER Position           */
#define QSPI_CTL_REORDER_Msk              (0x1ul << QSPI_CTL_REORDER_Pos)                    /*!< QSPI_T::CTL: REORDER Mask               */

#define QSPI_CTL_DATDIR_Pos               (20)                                               /*!< QSPI_T::CTL: DATDIR Position            */
#define QSPI_CTL_DATDIR_Msk               (0x1ul << QSPI_CTL_DATDIR_Pos)                     /*!< QSPI_T::CTL: DATDIR Mask                */

#define QSPI_CTL_DUALIOEN_Pos             (21)                                               /*!< QSPI_T::CTL: DUALIOEN Position          */
#define QSPI_CTL_DUALIOEN_Msk             (0x1ul << QSPI_CTL_DUALIOEN_Pos)                   /*!< QSPI_T::CTL: DUALIOEN Mask              */

#define QSPI_CTL_QUADIOEN_Pos             (22)                                               /*!< QSPI_T::CTL: QUADIOEN Position          */
#define QSPI_CTL_QUADIOEN_Msk             (0x1ul << QSPI_CTL_QUADIOEN_Pos)                   /*!< QSPI_T::CTL: QUADIOEN Mask              */

#define QSPI_CLKDIV_DIVIDER_Pos           (0)                                                /*!< QSPI_T::CLKDIV: DIVIDER Position        */
#define QSPI_CLKDIV_DIVIDER_Msk           (0x1fful << QSPI_CLKDIV_DIVIDER_Pos)               /*!< QSPI_T::CLKDIV: DIVIDER Mask            */

#define QSPI_SSCTL_SS_Pos                 (0)                                                /*!< QSPI_T::SSCTL: SS Position              */
#define QSPI_SSCTL_SS_Msk                 (0x1ul << QSPI_SSCTL_SS_Pos)                       /*!< QSPI_T::SSCTL: SS Mask                  */

#define QSPI_SSCTL_SSACTPOL_Pos           (2)                                                /*!< QSPI_T::SSCTL: SSACTPOL Position        */
#define QSPI_SSCTL_SSACTPOL_Msk           (0x1ul << QSPI_SSCTL_SSACTPOL_Pos)                 /*!< QSPI_T::SSCTL: SSACTPOL Mask            */

#define QSPI_SSCTL_AUTOSS_Pos             (3)                                                /*!< QSPI_T::SSCTL: AUTOSS Position          */
#define QSPI_SSCTL_AUTOSS_Msk             (0x1ul << QSPI_SSCTL_AUTOSS_Pos)                   /*!< QSPI_T::SSCTL: AUTOSS Mask              */

#define QSPI_SSCTL_SLV3WIRE_Pos           (4)                                                /*!< QSPI_T::SSCTL: SLV3WIRE Position        */
#define QSPI_SSCTL_SLV3WIRE_Msk           (0x1ul << QSPI_SSCTL_SLV3WIRE_Pos)                 /*!< QSPI_T::SSCTL: SLV3WIRE Mask            */

#define QSPI_SSCTL_SLVTOIEN_Pos           (5)                                                /*!< QSPI_T::SSCTL: SLVTOIEN Position        */
#define QSPI_SSCTL_SLVTOIEN_Msk           (0x1ul << QSPI_SSCTL_SLVTOIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVTOIEN Mask            */

#define QSPI_SSCTL_SLVTORST_Pos           (6)                                                /*!< QSPI_T::SSCTL: SLVTORST Position        */
#define QSPI_SSCTL_SLVTORST_Msk           (0x1ul << QSPI_SSCTL_SLVTORST_Pos)                 /*!< QSPI_T::SSCTL: SLVTORST Mask            */

#define QSPI_SSCTL_SLVBEIEN_Pos           (8)                                                /*!< QSPI_T::SSCTL: SLVBEIEN Position        */
#define QSPI_SSCTL_SLVBEIEN_Msk           (0x1ul << QSPI_SSCTL_SLVBEIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVBEIEN Mask            */

#define QSPI_SSCTL_SLVURIEN_Pos           (9)                                                /*!< QSPI_T::SSCTL: SLVURIEN Position        */
#define QSPI_SSCTL_SLVURIEN_Msk           (0x1ul << QSPI_SSCTL_SLVURIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVURIEN Mask            */

#define QSPI_SSCTL_SSACTIEN_Pos           (12)                                               /*!< QSPI_T::SSCTL: SSACTIEN Position        */
#define QSPI_SSCTL_SSACTIEN_Msk           (0x1ul << QSPI_SSCTL_SSACTIEN_Pos)                 /*!< QSPI_T::SSCTL: SSACTIEN Mask            */

#define QSPI_SSCTL_SSINAIEN_Pos           (13)                                               /*!< QSPI_T::SSCTL: SSINAIEN Position        */
#define QSPI_SSCTL_SSINAIEN_Msk           (0x1ul << QSPI_SSCTL_SSINAIEN_Pos)                 /*!< QSPI_T::SSCTL: SSINAIEN Mask            */

#define QSPI_SSCTL_SLVTOCNT_Pos           (16)                                               /*!< QSPI_T::SSCTL: SLVTOCNT Position        */
#define QSPI_SSCTL_SLVTOCNT_Msk           (0xfffful << QSPI_SSCTL_SLVTOCNT_Pos)              /*!< QSPI_T::SSCTL: SLVTOCNT Mask            */

#define QSPI_PDMACTL_TXPDMAEN_Pos         (0)                                                /*!< QSPI_T::PDMACTL: TXPDMAEN Position      */
#define QSPI_PDMACTL_TXPDMAEN_Msk         (0x1ul << QSPI_PDMACTL_TXPDMAEN_Pos)               /*!< QSPI_T::PDMACTL: TXPDMAEN Mask          */

#define QSPI_PDMACTL_RXPDMAEN_Pos         (1)                                                /*!< QSPI_T::PDMACTL: RXPDMAEN Position      */
#define QSPI_PDMACTL_RXPDMAEN_Msk         (0x1ul << QSPI_PDMACTL_RXPDMAEN_Pos)               /*!< QSPI_T::PDMACTL: RXPDMAEN Mask          */

#define QSPI_PDMACTL_PDMARST_Pos          (2)                                                /*!< QSPI_T::PDMACTL: PDMARST Position       */
#define QSPI_PDMACTL_PDMARST_Msk          (0x1ul << QSPI_PDMACTL_PDMARST_Pos)                /*!< QSPI_T::PDMACTL: PDMARST Mask           */

#define QSPI_FIFOCTL_RXRST_Pos            (0)                                                /*!< QSPI_T::FIFOCTL: RXRST Position         */
#define QSPI_FIFOCTL_RXRST_Msk            (0x1ul << QSPI_FIFOCTL_RXRST_Pos)                  /*!< QSPI_T::FIFOCTL: RXRST Mask             */

#define QSPI_FIFOCTL_TXRST_Pos            (1)                                                /*!< QSPI_T::FIFOCTL: TXRST Position         */
#define QSPI_FIFOCTL_TXRST_Msk            (0x1ul << QSPI_FIFOCTL_TXRST_Pos)                  /*!< QSPI_T::FIFOCTL: TXRST Mask             */

#define QSPI_FIFOCTL_RXTHIEN_Pos          (2)                                                /*!< QSPI_T::FIFOCTL: RXTHIEN Position       */
#define QSPI_FIFOCTL_RXTHIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXTHIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXTHIEN Mask           */

#define QSPI_FIFOCTL_TXTHIEN_Pos          (3)                                                /*!< QSPI_T::FIFOCTL: TXTHIEN Position       */
#define QSPI_FIFOCTL_TXTHIEN_Msk          (0x1ul << QSPI_FIFOCTL_TXTHIEN_Pos)                /*!< QSPI_T::FIFOCTL: TXTHIEN Mask           */

#define QSPI_FIFOCTL_RXTOIEN_Pos          (4)                                                /*!< QSPI_T::FIFOCTL: RXTOIEN Position       */
#define QSPI_FIFOCTL_RXTOIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXTOIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXTOIEN Mask           */

#define QSPI_FIFOCTL_RXOVIEN_Pos          (5)                                                /*!< QSPI_T::FIFOCTL: RXOVIEN Position       */
#define QSPI_FIFOCTL_RXOVIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXOVIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXOVIEN Mask           */

#define QSPI_FIFOCTL_TXUFPOL_Pos          (6)                                                /*!< QSPI_T::FIFOCTL: TXUFPOL Position       */
#define QSPI_FIFOCTL_TXUFPOL_Msk          (0x1ul << QSPI_FIFOCTL_TXUFPOL_Pos)                /*!< QSPI_T::FIFOCTL: TXUFPOL Mask           */

#define QSPI_FIFOCTL_TXUFIEN_Pos          (7)                                                /*!< QSPI_T::FIFOCTL: TXUFIEN Position       */
#define QSPI_FIFOCTL_TXUFIEN_Msk          (0x1ul << QSPI_FIFOCTL_TXUFIEN_Pos)                /*!< QSPI_T::FIFOCTL: TXUFIEN Mask           */

#define QSPI_FIFOCTL_RXFBCLR_Pos          (8)                                                /*!< QSPI_T::FIFOCTL: RXFBCLR Position       */
#define QSPI_FIFOCTL_RXFBCLR_Msk          (0x1ul << QSPI_FIFOCTL_RXFBCLR_Pos)                /*!< QSPI_T::FIFOCTL: RXFBCLR Mask           */

#define QSPI_FIFOCTL_TXFBCLR_Pos          (9)                                                /*!< QSPI_T::FIFOCTL: TXFBCLR Position       */
#define QSPI_FIFOCTL_TXFBCLR_Msk          (0x1ul << QSPI_FIFOCTL_TXFBCLR_Pos)                /*!< QSPI_T::FIFOCTL: TXFBCLR Mask           */

#define QSPI_FIFOCTL_RXTH_Pos             (24)                                               /*!< QSPI_T::FIFOCTL: RXTH Position          */
#define QSPI_FIFOCTL_RXTH_Msk             (0x7ul << QSPI_FIFOCTL_RXTH_Pos)                   /*!< QSPI_T::FIFOCTL: RXTH Mask              */

#define QSPI_FIFOCTL_TXTH_Pos             (28)                                               /*!< QSPI_T::FIFOCTL: TXTH Position          */
#define QSPI_FIFOCTL_TXTH_Msk             (0x7ul << QSPI_FIFOCTL_TXTH_Pos)                   /*!< QSPI_T::FIFOCTL: TXTH Mask              */

#define QSPI_STATUS_BUSY_Pos              (0)                                                /*!< QSPI_T::STATUS: BUSY Position           */
#define QSPI_STATUS_BUSY_Msk              (0x1ul << QSPI_STATUS_BUSY_Pos)                    /*!< QSPI_T::STATUS: BUSY Mask               */

#define QSPI_STATUS_UNITIF_Pos            (1)                                                /*!< QSPI_T::STATUS: UNITIF Position         */
#define QSPI_STATUS_UNITIF_Msk            (0x1ul << QSPI_STATUS_UNITIF_Pos)                  /*!< QSPI_T::STATUS: UNITIF Mask             */

#define QSPI_STATUS_SSACTIF_Pos           (2)                                                /*!< QSPI_T::STATUS: SSACTIF Position        */
#define QSPI_STATUS_SSACTIF_Msk           (0x1ul << QSPI_STATUS_SSACTIF_Pos)                 /*!< QSPI_T::STATUS: SSACTIF Mask            */

#define QSPI_STATUS_SSINAIF_Pos           (3)                                                /*!< QSPI_T::STATUS: SSINAIF Position        */
#define QSPI_STATUS_SSINAIF_Msk           (0x1ul << QSPI_STATUS_SSINAIF_Pos)                 /*!< QSPI_T::STATUS: SSINAIF Mask            */

#define QSPI_STATUS_SSLINE_Pos            (4)                                                /*!< QSPI_T::STATUS: SSLINE Position         */
#define QSPI_STATUS_SSLINE_Msk            (0x1ul << QSPI_STATUS_SSLINE_Pos)                  /*!< QSPI_T::STATUS: SSLINE Mask             */

#define QSPI_STATUS_SLVTOIF_Pos           (5)                                                /*!< QSPI_T::STATUS: SLVTOIF Position        */
#define QSPI_STATUS_SLVTOIF_Msk           (0x1ul << QSPI_STATUS_SLVTOIF_Pos)                 /*!< QSPI_T::STATUS: SLVTOIF Mask            */

#define QSPI_STATUS_SLVBEIF_Pos           (6)                                                /*!< QSPI_T::STATUS: SLVBEIF Position        */
#define QSPI_STATUS_SLVBEIF_Msk           (0x1ul << QSPI_STATUS_SLVBEIF_Pos)                 /*!< QSPI_T::STATUS: SLVBEIF Mask            */

#define QSPI_STATUS_SLVURIF_Pos           (7)                                                /*!< QSPI_T::STATUS: SLVURIF Position        */
#define QSPI_STATUS_SLVURIF_Msk           (0x1ul << QSPI_STATUS_SLVURIF_Pos)                 /*!< QSPI_T::STATUS: SLVURIF Mask            */

#define QSPI_STATUS_RXEMPTY_Pos           (8)                                                /*!< QSPI_T::STATUS: RXEMPTY Position        */
#define QSPI_STATUS_RXEMPTY_Msk           (0x1ul << QSPI_STATUS_RXEMPTY_Pos)                 /*!< QSPI_T::STATUS: RXEMPTY Mask            */

#define QSPI_STATUS_RXFULL_Pos            (9)                                                /*!< QSPI_T::STATUS: RXFULL Position         */
#define QSPI_STATUS_RXFULL_Msk            (0x1ul << QSPI_STATUS_RXFULL_Pos)                  /*!< QSPI_T::STATUS: RXFULL Mask             */

#define QSPI_STATUS_RXTHIF_Pos            (10)                                               /*!< QSPI_T::STATUS: RXTHIF Position         */
#define QSPI_STATUS_RXTHIF_Msk            (0x1ul << QSPI_STATUS_RXTHIF_Pos)                  /*!< QSPI_T::STATUS: RXTHIF Mask             */

#define QSPI_STATUS_RXOVIF_Pos            (11)                                               /*!< QSPI_T::STATUS: RXOVIF Position         */
#define QSPI_STATUS_RXOVIF_Msk            (0x1ul << QSPI_STATUS_RXOVIF_Pos)                  /*!< QSPI_T::STATUS: RXOVIF Mask             */

#define QSPI_STATUS_RXTOIF_Pos            (12)                                               /*!< QSPI_T::STATUS: RXTOIF Position         */
#define QSPI_STATUS_RXTOIF_Msk            (0x1ul << QSPI_STATUS_RXTOIF_Pos)                  /*!< QSPI_T::STATUS: RXTOIF Mask             */

#define QSPI_STATUS_QSPIENSTS_Pos          (15)                                              /*!< QSPI_T::STATUS: QSPIENSTS Position       */
#define QSPI_STATUS_QSPIENSTS_Msk          (0x1ul << QSPI_STATUS_QSPIENSTS_Pos)              /*!< QSPI_T::STATUS: QSPIENSTS Mask           */

#define QSPI_STATUS_TXEMPTY_Pos           (16)                                               /*!< QSPI_T::STATUS: TXEMPTY Position        */
#define QSPI_STATUS_TXEMPTY_Msk           (0x1ul << QSPI_STATUS_TXEMPTY_Pos)                 /*!< QSPI_T::STATUS: TXEMPTY Mask            */

#define QSPI_STATUS_TXFULL_Pos            (17)                                               /*!< QSPI_T::STATUS: TXFULL Position         */
#define QSPI_STATUS_TXFULL_Msk            (0x1ul << QSPI_STATUS_TXFULL_Pos)                  /*!< QSPI_T::STATUS: TXFULL Mask             */

#define QSPI_STATUS_TXTHIF_Pos            (18)                                               /*!< QSPI_T::STATUS: TXTHIF Position         */
#define QSPI_STATUS_TXTHIF_Msk            (0x1ul << QSPI_STATUS_TXTHIF_Pos)                  /*!< QSPI_T::STATUS: TXTHIF Mask             */

#define QSPI_STATUS_TXUFIF_Pos            (19)                                               /*!< QSPI_T::STATUS: TXUFIF Position         */
#define QSPI_STATUS_TXUFIF_Msk            (0x1ul << QSPI_STATUS_TXUFIF_Pos)                  /*!< QSPI_T::STATUS: TXUFIF Mask             */

#define QSPI_STATUS_TXRXRST_Pos           (23)                                               /*!< QSPI_T::STATUS: TXRXRST Position        */
#define QSPI_STATUS_TXRXRST_Msk           (0x1ul << QSPI_STATUS_TXRXRST_Pos)                 /*!< QSPI_T::STATUS: TXRXRST Mask            */

#define QSPI_STATUS_RXCNT_Pos             (24)                                               /*!< QSPI_T::STATUS: RXCNT Position          */
#define QSPI_STATUS_RXCNT_Msk             (0xful << QSPI_STATUS_RXCNT_Pos)                   /*!< QSPI_T::STATUS: RXCNT Mask              */

#define QSPI_STATUS_TXCNT_Pos             (28)                                               /*!< QSPI_T::STATUS: TXCNT Position          */
#define QSPI_STATUS_TXCNT_Msk             (0xful << QSPI_STATUS_TXCNT_Pos)                   /*!< QSPI_T::STATUS: TXCNT Mask              */

#define QSPI_TX_TX_Pos                    (0)                                                /*!< QSPI_T::TX: TX Position                 */
#define QSPI_TX_TX_Msk                    (0xfffffffful << QSPI_TX_TX_Pos)                   /*!< QSPI_T::TX: TX Mask                     */

#define QSPI_RX_RX_Pos                    (0)                                                /*!< QSPI_T::RX: RX Position                 */
#define QSPI_RX_RX_Msk                    (0xfffffffful << QSPI_RX_RX_Pos)                   /*!< QSPI_T::RX: RX Mask                     */




class QuadSPI: public SPI
{
public:
    QuadSPI(PinName mosi, PinName miso, PinName sclk, PinName cs=NC);
    virtual ~QuadSPI();	
    void SPIEN_ENABLE();
    void SPIEN_DISABLE();
    void CLEAR_RXFIFO();
    void ENABLE_QUAD_OUTPUT_MODE();
    void ENABLE_QUAD_INPUT_MODE(void);
    void DISABLE_QUAD_MODE(void);
    uint32_t READ_STATUS(void);
    uint32_t QSPI_IS_BUSY(void);          //qspi STATUS BUSY bit
    uint32_t GET_TX_FIFO_FULL_FLAG(void); //qspi STATUS TXFULL bit
    void QSPI_SET_SS_HIGH(void);
    void QSPI_SET_SS_LOW(void);
    void QSPI_WRITE_TX(uint32_t u32TxData);
    uint32_t QSPI_READ_RX();
    uint32_t QSPI_WRITE_READ(uint32_t u32TxData);
    void QSPI_ENABLE();
    void QSPI_DISABLE();

	SPI_T *spi_base ;

};

#endif

