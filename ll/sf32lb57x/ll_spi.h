/*
 * SPDX-FileCopyrightText: 2026 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LL_SPI_H
#define __LL_SPI_H

#include <stdint.h>
#include "spi.h"
#include "cmsis_utils.h"





#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file ll_spi.h
 * @brief Header-only low-level SPI APIs for SF32LB52x.
 */

/** @defgroup LL_SPI_PROTOCOL LL SPI Protocol Format */
/** @{ */
#define LL_SPI_PROTOCOL_SPI (0x0UL << SPI_TOP_CTRL_FRF_Pos)
#define LL_SPI_PROTOCOL_TI_SSP (0x1UL << SPI_TOP_CTRL_FRF_Pos)
#define LL_SPI_PROTOCOL_MICROWIRE (0x2UL << SPI_TOP_CTRL_FRF_Pos)
/** @} */

/** @defgroup LL_SPI_CPOL LL SPI Clock Polarity */
/** @{ */
#define LL_SPI_CPOL_LOW 0x00000000U
#define LL_SPI_CPOL_HIGH SPI_TOP_CTRL_SPO
/** @} */

/** @defgroup LL_SPI_CPHA LL SPI Clock Phase */
/** @{ */
#define LL_SPI_CPHA_1EDGE 0x00000000U
#define LL_SPI_CPHA_2EDGE SPI_TOP_CTRL_SPH
/** @} */

/** @defgroup LL_SPI_ROLE LL SPI Frame/Clock Role */
/** @{ */
#define LL_SPI_FRAME_MASTER 0x00000000U
#define LL_SPI_FRAME_SLAVE SPI_TOP_CTRL_SFRMDIR
#define LL_SPI_CLOCK_MASTER 0x00000000U
#define LL_SPI_CLOCK_SLAVE SPI_TOP_CTRL_SCLKDIR
/** @} */

/** @defgroup LL_SPI_DATAWIDTH LL SPI Data Width */
/** @{ */
#define LL_SPI_DATAWIDTH_8BIT (7UL << SPI_TOP_CTRL_DSS_Pos)
#define LL_SPI_DATAWIDTH_16BIT (15UL << SPI_TOP_CTRL_DSS_Pos)
#define LL_SPI_DATAWIDTH_24BIT (23UL << SPI_TOP_CTRL_DSS_Pos)
#define LL_SPI_DATAWIDTH_32BIT (31UL << SPI_TOP_CTRL_DSS_Pos)
/** @} */

/** @defgroup LL_SPI_CLOCKSRC LL SPI Clock Source */
/** @{ */
#define LL_SPI_CLOCKSRC_DIV 0x00000000U
/** @} */

/** @defgroup LL_SPI_ENDIAN LL SPI FIFO Endian */
/** @{ */
#define LL_SPI_TX_ENDIAN_MODE0 (0x0UL << SPI_FIFO_CTRL_TXFIFO_WR_ENDIAN_Pos)
#define LL_SPI_TX_ENDIAN_MODE1 (0x1UL << SPI_FIFO_CTRL_TXFIFO_WR_ENDIAN_Pos)
#define LL_SPI_TX_ENDIAN_MODE2 (0x2UL << SPI_FIFO_CTRL_TXFIFO_WR_ENDIAN_Pos)
#define LL_SPI_TX_ENDIAN_MODE3 (0x3UL << SPI_FIFO_CTRL_TXFIFO_WR_ENDIAN_Pos)

#define LL_SPI_RX_ENDIAN_MODE0 (0x0UL << SPI_FIFO_CTRL_RXFIFO_RD_ENDIAN_Pos)
#define LL_SPI_RX_ENDIAN_MODE1 (0x1UL << SPI_FIFO_CTRL_RXFIFO_RD_ENDIAN_Pos)
#define LL_SPI_RX_ENDIAN_MODE2 (0x2UL << SPI_FIFO_CTRL_RXFIFO_RD_ENDIAN_Pos)
#define LL_SPI_RX_ENDIAN_MODE3 (0x3UL << SPI_FIFO_CTRL_RXFIFO_RD_ENDIAN_Pos)
/** @} */

/**
 * @brief SPI protocol format configuration.
 */
