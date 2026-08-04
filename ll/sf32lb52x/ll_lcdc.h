/*
 * SPDX-FileCopyrightText: 2026 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LL_LCDC_H
#define __LL_LCDC_H

#include <stdint.h>
#include "regs/lcd_if.h"
#include "cmsis_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file ll_lcdc.h
 * @brief Header-only low-level LCD Controller (LCDC) APIs for SF32LB52x.
 *
 * LCDC supports dual-layer blending, multiple display interfaces (8080/SPI/QSPI/
 * DPI/JDI), hardware rotation, and eZip decompression.
 */

/*==============================================================================
 * Interface Mode
 *============================================================================*/

/**
 * @defgroup LL_LCDC_IF_MODE Display Interface Mode (LCD_CONF.LCD_INTF_SEL[4:2])
 *
 * Encodings follow the reference manual 10-1 (LCD_CONF register). Note that
 * QSPI is not a separate LCD_INTF_SEL mode: SPI/DSPI/QSPI all use
 * @ref LL_LCDC_IF_MODE_SPI and differ only in the data-line count configured
 * in SPI_IF_CONF.
 */
/** @{ */
#define LL_LCDC_IF_MODE_8080         (0x0UL) /* 000: 8080 DBI TypeB */
#define LL_LCDC_IF_MODE_SPI          (0x1UL) /* 001: SPI (incl. DSPI/QSPI) */
#define LL_LCDC_IF_MODE_DSI          (0x2UL) /* 010: DBI to DSI */
#define LL_LCDC_IF_MODE_DPI          (0x3UL) /* 011: DPI */
#define LL_LCDC_IF_MODE_JDI_SERIAL   (0x4UL) /* 100: JDI serial */
#define LL_LCDC_IF_MODE_JDI_PARALLEL (0x5UL) /* 101: JDI parallel */
#define LL_LCDC_IF_MODE_8080_TYPEA   (0x6UL) /* 110: 8080 DBI TypeA */
#define LL_LCDC_IF_MODE_DPI_TO_DSI   (0x7UL) /* 111: DPI to DSI */
/** @} */

/*==============================================================================
 * Interface & Target Selection (LCD_CONF)
 *============================================================================*/

/** @defgroup LL_LCDC_TARGET_LCD Display Target (LCD_CONF.TARGET_LCD[1:0]) */
/** @{ */
#define LL_LCDC_TARGET_PANEL0  (0x0UL) /* 00: LCD panel 0 */
#define LL_LCDC_TARGET_PANEL1  (0x1UL) /* 01: LCD panel 1 */
#define LL_LCDC_TARGET_AHB_LCD (0x2UL) /* 10: AHB LCD */
#define LL_LCDC_TARGET_AHB_RAM (0x3UL) /* 11: AHB RAM */
/** @} */

/**
 * @brief Select the display interface (LCD_CONF.LCD_INTF_SEL[4:2]).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] mode Display interface mode, one of @ref LL_LCDC_IF_MODE.
 */
static inline void ll_lcdc_set_interface_mode(LCD_IF_TypeDef *lcd, uint32_t mode)
{
	MODIFY_REG(lcd->LCD_CONF, LCD_IF_LCD_CONF_LCD_INTF_SEL,
		   MAKE_REG_VAL(mode, LCD_IF_LCD_CONF_LCD_INTF_SEL_Msk,
				LCD_IF_LCD_CONF_LCD_INTF_SEL_Pos));
}

/**
 * @brief Get the current display interface mode (LCD_CONF.LCD_INTF_SEL[4:2]).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Display interface mode, one of @ref LL_LCDC_IF_MODE.
 */
static inline uint32_t ll_lcdc_get_interface_mode(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->LCD_CONF, LCD_IF_LCD_CONF_LCD_INTF_SEL);
}

/**
 * @brief Select the data destination (LCD_CONF.TARGET_LCD[1:0]).
 * @param[in] lcd    LCD_IF instance pointer.
 * @param[in] target Destination, one of @ref LL_LCDC_TARGET_LCD.
 */
