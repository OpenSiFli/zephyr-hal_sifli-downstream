/*
 * SPDX-FileCopyrightText: 2026 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LL_LCDC_H
#define __LL_LCDC_H

#include <stdint.h>
#include "lcd_if.h"
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
static inline void ll_lcdc_reset(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->COMMAND, LCD_IF_COMMAND_RESET);
}

static inline void ll_lcdc_release_reset(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->COMMAND, LCD_IF_COMMAND_RESET);
}

/** @} */

/*==============================================================================
 * Basic Control
 *============================================================================*/

static inline void ll_lcdc_start(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->COMMAND, LCD_IF_COMMAND_START);
}

/**
 * @brief Check whether the JDI parallel interface is running (STATUS.JDI_PAR_RUN).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero when the JDI parallel interface is running.
 */
static inline uint32_t ll_lcdc_jdi_par_is_running(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->STATUS, LCD_IF_STATUS_JDI_PAR_RUN) ? 1UL : 0UL;
}

static inline uint32_t ll_lcdc_dpi_is_running(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->STATUS, LCD_IF_STATUS_DPI_RUN) ? 1UL : 0UL;
}

static inline uint32_t ll_lcdc_is_busy(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->STATUS, LCD_IF_STATUS_LCD_BUSY) ? 1UL : 0UL;
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

static inline uint32_t ll_lcdc_get_interrupt_raw(LCD_IF_TypeDef *lcd)
{
	return (READ_REG(lcd->IRQ) &
		(LCD_IF_IRQ_LINE_DONE_RAW_STAT | LCD_IF_IRQ_JDI_PAR_UDR_RAW_STAT |
		 LCD_IF_IRQ_JDI_PARL_INTR_RAW_STAT | LCD_IF_IRQ_DPI_UDR_RAW_STAT |
		 LCD_IF_IRQ_DPIL_INTR_RAW_STAT | LCD_IF_IRQ_ICB_OF_RAW_STAT |
		 LCD_IF_IRQ_EOF_RAW_STAT)) >> LCD_IF_IRQ_EOF_RAW_STAT_Pos;
}

static inline uint32_t ll_lcdc_get_interrupt_status(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->IRQ) &
	       (LCD_IF_IRQ_LINE_DONE_STAT | LCD_IF_IRQ_JDI_PAR_UDR_STAT |
		LCD_IF_IRQ_JDI_PARL_INTR_STAT | LCD_IF_IRQ_DPI_UDR_STAT |
		LCD_IF_IRQ_DPIL_INTR_STAT | LCD_IF_IRQ_ICB_OF_STAT |
		LCD_IF_IRQ_EOF_STAT);
}

/**
 * @brief Set the line-done interrupt threshold (SETTING.LINE_DONE_NUM).
 * @param[in] lcd     LCD_IF instance pointer.
 * @param[in] line_no Line number threshold.
 */
static inline void ll_lcdc_set_line_done_num(LCD_IF_TypeDef *lcd, uint32_t line_no)
{
	MODIFY_REG(lcd->SETTING, LCD_IF_SETTING_LINE_DONE_NUM,
		   MAKE_REG_VAL(line_no, LCD_IF_SETTING_LINE_DONE_NUM_Msk,
				LCD_IF_SETTING_LINE_DONE_NUM_Pos));
}

/**
 * @brief Enable or disable automatic LCDC clock gating (SETTING.AUTO_GATE_EN).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable automatic clock gating.
 */
static inline void ll_lcdc_set_auto_gate(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->SETTING, LCD_IF_SETTING_AUTO_GATE_EN,
		   en ? LCD_IF_SETTING_AUTO_GATE_EN : 0UL);
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
	const uint32_t valid_mask = LCD_IF_SETTING_LINE_DONE_MASK |
					LCD_IF_SETTING_JDI_PAR_UDR_MASK |
					LCD_IF_SETTING_JDI_PARL_INTR_MASK |
					LCD_IF_SETTING_DPI_UDR_MASK |
					LCD_IF_SETTING_DPIL_INTR_MASK |
					LCD_IF_SETTING_ICB_OF_MASK |
					LCD_IF_SETTING_EOF_MASK;

	SET_BIT(lcd->SETTING, mask & valid_mask);
}

static inline void ll_lcdc_disable_interrupt(LCD_IF_TypeDef *lcd, uint32_t mask)
{
	const uint32_t valid_mask = LCD_IF_SETTING_LINE_DONE_MASK |
					LCD_IF_SETTING_JDI_PAR_UDR_MASK |
					LCD_IF_SETTING_JDI_PARL_INTR_MASK |
					LCD_IF_SETTING_DPI_UDR_MASK |
					LCD_IF_SETTING_DPIL_INTR_MASK |
					LCD_IF_SETTING_ICB_OF_MASK |
					LCD_IF_SETTING_EOF_MASK;

	CLEAR_BIT(lcd->SETTING, mask & valid_mask);
}

/*==============================================================================
 * Canvas Configuration
 *============================================================================*/

static inline void ll_lcdc_set_canvas_pos(LCD_IF_TypeDef *lcd, uint16_t x0, uint16_t y0,
					  uint16_t x1, uint16_t y1)
{
	WRITE_REG(lcd->CANVAS_TL_POS,
		  MAKE_REG_VAL(x0, LCD_IF_CANVAS_TL_POS_X0_Msk,
			       LCD_IF_CANVAS_TL_POS_X0_Pos) |
		  MAKE_REG_VAL(y0, LCD_IF_CANVAS_TL_POS_Y0_Msk,
			       LCD_IF_CANVAS_TL_POS_Y0_Pos));
	WRITE_REG(lcd->CANVAS_BR_POS,
		  MAKE_REG_VAL(x1, LCD_IF_CANVAS_BR_POS_X1_Msk,
			       LCD_IF_CANVAS_BR_POS_X1_Pos) |
		  MAKE_REG_VAL(y1, LCD_IF_CANVAS_BR_POS_Y1_Msk,
			       LCD_IF_CANVAS_BR_POS_Y1_Pos));
}

/**
 * @brief Enable canvas background horizontal mirror (CANVAS_BG.H_MIRROR).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_set_canvas_bg_h_mirror(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->CANVAS_BG, LCD_IF_CANVAS_BG_H_MIRROR);
}

/**
 * @brief Disable canvas background horizontal mirror (CANVAS_BG.H_MIRROR = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_clear_canvas_bg_h_mirror(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->CANVAS_BG, LCD_IF_CANVAS_BG_H_MIRROR);
}

/**
 * @brief Enable canvas background layer-by-layer bypass (CANVAS_BG.LB_BYPASS).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_set_canvas_bg_lb_bypass(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->CANVAS_BG, LCD_IF_CANVAS_BG_LB_BYPASS);
}

/**
 * @brief Disable canvas background layer-by-layer bypass (CANVAS_BG.LB_BYPASS = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_clear_canvas_bg_lb_bypass(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->CANVAS_BG, LCD_IF_CANVAS_BG_LB_BYPASS);
}

/**
 * @brief Enable all blending bypass (CANVAS_BG.ALL_BLENDING_BYPASS).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_set_canvas_bg_all_blending_bypass(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->CANVAS_BG, LCD_IF_CANVAS_BG_ALL_BLENDING_BYPASS);
}

/**
 * @brief Disable all blending bypass (CANVAS_BG.ALL_BLENDING_BYPASS = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_clear_canvas_bg_all_blending_bypass(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->CANVAS_BG, LCD_IF_CANVAS_BG_ALL_BLENDING_BYPASS);
}

/**
 * @brief Enable background blending bypass (CANVAS_BG.BG_BLENDING_BYPASS).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_set_canvas_bg_blending_bypass(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->CANVAS_BG, LCD_IF_CANVAS_BG_BG_BLENDING_BYPASS);
}

/**
 * @brief Disable background blending bypass (CANVAS_BG.BG_BLENDING_BYPASS = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_clear_canvas_bg_blending_bypass(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->CANVAS_BG, LCD_IF_CANVAS_BG_BG_BLENDING_BYPASS);
}

static inline void ll_lcdc_set_canvas_bg(LCD_IF_TypeDef *lcd, uint8_t r, uint8_t g, uint8_t b)
{
	MODIFY_REG(lcd->CANVAS_BG,
		   LCD_IF_CANVAS_BG_RED | LCD_IF_CANVAS_BG_GREEN | LCD_IF_CANVAS_BG_BLUE,
		   ((uint32_t)b) | (((uint32_t)g) << 8U) | (((uint32_t)r) << 16U));
}

/**
 * @brief Enable/disable layer vertical mirror (LAYERx_CONFIG.V_MIRROR).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] en    Non-zero to enable, zero to disable.
 */
static inline void ll_lcdc_layer_set_v_mirror(LCD_IF_TypeDef *lcd, uint32_t layer, uint32_t en)
{
	if (layer == 0U) {
		MODIFY_REG(lcd->LAYER0_CONFIG, LCD_IF_LAYER0_CONFIG_V_MIRROR,
			   en ? LCD_IF_LAYER0_CONFIG_V_MIRROR : 0UL);
	} else if (layer == 1U) {
		MODIFY_REG(lcd->LAYER1_CONFIG, LCD_IF_LAYER1_CONFIG_V_MIRROR,
			   en ? LCD_IF_LAYER1_CONFIG_V_MIRROR : 0UL);
	}
}

/**
 * @brief Set the layer alpha blending mode (LAYERx_CONFIG.ALPHA_BLEND).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] mode  Alpha blending mode (1 bit).
 */