typedef struct
{
    uint32_t protocol; /**< Protocol format, use @ref LL_SPI_PROTOCOL_SPI to
                          @ref LL_SPI_PROTOCOL_MICROWIRE. */
    uint32_t clock_polarity; /**< Clock polarity, use @ref LL_SPI_CPOL_LOW or
                                @ref LL_SPI_CPOL_HIGH. */
    uint32_t clock_phase;    /**< Clock phase, use @ref LL_SPI_CPHA_1EDGE or
                                @ref LL_SPI_CPHA_2EDGE. */
} ll_spi_protocol_config_t;

/**
 * @brief SPI role configuration.
 */
typedef struct
{
    uint32_t frame_dir; /**< Frame direction, use @ref LL_SPI_FRAME_MASTER or
                           @ref LL_SPI_FRAME_SLAVE. */
    uint32_t clock_dir; /**< Clock direction, use @ref LL_SPI_CLOCK_MASTER or
                           @ref LL_SPI_CLOCK_SLAVE. */
} ll_spi_role_config_t;

/**
 * @brief SPI frame behavior configuration.
 */
typedef struct
{
    uint32_t data_width; /**< Data width field value, use @ref
                            LL_SPI_DATAWIDTH_8BIT to @ref LL_SPI_DATAWIDTH_32BIT
                            or encoded DSS value. */
    uint32_t
        invert_frame;   /**< Frame inversion control, 0 or SPI_TOP_CTRL_IFS. */
    uint32_t trail_dma; /**< Trailing DMA control, 0 or SPI_TOP_CTRL_TRAIL. */
    uint32_t tte;       /**< TXD tristate control, 0 or SPI_TOP_CTRL_TTE. */
    uint32_t ttelp;     /**< TXD tristate timing, 0 or SPI_TOP_CTRL_TTELP. */
} ll_spi_frame_config_t;

/**
 * @brief SPI FIFO behavior configuration.
 */
typedef struct
{
    uint32_t tx_threshold; /**< TX threshold field value for TFT. */
    uint32_t rx_threshold; /**< RX threshold field value for RFT. */
    uint32_t
        tx_endian; /**< TX FIFO write endian, use @ref
                      LL_SPI_TX_ENDIAN_MODE0 to @ref LL_SPI_TX_ENDIAN_MODE3. */
    uint32_t
        rx_endian; /**< RX FIFO read endian, use @ref
                      LL_SPI_RX_ENDIAN_MODE0 to @ref LL_SPI_RX_ENDIAN_MODE3. */
    uint32_t
        packing_enable; /**< FIFO packing control, 0 or SPI_FIFO_CTRL_FPCKE. */
} ll_spi_fifo_config_t;

/**
 * @brief SPI clock path configuration.
 */
typedef struct
{
    uint32_t clk_div; /**< Clock divider field value for CLK_DIV. */
    uint32_t clk_sel; /**< Clock source, use @ref LL_SPI_CLOCKSRC_DIV or
                         @ref LL_SPI_CLOCKSRC_SYS. */
} ll_spi_clock_config_t;

/**
 * @brief Enable or disable dynamic SSP work-width changes (TOP_CTRL.SSP_WORK_WIDTH_DYN_CHANGE).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] en   Non-zero to enable dynamic width changes.
 */
static inline void ll_spi_set_dynamic_work_width(SPI_TypeDef *SPIx, uint32_t en)
{
    MODIFY_REG(SPIx->TOP_CTRL, SPI_TOP_CTRL_SSP_WORK_WIDTH_DYN_CHANGE,
               en ? SPI_TOP_CTRL_SSP_WORK_WIDTH_DYN_CHANGE : 0UL);
}