static inline void ll_lcdc_set_target_lcd(LCD_IF_TypeDef *lcd, uint32_t target)
{
	MODIFY_REG(lcd->LCD_CONF, LCD_IF_LCD_CONF_TARGET_LCD,
		   MAKE_REG_VAL(target, LCD_IF_LCD_CONF_TARGET_LCD_Msk,
				LCD_IF_LCD_CONF_TARGET_LCD_Pos));
}

/*==============================================================================
 * Layer Format
 *============================================================================*/

/** @defgroup LL_LCDC_LAYER_FORMAT Layer Pixel Format */
/** @{ */
#define LL_LCDC_FORMAT_RGB565   LCD_IF_LAYER0_CONFIG_FORMAT_RGB565
#define LL_LCDC_FORMAT_RGB888   LCD_IF_LAYER0_CONFIG_FORMAT_RGB888
#define LL_LCDC_FORMAT_ARGB8888 LCD_IF_LAYER0_CONFIG_FORMAT_ARGB8888
#define LL_LCDC_FORMAT_ARGB8565 LCD_IF_LAYER0_CONFIG_FORMAT_ARGB8565
#define LL_LCDC_FORMAT_RGB332   LCD_IF_LAYER0_CONFIG_FORMAT_RGB332
#define LL_LCDC_FORMAT_A8       LCD_IF_LAYER0_CONFIG_FORMAT_A8
#define LL_LCDC_FORMAT_L8       LCD_IF_LAYER0_CONFIG_FORMAT_L8
/** @} */

/** @defgroup LL_LCDC_CTRL Internal Constants */
/** @{ */
#define LL_LCDC_TE_CONF_EN   (0x1U)
#define LL_LCDC_IRQ_STAT_Msk (0x7FU)
#define LL_LCDC_IRQ_RAW_Pos  (16U)
/** @} */

/*==============================================================================
 * Basic Control
 *============================================================================*/

static inline void ll_lcdc_start(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->COMMAND, LCD_IF_COMMAND_START);
}

static inline void ll_lcdc_reset(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->COMMAND, LCD_IF_COMMAND_RESET);
}

static inline void ll_lcdc_release_reset(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->COMMAND, LCD_IF_COMMAND_RESET);
}

static inline uint32_t ll_lcdc_is_busy(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->STATUS, LCD_IF_STATUS_LCD_BUSY) ? 1UL : 0UL;
}

/*==============================================================================
 * SPI Interface (SPI_IF_CONF)
 *============================================================================*/

/**
 * @brief Enable automatic chip-select de-assertion (SPI_IF_CONF.SPI_CS_AUTO_DIS).
 *        When the bus is busy, the LCDC automatically de-asserts CS.
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_spi_cs_auto_dis_set(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->SPI_IF_CONF, LCD_IF_SPI_IF_CONF_SPI_CS_AUTO_DIS);
}

/**
 * @brief Disable automatic chip-select de-assertion (SPI_IF_CONF.SPI_CS_AUTO_DIS).
 *        CS is kept asserted during the transfer.
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_spi_cs_auto_dis_clear(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->SPI_IF_CONF, LCD_IF_SPI_IF_CONF_SPI_CS_AUTO_DIS);
}

/**
 * @brief Set the SPI clock divider (SPI_IF_CONF.CLK_DIV).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] div Clock divider value.
 */
static inline void ll_lcdc_spi_set_clock_div(LCD_IF_TypeDef *lcd, uint32_t div)
{
	MODIFY_REG(lcd->SPI_IF_CONF, LCD_IF_SPI_IF_CONF_CLK_DIV,
		   MAKE_REG_VAL(div, LCD_IF_SPI_IF_CONF_CLK_DIV_Msk, LCD_IF_SPI_IF_CONF_CLK_DIV_Pos));
}

/**
 * @brief Set the SPI read/write data length (SPI_IF_CONF.RD_LEN/WR_LEN, len-1).
 * @param[in] lcd    LCD_IF instance pointer.
 * @param[in] rd_len Read data length (0 means 1 byte).
 * @param[in] wr_len Write data length (0 means 1 byte).
 */