static inline void ll_lcdc_layer_set_alpha_blend(LCD_IF_TypeDef *lcd, uint32_t layer,
						 uint32_t mode)
{
	if (layer == 0U) {
		MODIFY_REG(lcd->LAYER0_CONFIG, LCD_IF_LAYER0_CONFIG_ALPHA_BLEND,
			   mode ? LCD_IF_LAYER0_CONFIG_ALPHA_BLEND : 0UL);
	} else if (layer == 1U) {
		MODIFY_REG(lcd->LAYER1_CONFIG, LCD_IF_LAYER1_CONFIG_ALPHA_BLEND,
			   mode ? LCD_IF_LAYER1_CONFIG_ALPHA_BLEND : 0UL);
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

/**
 * @brief Set the layer line-fetch mode (LAYERx_CONFIG.LINE_FETCH_MODE).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] mode  Line fetch mode (1 bit).
 */
static inline void ll_lcdc_layer_set_line_fetch_mode(LCD_IF_TypeDef *lcd, uint32_t layer,
						     uint32_t mode)
{
	if (layer == 0U) {
		MODIFY_REG(lcd->LAYER0_CONFIG, LCD_IF_LAYER0_CONFIG_LINE_FETCH_MODE,
			   mode ? LCD_IF_LAYER0_CONFIG_LINE_FETCH_MODE : 0UL);
	} else if (layer == 1U) {
		MODIFY_REG(lcd->LAYER1_CONFIG, LCD_IF_LAYER1_CONFIG_LINE_FETCH_MODE,
			   mode ? LCD_IF_LAYER1_CONFIG_LINE_FETCH_MODE : 0UL);
	}
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
 * @brief Set the layer alpha source select (LAYERx_CONFIG.ALPHA_SEL).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] sel   Alpha source select (1 bit).
 */
static inline void ll_lcdc_layer_set_alpha_sel(LCD_IF_TypeDef *lcd, uint32_t layer,
					       uint32_t sel)
{
	if (layer == 0U) {
		MODIFY_REG(lcd->LAYER0_CONFIG, LCD_IF_LAYER0_CONFIG_ALPHA_SEL,
			   sel ? LCD_IF_LAYER0_CONFIG_ALPHA_SEL : 0UL);
	} else if (layer == 1U) {
		MODIFY_REG(lcd->LAYER1_CONFIG, LCD_IF_LAYER1_CONFIG_ALPHA_SEL,
			   sel ? LCD_IF_LAYER1_CONFIG_ALPHA_SEL : 0UL);
	}
}

static inline void ll_lcdc_layer_set_position(LCD_IF_TypeDef *lcd, uint32_t layer, uint16_t x0,
					      uint16_t y0, uint16_t x1, uint16_t y1)
{
	if (layer == 0U) {
		WRITE_REG(lcd->LAYER0_TL_POS,
			  MAKE_REG_VAL(x0, LCD_IF_LAYER0_TL_POS_X0_Msk,
				       LCD_IF_LAYER0_TL_POS_X0_Pos) |
			  MAKE_REG_VAL(y0, LCD_IF_LAYER0_TL_POS_Y0_Msk,
				       LCD_IF_LAYER0_TL_POS_Y0_Pos));
		WRITE_REG(lcd->LAYER0_BR_POS,
			  MAKE_REG_VAL(x1, LCD_IF_LAYER0_BR_POS_X1_Msk,
				       LCD_IF_LAYER0_BR_POS_X1_Pos) |
			  MAKE_REG_VAL(y1, LCD_IF_LAYER0_BR_POS_Y1_Msk,
				       LCD_IF_LAYER0_BR_POS_Y1_Pos));
	} else if (layer == 1U) {
		WRITE_REG(lcd->LAYER1_TL_POS,
			  MAKE_REG_VAL(x0, LCD_IF_LAYER1_TL_POS_X0_Msk,
				       LCD_IF_LAYER1_TL_POS_X0_Pos) |
			  MAKE_REG_VAL(y0, LCD_IF_LAYER1_TL_POS_Y0_Msk,
				       LCD_IF_LAYER1_TL_POS_Y0_Pos));
		WRITE_REG(lcd->LAYER1_BR_POS,
			  MAKE_REG_VAL(x1, LCD_IF_LAYER1_BR_POS_X1_Msk,
				       LCD_IF_LAYER1_BR_POS_X1_Pos) |
			  MAKE_REG_VAL(y1, LCD_IF_LAYER1_BR_POS_Y1_Msk,
				       LCD_IF_LAYER1_BR_POS_Y1_Pos));
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
		WRITE_REG(lcd->LAYER0_FILTER,
			  filt & (LCD_IF_LAYER0_FILTER_FILTER_MASK |
				   LCD_IF_LAYER0_FILTER_FILTER_R |
				   LCD_IF_LAYER0_FILTER_FILTER_G |
				   LCD_IF_LAYER0_FILTER_FILTER_B));
	} else if (layer == 1U) {
		WRITE_REG(lcd->LAYER1_FILTER,
			  filt & (LCD_IF_LAYER1_FILTER_FILTER_MASK |
				   LCD_IF_LAYER1_FILTER_FILTER_R |
				   LCD_IF_LAYER1_FILTER_FILTER_G |
				   LCD_IF_LAYER1_FILTER_FILTER_B));
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
 * @brief Write the layer fill register (LAYERx_FILL).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] layer Layer index, 0 or 1.
 * @param[in] fill  Raw LAYERx_FILL value.
 */
static inline void ll_lcdc_layer_set_fill(LCD_IF_TypeDef *lcd, uint32_t layer, uint32_t fill)
{
	if (layer == 0U) {
		WRITE_REG(lcd->LAYER0_FILL,
			  fill & (LCD_IF_LAYER0_FILL_ENDIAN | LCD_IF_LAYER0_FILL_BG_MODE |
				   LCD_IF_LAYER0_FILL_BG_R | LCD_IF_LAYER0_FILL_BG_G |
				   LCD_IF_LAYER0_FILL_BG_B));
	} else if (layer == 1U) {
		WRITE_REG(lcd->LAYER1_FILL,
			  fill & (LCD_IF_LAYER1_FILL_ENDIAN | LCD_IF_LAYER1_FILL_BG_MODE |
				   LCD_IF_LAYER1_FILL_BG_R | LCD_IF_LAYER1_FILL_BG_G |
				   LCD_IF_LAYER1_FILL_BG_B));
	}
}

/**
 * @brief Load the LFSR init value (DITHER_CONF.LFSR_LOAD, write 1 to load).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_dither_lfsr_load(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->DITHER_CONF, LCD_IF_DITHER_CONF_LFSR_LOAD);
}

/**
 * @brief Select the LFSR to load (DITHER_CONF.LFSR_LOAD_SEL).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] sel LFSR select: 0 none, 1 red, 2 green, 3 blue.
 */
static inline void ll_lcdc_dither_set_lfsr_load_sel(LCD_IF_TypeDef *lcd, uint32_t sel)
{
	MODIFY_REG(lcd->DITHER_CONF, LCD_IF_DITHER_CONF_LFSR_LOAD_SEL,
		   MAKE_REG_VAL(sel, LCD_IF_DITHER_CONF_LFSR_LOAD_SEL_Msk,
				LCD_IF_DITHER_CONF_LFSR_LOAD_SEL_Pos));
}

/**
 * @brief Set dither width for a color channel (DITHER_CONF.W_R/W_G/W_B).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] w_r Red channel dither width (3 bits).
 * @param[in] w_g Green channel dither width (3 bits).
 * @param[in] w_b Blue channel dither width (3 bits).
 */
static inline void ll_lcdc_dither_set_width(LCD_IF_TypeDef *lcd, uint32_t w_r,
					    uint32_t w_g, uint32_t w_b)
{
	MODIFY_REG(lcd->DITHER_CONF,
		   LCD_IF_DITHER_CONF_W_R | LCD_IF_DITHER_CONF_W_G | LCD_IF_DITHER_CONF_W_B,
		   MAKE_REG_VAL(w_r, LCD_IF_DITHER_CONF_W_R_Msk, LCD_IF_DITHER_CONF_W_R_Pos) |
		   MAKE_REG_VAL(w_g, LCD_IF_DITHER_CONF_W_G_Msk, LCD_IF_DITHER_CONF_W_G_Pos) |
		   MAKE_REG_VAL(w_b, LCD_IF_DITHER_CONF_W_B_Msk, LCD_IF_DITHER_CONF_W_B_Pos));
}

/*==============================================================================
 * Dither (DITHER_CONF / DITHER_LFSR)
 *============================================================================*/

/**
 * @brief Enable dithering (DITHER_CONF.EN).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_dither_enable(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->DITHER_CONF, LCD_IF_DITHER_CONF_EN);
}

/**
 * @brief Disable dithering (DITHER_CONF.EN = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_dither_disable(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->DITHER_CONF, LCD_IF_DITHER_CONF_EN);
}

/**
 * @brief Set the LFSR init value (DITHER_LFSR.INIT_VAL).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] value LFSR init value.
 */
static inline void ll_lcdc_dither_set_lfsr_init(LCD_IF_TypeDef *lcd, uint32_t value)
{
	WRITE_REG(lcd->DITHER_LFSR, value);
}

/*==============================================================================
 * Conversion (CONV_CFG / GREY_CONV)
 *============================================================================*/

/**
 * @brief Set the conversion format (CONV_CFG.FORMAT).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] format Conversion format (3 bits).
 */
static inline void ll_lcdc_conv_set_format(LCD_IF_TypeDef *lcd, uint32_t format)
{
	MODIFY_REG(lcd->CONV_CFG, LCD_IF_CONV_CFG_FORMAT,
		   MAKE_REG_VAL(format, LCD_IF_CONV_CFG_FORMAT_Msk, LCD_IF_CONV_CFG_FORMAT_Pos));
}

/**
 * @brief Set the grey-conversion order (GREY_CONV.ORDER).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] order Conversion order.
 */
static inline void ll_lcdc_grey_conv_set_order(LCD_IF_TypeDef *lcd, uint32_t order)
{
	MODIFY_REG(lcd->GREY_CONV, LCD_IF_GREY_CONV_ORDER,
		   order ? LCD_IF_GREY_CONV_ORDER : 0UL);
}

/**
 * @brief Set the grey-conversion coefficients (GREY_CONV.coef0/coef1/coef2).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] coef0 Coef 0 (10 bits).
 * @param[in] coef1 Coef 1 (10 bits).
 * @param[in] coef2 Coef 2 (10 bits).
 */
static inline void ll_lcdc_grey_conv_set_coefs(LCD_IF_TypeDef *lcd, uint32_t coef0,
					       uint32_t coef1, uint32_t coef2)
{
	MODIFY_REG(lcd->GREY_CONV,
		   LCD_IF_GREY_CONV_COEF0 | LCD_IF_GREY_CONV_COEF1 | LCD_IF_GREY_CONV_COEF2,
		   MAKE_REG_VAL(coef0, LCD_IF_GREY_CONV_COEF0_Msk, LCD_IF_GREY_CONV_COEF0_Pos) |
		   MAKE_REG_VAL(coef1, LCD_IF_GREY_CONV_COEF1_Msk, LCD_IF_GREY_CONV_COEF1_Pos) |
		   MAKE_REG_VAL(coef2, LCD_IF_GREY_CONV_COEF2_Msk, LCD_IF_GREY_CONV_COEF2_Pos));
}

/*==============================================================================
 * Flexible Select (FLEX_SEL_L / FLEX_SEL_H)
 *============================================================================*/

/**
 * @brief Set the low flexible-select bits (FLEX_SEL_L.bit0..bit3).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] bit0 Select for bit 0 (5 bits).
 * @param[in] bit1 Select for bit 1 (5 bits).
 * @param[in] bit2 Select for bit 2 (5 bits).
 * @param[in] bit3 Select for bit 3 (5 bits).
 */
static inline void ll_lcdc_flex_sel_l_set(LCD_IF_TypeDef *lcd, uint32_t bit0, uint32_t bit1,
					  uint32_t bit2, uint32_t bit3)
{
	MODIFY_REG(lcd->FLEX_SEL_L,
		   LCD_IF_FLEX_SEL_L_BIT0 | LCD_IF_FLEX_SEL_L_BIT1 |
			   LCD_IF_FLEX_SEL_L_BIT2 | LCD_IF_FLEX_SEL_L_BIT3,
		   MAKE_REG_VAL(bit0, LCD_IF_FLEX_SEL_L_BIT0_Msk, LCD_IF_FLEX_SEL_L_BIT0_Pos) |
		   MAKE_REG_VAL(bit1, LCD_IF_FLEX_SEL_L_BIT1_Msk, LCD_IF_FLEX_SEL_L_BIT1_Pos) |
		   MAKE_REG_VAL(bit2, LCD_IF_FLEX_SEL_L_BIT2_Msk, LCD_IF_FLEX_SEL_L_BIT2_Pos) |
		   MAKE_REG_VAL(bit3, LCD_IF_FLEX_SEL_L_BIT3_Msk, LCD_IF_FLEX_SEL_L_BIT3_Pos));
}

/**
 * @brief Set the high flexible-select bits (FLEX_SEL_H.bit4..bit7).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] bit4 Select for bit 4 (5 bits).
 * @param[in] bit5 Select for bit 5 (5 bits).
 * @param[in] bit6 Select for bit 6 (5 bits).
 * @param[in] bit7 Select for bit 7 (5 bits).
 */
static inline void ll_lcdc_flex_sel_h_set(LCD_IF_TypeDef *lcd, uint32_t bit4, uint32_t bit5,
					  uint32_t bit6, uint32_t bit7)
{
	MODIFY_REG(lcd->FLEX_SEL_H,
		   LCD_IF_FLEX_SEL_H_BIT4 | LCD_IF_FLEX_SEL_H_BIT5 |
			   LCD_IF_FLEX_SEL_H_BIT6 | LCD_IF_FLEX_SEL_H_BIT7,
		   MAKE_REG_VAL(bit4, LCD_IF_FLEX_SEL_H_BIT4_Msk, LCD_IF_FLEX_SEL_H_BIT4_Pos) |
		   MAKE_REG_VAL(bit5, LCD_IF_FLEX_SEL_H_BIT5_Msk, LCD_IF_FLEX_SEL_H_BIT5_Pos) |
		   MAKE_REG_VAL(bit6, LCD_IF_FLEX_SEL_H_BIT6_Msk, LCD_IF_FLEX_SEL_H_BIT6_Pos) |
		   MAKE_REG_VAL(bit7, LCD_IF_FLEX_SEL_H_BIT7_Msk, LCD_IF_FLEX_SEL_H_BIT7_Pos));
}

/**
 * @brief Select the interface clock 2.5 divider (LCD_CONF.INTF_CLK_DIV2P5_SEL).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to use the 2.5 divider.
 */
static inline void ll_lcdc_set_intf_clk_div2p5(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->LCD_CONF, LCD_IF_LCD_CONF_INTF_CLK_DIV2P5_SEL,
		   en ? LCD_IF_LCD_CONF_INTF_CLK_DIV2P5_SEL : 0UL);
}

/**
 * @brief Trigger the interface clock divider update (LCD_CONF.INTF_CLK_DIV_UPDATE).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_set_intf_clk_div_update(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->LCD_CONF, LCD_IF_LCD_CONF_INTF_CLK_DIV_UPDATE);
}

/**
 * @brief Set the interface clock divider (LCD_CONF.INTF_CLK_DIV).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] div Interface clock divider (4 bits).
 */
static inline void ll_lcdc_set_intf_clk_div(LCD_IF_TypeDef *lcd, uint32_t div)
{
	MODIFY_REG(lcd->LCD_CONF, LCD_IF_LCD_CONF_INTF_CLK_DIV,
		   MAKE_REG_VAL(div, LCD_IF_LCD_CONF_INTF_CLK_DIV_Msk, LCD_IF_LCD_CONF_INTF_CLK_DIV_Pos));
}

/**
 * @brief Enable the AHB clock divider (LCD_CONF.AHB_DIV_EN).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_set_ahb_div_en(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->LCD_CONF, LCD_IF_LCD_CONF_AHB_DIV_EN,
		   en ? LCD_IF_LCD_CONF_AHB_DIV_EN : 0UL);
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

/**
 * @brief Enable direct interface mode (LCD_CONF.DIRECT_INTF_EN).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_direct_intf_enable(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->LCD_CONF, LCD_IF_LCD_CONF_DIRECT_INTF_EN);
}

/**
 * @brief Disable direct interface mode (LCD_CONF.DIRECT_INTF_EN = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_direct_intf_disable(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->LCD_CONF, LCD_IF_LCD_CONF_DIRECT_INTF_EN);
}

/**
 * @brief Set LCD control output delay (LCD_IF_CONF.CTRL_DLY_SET).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to delay control output by one LCDC clock.
 */
static inline void ll_lcdc_set_control_delay(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->LCD_IF_CONF, LCD_IF_LCD_IF_CONF_CTRL_DLY_SET,
		   en ? LCD_IF_LCD_IF_CONF_CTRL_DLY_SET : 0UL);
}

/**
 * @brief Set LCD data output delay (LCD_IF_CONF.DO_DLY_SET).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to delay data output by one LCDC clock.
 */
static inline void ll_lcdc_set_data_delay(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->LCD_IF_CONF, LCD_IF_LCD_IF_CONF_DO_DLY_SET,
		   en ? LCD_IF_LCD_IF_CONF_DO_DLY_SET : 0UL);
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
 * @brief Set LCD control signal polarities (LCD_IF_CONF.*_POL).
 * @param[in] lcd    LCD_IF instance pointer.
 * @param[in] rd_pol LCD RD polarity.
 * @param[in] wr_pol LCD WR polarity.
 * @param[in] rs_pol LCD RS polarity.
 * @param[in] cs1_pol LCD1 CS polarity.
 * @param[in] cs0_pol LCD0 CS polarity.
 */
static inline void ll_lcdc_set_signal_polarity(LCD_IF_TypeDef *lcd, uint32_t rd_pol,
						       uint32_t wr_pol, uint32_t rs_pol,
						       uint32_t cs1_pol, uint32_t cs0_pol)
{
	MODIFY_REG(lcd->LCD_IF_CONF,
		   LCD_IF_LCD_IF_CONF_RD_POL | LCD_IF_LCD_IF_CONF_WR_POL |
			   LCD_IF_LCD_IF_CONF_RS_POL | LCD_IF_LCD_IF_CONF_CS1_POL |
			   LCD_IF_LCD_IF_CONF_CS0_POL,
		   (rd_pol ? LCD_IF_LCD_IF_CONF_RD_POL : 0UL) |
		   (wr_pol ? LCD_IF_LCD_IF_CONF_WR_POL : 0UL) |
		   (rs_pol ? LCD_IF_LCD_IF_CONF_RS_POL : 0UL) |
		   (cs1_pol ? LCD_IF_LCD_IF_CONF_CS1_POL : 0UL) |
		   (cs0_pol ? LCD_IF_LCD_IF_CONF_CS0_POL : 0UL));
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

/*==============================================================================
 * Memory Address (LCD_MEM)
 *============================================================================*/

/**
 * @brief Set the AHB LCD/AHB RAM base address (LCD_MEM.ADDR).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] addr AHB LCD/AHB RAM address.
 */
static inline void ll_lcdc_set_mem_addr(LCD_IF_TypeDef *lcd, uint32_t addr)
{
	WRITE_REG(lcd->LCD_MEM, addr);
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
 * @brief Check whether a single read/write transfer is in progress (LCD_SINGLE.LCD_BUSY).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero while busy, 0 otherwise.
 */
static inline uint32_t ll_lcdc_is_single_busy(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->LCD_SINGLE, LCD_IF_LCD_SINGLE_LCD_BUSY) != 0UL;
}

/**
 * @brief Trigger a single read/write transfer (LCD_SINGLE).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] val Raw LCD_SINGLE trigger value (WR_TRIG / RD_TRIG / TYPE).
 */
static inline void ll_lcdc_single_trigger(LCD_IF_TypeDef *lcd, uint32_t val)
{
	WRITE_REG(lcd->LCD_SINGLE,
		  val & (LCD_IF_LCD_SINGLE_RD_TRIG | LCD_IF_LCD_SINGLE_WR_TRIG |
			  LCD_IF_LCD_SINGLE_TYPE));
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
 * @brief Write the full SPI interface configuration (SPI_IF_CONF).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] conf Raw SPI_IF_CONF value.
 */
static inline void ll_lcdc_spi_set_bus_config(LCD_IF_TypeDef *lcd, uint32_t conf)
{
	const uint32_t valid_mask = LCD_IF_SPI_IF_CONF_SPI_CLK_INIT |
					LCD_IF_SPI_IF_CONF_SPI_CLK_PHASE |
					LCD_IF_SPI_IF_CONF_SPI_CS_POL |
					LCD_IF_SPI_IF_CONF_SPI_CS_AUTO_DIS |
					LCD_IF_SPI_IF_CONF_SPI_CS_NO_IDLE |
					LCD_IF_SPI_IF_CONF_SPI_CLK_AUTO_DIS |
					LCD_IF_SPI_IF_CONF_SPI_RD_MODE |
					LCD_IF_SPI_IF_CONF_WR_LEN |
					LCD_IF_SPI_IF_CONF_RD_LEN |
					LCD_IF_SPI_IF_CONF_LINE |
					LCD_IF_SPI_IF_CONF_DUMMY_CYCLE |
					LCD_IF_SPI_IF_CONF_EXT_CLK_SDR_DIV |
					LCD_IF_SPI_IF_CONF_EXT_LINE_WAIT_CYCLE;

	MODIFY_REG(lcd->SPI_IF_CONF,
		   LCD_IF_SPI_IF_CONF_SPI_CLK_INIT |
			   LCD_IF_SPI_IF_CONF_SPI_CLK_PHASE |
			   LCD_IF_SPI_IF_CONF_SPI_CS_POL |
			   LCD_IF_SPI_IF_CONF_SPI_CS_AUTO_DIS |
			   LCD_IF_SPI_IF_CONF_SPI_CS_NO_IDLE |
			   LCD_IF_SPI_IF_CONF_SPI_CLK_AUTO_DIS |
			   LCD_IF_SPI_IF_CONF_SPI_RD_MODE |
			   LCD_IF_SPI_IF_CONF_WR_LEN |
			   LCD_IF_SPI_IF_CONF_RD_LEN |
			   LCD_IF_SPI_IF_CONF_LINE |
			   LCD_IF_SPI_IF_CONF_DUMMY_CYCLE,
		   conf & valid_mask);
	MODIFY_REG(lcd->SPI_IF_CONF_EXT,
		   LCD_IF_SPI_IF_CONF_EXT_CLK_SDR_DIV | LCD_IF_SPI_IF_CONF_EXT_LINE_WAIT_CYCLE,
		   conf & (LCD_IF_SPI_IF_CONF_EXT_CLK_SDR_DIV | LCD_IF_SPI_IF_CONF_EXT_LINE_WAIT_CYCLE));
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
 * @brief Set the SPI clock DDR divider low/high (SPI_IF_CONF.CLK_DDR_DIV_L/H).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] divl DDR divider low (7 bits).
 * @param[in] divh DDR divider high (7 bits).
 */
static inline void ll_lcdc_spi_set_clk_ddr_div(LCD_IF_TypeDef *lcd, uint32_t divl, uint32_t divh)
{
	MODIFY_REG(lcd->SPI_IF_CONF,
		   LCD_IF_SPI_IF_CONF_CLK_DDR_DIV_L | LCD_IF_SPI_IF_CONF_CLK_DDR_DIV_H,
		   MAKE_REG_VAL(divl, LCD_IF_SPI_IF_CONF_CLK_DDR_DIV_L_Msk, LCD_IF_SPI_IF_CONF_CLK_DDR_DIV_L_Pos) |
		   MAKE_REG_VAL(divh, LCD_IF_SPI_IF_CONF_CLK_DDR_DIV_H_Msk, LCD_IF_SPI_IF_CONF_CLK_DDR_DIV_H_Pos));
}

/**
 * @brief Set the SPI clock divider (SPI_IF_CONF_EXT.EXT_CLK_SDR_DIV).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] div Clock divider value.
 */
static inline void ll_lcdc_spi_set_clock_div(LCD_IF_TypeDef *lcd, uint32_t div)
{
	MODIFY_REG(lcd->SPI_IF_CONF_EXT, LCD_IF_SPI_IF_CONF_EXT_CLK_SDR_DIV,
		   MAKE_REG_VAL(div, LCD_IF_SPI_IF_CONF_EXT_CLK_SDR_DIV_Msk, LCD_IF_SPI_IF_CONF_EXT_CLK_SDR_DIV_Pos));
}

/**
 * @brief Set the SPI read selection (SPI_IF_CONF_EXT.EXT_SPI_RD_SEL).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] sel SPI read select (2 bits).
 */
static inline void ll_lcdc_set_spi_rd_sel(LCD_IF_TypeDef *lcd, uint32_t sel)
{
	MODIFY_REG(lcd->SPI_IF_CONF_EXT, LCD_IF_SPI_IF_CONF_EXT_SPI_RD_SEL,
		   MAKE_REG_VAL(sel, LCD_IF_SPI_IF_CONF_EXT_SPI_RD_SEL_Msk,
				LCD_IF_SPI_IF_CONF_EXT_SPI_RD_SEL_Pos));
}

/**
 * @brief Set the SPI clock half-delay (SPI_IF_CONF_EXT.SPI_CLK_HALF_DLY).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable half delay.
 */
static inline void ll_lcdc_spi_set_clk_half_dly(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->SPI_IF_CONF_EXT, LCD_IF_SPI_IF_CONF_EXT_SPI_CLK_HALF_DLY,
		   en ? LCD_IF_SPI_IF_CONF_EXT_SPI_CLK_HALF_DLY : 0UL);
}

/**
 * @brief Set the SPI clock DDR mode (SPI_IF_CONF_EXT.SPI_CLK_DDR_MODE).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable DDR mode.
 */
static inline void ll_lcdc_spi_set_clk_ddr_mode(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->SPI_IF_CONF_EXT, LCD_IF_SPI_IF_CONF_EXT_SPI_CLK_DDR_MODE,
		   en ? LCD_IF_SPI_IF_CONF_EXT_SPI_CLK_DDR_MODE : 0UL);
}