/**
 * @brief Set three-wire direction to TX (TOP_CTRL.TXD_OEN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_set_three_wire_tx(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_TXD_OEN);
}

/**
 * @brief Set three-wire direction to RX (TOP_CTRL.TXD_OEN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_set_three_wire_rx(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_TXD_OEN);
}

/**
 * @brief Enable three-wire half-duplex mode (TOP_CTRL.SPI_TRI_WIRE_EN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_three_wire(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_SPI_TRI_WIRE_EN);
}

/**
 * @brief Disable three-wire half-duplex mode (TOP_CTRL.SPI_TRI_WIRE_EN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_three_wire(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_SPI_TRI_WIRE_EN);
}

/**
 * @brief Select SPI_DI pin as data input source (TOP_CTRL.SPI_DI_SEL).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_select_data_input_from_spi_di(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_SPI_DI_SEL);
}

/**
 * @brief Select SPI_DIO pin as data input source (TOP_CTRL.SPI_DI_SEL).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_select_data_input_from_spi_dio(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_SPI_DI_SEL);
}

/**
 * @brief Configure SPI clock divider/source and enable SPI clock path.
 * @param[in] SPIx SPI instance pointer.
 * @param[in] cfg Pointer to clock configuration.
 */
static inline void ll_spi_config_clock(SPI_TypeDef *SPIx,
                                       const ll_spi_clock_config_t *cfg)
{
    MODIFY_REG(SPIx->TOP_CTRL,
               SPI_TOP_CTRL_CLK_DIV | SPI_TOP_CTRL_CLK_SEL |
                   SPI_TOP_CTRL_CLK_SSP_EN,
               ((cfg->clk_div << SPI_TOP_CTRL_CLK_DIV_Pos) &
                SPI_TOP_CTRL_CLK_DIV_Msk) |
                   cfg->clk_sel | SPI_TOP_CTRL_CLK_SSP_EN);
}

/**
 * @brief Enable the SPI clock path (TOP_CTRL.CLK_SSP_EN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_clock(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_CLK_SSP_EN);
}

/**
 * @brief Disable the SPI clock path (TOP_CTRL.CLK_SSP_EN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_clock(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_CLK_SSP_EN);
}

/**
 * @brief Set the SPI clock source (TOP_CTRL.CLK_SEL).
 * @param[in] SPIx   SPI instance pointer.
 * @param[in] sel    Clock source, use @ref LL_SPI_CLOCKSRC_DIV or
 *                   @ref LL_SPI_CLOCKSRC_SYS.
 */
static inline void ll_spi_set_clock_source(SPI_TypeDef *SPIx, uint32_t sel)
{
    MODIFY_REG(SPIx->TOP_CTRL, SPI_TOP_CTRL_CLK_SEL,
               sel ? SPI_TOP_CTRL_CLK_SEL : 0UL);
}

/**
 * @brief Set the SPI clock divider (TOP_CTRL.CLK_DIV).
 * @param[in] SPIx   SPI instance pointer.
 * @param[in] div    Clock divider field value.
 */
static inline void ll_spi_set_clock_divider(SPI_TypeDef *SPIx, uint32_t div)
{
    MODIFY_REG(SPIx->TOP_CTRL, SPI_TOP_CTRL_CLK_DIV,
               MAKE_REG_VAL(div, SPI_TOP_CTRL_CLK_DIV_Msk, SPI_TOP_CTRL_CLK_DIV_Pos));
}

/**
 * @brief Configure SPI frame width and frame behavior fields.
 * @param[in] SPIx SPI instance pointer.
 * @param[in] cfg Pointer to frame configuration.
 */
static inline void ll_spi_config_frame(SPI_TypeDef *SPIx,
                                       const ll_spi_frame_config_t *cfg)
{
    MODIFY_REG(SPIx->TOP_CTRL,
               SPI_TOP_CTRL_DSS | SPI_TOP_CTRL_IFS | SPI_TOP_CTRL_TRAIL |
                   SPI_TOP_CTRL_TTE | SPI_TOP_CTRL_TTELP,
               cfg->data_width | cfg->invert_frame | cfg->trail_dma | cfg->tte |
                   cfg->ttelp);
}

/**
 * @brief Enable or disable free-running slave clock (TOP_CTRL.SCFR).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] en   Non-zero to enable free-running clock.
 */
static inline void ll_spi_set_slave_clock_free_running(SPI_TypeDef *SPIx,
                                                       uint32_t en)
{
    MODIFY_REG(SPIx->TOP_CTRL, SPI_TOP_CTRL_SCFR,
               en ? SPI_TOP_CTRL_SCFR : 0UL);
}