static inline void ll_lcdc_spi_set_data_len(LCD_IF_TypeDef *lcd, uint32_t rd_len, uint32_t wr_len)
{
	MODIFY_REG(lcd->SPI_IF_CONF,
		   LCD_IF_SPI_IF_CONF_RD_LEN | LCD_IF_SPI_IF_CONF_WR_LEN |
			   LCD_IF_SPI_IF_CONF_SPI_RD_MODE,
		   MAKE_REG_VAL(rd_len, LCD_IF_SPI_IF_CONF_RD_LEN_Msk, LCD_IF_SPI_IF_CONF_RD_LEN_Pos) |
		   MAKE_REG_VAL(wr_len, LCD_IF_SPI_IF_CONF_WR_LEN_Msk, LCD_IF_SPI_IF_CONF_WR_LEN_Pos));
}

/**
 * @brief Enable/disable SPI read mode (SPI_IF_CONF.SPI_RD_MODE).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable read mode, zero to disable.
 */
static inline void ll_lcdc_spi_set_read_mode(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->SPI_IF_CONF, LCD_IF_SPI_IF_CONF_SPI_RD_MODE,
		   en ? LCD_IF_SPI_IF_CONF_SPI_RD_MODE : 0UL);
}

/**
 * @brief Write the full SPI interface configuration (SPI_IF_CONF).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] conf Raw SPI_IF_CONF value.
 */
static inline void ll_lcdc_spi_set_bus_config(LCD_IF_TypeDef *lcd, uint32_t conf)
{
	WRITE_REG(lcd->SPI_IF_CONF, conf);
}

/*==============================================================================
 * Data Access (LCD_WR / LCD_RD / LCD_SINGLE)
 *============================================================================*/

/**
 * @brief Write a data/command word to the LCD write register (LCD_WR).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] data Data value.
 */
static inline void ll_lcdc_write_data(LCD_IF_TypeDef *lcd, uint32_t data)
{
	WRITE_REG(lcd->LCD_WR, data);
}

/**
 * @brief Read a data word from the LCD read register (LCD_RD).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Read data value.
 */
static inline uint32_t ll_lcdc_read_data(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->LCD_RD);
}

/**
 * @brief Trigger a single read/write transfer (LCD_SINGLE).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] val Raw LCD_SINGLE trigger value (WR_TRIG / RD_TRIG / TYPE).
 */
static inline void ll_lcdc_single_trigger(LCD_IF_TypeDef *lcd, uint32_t val)
{
	WRITE_REG(lcd->LCD_SINGLE, val);
}

/**
 * @brief Check whether a single read/write transfer is in progress (LCD_SINGLE.LCD_BUSY).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero while busy, 0 otherwise.
 */
static inline uint32_t ll_lcdc_is_single_busy(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->LCD_SINGLE, LCD_IF_LCD_SINGLE_LCD_BUSY) != 0UL;
}

/*==============================================================================
 * Canvas Configuration
 *============================================================================*/

static inline void ll_lcdc_set_canvas_pos(LCD_IF_TypeDef *lcd, uint16_t x0, uint16_t y0,
					  uint16_t x1, uint16_t y1)
{
	WRITE_REG(lcd->CANVAS_TL_POS, ((uint32_t)x0) | (((uint32_t)y0) << 16U));
	WRITE_REG(lcd->CANVAS_BR_POS, ((uint32_t)x1) | (((uint32_t)y1) << 16U));
}

static inline void ll_lcdc_set_canvas_bg(LCD_IF_TypeDef *lcd, uint8_t r, uint8_t g, uint8_t b)
{
	MODIFY_REG(lcd->CANVAS_BG,
		   LCD_IF_CANVAS_BG_RED | LCD_IF_CANVAS_BG_GREEN | LCD_IF_CANVAS_BG_BLUE,
		   ((uint32_t)b) | (((uint32_t)g) << 8U) | (((uint32_t)r) << 16U));
}