/**
 * @brief Enable the post-wait clock (SPI_IF_CONF_EXT.POST_WAIT_CLK_EN).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_spi_set_post_wait_clk_en(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->SPI_IF_CONF_EXT, LCD_IF_SPI_IF_CONF_EXT_POST_WAIT_CLK_EN,
		   en ? LCD_IF_SPI_IF_CONF_EXT_POST_WAIT_CLK_EN : 0UL);
}

/**
 * @brief Set the post-wait cycle count (SPI_IF_CONF_EXT.POST_WAIT_CYCLE).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] cycle Post-wait cycle count (6 bits).
 */
static inline void ll_lcdc_spi_set_post_wait_cycle(LCD_IF_TypeDef *lcd, uint32_t cycle)
{
	MODIFY_REG(lcd->SPI_IF_CONF_EXT, LCD_IF_SPI_IF_CONF_EXT_POST_WAIT_CYCLE,
		   MAKE_REG_VAL(cycle, LCD_IF_SPI_IF_CONF_EXT_POST_WAIT_CYCLE_Msk,
				LCD_IF_SPI_IF_CONF_EXT_POST_WAIT_CYCLE_Pos));
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
 * @brief Set the TE frame-mark source (TE_CONF.FMARK_SOURCE).
 * @param[in] lcd    LCD_IF instance pointer.
 * @param[in] source Frame-mark source (1 bit).
 */
static inline void ll_lcdc_te_set_fmark_source(LCD_IF_TypeDef *lcd, uint32_t source)
{
	MODIFY_REG(lcd->TE_CONF, LCD_IF_TE_CONF_FMARK_SOURCE,
		   source ? LCD_IF_TE_CONF_FMARK_SOURCE : 0UL);
}

/**
 * @brief Set the TE frame-mark trigger mode (TE_CONF.FMARK_MODE).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] mode Non-zero for edge trigger, zero for pulse trigger.
 */
static inline void ll_lcdc_te_set_fmark_mode(LCD_IF_TypeDef *lcd, uint32_t mode)
{
	MODIFY_REG(lcd->TE_CONF, LCD_IF_TE_CONF_FMARK_MODE,
		   mode ? LCD_IF_TE_CONF_FMARK_MODE : 0UL);
}

/**
 * @brief Set the TE vsync-detect counter (TE_CONF.VSYNC_DET_CNT).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] cnt VSYNC detect counter (16 bits).
 */
static inline void ll_lcdc_te_set_vsync_det_cnt(LCD_IF_TypeDef *lcd, uint32_t cnt)
{
	MODIFY_REG(lcd->TE_CONF, LCD_IF_TE_CONF_VSYNC_DET_CNT,
		   MAKE_REG_VAL(cnt, LCD_IF_TE_CONF_VSYNC_DET_CNT_Msk,
				LCD_IF_TE_CONF_VSYNC_DET_CNT_Pos));
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
 * Tearing Effect (TE_CONF3 / TE_CONF4 / TE_STAT / TE_STAT2)
 *============================================================================*/

/**
 * @brief Set the TE delay count 1 (TE_CONF3.DLY_CNT1).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] count Delay count.
 */
static inline void ll_lcdc_te_set_dly_cnt1(LCD_IF_TypeDef *lcd, uint32_t count)
{
	WRITE_REG(lcd->TE_CONF3, count & LCD_IF_TE_CONF3_DLY_CNT1);
}

/**
 * @brief Set the TE delay count 2 (TE_CONF4.DLY_CNT2).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] count Delay count.
 */
static inline void ll_lcdc_te_set_dly_cnt2(LCD_IF_TypeDef *lcd, uint32_t count)
{
	WRITE_REG(lcd->TE_CONF4, count & LCD_IF_TE_CONF4_DLY_CNT2);
}

/**
 * @brief Get the TE current count (TE_STAT.TE_C_CNT).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Current TE count.
 */
static inline uint32_t ll_lcdc_te_get_count(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->TE_STAT) & LCD_IF_TE_STAT_TE_C_CNT;
}

/**
 * @brief Get the TE max count (TE_STAT2.TE_MAX_CNT).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Max TE count.
 */
static inline uint32_t ll_lcdc_te_get_max_count(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->TE_STAT2) & LCD_IF_TE_STAT2_TE_MAX_CNT;
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

/*==============================================================================
 * DPI (DPI_IF_CONF5 / DPI_CTRL)
 *============================================================================*/

/**
 * @brief Set the DPI interlace mode (DPI_IF_CONF5.interlace).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] en   Non-zero to enable interlace.
 */
static inline void ll_lcdc_dpi_set_interlace(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->DPI_IF_CONF5, LCD_IF_DPI_IF_CONF5_INTERLACE,
		   en ? LCD_IF_DPI_IF_CONF5_INTERLACE : 0UL);
}