/**
 * @brief Enable hold-frame-low mode.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_hold_frame_low(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_HOLD_FRAME_LOW);
}

/**
 * @brief Disable hold-frame-low mode.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_hold_frame_low(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_HOLD_FRAME_LOW);
}

/**
 * @brief Enable or disable SPI loopback mode (TOP_CTRL.LBM).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] en   Non-zero to enable loopback.
 */
static inline void ll_spi_set_loopback(SPI_TypeDef *SPIx, uint32_t en)
{
    MODIFY_REG(SPIx->TOP_CTRL, SPI_TOP_CTRL_LBM,
               en ? SPI_TOP_CTRL_LBM : 0UL);
}

/**
 * @brief Configure SPI protocol and clock mode fields.
 * @param[in] SPIx SPI instance pointer.
 * @param[in] cfg Pointer to protocol configuration.
 */
static inline void ll_spi_config_protocol(SPI_TypeDef *SPIx,
                                          const ll_spi_protocol_config_t *cfg)
{
    MODIFY_REG(SPIx->TOP_CTRL,
               SPI_TOP_CTRL_FRF | SPI_TOP_CTRL_SPO | SPI_TOP_CTRL_SPH,
               cfg->protocol | cfg->clock_polarity | cfg->clock_phase);
}

/**
 * @brief Configure SPI frame and clock role fields.
 * @param[in] SPIx SPI instance pointer.
 * @param[in] cfg Pointer to role configuration.
 */
static inline void ll_spi_config_role(SPI_TypeDef *SPIx,
                                      const ll_spi_role_config_t *cfg)
{
    MODIFY_REG(SPIx->TOP_CTRL, SPI_TOP_CTRL_SFRMDIR | SPI_TOP_CTRL_SCLKDIR,
               cfg->frame_dir | cfg->clock_dir);
}

/**
 * @brief Enable SPI peripheral.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_SSE);
}

/**
 * @brief Disable SPI peripheral.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_SSE);
}

/**
 * @brief Check whether SPI peripheral is enabled.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when enabled.
 */
static inline uint32_t ll_spi_is_enabled(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->TOP_CTRL, SPI_TOP_CTRL_SSE);
}

/**
 * @brief Configure FIFO test selection and RX auto-full control.
 * @param[in] SPIx       SPI instance pointer.
 * @param[in] select_rx  Non-zero selects RX FIFO for test access.
 * @param[in] enable_rw  Non-zero enables FIFO test read/write access.
 * @param[in] auto_full  Non-zero enables RX FIFO auto-full control.
 */
static inline void ll_spi_set_fifo_test_control(SPI_TypeDef *SPIx,
                                                uint32_t select_rx,
                                                uint32_t enable_rw,
                                                uint32_t auto_full)
{
    MODIFY_REG(SPIx->FIFO_CTRL,
               SPI_FIFO_CTRL_STRF | SPI_FIFO_CTRL_EFWR |
                   SPI_FIFO_CTRL_RXFIFO_AUTO_FULL_CTRL,
               (select_rx ? SPI_FIFO_CTRL_STRF : 0UL) |
                   (enable_rw ? SPI_FIFO_CTRL_EFWR : 0UL) |
                   (auto_full ? SPI_FIFO_CTRL_RXFIFO_AUTO_FULL_CTRL : 0UL));
}

/**
 * @brief Configure SPI FIFO threshold, packing and endian fields.
 * @param[in] SPIx SPI instance pointer.
 * @param[in] cfg Pointer to FIFO configuration.
 */
static inline void ll_spi_config_fifo(SPI_TypeDef *SPIx,
                                      const ll_spi_fifo_config_t *cfg)
{
    MODIFY_REG(
        SPIx->FIFO_CTRL,
        SPI_FIFO_CTRL_TFT | SPI_FIFO_CTRL_RFT | SPI_FIFO_CTRL_TXFIFO_WR_ENDIAN |
            SPI_FIFO_CTRL_RXFIFO_RD_ENDIAN | SPI_FIFO_CTRL_FPCKE,
        ((cfg->tx_threshold << SPI_FIFO_CTRL_TFT_Pos) & SPI_FIFO_CTRL_TFT_Msk) |
            ((cfg->rx_threshold << SPI_FIFO_CTRL_RFT_Pos) &
             SPI_FIFO_CTRL_RFT_Msk) |
            cfg->tx_endian | cfg->rx_endian | cfg->packing_enable);
}