/*==============================================================================
 * Layer Configuration (Layer 0 / Layer 1)
 *============================================================================*/

/**
 * @brief Configure layer format, alpha, and dimensions
 * @param layer  0 or 1
 * @note Invalid layer indices are ignored.
 */
static inline void ll_lcdc_layer_config(LCD_IF_TypeDef *lcd, uint32_t layer, uint32_t format,
					uint8_t alpha, uint16_t width, uint32_t filter_en)
{
	if ((layer != 0U) && (layer != 1U)) {
		return;
	}
	uint32_t val = MAKE_REG_VAL(format, LCD_IF_LAYER0_CONFIG_FORMAT_Msk, LCD_IF_LAYER0_CONFIG_FORMAT_Pos) |
		       MAKE_REG_VAL(alpha, LCD_IF_LAYER0_CONFIG_ALPHA_Msk, LCD_IF_LAYER0_CONFIG_ALPHA_Pos) |
		       MAKE_REG_VAL(width, LCD_IF_LAYER0_CONFIG_WIDTH_Msk, LCD_IF_LAYER0_CONFIG_WIDTH_Pos);
	if (filter_en) {
		val |= LCD_IF_LAYER0_CONFIG_FILTER_EN;
	}
	if (layer == 0U) {
		MODIFY_REG(lcd->LAYER0_CONFIG,
			   LCD_IF_LAYER0_CONFIG_FORMAT | LCD_IF_LAYER0_CONFIG_ALPHA |
				   LCD_IF_LAYER0_CONFIG_WIDTH | LCD_IF_LAYER0_CONFIG_FILTER_EN,
			   val);
	} else {
		MODIFY_REG(lcd->LAYER1_CONFIG,
			   LCD_IF_LAYER1_CONFIG_FORMAT | LCD_IF_LAYER1_CONFIG_ALPHA |
				   LCD_IF_LAYER1_CONFIG_WIDTH | LCD_IF_LAYER1_CONFIG_FILTER_EN,
			   val);
	}
}

/**
 * @brief Enable or disable a display layer.
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] en Non-zero to activate the layer, zero to deactivate it.
 * @note Invalid layer indices are ignored.
 */
static inline void ll_lcdc_layer_set_active(LCD_IF_TypeDef *lcd, uint32_t layer, uint32_t en)
{
	if (layer == 0U) {
		MODIFY_REG(lcd->LAYER0_CONFIG, LCD_IF_LAYER0_CONFIG_ACTIVE,
			   en ? LCD_IF_LAYER0_CONFIG_ACTIVE : 0UL);
	} else if (layer == 1U) {
		MODIFY_REG(lcd->LAYER1_CONFIG, LCD_IF_LAYER1_CONFIG_ACTIVE,
			   en ? LCD_IF_LAYER1_CONFIG_ACTIVE : 0UL);
	}
}

static inline void ll_lcdc_layer_set_position(LCD_IF_TypeDef *lcd, uint32_t layer, uint16_t x0,
					      uint16_t y0, uint16_t x1, uint16_t y1)
{
	if (layer == 0U) {
		WRITE_REG(lcd->LAYER0_TL_POS, ((uint32_t)x0) | (((uint32_t)y0) << 16U));
		WRITE_REG(lcd->LAYER0_BR_POS, ((uint32_t)x1) | (((uint32_t)y1) << 16U));
	} else if (layer == 1U) {
		WRITE_REG(lcd->LAYER1_TL_POS, ((uint32_t)x0) | (((uint32_t)y0) << 16U));
		WRITE_REG(lcd->LAYER1_BR_POS, ((uint32_t)x1) | (((uint32_t)y1) << 16U));
	}
}

static inline void ll_lcdc_layer_set_src(LCD_IF_TypeDef *lcd, uint32_t layer, uint32_t addr)
{
	if (layer == 0U) {
		WRITE_REG(lcd->LAYER0_SRC, addr);
	} else if (layer == 1U) {
		WRITE_REG(lcd->LAYER1_SRC, addr);
	}
}