/**
 * @brief Set the DPI next parity (DPI_IF_CONF5.nxt_parity).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] par  Parity value.
 */
static inline void ll_lcdc_dpi_set_nxt_parity(LCD_IF_TypeDef *lcd, uint32_t par)
{
	MODIFY_REG(lcd->DPI_IF_CONF5, LCD_IF_DPI_IF_CONF5_NXT_PARITY,
		   par ? LCD_IF_DPI_IF_CONF5_NXT_PARITY : 0UL);
}

/**
 * @brief Set the DPI current parity (DPI_IF_CONF5.cur_parity).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] par  Parity value.
 */
static inline void ll_lcdc_dpi_set_cur_parity(LCD_IF_TypeDef *lcd, uint32_t par)
{
	MODIFY_REG(lcd->DPI_IF_CONF5, LCD_IF_DPI_IF_CONF5_CUR_PARITY,
		   par ? LCD_IF_DPI_IF_CONF5_CUR_PARITY : 0UL);
}

/**
 * @brief Configure DPI clock and polarity (DPI_IF_CONF5).
 * @param[in] lcd        LCD_IF instance pointer.
 * @param[in] pclk_div   Pixel clock divider (8 bits).
 * @param[in] pclk_pol   Pixel clock polarity (1 bit).
 * @param[in] de_pol     DE polarity (1 bit).
 * @param[in] vs_pol     VSYNC polarity (1 bit).
 * @param[in] hs_pol     HSYNC polarity (1 bit).
 * @param[in] int_line   Interrupt line number (11 bits).
 * @param[in] clk_force  Force DPI clock on (1 bit).
 */
static inline void ll_lcdc_dpi_set_clock_polarity(LCD_IF_TypeDef *lcd, uint32_t pclk_div,
						  uint32_t pclk_pol, uint32_t de_pol,
						  uint32_t vs_pol, uint32_t hs_pol,
						  uint32_t int_line, uint32_t clk_force)
{
	MODIFY_REG(lcd->DPI_IF_CONF5,
		   LCD_IF_DPI_IF_CONF5_PCLK_DIV | LCD_IF_DPI_IF_CONF5_PCLKPOL |
			   LCD_IF_DPI_IF_CONF5_DEPOL | LCD_IF_DPI_IF_CONF5_VSPOL |
			   LCD_IF_DPI_IF_CONF5_HSPOL | LCD_IF_DPI_IF_CONF5_INT_LINE_NUM |
			   LCD_IF_DPI_IF_CONF5_CLK_FORCE_ON,
		   MAKE_REG_VAL(pclk_div, LCD_IF_DPI_IF_CONF5_PCLK_DIV_Msk,
				LCD_IF_DPI_IF_CONF5_PCLK_DIV_Pos) |
		   (pclk_pol ? LCD_IF_DPI_IF_CONF5_PCLKPOL : 0UL) |
		   (de_pol ? LCD_IF_DPI_IF_CONF5_DEPOL : 0UL) |
		   (vs_pol ? LCD_IF_DPI_IF_CONF5_VSPOL : 0UL) |
		   (hs_pol ? LCD_IF_DPI_IF_CONF5_HSPOL : 0UL) |
		   MAKE_REG_VAL(int_line, LCD_IF_DPI_IF_CONF5_INT_LINE_NUM_Msk,
				LCD_IF_DPI_IF_CONF5_INT_LINE_NUM_Pos) |
		   (clk_force ? LCD_IF_DPI_IF_CONF5_CLK_FORCE_ON : 0UL));
}

/**
 * @brief Enable the DPI auto gate (DPI_CTRL.auto_gate_en).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_dpi_set_auto_gate(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->DPI_CTRL, LCD_IF_DPI_CTRL_AUTO_GATE_EN,
		   en ? LCD_IF_DPI_CTRL_AUTO_GATE_EN : 0UL);
}

/**
 * @brief Set the DPI HSTAT select (DPI_CTRL.HSTAT).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] sel  HSTAT select (3 bits).
 */
static inline void ll_lcdc_dpi_set_hstat(LCD_IF_TypeDef *lcd, uint32_t sel)
{
	MODIFY_REG(lcd->DPI_CTRL, LCD_IF_DPI_CTRL_HSTAT,
		   MAKE_REG_VAL(sel, LCD_IF_DPI_CTRL_HSTAT_Msk, LCD_IF_DPI_CTRL_HSTAT_Pos));
}

/**
 * @brief Set the DPI update-config control (DPI_CTRL.DPI_UC).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] uc  Update-config control (1 bit).
 */
static inline void ll_lcdc_dpi_set_update_cfg(LCD_IF_TypeDef *lcd, uint32_t uc)
{
	MODIFY_REG(lcd->DPI_CTRL, LCD_IF_DPI_CTRL_DPI_UC,
		   uc ? LCD_IF_DPI_CTRL_DPI_UC : 0UL);
}

/**
 * @brief Set the DPI shutdown control (DPI_CTRL.DPI_SD).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] sd  Shutdown control (1 bit).
 */
static inline void ll_lcdc_dpi_set_shutdown(LCD_IF_TypeDef *lcd, uint32_t sd)
{
	MODIFY_REG(lcd->DPI_CTRL, LCD_IF_DPI_CTRL_DPI_SD,
		   sd ? LCD_IF_DPI_CTRL_DPI_SD : 0UL);
}

/**
 * @brief Set the DPI color mode (DPI_CTRL.DPI_CM).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] cm  Color mode (1 bit).
 */
static inline void ll_lcdc_dpi_set_color_mode(LCD_IF_TypeDef *lcd, uint32_t cm)
{
	MODIFY_REG(lcd->DPI_CTRL, LCD_IF_DPI_CTRL_DPI_CM,
		   cm ? LCD_IF_DPI_CTRL_DPI_CM : 0UL);
}

/*==============================================================================
 * DPI Control & Status (DPI_CTRL / DPI_IF_CONF5 / DPI_STAT)
 *============================================================================*/

/**
 * @brief Enable the DPI interface (DPI_CTRL.DPI_EN).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_dpi_enable(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->DPI_CTRL, LCD_IF_DPI_CTRL_DPI_EN);
}

/**
 * @brief Disable the DPI interface (DPI_CTRL.DPI_EN = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_dpi_disable(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->DPI_CTRL, LCD_IF_DPI_CTRL_DPI_EN);
}

/**
 * @brief Get the DPI vertical position (DPI_STAT.VPOS).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Vertical position.
 */
static inline uint32_t ll_lcdc_dpi_get_vpos(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->DPI_STAT, LCD_IF_DPI_STAT_VPOS);
}

/**
 * @brief Get the DPI horizontal position (DPI_STAT.HPOS).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Horizontal position.
 */
static inline uint32_t ll_lcdc_dpi_get_hpos(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->DPI_STAT, LCD_IF_DPI_STAT_HPOS);
}

/*==============================================================================
 * JDI Serial Interface (JDI_SER_CONF1 / JDI_SER_CONF2 / JDI_SER_CTRL)
 *============================================================================*/

/**
 * @brief Configure the JDI serial clock divider and write length (JDI_SER_CONF1).
 * @param[in] lcd    LCD_IF instance pointer.
 * @param[in] clk_div Clock divider (8 bits).
 * @param[in] wr_len  Single write bit length (5 bits).
 */
static inline void ll_lcdc_jdi_ser_set_conf1(LCD_IF_TypeDef *lcd, uint32_t clk_div,
					     uint32_t wr_len)
{
	MODIFY_REG(lcd->JDI_SER_CONF1,
		   LCD_IF_JDI_SER_CONF1_CLK_DIV | LCD_IF_JDI_SER_CONF1_WR_LEN,
		   MAKE_REG_VAL(clk_div, LCD_IF_JDI_SER_CONF1_CLK_DIV_Msk,
				LCD_IF_JDI_SER_CONF1_CLK_DIV_Pos) |
		   MAKE_REG_VAL(wr_len, LCD_IF_JDI_SER_CONF1_WR_LEN_Msk,
				LCD_IF_JDI_SER_CONF1_WR_LEN_Pos));
}

/**
 * @brief Configure the JDI serial init line count and write command (JDI_SER_CONF2).
 * @param[in] lcd       LCD_IF instance pointer.
 * @param[in] init_line Init line counter (16 bits).
 * @param[in] wr_cmd    Data transfer write command (16 bits).
 */
static inline void ll_lcdc_jdi_ser_set_conf2(LCD_IF_TypeDef *lcd, uint32_t init_line,
					     uint32_t wr_cmd)
{
	WRITE_REG(lcd->JDI_SER_CONF2,
		  MAKE_REG_VAL(init_line, LCD_IF_JDI_SER_CONF2_INIT_LINE_CNT_Msk,
			       LCD_IF_JDI_SER_CONF2_INIT_LINE_CNT_Pos) |
		  MAKE_REG_VAL(wr_cmd, LCD_IF_JDI_SER_CONF2_WR_CMD_Msk,
			       LCD_IF_JDI_SER_CONF2_WR_CMD_Pos));
}

/**
 * @brief Set the JDI serial EXTCOMIN control (JDI_SER_CTRL.EXTCOMIN).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] extcomin EXTCOMIN control (1 bit).
 */
static inline void ll_lcdc_jdi_ser_set_extcomin(LCD_IF_TypeDef *lcd, uint32_t extcomin)
{
	MODIFY_REG(lcd->JDI_SER_CTRL, LCD_IF_JDI_SER_CTRL_EXTCOMIN,
		   extcomin ? LCD_IF_JDI_SER_CTRL_EXTCOMIN : 0UL);
}

/**
 * @brief Enable the JDI serial display control (JDI_SER_CTRL.DISP).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_jdi_ser_display_enable(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->JDI_SER_CTRL, LCD_IF_JDI_SER_CTRL_DISP);
}

/**
 * @brief Disable the JDI serial display control (JDI_SER_CTRL.DISP = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_jdi_ser_display_disable(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->JDI_SER_CTRL, LCD_IF_JDI_SER_CTRL_DISP);
}

/*==============================================================================
 * JDI Parallel Interface (JDI_PAR_CONF1..CONF10 / JDI_PAR_CTRL / JDI_PAR_STAT /
 *                       JDI_PAR_EX_CTRL)
 *============================================================================*/