/**
 * @brief Enable RX DMA request.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_dma_rx(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->FIFO_CTRL, SPI_FIFO_CTRL_RSRE);
}

/**
 * @brief Disable RX DMA request.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_dma_rx(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->FIFO_CTRL, SPI_FIFO_CTRL_RSRE);
}

/**
 * @brief Check RX DMA request enable state.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when RX DMA request is enabled.
 */
static inline uint32_t ll_spi_is_enabled_dma_rx(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->FIFO_CTRL, SPI_FIFO_CTRL_RSRE);
}

/**
 * @brief Pulse the TX/RX FIFO reset bits (FIFO_CTRL.TSRE/RSRE set then clear).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_pulse_fifo_reset(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->FIFO_CTRL, SPI_FIFO_CTRL_TSRE | SPI_FIFO_CTRL_RSRE);
    CLEAR_BIT(SPIx->FIFO_CTRL, SPI_FIFO_CTRL_TSRE | SPI_FIFO_CTRL_RSRE);
}

/**
 * @brief Enable TX DMA request.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_dma_tx(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->FIFO_CTRL, SPI_FIFO_CTRL_TSRE);
}

/**
 * @brief Disable TX DMA request.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_dma_tx(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->FIFO_CTRL, SPI_FIFO_CTRL_TSRE);
}

/**
 * @brief Check TX DMA request enable state.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when TX DMA request is enabled.
 */
static inline uint32_t ll_spi_is_enabled_dma_tx(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->FIFO_CTRL, SPI_FIFO_CTRL_TSRE);
}

/**
 * @brief Enable the error/event interrupt (INTE.EBCEI).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_it_ebcei(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->INTE, SPI_INTE_EBCEI);
}

/**
 * @brief Disable the error/event interrupt (INTE.EBCEI = 0).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_it_ebcei(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->INTE, SPI_INTE_EBCEI);
}

/**
 * @brief Mask TX underrun interrupt source.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_mask_it_tx_underrun(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->INTE, SPI_INTE_TIM);
}

/**
 * @brief Unmask TX underrun interrupt source.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_unmask_it_tx_underrun(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->INTE, SPI_INTE_TIM);
}

/**
 * @brief Check TX underrun interrupt mask state.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when TX underrun interrupt is masked.
 */
static inline uint32_t ll_spi_is_masked_it_tx_underrun(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->INTE, SPI_INTE_TIM);
}

/**
 * @brief Mask RX overrun interrupt source.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_mask_it_rx_overrun(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->INTE, SPI_INTE_RIM);
}

/**
 * @brief Unmask RX overrun interrupt source.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_unmask_it_rx_overrun(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->INTE, SPI_INTE_RIM);
}

/**
 * @brief Check RX overrun interrupt mask state.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when RX overrun interrupt is masked.
 */
static inline uint32_t ll_spi_is_masked_it_rx_overrun(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->INTE, SPI_INTE_RIM);
}

/**
 * @brief Enable TX threshold interrupt.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_it_tx_threshold(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->INTE, SPI_INTE_TIE);
}

/**
 * @brief Disable TX threshold interrupt.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_it_tx_threshold(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->INTE, SPI_INTE_TIE);
}

/**
 * @brief Check TX threshold interrupt enable state.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when TX threshold interrupt is enabled.
 */
static inline uint32_t ll_spi_is_enabled_it_tx_threshold(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->INTE, SPI_INTE_TIE);
}

/**
 * @brief Enable RX threshold interrupt.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_it_rx_threshold(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->INTE, SPI_INTE_RIE);
}

/**
 * @brief Disable RX threshold interrupt.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_it_rx_threshold(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->INTE, SPI_INTE_RIE);
}

/**
 * @brief Check RX threshold interrupt enable state.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when RX threshold interrupt is enabled.
 */
static inline uint32_t ll_spi_is_enabled_it_rx_threshold(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->INTE, SPI_INTE_RIE);
}