/**
 * @brief Enable/disable layer prefetch (LAYERx_CONFIG.PREFETCH_EN).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] en    Non-zero to enable prefetch, zero to disable.
 */
static inline void ll_lcdc_layer_set_prefetch(LCD_IF_TypeDef *lcd, uint32_t layer, uint32_t en)
{
	if (layer == 0U) {
		MODIFY_REG(lcd->LAYER0_CONFIG, LCD_IF_LAYER0_CONFIG_PREFETCH_EN,
			   en ? LCD_IF_LAYER0_CONFIG_PREFETCH_EN : 0UL);
	} else if (layer == 1U) {
		MODIFY_REG(lcd->LAYER1_CONFIG, LCD_IF_LAYER1_CONFIG_PREFETCH_EN,
			   en ? LCD_IF_LAYER1_CONFIG_PREFETCH_EN : 0UL);
	}
}

/**
 * @brief Write the layer fill register (LAYERx_FILL).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] fill  Raw LAYERx_FILL value.
 */
static inline void ll_lcdc_layer_set_fill(LCD_IF_TypeDef *lcd, uint32_t layer, uint32_t fill)
{
	if (layer == 0U) {
		WRITE_REG(lcd->LAYER0_FILL, fill);
	} else if (layer == 1U) {
		WRITE_REG(lcd->LAYER1_FILL, fill);
	}
}

/**
 * @brief Write the layer filter register (LAYERx_FILTER).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] filt  Raw LAYERx_FILTER value.
 */
static inline void ll_lcdc_layer_set_filter(LCD_IF_TypeDef *lcd, uint32_t layer, uint32_t filt)
{
	if (layer == 0U) {
		WRITE_REG(lcd->LAYER0_FILTER, filt);
	} else if (layer == 1U) {
		WRITE_REG(lcd->LAYER1_FILTER, filt);
	}
}

/*==============================================================================
 * LCD Output Configuration
 *============================================================================*/

/**
 * @brief Set the AHB RAM line offset (LCD_O_WIDTH).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] offset AHB RAM address offset for each line.
 */
static inline void ll_lcdc_set_mem_line_offset(LCD_IF_TypeDef *lcd, uint16_t offset)
{
	WRITE_REG(lcd->LCD_O_WIDTH, offset);
}

/**
 * @brief Configure 8080/DBI bus timing (LCD_IF_CONF).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] tas Setup cycles, delay from CS active to WR/RD active, 0 to 7.
 * @param[in] tah Hold cycles, delay from WR/RD inactive to CS inactive, 0 to 7.
 * @param[in] pwl Active cycles of LCD_WR/LCD_RD, 0 to 63.
 * @param[in] pwh Inactive cycles of LCD_WR/LCD_RD, 0 to 63.
 */
static inline void ll_lcdc_set_bus_timing(LCD_IF_TypeDef *lcd, uint32_t tas, uint32_t tah,
					  uint32_t pwl, uint32_t pwh)
{
	WRITE_REG(lcd->LCD_IF_CONF,
		  MAKE_REG_VAL(tas, LCD_IF_LCD_IF_CONF_TAS_Msk, LCD_IF_LCD_IF_CONF_TAS_Pos) |
		  MAKE_REG_VAL(tah, LCD_IF_LCD_IF_CONF_TAH_Msk, LCD_IF_LCD_IF_CONF_TAH_Pos) |
		  MAKE_REG_VAL(pwl, LCD_IF_LCD_IF_CONF_PWL_Msk, LCD_IF_LCD_IF_CONF_PWL_Pos) |
		  MAKE_REG_VAL(pwh, LCD_IF_LCD_IF_CONF_PWH_Msk, LCD_IF_LCD_IF_CONF_PWH_Pos));
}

/**
 * @brief Modify only the 8080/DBI setup/hold timing (LCD_IF_CONF.TAS/TAH).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] tas Setup cycles, 0 to 7.
 * @param[in] tah Hold cycles, 0 to 7.
 */