/**
 * @brief Set the JDI parallel max line/column (JDI_PAR_CONF1).
 * @param[in] lcd      LCD_IF instance pointer.
 * @param[in] max_line Max line (16 bits).
 * @param[in] max_col  Max column (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_max(LCD_IF_TypeDef *lcd, uint32_t max_line,
					   uint32_t max_col)
{
	WRITE_REG(lcd->JDI_PAR_CONF1,
		  MAKE_REG_VAL(max_line, LCD_IF_JDI_PAR_CONF1_MAX_LINE_Msk,
			       LCD_IF_JDI_PAR_CONF1_MAX_LINE_Pos) |
		  MAKE_REG_VAL(max_col, LCD_IF_JDI_PAR_CONF1_MAX_COL_Msk,
			       LCD_IF_JDI_PAR_CONF1_MAX_COL_Pos));
}

/**
 * @brief Set the JDI parallel start/end line (JDI_PAR_CONF2).
 * @param[in] lcd      LCD_IF instance pointer.
 * @param[in] st_line  Start line (16 bits).
 * @param[in] end_line End line (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_line_range(LCD_IF_TypeDef *lcd, uint32_t st_line,
						  uint32_t end_line)
{
	WRITE_REG(lcd->JDI_PAR_CONF2,
		  MAKE_REG_VAL(st_line, LCD_IF_JDI_PAR_CONF2_ST_LINE_Msk,
			       LCD_IF_JDI_PAR_CONF2_ST_LINE_Pos) |
		  MAKE_REG_VAL(end_line, LCD_IF_JDI_PAR_CONF2_END_LINE_Msk,
			       LCD_IF_JDI_PAR_CONF2_END_LINE_Pos));
}

/**
 * @brief Set the JDI parallel start/end column (JDI_PAR_CONF3).
 * @param[in] lcd     LCD_IF instance pointer.
 * @param[in] st_col  Start column (16 bits).
 * @param[in] end_col End column (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_col_range(LCD_IF_TypeDef *lcd, uint32_t st_col,
						 uint32_t end_col)
{
	WRITE_REG(lcd->JDI_PAR_CONF3,
		  MAKE_REG_VAL(st_col, LCD_IF_JDI_PAR_CONF3_ST_COL_Msk,
			       LCD_IF_JDI_PAR_CONF3_ST_COL_Pos) |
		  MAKE_REG_VAL(end_col, LCD_IF_JDI_PAR_CONF3_END_COL_Msk,
			       LCD_IF_JDI_PAR_CONF3_END_COL_Pos));
}

/**
 * @brief Set the JDI parallel HCK/HST width (JDI_PAR_CONF4).
 * @param[in] lcd       LCD_IF instance pointer.
 * @param[in] hck_width HCK width (16 bits).
 * @param[in] hst_width HST width (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_hck_hst(LCD_IF_TypeDef *lcd, uint32_t hck_width,
					       uint32_t hst_width)
{
	WRITE_REG(lcd->JDI_PAR_CONF4,
		  MAKE_REG_VAL(hck_width, LCD_IF_JDI_PAR_CONF4_HCK_WIDTH_Msk,
			       LCD_IF_JDI_PAR_CONF4_HCK_WIDTH_Pos) |
		  MAKE_REG_VAL(hst_width, LCD_IF_JDI_PAR_CONF4_HST_WIDTH_Msk,
			       LCD_IF_JDI_PAR_CONF4_HST_WIDTH_Pos));
}

/**
 * @brief Set the JDI parallel VCK/VST width (JDI_PAR_CONF5).
 * @param[in] lcd       LCD_IF instance pointer.
 * @param[in] vck_width VCK width (16 bits).
 * @param[in] vst_width VST width (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_vck_vst(LCD_IF_TypeDef *lcd, uint32_t vck_width,
					       uint32_t vst_width)
{
	WRITE_REG(lcd->JDI_PAR_CONF5,
		  MAKE_REG_VAL(vck_width, LCD_IF_JDI_PAR_CONF5_VCK_WIDTH_Msk,
			       LCD_IF_JDI_PAR_CONF5_VCK_WIDTH_Pos) |
		  MAKE_REG_VAL(vst_width, LCD_IF_JDI_PAR_CONF5_VST_WIDTH_Msk,
			       LCD_IF_JDI_PAR_CONF5_VST_WIDTH_Pos));
}

/**
 * @brief Set the JDI parallel VCK/HST delay (JDI_PAR_CONF6).
 * @param[in] lcd     LCD_IF instance pointer.
 * @param[in] vck_dly VCK delay (16 bits).
 * @param[in] hst_dly HST delay (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_vck_hst_delay(LCD_IF_TypeDef *lcd, uint32_t vck_dly,
						     uint32_t hst_dly)
{
	WRITE_REG(lcd->JDI_PAR_CONF6,
		  MAKE_REG_VAL(vck_dly, LCD_IF_JDI_PAR_CONF6_VCK_DLY_Msk,
			       LCD_IF_JDI_PAR_CONF6_VCK_DLY_Pos) |
		  MAKE_REG_VAL(hst_dly, LCD_IF_JDI_PAR_CONF6_HST_DLY_Msk,
			       LCD_IF_JDI_PAR_CONF6_HST_DLY_Pos));
}

/**
 * @brief Set the JDI parallel double-pixel mode (JDI_PAR_CONF7.DP_MODE).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] mode Double-pixel mode (1 bit).
 */
static inline void ll_lcdc_jdi_par_set_dp_mode(LCD_IF_TypeDef *lcd, uint32_t mode)
{
	MODIFY_REG(lcd->JDI_PAR_CONF7, LCD_IF_JDI_PAR_CONF7_DP_MODE,
		   mode ? LCD_IF_JDI_PAR_CONF7_DP_MODE : 0UL);
}

/**
 * @brief Set the JDI parallel HCK delay (JDI_PAR_CONF7.HCK_DLY).
 * @param[in] lcd     LCD_IF instance pointer.
 * @param[in] hck_dly HCK delay (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_hck_delay(LCD_IF_TypeDef *lcd, uint32_t hck_dly)
{
	MODIFY_REG(lcd->JDI_PAR_CONF7, LCD_IF_JDI_PAR_CONF7_HCK_DLY,
		   MAKE_REG_VAL(hck_dly, LCD_IF_JDI_PAR_CONF7_HCK_DLY_Msk,
				LCD_IF_JDI_PAR_CONF7_HCK_DLY_Pos));
}

/**
 * @brief Set the JDI parallel interrupt line number (JDI_PAR_CTRL.INT_LINE_NUM).
 * @param[in] lcd     LCD_IF instance pointer.
 * @param[in] line_no Interrupt line number (16 bits, line starts from 0).
 */
static inline void ll_lcdc_jdi_par_set_int_line(LCD_IF_TypeDef *lcd, uint32_t line_no)
{
	MODIFY_REG(lcd->JDI_PAR_CTRL, LCD_IF_JDI_PAR_CTRL_INT_LINE_NUM,
		   MAKE_REG_VAL(line_no, LCD_IF_JDI_PAR_CTRL_INT_LINE_NUM_Msk,
				LCD_IF_JDI_PAR_CTRL_INT_LINE_NUM_Pos));
}

/**
 * @brief Set the JDI parallel interface polarities (JDI_PAR_CTRL.*POL).
 * @param[in] lcd      LCD_IF instance pointer.
 * @param[in] vst_pol  VST polarity (1 bit).
 * @param[in] vck_pol  VCK polarity (1 bit).
 * @param[in] hst_pol  HST polarity (1 bit).
 * @param[in] hck_pol  HCK polarity (1 bit).
 * @param[in] enb_pol  ENB polarity (1 bit).
 */
static inline void ll_lcdc_jdi_par_set_polarity(LCD_IF_TypeDef *lcd, uint32_t vst_pol,
						uint32_t vck_pol, uint32_t hst_pol,
						uint32_t hck_pol, uint32_t enb_pol)
{
	MODIFY_REG(lcd->JDI_PAR_CTRL,
		   LCD_IF_JDI_PAR_CTRL_VSTPOL | LCD_IF_JDI_PAR_CTRL_VCKPOL |
			   LCD_IF_JDI_PAR_CTRL_HSTPOL | LCD_IF_JDI_PAR_CTRL_HCKPOL |
			   LCD_IF_JDI_PAR_CTRL_ENBPOL,
		   (vst_pol ? LCD_IF_JDI_PAR_CTRL_VSTPOL : 0UL) |
		   (vck_pol ? LCD_IF_JDI_PAR_CTRL_VCKPOL : 0UL) |
		   (hst_pol ? LCD_IF_JDI_PAR_CTRL_HSTPOL : 0UL) |
		   (hck_pol ? LCD_IF_JDI_PAR_CTRL_HCKPOL : 0UL) |
		   (enb_pol ? LCD_IF_JDI_PAR_CTRL_ENBPOL : 0UL));
}

/**
 * @brief Set the JDI parallel XRST control (JDI_PAR_CTRL.XRST).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] xrst XRST control (1 bit).
 */
static inline void ll_lcdc_jdi_par_set_xrst(LCD_IF_TypeDef *lcd, uint32_t xrst)
{
	MODIFY_REG(lcd->JDI_PAR_CTRL, LCD_IF_JDI_PAR_CTRL_XRST,
		   xrst ? LCD_IF_JDI_PAR_CTRL_XRST : 0UL);
}

/**
 * @brief Enable the JDI parallel interface (JDI_PAR_CTRL.ENABLE).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_jdi_par_enable(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->JDI_PAR_CTRL, LCD_IF_JDI_PAR_CTRL_ENABLE);
}

/**
 * @brief Disable the JDI parallel interface (JDI_PAR_CTRL.ENABLE = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_jdi_par_disable(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->JDI_PAR_CTRL, LCD_IF_JDI_PAR_CTRL_ENABLE);
}

/**
 * @brief Get the JDI parallel vertical position (JDI_PAR_STAT.VPOS).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Vertical position.
 */
static inline uint32_t ll_lcdc_jdi_par_get_vpos(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->JDI_PAR_STAT, LCD_IF_JDI_PAR_STAT_VPOS);
}

/**
 * @brief Get the JDI parallel horizontal position (JDI_PAR_STAT.HPOS).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Horizontal position.
 */
static inline uint32_t ll_lcdc_jdi_par_get_hpos(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->JDI_PAR_STAT, LCD_IF_JDI_PAR_STAT_HPOS);
}

/**
 * @brief Get the JDI parallel VCOM value (JDI_PAR_EX_CTRL.VCOM).
 * @param[in] lcd LCD_IF instance pointer.
 * @return VCOM value.
 */
static inline uint32_t ll_lcdc_jdi_par_get_vcom(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->JDI_PAR_EX_CTRL, LCD_IF_JDI_PAR_EX_CTRL_VCOM);
}

/**
 * @brief Get the JDI parallel FRP value (JDI_PAR_EX_CTRL.FRP).
 * @param[in] lcd LCD_IF instance pointer.
 * @return FRP value.
 */
static inline uint32_t ll_lcdc_jdi_par_get_frp(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->JDI_PAR_EX_CTRL, LCD_IF_JDI_PAR_EX_CTRL_FRP);
}

/**
 * @brief Get the JDI parallel XFRP value (JDI_PAR_EX_CTRL.XFRP).
 * @param[in] lcd LCD_IF instance pointer.
 * @return XFRP value.
 */
static inline uint32_t ll_lcdc_jdi_par_get_xfrp(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->JDI_PAR_EX_CTRL, LCD_IF_JDI_PAR_EX_CTRL_XFRP);
}

/**
 * @brief Enable the VCOM/FRP/XFRP counter (JDI_PAR_EX_CTRL.CNT_EN).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_jdi_par_ext_cnt_enable(LCD_IF_TypeDef *lcd)
{
	SET_BIT(lcd->JDI_PAR_EX_CTRL, LCD_IF_JDI_PAR_EX_CTRL_CNT_EN);
}

/**
 * @brief Disable the VCOM/FRP/XFRP counter (JDI_PAR_EX_CTRL.CNT_EN = 0).
 * @param[in] lcd LCD_IF instance pointer.
 */
static inline void ll_lcdc_jdi_par_ext_cnt_disable(LCD_IF_TypeDef *lcd)
{
	CLEAR_BIT(lcd->JDI_PAR_EX_CTRL, LCD_IF_JDI_PAR_EX_CTRL_CNT_EN);
}

/**
 * @brief Set the VCOM/FRP/XFRP max counter (JDI_PAR_EX_CTRL.MAX_CNT).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] max_cnt Max counter (24 bits).
 */
static inline void ll_lcdc_jdi_par_set_ext_max_cnt(LCD_IF_TypeDef *lcd, uint32_t max_cnt)
{
	MODIFY_REG(lcd->JDI_PAR_EX_CTRL, LCD_IF_JDI_PAR_EX_CTRL_MAX_CNT,
		   MAKE_REG_VAL(max_cnt, LCD_IF_JDI_PAR_EX_CTRL_MAX_CNT_Msk,
				LCD_IF_JDI_PAR_EX_CTRL_MAX_CNT_Pos));
}