/**
 * @brief Enable receiver timeout interrupt.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_it_timeout(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->INTE, SPI_INTE_TINTE);
}

/**
 * @brief Disable receiver timeout interrupt.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_it_timeout(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->INTE, SPI_INTE_TINTE);
}

/**
 * @brief Check receiver timeout interrupt enable state.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when timeout interrupt is enabled.
 */
static inline uint32_t ll_spi_is_enabled_it_timeout(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->INTE, SPI_INTE_TINTE);
}

/**
 * @brief Enable the pause interrupt (INTE.PINTE).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_it_pinte(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->INTE, SPI_INTE_PINTE);
}

/**
 * @brief Disable the pause interrupt (INTE.PINTE = 0).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_it_pinte(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->INTE, SPI_INTE_PINTE);
}

/**
 * @brief Configure receiver timeout threshold.
 * @param[in] SPIx SPI instance pointer.
 * @param[in] timeout Timeout field value.
 */
static inline void ll_spi_set_timeout(SPI_TypeDef *SPIx, uint32_t timeout)
{
    MODIFY_REG(SPIx->TO, SPI_TO_TIMEOUT,
               ((timeout << SPI_TO_TIMEOUT_Pos) & SPI_TO_TIMEOUT_Msk));
}

/**
 * @brief Read the aggregate STATUS register.
 * @param[in] SPIx SPI instance pointer.
 * @return STATUS register value.
 */
static inline uint32_t ll_spi_get_status(SPI_TypeDef *SPIx)
{
    return READ_REG(SPIx->STATUS);
}

/**
 * @brief Get RX odd sample status.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when OSS is set.
 */
static inline uint32_t ll_spi_get_rx_odd_sample_status(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_OSS);
}

/**
 * @brief Get TX odd sample status.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when TX_OSS is set.
 */
static inline uint32_t ll_spi_get_tx_odd_sample_status(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_TX_OSS);
}

/**
 * @brief Check the bit-count error flag (STATUS.BCE).
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when a bit-count error is pending.
 */
static inline uint32_t ll_spi_is_active_flag_bce(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_BCE);
}

/**
 * @brief Clear the bit-count error flag (STATUS.BCE).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_clear_flag_bce(SPI_TypeDef *SPIx)
{
    WRITE_REG(SPIx->STATUS, SPI_STATUS_BCE);
}

/**
 * @brief Check ROR flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when ROR is set.
 */
static inline uint32_t ll_spi_is_active_flag_ror(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_ROR);
}

/**
 * @brief Clear ROR flag by rw1c write.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_clear_flag_ror(SPI_TypeDef *SPIx)
{
    WRITE_REG(SPIx->STATUS, SPI_STATUS_ROR);
}

/**
 * @brief Get RX FIFO level.
 * @param[in] SPIx SPI instance pointer.
 * @return RX FIFO level field value.
 */
static inline uint32_t ll_spi_get_rx_fifo_level(SPI_TypeDef *SPIx)
{
    return ((READ_REG(SPIx->STATUS) & SPI_STATUS_RFL_Msk) >>
            SPI_STATUS_RFL_Pos);
}

/**
 * @brief Check RNE flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when RNE is set.
 */
static inline uint32_t ll_spi_is_active_flag_rne(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_RNE);
}

/**
 * @brief Check RFS flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when RFS is set.
 */
static inline uint32_t ll_spi_is_active_flag_rfs(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_RFS);
}

/**
 * @brief Check TUR flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when TUR is set.
 */
static inline uint32_t ll_spi_is_active_flag_tur(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_TUR);
}

/**
 * @brief Clear TUR flag by rw1c write.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_clear_flag_tur(SPI_TypeDef *SPIx)
{
    WRITE_REG(SPIx->STATUS, SPI_STATUS_TUR);
}

/**
 * @brief Get TX FIFO level.
 * @param[in] SPIx SPI instance pointer.
 * @return TX FIFO level field value.
 */
static inline uint32_t ll_spi_get_tx_fifo_level(SPI_TypeDef *SPIx)
{
    return ((READ_REG(SPIx->STATUS) & SPI_STATUS_TFL_Msk) >>
            SPI_STATUS_TFL_Pos);
}

/**
 * @brief Check TNF flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when TNF is set.
 */
static inline uint32_t ll_spi_is_active_flag_tnf(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_TNF);
}