static inline void ll_lcdc_set_bus_tas_tah(LCD_IF_TypeDef *lcd, uint32_t tas, uint32_t tah)
{
	MODIFY_REG(lcd->LCD_IF_CONF,
		   LCD_IF_LCD_IF_CONF_TAS | LCD_IF_LCD_IF_CONF_TAH,
		   MAKE_REG_VAL(tas, LCD_IF_LCD_IF_CONF_TAS_Msk, LCD_IF_LCD_IF_CONF_TAS_Pos) |
		   MAKE_REG_VAL(tah, LCD_IF_LCD_IF_CONF_TAH_Msk, LCD_IF_LCD_IF_CONF_TAH_Pos));
}

/**
 * @brief Modify only the 8080/DBI pulse width timing (LCD_IF_CONF.PWL/PWH).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] pwl Active cycles of LCD_WR/LCD_RD, 0 to 63.
 * @param[in] pwh Inactive cycles of LCD_WR/LCD_RD, 0 to 63.
 */
static inline void ll_lcdc_set_bus_pwl_pwh(LCD_IF_TypeDef *lcd, uint32_t pwl, uint32_t pwh)
{
	MODIFY_REG(lcd->LCD_IF_CONF,
		   LCD_IF_LCD_IF_CONF_PWL | LCD_IF_LCD_IF_CONF_PWH,
		   MAKE_REG_VAL(pwl, LCD_IF_LCD_IF_CONF_PWL_Msk, LCD_IF_LCD_IF_CONF_PWL_Pos) |
		   MAKE_REG_VAL(pwh, LCD_IF_LCD_IF_CONF_PWH_Msk, LCD_IF_LCD_IF_CONF_PWH_Pos));
}

/**
 * @brief Drive the LCD reset pin (LCD_IF_CONF.LCD_RSTB).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to assert reset (pin low), zero to release.
 */
static inline void ll_lcdc_set_lcd_reset_pin(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->LCD_IF_CONF, LCD_IF_LCD_IF_CONF_LCD_RSTB,
		   en ? 0UL : LCD_IF_LCD_IF_CONF_LCD_RSTB);
}

/**
 * @brief Set the LCD output formats (LCD_CONF.SPI_LCD_FORMAT/DPI_LCD_FORMAT/
 *        LCD_FORMAT/ENDIAN).
 * @param[in] lcd      LCD_IF instance pointer.
 * @param[in] spi_fmt  SPI LCD format (2 bits).
 * @param[in] dpi_fmt  DPI LCD format (3 bits).
 * @param[in] lcd_fmt  LCD format (e.g. @ref LL_LCDC_FORMAT_RGB565).
 * @param[in] endian   Endianness (0 = little, 1 = big).
 */
static inline void ll_lcdc_set_output_format(LCD_IF_TypeDef *lcd, uint32_t spi_fmt,
					     uint32_t dpi_fmt, uint32_t lcd_fmt, uint32_t endian)
{
	MODIFY_REG(lcd->LCD_CONF,
		   LCD_IF_LCD_CONF_LCD_FORMAT | LCD_IF_LCD_CONF_AHB_FORMAT |
			   LCD_IF_LCD_CONF_SPI_LCD_FORMAT | LCD_IF_LCD_CONF_DPI_LCD_FORMAT |
			   LCD_IF_LCD_CONF_JDI_SER_FORMAT | LCD_IF_LCD_CONF_ENDIAN,
		   MAKE_REG_VAL(spi_fmt, LCD_IF_LCD_CONF_SPI_LCD_FORMAT_Msk,
				LCD_IF_LCD_CONF_SPI_LCD_FORMAT_Pos) |
		   MAKE_REG_VAL(dpi_fmt, LCD_IF_LCD_CONF_DPI_LCD_FORMAT_Msk,
				LCD_IF_LCD_CONF_DPI_LCD_FORMAT_Pos) |
		   MAKE_REG_VAL(lcd_fmt, LCD_IF_LCD_CONF_LCD_FORMAT_Msk,
				LCD_IF_LCD_CONF_LCD_FORMAT_Pos) |
		   (endian ? LCD_IF_LCD_CONF_ENDIAN : 0UL));
}