/**
 * @brief Set the JDI parallel ENB start/end column (JDI_PAR_CONF8).
 * @param[in] lcd        LCD_IF instance pointer.
 * @param[in] enb_st_col ENB start column (16 bits).
 * @param[in] enb_end_col ENB end column (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_enb_col(LCD_IF_TypeDef *lcd, uint32_t enb_st_col,
					       uint32_t enb_end_col)
{
	WRITE_REG(lcd->JDI_PAR_CONF8,
		  MAKE_REG_VAL(enb_st_col, LCD_IF_JDI_PAR_CONF8_ENB_ST_COL_Msk,
			       LCD_IF_JDI_PAR_CONF8_ENB_ST_COL_Pos) |
		  MAKE_REG_VAL(enb_end_col, LCD_IF_JDI_PAR_CONF8_ENB_END_COL_Msk,
			       LCD_IF_JDI_PAR_CONF8_ENB_END_COL_Pos));
}

/**
 * @brief Set the JDI parallel ENB start/end line (JDI_PAR_CONF9).
 * @param[in] lcd         LCD_IF instance pointer.
 * @param[in] enb_st_line ENB start line (16 bits).
 * @param[in] enb_end_line ENB end line (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_enb_line(LCD_IF_TypeDef *lcd, uint32_t enb_st_line,
						uint32_t enb_end_line)
{
	WRITE_REG(lcd->JDI_PAR_CONF9,
		  MAKE_REG_VAL(enb_st_line, LCD_IF_JDI_PAR_CONF9_ENB_ST_LINE_Msk,
			       LCD_IF_JDI_PAR_CONF9_ENB_ST_LINE_Pos) |
		  MAKE_REG_VAL(enb_end_line, LCD_IF_JDI_PAR_CONF9_ENB_END_LINE_Msk,
			       LCD_IF_JDI_PAR_CONF9_ENB_END_LINE_Pos));
}

/**
 * @brief Set the JDI parallel horizontal control start/end line (JDI_PAR_CONF10).
 * @param[in] lcd        LCD_IF instance pointer.
 * @param[in] hc_st_line HC start line (16 bits).
 * @param[in] hc_end_line HC end line (16 bits).
 */
static inline void ll_lcdc_jdi_par_set_hc_line(LCD_IF_TypeDef *lcd, uint32_t hc_st_line,
					       uint32_t hc_end_line)
{
	WRITE_REG(lcd->JDI_PAR_CONF10,
		  MAKE_REG_VAL(hc_st_line, LCD_IF_JDI_PAR_CONF10_HC_ST_LINE_Msk,
			       LCD_IF_JDI_PAR_CONF10_HC_ST_LINE_Pos) |
		  MAKE_REG_VAL(hc_end_line, LCD_IF_JDI_PAR_CONF10_HC_END_LINE_Msk,
			       LCD_IF_JDI_PAR_CONF10_HC_END_LINE_Pos));
}

/**
 * @brief Set the TCON SDCLK always-on external-2 (TCON_IF_CONF1.SDCLK_AON_EXT_2).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_tcon_set_sdclk_aon_ext2(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->TCON_IF_CONF1, LCD_IF_TCON_IF_CONF1_SDCLK_AON_EXT_2,
		   en ? LCD_IF_TCON_IF_CONF1_SDCLK_AON_EXT_2 : 0UL);
}

/**
 * @brief Set the TCON SDCLK always-on external (TCON_IF_CONF1.SDCLK_AON_EXT).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_tcon_set_sdclk_aon_ext(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->TCON_IF_CONF1, LCD_IF_TCON_IF_CONF1_SDCLK_AON_EXT,
		   en ? LCD_IF_TCON_IF_CONF1_SDCLK_AON_EXT : 0UL);
}

/**
 * @brief Set the TCON GDCLK always-on external (TCON_IF_CONF1.GDCLK_AON_EXT).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_tcon_set_gdclk_aon_ext(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->TCON_IF_CONF1, LCD_IF_TCON_IF_CONF1_GDCLK_AON_EXT,
		   en ? LCD_IF_TCON_IF_CONF1_GDCLK_AON_EXT : 0UL);
}

/**
 * @brief Set the TCON SDCLK always-on (TCON_IF_CONF1.SDCLK_AON).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_tcon_set_sdclk_aon(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->TCON_IF_CONF1, LCD_IF_TCON_IF_CONF1_SDCLK_AON,
		   en ? LCD_IF_TCON_IF_CONF1_SDCLK_AON : 0UL);
}

/**
 * @brief Set the TCON GDCLK always-on (TCON_IF_CONF1.GDCLK_AON).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_tcon_set_gdclk_aon(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->TCON_IF_CONF1, LCD_IF_TCON_IF_CONF1_GDCLK_AON,
		   en ? LCD_IF_TCON_IF_CONF1_GDCLK_AON : 0UL);
}

/**
 * @brief Set the TCON signal polarities (TCON_IF_CONF1.GDSP_POL/GDCLK_POL/SDLE_POL/...).
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] gdsp  GDSP polarity.
 * @param[in] gdclk GDCLK polarity.
 * @param[in] sdl   SDLE polarity.
 * @param[in] sdo   SDOE polarity.
 * @param[in] sdstl SDSTL polarity.
 * @param[in] sdclk SDCLK polarity.
 */
static inline void ll_lcdc_tcon_set_polarity(LCD_IF_TypeDef *lcd, uint32_t gdsp, uint32_t gdclk,
					     uint32_t sdl, uint32_t sdo, uint32_t sdstl, uint32_t sdclk)
{
	MODIFY_REG(lcd->TCON_IF_CONF1,
		   LCD_IF_TCON_IF_CONF1_GDSP_POL | LCD_IF_TCON_IF_CONF1_GDCLK_POL |
			   LCD_IF_TCON_IF_CONF1_SDLE_POL | LCD_IF_TCON_IF_CONF1_SDOE_POL |
			   LCD_IF_TCON_IF_CONF1_SDSTL_POL | LCD_IF_TCON_IF_CONF1_SDCLK_POL,
		   (gdsp ? LCD_IF_TCON_IF_CONF1_GDSP_POL : 0UL) |
		   (gdclk ? LCD_IF_TCON_IF_CONF1_GDCLK_POL : 0UL) |
		   (sdl ? LCD_IF_TCON_IF_CONF1_SDLE_POL : 0UL) |
		   (sdo ? LCD_IF_TCON_IF_CONF1_SDOE_POL : 0UL) |
		   (sdstl ? LCD_IF_TCON_IF_CONF1_SDSTL_POL : 0UL) |
		   (sdclk ? LCD_IF_TCON_IF_CONF1_SDCLK_POL : 0UL));
}

/*==============================================================================
 * TCON Interface (TCON_IF_CONF1..CONF4)
 *============================================================================*/

/**
 * @brief Set the TCON output format (TCON_IF_CONF1.FORMAT).
 * @param[in] lcd    LCD_IF instance pointer.
 * @param[in] format Output format (2 bits).
 */
static inline void ll_lcdc_tcon_set_format(LCD_IF_TypeDef *lcd, uint32_t format)
{
	MODIFY_REG(lcd->TCON_IF_CONF1, LCD_IF_TCON_IF_CONF1_FORMAT,
		   MAKE_REG_VAL(format, LCD_IF_TCON_IF_CONF1_FORMAT_Msk, LCD_IF_TCON_IF_CONF1_FORMAT_Pos));
}

/**
 * @brief Set the TCON scan mode (TCON_IF_CONF1.SMODE).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] mode Scan mode.
 */
static inline void ll_lcdc_tcon_set_scan_mode(LCD_IF_TypeDef *lcd, uint32_t mode)
{
	MODIFY_REG(lcd->TCON_IF_CONF1, LCD_IF_TCON_IF_CONF1_SMODE,
		   mode ? LCD_IF_TCON_IF_CONF1_SMODE : 0UL);
}

/**
 * @brief Set the TCON clock divider (TCON_IF_CONF1.CLK_DIV).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] div Clock divider (8 bits).
 */
static inline void ll_lcdc_tcon_set_clk_div(LCD_IF_TypeDef *lcd, uint32_t div)
{
	MODIFY_REG(lcd->TCON_IF_CONF1, LCD_IF_TCON_IF_CONF1_CLK_DIV,
		   MAKE_REG_VAL(div, LCD_IF_TCON_IF_CONF1_CLK_DIV_Msk, LCD_IF_TCON_IF_CONF1_CLK_DIV_Pos));
}

/**
 * @brief Set the TCON timing widths (TCON_IF_CONF2.GSTA/LEL/LBL/LSL).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] gsta Gate start (8 bits).
 * @param[in] lel  Line end (8 bits).
 * @param[in] lbl  Line blank (8 bits).
 * @param[in] lsl  Line start (8 bits).
 */
static inline void ll_lcdc_tcon_set_conf2(LCD_IF_TypeDef *lcd, uint32_t gsta, uint32_t lel,
					  uint32_t lbl, uint32_t lsl)
{
	WRITE_REG(lcd->TCON_IF_CONF2,
		  MAKE_REG_VAL(gsta, LCD_IF_TCON_IF_CONF2_GSTA_Msk, LCD_IF_TCON_IF_CONF2_GSTA_Pos) |
		  MAKE_REG_VAL(lel, LCD_IF_TCON_IF_CONF2_LEL_Msk, LCD_IF_TCON_IF_CONF2_LEL_Pos) |
		  MAKE_REG_VAL(lbl, LCD_IF_TCON_IF_CONF2_LBL_Msk, LCD_IF_TCON_IF_CONF2_LBL_Pos) |
		  MAKE_REG_VAL(lsl, LCD_IF_TCON_IF_CONF2_LSL_Msk, LCD_IF_TCON_IF_CONF2_LSL_Pos));
}

/**
 * @brief Set the TCON line length and gate data hold (TCON_IF_CONF3.LDL/GDH).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] ldl Line data length (16 bits).
 * @param[in] gdh Gate data hold (16 bits).
 */
static inline void ll_lcdc_tcon_set_conf3(LCD_IF_TypeDef *lcd, uint32_t ldl, uint32_t gdh)
{
	WRITE_REG(lcd->TCON_IF_CONF3,
		  MAKE_REG_VAL(ldl, LCD_IF_TCON_IF_CONF3_LDL_Msk, LCD_IF_TCON_IF_CONF3_LDL_Pos) |
		  MAKE_REG_VAL(gdh, LCD_IF_TCON_IF_CONF3_GDH_Msk, LCD_IF_TCON_IF_CONF3_GDH_Pos));
}

/**
 * @brief Set the TCON frame timing widths (TCON_IF_CONF4.FDL/FSL/FBL/FEL).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] fdl Frame data length (16 bits).
 * @param[in] fsl Frame start (4 bits).
 * @param[in] fbl Frame blank (4 bits).
 * @param[in] fel Frame end (4 bits).
 */
static inline void ll_lcdc_tcon_set_conf4(LCD_IF_TypeDef *lcd, uint32_t fdl, uint32_t fsl,
					  uint32_t fbl, uint32_t fel)
{
	WRITE_REG(lcd->TCON_IF_CONF4,
		  MAKE_REG_VAL(fdl, LCD_IF_TCON_IF_CONF4_FDL_Msk, LCD_IF_TCON_IF_CONF4_FDL_Pos) |
		  MAKE_REG_VAL(fsl, LCD_IF_TCON_IF_CONF4_FSL_Msk, LCD_IF_TCON_IF_CONF4_FSL_Pos) |
		  MAKE_REG_VAL(fbl, LCD_IF_TCON_IF_CONF4_FBL_Msk, LCD_IF_TCON_IF_CONF4_FBL_Pos) |
		  MAKE_REG_VAL(fel, LCD_IF_TCON_IF_CONF4_FEL_Msk, LCD_IF_TCON_IF_CONF4_FEL_Pos));
}

/**
 * @brief Set the JPEG channel select (COENG_CFG.JPEG_CH_SEL).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] sel Channel select (2 bits).
 */
static inline void ll_lcdc_jpeg_set_ch_sel(LCD_IF_TypeDef *lcd, uint32_t sel)
{
	MODIFY_REG(lcd->COENG_CFG, LCD_IF_COENG_CFG_JPEG_CH_SEL,
		   MAKE_REG_VAL(sel, LCD_IF_COENG_CFG_JPEG_CH_SEL_Msk, LCD_IF_COENG_CFG_JPEG_CH_SEL_Pos));
}

/*==============================================================================
 * JPEG Engine (COENG_CFG / JPEG_ENG_CFG0 / JPEG_ENG_CFG1)
 *============================================================================*/

/**
 * @brief Enable the JPEG engine (COENG_CFG.JPEG_EN).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_jpeg_enable(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->COENG_CFG, LCD_IF_COENG_CFG_JPEG_EN,
		   en ? LCD_IF_COENG_CFG_JPEG_EN : 0UL);
}

/**
 * @brief Set the decompression channel select (COENG_CFG.DECOMP_CH_SEL).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] sel Channel select (2 bits).
 */
static inline void ll_lcdc_decomp_set_ch_sel(LCD_IF_TypeDef *lcd, uint32_t sel)
{
	MODIFY_REG(lcd->COENG_CFG, LCD_IF_COENG_CFG_DECOMP_CH_SEL,
		   MAKE_REG_VAL(sel, LCD_IF_COENG_CFG_DECOMP_CH_SEL_Msk, LCD_IF_COENG_CFG_DECOMP_CH_SEL_Pos));
}