/**
 * @brief Check TFS flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when TFS is set.
 */
static inline uint32_t ll_spi_is_active_flag_tfs(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_TFS);
}

/**
 * @brief Check the end-of-chain flag (STATUS.EOC).
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when an end-of-chain condition is pending.
 */
static inline uint32_t ll_spi_is_active_flag_eoc(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_EOC);
}

/**
 * @brief Clear the end-of-chain flag (STATUS.EOC).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_clear_flag_eoc(SPI_TypeDef *SPIx)
{
    WRITE_REG(SPIx->STATUS, SPI_STATUS_EOC);
}

/**
 * @brief Check TINT flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when TINT is set.
 */
static inline uint32_t ll_spi_is_active_flag_tint(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_TINT);
}

/**
 * @brief Clear TINT flag by rw1c write.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_clear_flag_tint(SPI_TypeDef *SPIx)
{
    WRITE_REG(SPIx->STATUS, SPI_STATUS_TINT);
}

/**
 * @brief Check the peripheral trailing-byte interrupt flag (STATUS.PINT).
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when the flag is pending.
 */
static inline uint32_t ll_spi_is_active_flag_pint(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_PINT);
}

/**
 * @brief Clear the peripheral trailing-byte interrupt flag (STATUS.PINT).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_clear_flag_pint(SPI_TypeDef *SPIx)
{
    WRITE_REG(SPIx->STATUS, SPI_STATUS_PINT);
}

/**
 * @brief Check CSS flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when CSS is set.
 */
static inline uint32_t ll_spi_is_active_flag_css(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_CSS);
}

/**
 * @brief Check BSY flag.
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when BSY is set.
 */
static inline uint32_t ll_spi_is_active_flag_busy(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATUS, SPI_STATUS_BSY);
}

/**
 * @brief Write one 32-bit item to TX FIFO data port.
 * @param[in] SPIx SPI instance pointer.
 * @param[in] data 32-bit data payload.
 */
static inline void ll_spi_transmit_data32(SPI_TypeDef *SPIx, uint32_t data)
{
    WRITE_REG(SPIx->DATA, data);
}

/**
 * @brief Read one 32-bit item from RX FIFO data port.
 * @param[in] SPIx SPI instance pointer.
 * @return 32-bit data payload.
 */
static inline uint32_t ll_spi_receive_data32(SPI_TypeDef *SPIx)
{
    return READ_REG(SPIx->DATA);
}

/**
 * @brief Write the frame header data (FRM_HDR_DATA.HDR_DATA).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] data 32-bit frame header data.
 */
static inline void ll_spi_set_frame_header_data(SPI_TypeDef *SPIx, uint32_t data)
{
    WRITE_REG(SPIx->FRM_HDR_DATA, data);
}

/**
 * @brief Set the RWOT capture condition count (TOP_CTRL2.SSPRWOTCCM).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] cnt   Capture condition count (16 bits).
 */
static inline void ll_spi_set_rwot_capture_condition_count(SPI_TypeDef *SPIx, uint32_t cnt)
{
    MODIFY_REG(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_SSPRWOTCCM,
               MAKE_REG_VAL(cnt, SPI_TOP_CTRL2_SSPRWOTCCM_Msk, SPI_TOP_CTRL2_SSPRWOTCCM_Pos));
}

/**
 * @brief Select GPIO clock input for SPI clock (TOP_CTRL2.SELECT_GPIO_CLKI).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_select_gpio_clki(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_SELECT_GPIO_CLKI);
}

/**
 * @brief Deselect GPIO clock input for SPI clock (TOP_CTRL2.SELECT_GPIO_CLKI).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_deselect_gpio_clki(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_SELECT_GPIO_CLKI);
}

/**
 * @brief Invert the RX clock (TOP_CTRL2.INV_RX_CLK).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] en   Non-zero to invert RX clock.
 */
static inline void ll_spi_set_rx_clock_inversion(SPI_TypeDef *SPIx, uint32_t en)
{
    MODIFY_REG(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_INV_RX_CLK,
               en ? SPI_TOP_CTRL2_INV_RX_CLK : 0UL);
}

/**
 * @brief Set the frame mode (TOP_CTRL2.FRM_MODE).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] mode Frame mode, 0 or SPI_TOP_CTRL2_FRM_MODE.
 */