/*==============================================================================
 * TE (Tearing Effect) Configuration
 *============================================================================*/

static inline void ll_lcdc_te_enable(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->TE_CONF, LL_LCDC_TE_CONF_EN);
}

static inline void ll_lcdc_te_disable(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->TE_CONF, LL_LCDC_TE_CONF_EN);
}

/**
 * @brief Configure the tearing-effect signal (TE_CONF).
 * @param[in] lcd      LCD_IF instance pointer.
 * @param[in] enable   Non-zero to enable TE, zero to disable.
 * @param[in] polarity Frame-mark polarity (0 = falling, 1 = rising).
 * @param[in] mode     TE mode.
 */
static inline void ll_lcdc_te_set_config(LCD_IF_TypeDef *lcd, uint32_t enable,
					 uint32_t polarity, uint32_t mode)
{
	WRITE_REG(lcd->TE_CONF,
		  MAKE_REG_VAL(enable, LCD_IF_TE_CONF_ENABLE_Msk, LCD_IF_TE_CONF_ENABLE_Pos) |
		  MAKE_REG_VAL(polarity, LCD_IF_TE_CONF_FMARK_POL_Msk, LCD_IF_TE_CONF_FMARK_POL_Pos) |
		  MAKE_REG_VAL(mode, LCD_IF_TE_CONF_MODE_Msk, LCD_IF_TE_CONF_MODE_Pos));
}

/**
 * @brief Set the TE delay count (TE_CONF2.DLY_CNT, in microseconds).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] dly Delay count value.
 */
static inline void ll_lcdc_te_set_delay(LCD_IF_TypeDef *lcd, uint32_t dly)
{
	WRITE_REG(lcd->TE_CONF2, dly);
}

/*==============================================================================
 * DPI Interface
 *============================================================================*/

/**
 * @brief Configure DPI timing.
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] hsync HSW, hsync width.
 * @param[in] hbp HBP, horizontal back porch.
 * @param[in] hfp HFP, horizontal front porch.
 * @param[in] vsync VSH, vsync height.
 * @param[in] vbp VBP, vertical back porch.
 * @param[in] vfp VFP, vertical front porch.
 */
static inline void ll_lcdc_dpi_set_timing(LCD_IF_TypeDef *lcd, uint16_t hsync, uint16_t hbp,
					  uint16_t hfp, uint16_t vsync, uint16_t vbp, uint16_t vfp)
{
	WRITE_REG(lcd->DPI_IF_CONF1,
		  MAKE_REG_VAL(vsync, LCD_IF_DPI_IF_CONF1_VSH_Msk, LCD_IF_DPI_IF_CONF1_VSH_Pos) |
		  MAKE_REG_VAL(hsync, LCD_IF_DPI_IF_CONF1_HSW_Msk, LCD_IF_DPI_IF_CONF1_HSW_Pos));
	WRITE_REG(lcd->DPI_IF_CONF2,
		  MAKE_REG_VAL(vbp, LCD_IF_DPI_IF_CONF2_VBP_Msk, LCD_IF_DPI_IF_CONF2_VBP_Pos) |
		  MAKE_REG_VAL(hbp, LCD_IF_DPI_IF_CONF2_HBP_Msk, LCD_IF_DPI_IF_CONF2_HBP_Pos));
	WRITE_REG(lcd->DPI_IF_CONF3,
		  MAKE_REG_VAL(vfp, LCD_IF_DPI_IF_CONF3_VFP_Msk, LCD_IF_DPI_IF_CONF3_VFP_Pos) |
		  MAKE_REG_VAL(hfp, LCD_IF_DPI_IF_CONF3_HFP_Msk, LCD_IF_DPI_IF_CONF3_HFP_Pos));
}

/**
 * @brief Configure DPI active display size (DPI_IF_CONF4).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] active_w HAW, horizontal active width.
 * @param[in] active_h VAH, vertical active height.
 */