/*==============================================================================
 * eZip Decompression (Layer 0)
 *============================================================================*/

/**
 * @brief Configure layer 0 decompression (DECOMP_CFG0 + COENG_CFG).
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
	WRITE_REG(lcd->DECOMP_CFG0,
		  MAKE_REG_VAL(target_words, LCD_IF_DECOMP_CFG0_TARGET_WORDS_Msk,
			       LCD_IF_DECOMP_CFG0_TARGET_WORDS_Pos) |
		  MAKE_REG_VAL(col_size, LCD_IF_DECOMP_CFG0_COL_SIZE_Msk,
			       LCD_IF_DECOMP_CFG0_COL_SIZE_Pos));
	MODIFY_REG(lcd->COENG_CFG, LCD_IF_COENG_CFG_DECOMP_EN,
		   en ? LCD_IF_COENG_CFG_DECOMP_EN : 0UL);
}

/**
 * @brief Set the JPEG range select (JPEG_ENG_CFG0.RANGE_SEL).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] sel  Range select.
 */
static inline void ll_lcdc_jpeg_set_range_sel(LCD_IF_TypeDef *lcd, uint32_t sel)
{
	MODIFY_REG(lcd->JPEG_ENG_CFG0, LCD_IF_JPEG_ENG_CFG0_RANGE_SEL,
		   sel ? LCD_IF_JPEG_ENG_CFG0_RANGE_SEL : 0UL);
}

/**
 * @brief Set the JPEG RGB-to-YUV coefficients (JPEG_ENG_CFG0.Fy/Fub/Fug).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] fy   Fy coefficient (10 bits).
 * @param[in] fub  Fub coefficient (10 bits).
 * @param[in] fug  Fug coefficient (10 bits).
 */
static inline void ll_lcdc_jpeg_set_cfg0(LCD_IF_TypeDef *lcd, uint32_t fy, uint32_t fub,
					 uint32_t fug)
{
	MODIFY_REG(lcd->JPEG_ENG_CFG0,
		   LCD_IF_JPEG_ENG_CFG0_FY | LCD_IF_JPEG_ENG_CFG0_FUB | LCD_IF_JPEG_ENG_CFG0_FUG,
		   MAKE_REG_VAL(fy, LCD_IF_JPEG_ENG_CFG0_FY_Msk, LCD_IF_JPEG_ENG_CFG0_FY_Pos) |
		   MAKE_REG_VAL(fub, LCD_IF_JPEG_ENG_CFG0_FUB_Msk, LCD_IF_JPEG_ENG_CFG0_FUB_Pos) |
		   MAKE_REG_VAL(fug, LCD_IF_JPEG_ENG_CFG0_FUG_Msk, LCD_IF_JPEG_ENG_CFG0_FUG_Pos));
}

/**
 * @brief Set the JPEG YUV coefficients (JPEG_ENG_CFG1.Fvg/Fvr).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] fvg Fvg coefficient (10 bits).
 * @param[in] fvr Fvr coefficient (10 bits).
 */
static inline void ll_lcdc_jpeg_set_cfg1(LCD_IF_TypeDef *lcd, uint32_t fvg, uint32_t fvr)
{
	MODIFY_REG(lcd->JPEG_ENG_CFG1,
		   LCD_IF_JPEG_ENG_CFG1_FVG | LCD_IF_JPEG_ENG_CFG1_FVR,
		   MAKE_REG_VAL(fvg, LCD_IF_JPEG_ENG_CFG1_FVG_Msk, LCD_IF_JPEG_ENG_CFG1_FVG_Pos) |
		   MAKE_REG_VAL(fvr, LCD_IF_JPEG_ENG_CFG1_FVR_Msk, LCD_IF_JPEG_ENG_CFG1_FVR_Pos));
}

/**
 * @brief Get the layer 0 decompression CFG0 reserved field.
 * @param[in] lcd LCD_IF instance pointer.
 * @return CFG0 reserved field value.
 */
static inline uint32_t ll_lcdc_ezip_get_cfg0_reserved(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->DECOMP_CFG1,
			    LCD_IF_DECOMP_CFG1_RESERVED0);
}

/**
 * @brief Set the layer 0 decompression CFG0 reserved field.
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] value CFG0 reserved field value.
 */
static inline void ll_lcdc_ezip_set_cfg0_reserved(LCD_IF_TypeDef *lcd, uint32_t value)
{
	MODIFY_REG(lcd->DECOMP_CFG1,
		   LCD_IF_DECOMP_CFG1_RESERVED0,
		   MAKE_REG_VAL(value, LCD_IF_DECOMP_CFG1_RESERVED0_Msk,
				LCD_IF_DECOMP_CFG1_RESERVED0_Pos));
}

/*==============================================================================
 * Layer 0 Decompression Config (LAYER0_DECOMP_CFG0 / LAYER0_DECOMP_CFG1)
 *============================================================================*/

/**
 * @brief Configure the layer 0 decompression quality table (LAYER0_DECOMP_CFG0).
 * @param[in] lcd            LCD_IF instance pointer.
 * @param[in] extra_high     Extra bit for high-quality block (4 bits).
 * @param[in] extra_threshold Threshold to distinguish high/low quality (4 bits).
 * @param[in] use_lossless   Condition to increase qidx (4 bits).
 * @param[in] lossless_qidx1 Up level for adjusted qidx (4 bits).
 * @param[in] lossless_qidx2 Condition to decrease qidx (4 bits).
 */
static inline void ll_lcdc_ezip_set_cfg0(LCD_IF_TypeDef *lcd, uint32_t extra_high,
					 uint32_t extra_threshold, uint32_t use_lossless,
					 uint32_t lossless_qidx1, uint32_t lossless_qidx2)
{
	MODIFY_REG(lcd->DECOMP_CFG1,
		   LCD_IF_DECOMP_CFG1_EXTRA_HIGH |
			   LCD_IF_DECOMP_CFG1_EXTRA_THRESHOLD |
			   LCD_IF_DECOMP_CFG1_USE_LOSSLESS_QIDX |
			   LCD_IF_DECOMP_CFG1_LOSSLESS_QIDX1 |
			   LCD_IF_DECOMP_CFG1_LOSSLESS_QIDX2,
		   MAKE_REG_VAL(extra_high, LCD_IF_DECOMP_CFG1_EXTRA_HIGH_Msk,
				LCD_IF_DECOMP_CFG1_EXTRA_HIGH_Pos) |
		   MAKE_REG_VAL(extra_threshold, LCD_IF_DECOMP_CFG1_EXTRA_THRESHOLD_Msk,
				LCD_IF_DECOMP_CFG1_EXTRA_THRESHOLD_Pos) |
		   MAKE_REG_VAL(use_lossless, LCD_IF_DECOMP_CFG1_USE_LOSSLESS_QIDX_Msk,
				LCD_IF_DECOMP_CFG1_USE_LOSSLESS_QIDX_Pos) |
		   MAKE_REG_VAL(lossless_qidx1, LCD_IF_DECOMP_CFG1_LOSSLESS_QIDX1_Msk,
				LCD_IF_DECOMP_CFG1_LOSSLESS_QIDX1_Pos) |
		   MAKE_REG_VAL(lossless_qidx2, LCD_IF_DECOMP_CFG1_LOSSLESS_QIDX2_Msk,
				LCD_IF_DECOMP_CFG1_LOSSLESS_QIDX2_Pos));
}

/**
 * @brief Configure the layer 0 decompression block/line options (LAYER0_DECOMP_CFG1).
 * @param[in] lcd             LCD_IF instance pointer.
 * @param[in] extra_low       Extra bit for low-quality block (4 bits).
 * @param[in] block_min_qidx  Minimum qidx for block mode (4 bits).
 * @param[in] line_min_qidx   Minimum qidx for line mode (4 bits).
 * @param[in] failover_r      Failover target bits (Red, 4 bits).
 * @param[in] failover_g      Failover target bits (Green, 4 bits).
 * @param[in] failover_b      Failover target bits (Blue, 4 bits).
 * @param[in] dither          Dithering function (1 bit).
 * @param[in] block_width     Block size: 0 = 16 pixels, 1 = 32 pixels.
 */
static inline void ll_lcdc_ezip_set_cfg1(LCD_IF_TypeDef *lcd, uint32_t extra_low,
					 uint32_t block_min_qidx, uint32_t line_min_qidx,
					 uint32_t failover_r, uint32_t failover_g,
					 uint32_t failover_b, uint32_t dither,
					 uint32_t block_width)
{
	MODIFY_REG(lcd->DECOMP_CFG2,
		   LCD_IF_DECOMP_CFG2_EXTRA_LOW |
			   LCD_IF_DECOMP_CFG2_BLOCK_MIN_QIDX |
			   LCD_IF_DECOMP_CFG2_LINE_MIN_QIDX |
			   LCD_IF_DECOMP_CFG2_FAILOVER_BITS_R |
			   LCD_IF_DECOMP_CFG2_FAILOVER_BITS_G |
			   LCD_IF_DECOMP_CFG2_FAILOVER_BITS_B |
			   LCD_IF_DECOMP_CFG2_DITHER |
			   LCD_IF_DECOMP_CFG2_BLOCK_WIDTH,
		   MAKE_REG_VAL(extra_low, LCD_IF_DECOMP_CFG2_EXTRA_LOW_Msk,
				LCD_IF_DECOMP_CFG2_EXTRA_LOW_Pos) |
		   MAKE_REG_VAL(block_min_qidx, LCD_IF_DECOMP_CFG2_BLOCK_MIN_QIDX_Msk,
				LCD_IF_DECOMP_CFG2_BLOCK_MIN_QIDX_Pos) |
		   MAKE_REG_VAL(line_min_qidx, LCD_IF_DECOMP_CFG2_LINE_MIN_QIDX_Msk,
				LCD_IF_DECOMP_CFG2_LINE_MIN_QIDX_Pos) |
		   MAKE_REG_VAL(failover_r, LCD_IF_DECOMP_CFG2_FAILOVER_BITS_R_Msk,
				LCD_IF_DECOMP_CFG2_FAILOVER_BITS_R_Pos) |
		   MAKE_REG_VAL(failover_g, LCD_IF_DECOMP_CFG2_FAILOVER_BITS_G_Msk,
				LCD_IF_DECOMP_CFG2_FAILOVER_BITS_G_Pos) |
		   MAKE_REG_VAL(failover_b, LCD_IF_DECOMP_CFG2_FAILOVER_BITS_B_Msk,
				LCD_IF_DECOMP_CFG2_FAILOVER_BITS_B_Pos) |
		   (dither ? LCD_IF_DECOMP_CFG2_DITHER : 0UL) |
		   (block_width ? LCD_IF_DECOMP_CFG2_BLOCK_WIDTH : 0UL));
}

/**
 * @brief Get the layer 0 decompression CFG1 reserved field.
 * @param[in] lcd LCD_IF instance pointer.
 * @return CFG1 reserved field value.
 */
static inline uint32_t ll_lcdc_ezip_get_cfg1_reserved(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->DECOMP_CFG2,
			    LCD_IF_DECOMP_CFG2_RESERVED1);
}

/**
 * @brief Set the layer 0 decompression CFG1 reserved field.
 * @param[in] lcd   LCD_IF instance pointer.
 * @param[in] value CFG1 reserved field value.
 */
static inline void ll_lcdc_ezip_set_cfg1_reserved(LCD_IF_TypeDef *lcd, uint32_t value)
{
	MODIFY_REG(lcd->DECOMP_CFG2,
		   LCD_IF_DECOMP_CFG2_RESERVED1,
		   MAKE_REG_VAL(value, LCD_IF_DECOMP_CFG2_RESERVED1_Msk,
				LCD_IF_DECOMP_CFG2_RESERVED1_Pos));
}

/**
 * @brief Get the layer 0 decompression buffer maximum usage.
 */
static inline uint32_t ll_lcdc_ezip_get_status(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->DECOMP_STAT);
}

/*==============================================================================
 * Performance Counter
 *============================================================================*/

static inline uint32_t ll_lcdc_get_perf_count(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->PERF_CNT);
}

/*==============================================================================
 * Line Buffer (LINE_BUF0 / LINE_BUF1)
 *============================================================================*/

/**
 * @brief Set the line buffer 0 address (LINE_BUF0.addr).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] addr Buffer address (word-aligned).
 */
static inline void ll_lcdc_line_buf0_set_addr(LCD_IF_TypeDef *lcd, uint32_t addr)
{
	WRITE_REG(lcd->LINE_BUF0, addr & LCD_IF_LINE_BUF0_ADDR);
}

/**
 * @brief Set the line buffer 1 address (LINE_BUF1.addr).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] addr Buffer address (word-aligned).
 */