static inline void ll_spi_set_frame_mode(SPI_TypeDef *SPIx, uint32_t mode)
{
    MODIFY_REG(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_FRM_MODE,
               mode ? SPI_TOP_CTRL2_FRM_MODE : 0UL);
}

/**
 * @brief Enable frame three-wire mode (TOP_CTRL2.FRM_TRI_WIRE_EN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_frame_three_wire(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_FRM_TRI_WIRE_EN);
}

/**
 * @brief Disable frame three-wire mode (TOP_CTRL2.FRM_TRI_WIRE_EN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_frame_three_wire(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_FRM_TRI_WIRE_EN);
}

/**
 * @brief Set the frame header length (TOP_CTRL2.FRM_HDR_LENGTH).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] len   Frame header length (5 bits).
 */
static inline void ll_spi_set_frame_header_length(SPI_TypeDef *SPIx, uint32_t len)
{
    MODIFY_REG(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_FRM_HDR_LENGTH,
               MAKE_REG_VAL(len, SPI_TOP_CTRL2_FRM_HDR_LENGTH_Msk, SPI_TOP_CTRL2_FRM_HDR_LENGTH_Pos));
}

/**
 * @brief Start frame transmission (TOP_CTRL2.FRM_START).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_start_frame(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_FRM_START);
}

/**
 * @brief Mask the last sample for RWOT capture (TOP_CTRL2.MASK_RWOT_LAST_SAMPLE).
 * @param[in] SPIx SPI instance pointer.
 * @param[in] en   Non-zero to mask last sample.
 */
static inline void ll_spi_set_rwot_last_sample_mask(SPI_TypeDef *SPIx, uint32_t en)
{
    MODIFY_REG(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_MASK_RWOT_LAST_SAMPLE,
               en ? SPI_TOP_CTRL2_MASK_RWOT_LAST_SAMPLE : 0UL);
}

/**
 * @brief Clear the RWOT cycle counter (TOP_CTRL2.CLR_RWOT_CYCLE).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_clear_rwot_cycle_counter(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_CLR_RWOT_CYCLE);
}

/**
 * @brief Set the RWOT cycle counter (TOP_CTRL2.SET_RWOT_CYCLE).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_set_rwot_cycle_counter(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_SET_RWOT_CYCLE);
}

/**
 * @brief Enable the RWOT cycle counter (TOP_CTRL2.CYCLE_RWOT_EN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_enable_rwot_cycle_counter(SPI_TypeDef *SPIx)
{
    SET_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_CYCLE_RWOT_EN);
}

/**
 * @brief Disable the RWOT cycle counter (TOP_CTRL2.CYCLE_RWOT_EN).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_disable_rwot_cycle_counter(SPI_TypeDef *SPIx)
{
    CLEAR_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_CYCLE_RWOT_EN);
}

/**
 * @brief Check whether the RWOT flag is set (TOP_CTRL2.RWOT).
 * @param[in] SPIx SPI instance pointer.
 * @return Non-zero when RWOT is set.
 */
static inline uint32_t ll_spi_is_active_flag_rwot(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_RWOT);
}

/**
 * @brief Clear the RWOT flag by rw1c write (TOP_CTRL2.RWOT).
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_clear_flag_rwot(SPI_TypeDef *SPIx)
{
    WRITE_REG(SPIx->TOP_CTRL2, SPI_TOP_CTRL2_RWOT);
}

/**
 * @brief Capture RWOT cycle counter sample.
 * @param[in] SPIx SPI instance pointer.
 */
static inline void ll_spi_capture_rwot_counter(SPI_TypeDef *SPIx)
{
    WRITE_REG(SPIx->RWOT_CVWRN, 1U);
}

/**
 * @brief Read captured RWOT cycle counter value.
 * @param[in] SPIx SPI instance pointer.
 * @return Captured RWOT cycle count.
 */
static inline uint32_t ll_spi_get_rwot_counter_capture(SPI_TypeDef *SPIx)
{
    return READ_REG(SPIx->RWOT_CVWRN);
}

#ifdef __cplusplus
}
#endif

#endif /* __LL_SPI_H */