static inline void ll_lcdc_dpi_set_active_size(LCD_IF_TypeDef *lcd, uint16_t active_w,
					       uint16_t active_h)
{
	WRITE_REG(lcd->DPI_IF_CONF4,
		  MAKE_REG_VAL(active_h, LCD_IF_DPI_IF_CONF4_VAH_Msk, LCD_IF_DPI_IF_CONF4_VAH_Pos) |
		  MAKE_REG_VAL(active_w, LCD_IF_DPI_IF_CONF4_HAW_Msk, LCD_IF_DPI_IF_CONF4_HAW_Pos));
}

static inline uint32_t ll_lcdc_dpi_is_running(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->STATUS, LCD_IF_STATUS_DPI_RUN) ? 1UL : 0UL;
}

/*==============================================================================
 * eZip Decompression (Layer 0)
 *============================================================================*/

/**
 * @brief Configure layer 0 decompression (LAYER0_DECOMP).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] col_size Number of columns in a line of the original image.
 * @param[in] target_words Size of a single channel data before decompression,
 *                         in half words.
 * @param[in] en Non-zero to enable decompression, zero to disable it.
 * @note eZip standalone DMA source/dest addresses belong to the separate EZIP
 *       module, not to these LCDC registers.
 */
static inline void ll_lcdc_ezip_set_config(LCD_IF_TypeDef *lcd, uint16_t col_size,
					   uint16_t target_words, uint32_t en)
{
	WRITE_REG(lcd->LAYER0_DECOMP,
		  MAKE_REG_VAL(en, LCD_IF_LAYER0_DECOMP_ENABLE_Msk, LCD_IF_LAYER0_DECOMP_ENABLE_Pos) |
		  MAKE_REG_VAL(target_words, LCD_IF_LAYER0_DECOMP_TARGET_WORDS_Msk,
			       LCD_IF_LAYER0_DECOMP_TARGET_WORDS_Pos) |
		  MAKE_REG_VAL(col_size, LCD_IF_LAYER0_DECOMP_COL_SIZE_Msk,
			       LCD_IF_LAYER0_DECOMP_COL_SIZE_Pos));
}

/**
 * @brief Get the layer 0 decompression buffer maximum usage.
 */
static inline uint32_t ll_lcdc_ezip_get_status(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->LAYER0_DECOMP_STAT);
}

/*==============================================================================
 * Status & Interrupt
 *============================================================================*/

/**
 * @brief Enable interrupts selected by @p mask.
 * @note SETTING mask bits are active high: 1 enables, 0 masks the interrupt.
 */
static inline void ll_lcdc_enable_interrupt(LCD_IF_TypeDef *lcd, uint32_t mask)
{
	SET_BIT(lcd->SETTING, mask);
}

static inline void ll_lcdc_disable_interrupt(LCD_IF_TypeDef *lcd, uint32_t mask)
{
	CLEAR_BIT(lcd->SETTING, mask);
}

/**
 * @brief Clear interrupt status flags.
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] mask Interrupt status flags to clear.
 * @note LCDC IRQ status flags are cleared by writing one.
 */
static inline void ll_lcdc_clear_interrupt_status(LCD_IF_TypeDef *lcd, uint32_t mask)
{
	WRITE_REG(lcd->IRQ, mask);
}

static inline uint32_t ll_lcdc_get_interrupt_status(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->IRQ) & LL_LCDC_IRQ_STAT_Msk;
}

static inline uint32_t ll_lcdc_get_interrupt_raw(LCD_IF_TypeDef *lcd)
{
	return (READ_REG(lcd->IRQ) >> LL_LCDC_IRQ_RAW_Pos) & LL_LCDC_IRQ_STAT_Msk;
}

/*==============================================================================
 * Performance Counter
 *============================================================================*/

static inline uint32_t ll_lcdc_get_perf_count(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->PERF_CNT);
}

#ifdef __cplusplus
}
#endif

#endif /* __LL_LCDC_H */