static inline void ll_lcdc_line_buf1_set_addr(LCD_IF_TypeDef *lcd, uint32_t addr)
{
	WRITE_REG(lcd->LINE_BUF1, addr & LCD_IF_LINE_BUF1_ADDR);
}

/**
 * @brief Get the canvas Y coordinate (CANVAS_STAT0.Y_COR).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Canvas Y coordinate.
 */
static inline uint32_t ll_lcdc_get_canvas_y(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->CANVAS_STAT0, LCD_IF_CANVAS_STAT0_Y_COR);
}

/*==============================================================================
 * Canvas / Layer Status (CANVAS_STAT0 / CANVAS_STAT1 / OL0_STAT / OL1_STAT /
 *                       MEM_IF_STAT / LAYER0_DECOMP_STAT)
 *============================================================================*/

/**
 * @brief Get the canvas X coordinate (CANVAS_STAT0.X_COR).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Canvas X coordinate.
 */
static inline uint32_t ll_lcdc_get_canvas_x(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->CANVAS_STAT0, LCD_IF_CANVAS_STAT0_X_COR);
}

/**
 * @brief Get the canvas fetch status (CANVAS_STAT1.FETCH_STAT).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Fetch status.
 */
static inline uint32_t ll_lcdc_get_canvas_fetch_stat(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->CANVAS_STAT1, LCD_IF_CANVAS_STAT1_FETCH_STAT);
}

/**
 * @brief Get the canvas prefetch status (CANVAS_STAT1.PREC_STAT).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Pre-calc status.
 */
static inline uint32_t ll_lcdc_get_canvas_prec_stat(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->CANVAS_STAT1, LCD_IF_CANVAS_STAT1_PREC_STAT);
}

/**
 * @brief Get the canvas post-calc status (CANVAS_STAT1.POSTC_STAT).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Post-calc status.
 */
static inline uint32_t ll_lcdc_get_canvas_postc_stat(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->CANVAS_STAT1, LCD_IF_CANVAS_STAT1_POSTC_STAT);
}

/**
 * @brief Get the canvas FIFO count (CANVAS_STAT1.FIFO_CNT).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Pre-calc FIFO count.
 */
static inline uint32_t ll_lcdc_get_canvas_fifo_cnt(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->CANVAS_STAT1, LCD_IF_CANVAS_STAT1_FIFO_CNT);
}

/**
 * @brief Get the overlay 0 prefetch-private state (OL0_STAT.PF_PR).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Prefetch-private state.
 */
static inline uint32_t ll_lcdc_get_ol0_pf_pr(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->OL0_STAT, LCD_IF_OL0_STAT_PF_PR);
}

/**
 * @brief Get the overlay 0 prefetch-df state (OL0_STAT.PF_DF).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Prefetch-df state.
 */
static inline uint32_t ll_lcdc_get_ol0_pf_df(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->OL0_STAT, LCD_IF_OL0_STAT_PF_DF);
}

/**
 * @brief Get the overlay 0 data-conversion state (OL0_STAT.DATA_CONV).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Data-conversion state.
 */
static inline uint32_t ll_lcdc_get_ol0_data_conv(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->OL0_STAT, LCD_IF_OL0_STAT_DATA_CONV);
}

/**
 * @brief Get the overlay 0 prefetch-read state (OL0_STAT.PREFETCH_READ).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Prefetch-read state.
 */
static inline uint32_t ll_lcdc_get_ol0_prefetch_read(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->OL0_STAT, LCD_IF_OL0_STAT_PREFETCH_READ);
}

/**
 * @brief Get the overlay 0 prefetch-out state (OL0_STAT.PREFETCH_OUT).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Prefetch-out state.
 */
static inline uint32_t ll_lcdc_get_ol0_prefetch_out(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->OL0_STAT, LCD_IF_OL0_STAT_PREFETCH_OUT);
}

/**
 * @brief Get the overlay 0 done-request flag (OL0_STAT.DONE_REQ).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Done-request flag.
 */
static inline uint32_t ll_lcdc_get_ol0_done_req(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->OL0_STAT, LCD_IF_OL0_STAT_DONE_REQ);
}

/**
 * @brief Get the overlay 1 prefetch-private state (OL1_STAT.PF_PR).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Prefetch-private state.
 */
static inline uint32_t ll_lcdc_get_ol1_pf_pr(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->OL1_STAT, LCD_IF_OL1_STAT_PF_PR);
}

/**
 * @brief Get the overlay 1 prefetch-df state (OL1_STAT.PF_DF).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Prefetch-df state.
 */
static inline uint32_t ll_lcdc_get_ol1_pf_df(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->OL1_STAT, LCD_IF_OL1_STAT_PF_DF);
}

/**
 * @brief Get the overlay 1 data-conversion state (OL1_STAT.DATA_CONV).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Data-conversion state.
 */
static inline uint32_t ll_lcdc_get_ol1_data_conv(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->OL1_STAT, LCD_IF_OL1_STAT_DATA_CONV);
}

/**
 * @brief Get the overlay 1 prefetch-read state (OL1_STAT.PREFETCH_READ).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Prefetch-read state.
 */
static inline uint32_t ll_lcdc_get_ol1_prefetch_read(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->OL1_STAT, LCD_IF_OL1_STAT_PREFETCH_READ);
}

/**
 * @brief Get the overlay 1 prefetch-out state (OL1_STAT.PREFETCH_OUT).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Prefetch-out state.
 */
static inline uint32_t ll_lcdc_get_ol1_prefetch_out(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->OL1_STAT, LCD_IF_OL1_STAT_PREFETCH_OUT);
}

/**
 * @brief Get the overlay 1 done-request flag (OL1_STAT.DONE_REQ).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Done-request flag.
 */
static inline uint32_t ll_lcdc_get_ol1_done_req(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->OL1_STAT, LCD_IF_OL1_STAT_DONE_REQ);
}

/**
 * @brief Get the memory-interface main arbiter B status (MEM_IF_STAT.ARB_MAIN_B).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Main arbiter-B status.
 */
static inline uint32_t ll_lcdc_get_mem_if_arb_main_b(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->MEM_IF_STAT, LCD_IF_MEM_IF_STAT_ARB_MAIN_B);
}

/**
 * @brief Get the memory-interface read-port arbiter B status (MEM_IF_STAT.ARB_READ_PORT_B).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Read-port arbiter-B status.
 */
static inline uint32_t ll_lcdc_get_mem_if_arb_read_port_b(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->MEM_IF_STAT, LCD_IF_MEM_IF_STAT_ARB_READ_PORT_B);
}

/**
 * @brief Get the memory-interface AHB bus B status (MEM_IF_STAT.AHB_B).
 * @param[in] lcd LCD_IF instance pointer.
 * @return AHB-B status.
 */
static inline uint32_t ll_lcdc_get_mem_if_ahb_b(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->MEM_IF_STAT, LCD_IF_MEM_IF_STAT_AHB_B);
}

/**
 * @brief Get the memory-interface main arbiter status (MEM_IF_STAT.ARB_MAIN_A).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Main arbiter status.
 */
static inline uint32_t ll_lcdc_get_mem_if_arb_main(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->MEM_IF_STAT, LCD_IF_MEM_IF_STAT_ARB_MAIN_A);
}

/**
 * @brief Get the memory-interface read-port arbiter status (MEM_IF_STAT.ARB_READ_PORT_A).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Read-port arbiter status.
 */
static inline uint32_t ll_lcdc_get_mem_if_arb_read_port(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->MEM_IF_STAT, LCD_IF_MEM_IF_STAT_ARB_READ_PORT_A);
}

/**
 * @brief Get the memory-interface AHB bus status (MEM_IF_STAT.AHB_A).
 * @param[in] lcd LCD_IF instance pointer.
 * @return AHB status.
 */
static inline uint32_t ll_lcdc_get_mem_if_ahb(LCD_IF_TypeDef *lcd)
{
	return GET_REG_VAL2(lcd->MEM_IF_STAT, LCD_IF_MEM_IF_STAT_AHB_A);
}

/*==============================================================================
 * Counters (TE_WIDTH_CNT0 / TE_WIDTH_CNT1 / DPI_FRAME_CNT)
 *============================================================================*/

/**
 * @brief Enable the TE width counter (TE_WIDTH_CNT0.EN).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_te_width_cnt_enable(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->TE_WIDTH_CNT0, LCD_IF_TE_WIDTH_CNT0_EN,
		   en ? LCD_IF_TE_WIDTH_CNT0_EN : 0UL);
}

/**
 * @brief Set the TE width counter edge select (TE_WIDTH_CNT0.EDGE).
 * @param[in] lcd  LCD_IF instance pointer.
 * @param[in] edge Edge select.
 */
static inline void ll_lcdc_te_width_cnt_set_edge(LCD_IF_TypeDef *lcd, uint32_t edge)
{
	MODIFY_REG(lcd->TE_WIDTH_CNT0, LCD_IF_TE_WIDTH_CNT0_EDGE,
		   edge ? LCD_IF_TE_WIDTH_CNT0_EDGE : 0UL);
}

/**
 * @brief Get the TE width counter valid flag (TE_WIDTH_CNT0.VALID).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero when valid.
 */
static inline uint32_t ll_lcdc_te_width_cnt_is_valid(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->TE_WIDTH_CNT0, LCD_IF_TE_WIDTH_CNT0_VALID) ? 1UL : 0UL;
}

/**
 * @brief Get the TE width counter overflow flag (TE_WIDTH_CNT0.OVERFLOW).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero when overflowed.
 */
static inline uint32_t ll_lcdc_te_width_cnt_is_overflow(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->TE_WIDTH_CNT0, LCD_IF_TE_WIDTH_CNT0_OVERFLOW) ? 1UL : 0UL;
}

/**
 * @brief Get the TE width cycle count (TE_WIDTH_CNT0.CYCLE).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Cycle count.
 */
static inline uint32_t ll_lcdc_te_width_cnt_get_cycle(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->TE_WIDTH_CNT0) & LCD_IF_TE_WIDTH_CNT0_CYCLE;
}

/**
 * @brief Get the TE width counter 1 valid flag (TE_WIDTH_CNT1.VALID).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero when valid.
 */
static inline uint32_t ll_lcdc_te_width_cnt1_is_valid(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->TE_WIDTH_CNT1, LCD_IF_TE_WIDTH_CNT1_VALID) ? 1UL : 0UL;
}

/**
 * @brief Get the TE width counter 1 overflow flag (TE_WIDTH_CNT1.OVERFLOW).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero when overflowed.
 */
static inline uint32_t ll_lcdc_te_width_cnt1_is_overflow(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->TE_WIDTH_CNT1, LCD_IF_TE_WIDTH_CNT1_OVERFLOW) ? 1UL : 0UL;
}

/**
 * @brief Get the TE width counter 1 high count (TE_WIDTH_CNT1.HIGH).
 * @param[in] lcd LCD_IF instance pointer.
 * @return High count.
 */
static inline uint32_t ll_lcdc_te_width_cnt1_get_high(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->TE_WIDTH_CNT1) & LCD_IF_TE_WIDTH_CNT1_HIGH;
}

/**
 * @brief Enable the DPI frame counter (DPI_FRAME_CNT.EN).
 * @param[in] lcd LCD_IF instance pointer.
 * @param[in] en  Non-zero to enable.
 */
static inline void ll_lcdc_dpi_frame_cnt_enable(LCD_IF_TypeDef *lcd, uint32_t en)
{
	MODIFY_REG(lcd->DPI_FRAME_CNT, LCD_IF_DPI_FRAME_CNT_EN,
		   en ? LCD_IF_DPI_FRAME_CNT_EN : 0UL);
}

/**
 * @brief Get the DPI frame counter valid flag (DPI_FRAME_CNT.VALID).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero when valid.
 */
static inline uint32_t ll_lcdc_dpi_frame_cnt_is_valid(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->DPI_FRAME_CNT, LCD_IF_DPI_FRAME_CNT_VALID) ? 1UL : 0UL;
}

/**
 * @brief Get the DPI frame counter overflow flag (DPI_FRAME_CNT.OVERFLOW).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Non-zero when overflowed.
 */
static inline uint32_t ll_lcdc_dpi_frame_cnt_is_overflow(LCD_IF_TypeDef *lcd)
{
	return READ_BIT(lcd->DPI_FRAME_CNT, LCD_IF_DPI_FRAME_CNT_OVERFLOW) ? 1UL : 0UL;
}

/**
 * @brief Get the DPI frame count (DPI_FRAME_CNT.CYCLE).
 * @param[in] lcd LCD_IF instance pointer.
 * @return Frame count.
 */
static inline uint32_t ll_lcdc_dpi_frame_cnt_get(LCD_IF_TypeDef *lcd)
{
	return READ_REG(lcd->DPI_FRAME_CNT) & LCD_IF_DPI_FRAME_CNT_CYCLE;
}

#ifdef __cplusplus
}
#endif

#endif /* __LL_LCDC_H */