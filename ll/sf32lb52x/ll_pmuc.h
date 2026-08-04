/*
 * SPDX-FileCopyrightText: 2026 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LL_PMUC_H
#define __LL_PMUC_H

#include <stdint.h>
#include "regs/pmuc.h"
#include "cmsis_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file ll_pmuc.h
 * @brief Header-only low-level PMUC APIs for SF32LB52x.
 */

/** @defgroup LL_PMUC_LPCLK LL PMUC Low-Power Clock Select */
/** @{ */
#define LL_PMUC_LPCLK_LRC10 0x00000000U
#define LL_PMUC_LPCLK_LRC32 PMUC_CR_SEL_LPCLK
/** @} */

/** @defgroup LL_PMUC_WKUP LL PMUC Wakeup Source Mask */
/** @{ */
#define LL_PMUC_WKUP_RTC    PMUC_WER_RTC
#define LL_PMUC_WKUP_WDT1   PMUC_WER_WDT1
#define LL_PMUC_WKUP_WDT2   PMUC_WER_WDT2
#define LL_PMUC_WKUP_PIN0   PMUC_WER_PIN0
#define LL_PMUC_WKUP_PIN1   PMUC_WER_PIN1
#define LL_PMUC_WKUP_LOWBAT PMUC_WER_LOWBAT
#define LL_PMUC_WKUP_CHG    PMUC_WER_CHG
/** @} */

/** @defgroup LL_PMUC_PIN_MODE LL PMUC Wakeup Pin Mode */
/** @{ */
#define LL_PMUC_PIN_MODE_HIGH_LEVEL            0x0U
#define LL_PMUC_PIN_MODE_LOW_LEVEL             0x1U
#define LL_PMUC_PIN_MODE_POS_EDGE              0x2U
#define LL_PMUC_PIN_MODE_NEG_EDGE              0x3U
#define LL_PMUC_PIN_MODE_BOTH_EDGE_HIGH_ACTIVE 0x4U
#define LL_PMUC_PIN_MODE_BOTH_EDGE_LOW_ACTIVE  0x5U
/** @} */

/** @defgroup LL_PMUC_PINSEL LL PMUC Wakeup Pin Select (PA24..PA44) */
/** @{ */
#define LL_PMUC_PINSEL_PA24 0U
#define LL_PMUC_PINSEL_PA25 1U
#define LL_PMUC_PINSEL_PA26 2U
#define LL_PMUC_PINSEL_PA27 3U
#define LL_PMUC_PINSEL_PA28 4U
#define LL_PMUC_PINSEL_PA29 5U
#define LL_PMUC_PINSEL_PA30 6U
#define LL_PMUC_PINSEL_PA31 7U
#define LL_PMUC_PINSEL_PA32 8U
#define LL_PMUC_PINSEL_PA33 9U
#define LL_PMUC_PINSEL_PA34 10U
#define LL_PMUC_PINSEL_PA35 11U
#define LL_PMUC_PINSEL_PA36 12U
#define LL_PMUC_PINSEL_PA37 13U
#define LL_PMUC_PINSEL_PA38 14U
#define LL_PMUC_PINSEL_PA39 15U
#define LL_PMUC_PINSEL_PA40 16U
#define LL_PMUC_PINSEL_PA41 17U
#define LL_PMUC_PINSEL_PA42 18U
#define LL_PMUC_PINSEL_PA43 19U
#define LL_PMUC_PINSEL_PA44 20U
/** @} */

/** @defgroup LL_PMUC_MASK LL PMUC Internal Masks */
/** @{ */
#define LL_PMUC_WER_MASK                                                                           \
	(PMUC_WER_RTC | PMUC_WER_WDT1 | PMUC_WER_WDT2 | PMUC_WER_PIN0 | PMUC_WER_PIN1 |            \
	 PMUC_WER_LOWBAT | PMUC_WER_CHG)
/** @} */

/**
 * @brief PMUC wakeup pin configuration.
 */
typedef struct {
	uint32_t pin_sel; /**< Wakeup pin source select value for PA24..PA44. */
	uint32_t mode;    /**< Trigger mode, use @ref LL_PMUC_PIN_MODE_HIGH_LEVEL to @ref
			     LL_PMUC_PIN_MODE_BOTH_EDGE_LOW_ACTIVE. */
} ll_pmuc_wakeup_pin_config_t;

/**
 * @brief PMUC VRET configuration.
 */
typedef struct {
	uint32_t dly;  /**< VRET startup delay for VRET_CR.DLY field. */
	uint32_t vbit; /**< VRET output setting for VRET_CR.VBIT field. */
	uint32_t trim; /**< VRET trim setting for VRET_CR.TRIM field. */
} ll_pmuc_vret_config_t;

/**
 * @brief Configure wakeup PIN0 select and trigger mode.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] cfg Pointer to wakeup pin configuration.
 */
static inline void ll_pmuc_config_wakeup_pin0(PMUC_TypeDef *PMUCx,
					      const ll_pmuc_wakeup_pin_config_t *cfg)
{
	MODIFY_REG(PMUCx->CR, PMUC_CR_PIN0_SEL | PMUC_CR_PIN0_MODE,
		   ((cfg->pin_sel << PMUC_CR_PIN0_SEL_Pos) & PMUC_CR_PIN0_SEL) |
			   ((cfg->mode << PMUC_CR_PIN0_MODE_Pos) & PMUC_CR_PIN0_MODE));
}

/**
 * @brief Configure wakeup PIN1 select and trigger mode.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] cfg Pointer to wakeup pin configuration.
 */
static inline void ll_pmuc_config_wakeup_pin1(PMUC_TypeDef *PMUCx,
					      const ll_pmuc_wakeup_pin_config_t *cfg)
{
	MODIFY_REG(PMUCx->CR, PMUC_CR_PIN1_SEL | PMUC_CR_PIN1_MODE,
		   ((cfg->pin_sel << PMUC_CR_PIN1_SEL_Pos) & PMUC_CR_PIN1_SEL) |
			   ((cfg->mode << PMUC_CR_PIN1_MODE_Pos) & PMUC_CR_PIN1_MODE));
}

/**
 * @brief Select PMUC low-power clock source.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] sel Clock select value, use @ref LL_PMUC_LPCLK_LRC10 or @ref
 * LL_PMUC_LPCLK_LRC32.
 */
static inline void ll_pmuc_select_lpclk(PMUC_TypeDef *PMUCx, uint32_t sel)
{
	MODIFY_REG(PMUCx->CR, PMUC_CR_SEL_LPCLK, (sel & PMUC_CR_SEL_LPCLK));
}

/**
 * @brief Configure VRET delay/voltage related fields.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] cfg Pointer to VRET configuration.
 */
static inline void ll_pmuc_config_vret(PMUC_TypeDef *PMUCx, const ll_pmuc_vret_config_t *cfg)
{
	MODIFY_REG(PMUCx->VRET_CR, PMUC_VRET_CR_DLY | PMUC_VRET_CR_VBIT | PMUC_VRET_CR_TRIM,
		   ((cfg->dly << PMUC_VRET_CR_DLY_Pos) & PMUC_VRET_CR_DLY) |
			   ((cfg->vbit << PMUC_VRET_CR_VBIT_Pos) & PMUC_VRET_CR_VBIT) |
			   ((cfg->trim << PMUC_VRET_CR_TRIM_Pos) & PMUC_VRET_CR_TRIM));
}

/**
 * @brief Enable pin retention during hibernate.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_enable_pin_retention_in_hibernate(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CR, PMUC_CR_PIN_RET);
}

/**
 * @brief Disable pin retention during hibernate.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_disable_pin_retention_in_hibernate(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CR, PMUC_CR_PIN_RET);
}

/**
 * @brief Check whether pin retention in hibernate is enabled.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when PIN_RET is set.
 */
static inline uint32_t ll_pmuc_is_pin_retention_in_hibernate_enabled(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->CR, PMUC_CR_PIN_RET);
}

/**
 * @brief Enable PMUC wakeup sources.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] src_mask Wakeup source mask, use @ref LL_PMUC_WKUP_RTC,
 * @ref LL_PMUC_WKUP_WDT1, @ref LL_PMUC_WKUP_WDT2, @ref LL_PMUC_WKUP_PIN0,
 * @ref LL_PMUC_WKUP_PIN1, @ref LL_PMUC_WKUP_LOWBAT, @ref LL_PMUC_WKUP_CHG.
 */
static inline void ll_pmuc_enable_wakeup_source(PMUC_TypeDef *PMUCx, uint32_t src_mask)
{
	SET_BIT(PMUCx->WER, (src_mask & LL_PMUC_WER_MASK));
}

/**
 * @brief Disable PMUC wakeup sources.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] src_mask Wakeup source mask, use @ref LL_PMUC_WKUP_RTC,
 * @ref LL_PMUC_WKUP_WDT1, @ref LL_PMUC_WKUP_WDT2, @ref LL_PMUC_WKUP_PIN0,
 * @ref LL_PMUC_WKUP_PIN1, @ref LL_PMUC_WKUP_LOWBAT, @ref LL_PMUC_WKUP_CHG.
 */
static inline void ll_pmuc_disable_wakeup_source(PMUC_TypeDef *PMUCx, uint32_t src_mask)
{
	CLEAR_BIT(PMUCx->WER, (src_mask & LL_PMUC_WER_MASK));
}

/**
 * @brief Get currently enabled PMUC wakeup source bits.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Enabled wakeup source mask from WER.
 */
static inline uint32_t ll_pmuc_get_enabled_wakeup_source(PMUC_TypeDef *PMUCx)
{
	return (READ_REG(PMUCx->WER) & LL_PMUC_WER_MASK);
}

/**
 * @brief Enter hibernate mode.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_enter_hibernate(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CR, PMUC_CR_HIBER_EN);
}

/**
 * @brief Clear hibernate flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_hibernate_flag(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CR, PMUC_CR_HIBER_EN);
}

/**
 * @brief Check hibernate flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when hibernate flag is set.
 */
static inline uint32_t ll_pmuc_is_hibernate_flag_set(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->CR, PMUC_CR_HIBER_EN);
}

/**
 * @brief Request software reboot.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_request_reboot(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CR, PMUC_CR_REBOOT);
}

/**
 * @brief Clear reboot flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_reboot_flag(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CR, PMUC_CR_REBOOT);
}

/**
 * @brief Check reboot flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when reboot flag is set.
 */
static inline uint32_t ll_pmuc_is_reboot_flag_set(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->CR, PMUC_CR_REBOOT);
}

/**
 * @brief Read PMUC wakeup status register.
 * @param[in] PMUCx PMUC instance pointer.
 * @return WSR register value.
 */
static inline uint32_t ll_pmuc_get_wakeup_status(PMUC_TypeDef *PMUCx)
{
	return READ_REG(PMUCx->WSR);
}

/**
 * @brief Check RTC wakeup status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.RTC is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_rtc(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_RTC);
}

/**
 * @brief Check PIN0 wakeup status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.PIN0 is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_pin0(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_PIN0);
}

/**
 * @brief Check PIN1 wakeup status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.PIN1 is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_pin1(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_PIN1);
}

/**
 * @brief Check LOWBAT wakeup status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.LOWBAT is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_lowbat(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_LOWBAT);
}

/**
 * @brief Check PWRKEY status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.PWRKEY is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_pwrkey(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_PWRKEY);
}

/**
 * @brief Check IWDT status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.IWDT is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_iwdt(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_IWDT);
}

/**
 * @brief Check WDT1 status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.WDT1 is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_wdt1(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_WDT1);
}

/**
 * @brief Check WDT2 status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.WDT2 is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_wdt2(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_WDT2);
}

/**
 * @brief Check CHG status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.CHG is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_chg(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_CHG);
}

/**
 * @brief Clear PIN0 wakeup status flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_pin0(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_PIN0);
}

/**
 * @brief Clear PIN1 wakeup status flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_pin1(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_PIN1);
}

/**
 * @brief Clear LOWBAT status flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_lowbat(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_LOWBAT);
}

/**
 * @brief Clear PWRKEY status flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_pwrkey(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_PWRKEY);
}

/**
 * @brief Clear WDT1 status flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_wdt1(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_WDT1);
}

/**
 * @brief Clear WDT2 status flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_wdt2(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_WDT2);
}

/**
 * @brief Clear AON wakeup IRQ status flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_aon_irq(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_AON);
}

/**
 * @brief Enable LRC10 oscillator.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_enable_lrc10(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->LRC10_CR, PMUC_LRC10_CR_EN);
}

/**
 * @brief Disable LRC10 oscillator.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_disable_lrc10(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->LRC10_CR, PMUC_LRC10_CR_EN);
}

/**
 * @brief Check LRC10 ready status.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when LRC10 is ready.
 */
static inline uint32_t ll_pmuc_is_lrc10_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LRC10_CR, PMUC_LRC10_CR_RDY);
}

/**
 * @brief Enable LRC32 oscillator.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_enable_lrc32(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->LRC32_CR, PMUC_LRC32_CR_EN);
}

/**
 * @brief Disable LRC32 oscillator.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_disable_lrc32(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->LRC32_CR, PMUC_LRC32_CR_EN);
}

/**
 * @brief Check LRC32 ready status.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when LRC32 is ready.
 */
static inline uint32_t ll_pmuc_is_lrc32_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LRC32_CR, PMUC_LRC32_CR_RDY);
}

/**
 * @brief Enable LXT32 oscillator.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_enable_lxt32(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->LXT_CR, PMUC_LXT_CR_EN);
}

/**
 * @brief Disable LXT32 oscillator.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_disable_lxt32(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->LXT_CR, PMUC_LXT_CR_EN);
}

/**
 * @brief Check LXT32 ready status.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when LXT32 is ready.
 */
static inline uint32_t ll_pmuc_is_lxt32_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LXT_CR, PMUC_LXT_CR_RDY);
}

/*==============================================================================
 * BUCK Converter
 *============================================================================*/

static inline void ll_pmuc_buck_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_EN);
}

static inline void ll_pmuc_buck_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_EN);
}

static inline uint32_t ll_pmuc_buck_is_soft_start_done(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_SS_DONE);
}

static inline void ll_pmuc_buck_set_pwm_mode(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_CTRL);
}

static inline void ll_pmuc_buck_set_pfm_mode(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_CTRL);
}

static inline void ll_pmuc_buck_set_vout_mid(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->BUCK_CR2, PMUC_BUCK_CR2_SET_VOUT_M,
		   MAKE_REG_VAL(vout, PMUC_BUCK_CR2_SET_VOUT_M_Msk, PMUC_BUCK_CR2_SET_VOUT_M_Pos));
}

static inline void ll_pmuc_buck_set_vout_low(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->BUCK_CR2, PMUC_BUCK_CR2_SET_VOUT_L,
		   MAKE_REG_VAL(vout, PMUC_BUCK_CR2_SET_VOUT_L_Msk, PMUC_BUCK_CR2_SET_VOUT_L_Pos));
}

/*==============================================================================
 * LDO Control
 *============================================================================*/

/**
 * @brief Set HPSYS LDO output voltage (HPSYS_LDO.VREF[5:2]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vout 4-bit voltage code (must be <= 0xF).
 */
static inline void ll_pmuc_hpsys_ldo_set_vout(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->HPSYS_LDO, PMUC_HPSYS_LDO_VREF,
		   MAKE_REG_VAL(vout, PMUC_HPSYS_LDO_VREF_Msk, PMUC_HPSYS_LDO_VREF_Pos));
}

/**
 * @brief Set the HPSYS output voltage code (HPSYS_VOUT.VOUT[3:0]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vout 4-bit voltage code (must be <= 0xF).
 */
static inline void ll_pmuc_set_hpsys_vout(PMUC_TypeDef *PMUCx, uint32_t vout)
{
        MODIFY_REG(PMUCx->HPSYS_VOUT, PMUC_HPSYS_VOUT_VOUT,
                   MAKE_REG_VAL(vout, PMUC_HPSYS_VOUT_VOUT_Msk, PMUC_HPSYS_VOUT_VOUT_Pos));
}

/**
 * @brief Set LPSYS LDO output voltage (LPSYS_LDO.VREF[5:2]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vout 4-bit voltage code (must be <= 0xF).
 */
static inline void ll_pmuc_lpsys_ldo_set_vout(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->LPSYS_LDO, PMUC_LPSYS_LDO_VREF,
		   MAKE_REG_VAL(vout, PMUC_LPSYS_LDO_VREF_Msk, PMUC_LPSYS_LDO_VREF_Pos));
}

/**
 * @brief Set PERI LDO18 reference voltage (PERI_LDO.LDO18_VREF_SEL[4:1]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vref 4-bit voltage code (must be <= 0xF).
 */
static inline void ll_pmuc_peri_ldo_set_ldo18_vref(PMUC_TypeDef *PMUCx, uint32_t vref)
{
	MODIFY_REG(PMUCx->PERI_LDO, PMUC_PERI_LDO_LDO18_VREF_SEL,
		   MAKE_REG_VAL(vref, PMUC_PERI_LDO_LDO18_VREF_SEL_Msk, PMUC_PERI_LDO_LDO18_VREF_SEL_Pos));
}

/**
 * @brief Set PERI VDD33 LDO2 output voltage (PERI_LDO.VDD33_LDO2_SET_VOUT[12:9]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vout 4-bit voltage code (must be <= 0xF).
 */
static inline void ll_pmuc_peri_ldo_set_vdd33_ldo2_vout(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->PERI_LDO, PMUC_PERI_LDO_VDD33_LDO2_SET_VOUT,
		   MAKE_REG_VAL(vout, PMUC_PERI_LDO_VDD33_LDO2_SET_VOUT_Msk, PMUC_PERI_LDO_VDD33_LDO2_SET_VOUT_Pos));
}

/**
 * @brief Set PERI VDD33 LDO3 output voltage (PERI_LDO.VDD33_LDO3_SET_VOUT[20:17]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vout 4-bit voltage code (must be <= 0xF).
 */
static inline void ll_pmuc_peri_ldo_set_vdd33_ldo3_vout(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->PERI_LDO, PMUC_PERI_LDO_VDD33_LDO3_SET_VOUT,
		   MAKE_REG_VAL(vout, PMUC_PERI_LDO_VDD33_LDO3_SET_VOUT_Msk, PMUC_PERI_LDO_VDD33_LDO3_SET_VOUT_Pos));
}

/**
 * @brief Enable a PERI LDO (PERI_LDO): clear @p pd_mask and set @p en_mask.
 * @param[in] PMUCx   PMUC instance pointer.
 * @param[in] en_mask Enable bit mask of the target LDO.
 * @param[in] pd_mask Power-down bit mask of the target LDO.
 */
static inline void ll_pmuc_peri_ldo_enable(PMUC_TypeDef *PMUCx, uint32_t en_mask,
					   uint32_t pd_mask)
{
	MODIFY_REG(PMUCx->PERI_LDO, pd_mask | en_mask, en_mask);
}

/**
 * @brief Disable a PERI LDO (PERI_LDO): clear @p en_mask and set @p pd_mask.
 * @param[in] PMUCx   PMUC instance pointer.
 * @param[in] en_mask Enable bit mask of the target LDO.
 * @param[in] pd_mask Power-down bit mask of the target LDO.
 */
static inline void ll_pmuc_peri_ldo_disable(PMUC_TypeDef *PMUCx, uint32_t en_mask,
					    uint32_t pd_mask)
{
	MODIFY_REG(PMUCx->PERI_LDO, pd_mask | en_mask, pd_mask);
}

/*==============================================================================
 * Power Switches
 *============================================================================*/

/** @defgroup LL_PMUC_SWR Power Switch Source Select */
/** @{ */
/** PSW[1:0]: use the RET_LDO supply. */
#define LL_PMUC_SWR_SOURCE_RET_LDO    0U
/** HPSYS_SWR PSW[1:0]: use the HPSYS_LDO supply. */
#define LL_PMUC_SWR_SOURCE_HPSYS_LDO  1U
/** LPSYS_SWR PSW[1:0]: use the LPSYS_LDO supply. */
#define LL_PMUC_SWR_SOURCE_LPSYS_LDO  1U
/** @} */

/**
 * @brief Select the HPSYS power switch source (HPSYS_SWR.PSW[1:0]).
 * @note HPSYS_SWR has no enable bit; PSW selects the supply feeding the HPSYS
 *       power domain (see reference manual page 49).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] source Power source, see @ref LL_PMUC_SWR_SOURCE_*.
 */
static inline void ll_pmuc_swr_hpsys_set_power_source(PMUC_TypeDef *PMUCx, uint32_t source)
{
	MODIFY_REG(PMUCx->HPSYS_SWR, PMUC_HPSYS_SWR_PSW,
		   MAKE_REG_VAL(source, PMUC_HPSYS_SWR_PSW_Msk, PMUC_HPSYS_SWR_PSW_Pos));
}

/**
 * @brief Check the HPSYS power switch ready status (HPSYS_SWR.RDY).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the switch is ready.
 */
static inline uint32_t ll_pmuc_swr_hpsys_is_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->HPSYS_SWR, PMUC_HPSYS_SWR_RDY);
}

/**
 * @brief Select the LPSYS power switch source (LPSYS_SWR.PSW[1:0]).
 * @note LPSYS_SWR has no enable bit; PSW selects the supply feeding the LPSYS
 *       power domain (see reference manual page 49).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] source Power source, see @ref LL_PMUC_SWR_SOURCE_*.
 */
static inline void ll_pmuc_swr_lpsys_set_power_source(PMUC_TypeDef *PMUCx, uint32_t source)
{
	MODIFY_REG(PMUCx->LPSYS_SWR, PMUC_LPSYS_SWR_PSW,
		   MAKE_REG_VAL(source, PMUC_LPSYS_SWR_PSW_Msk, PMUC_LPSYS_SWR_PSW_Pos));
}

/**
 * @brief Check the LPSYS power switch ready status (LPSYS_SWR.RDY).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the switch is ready.
 */
static inline uint32_t ll_pmuc_swr_lpsys_is_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LPSYS_SWR, PMUC_LPSYS_SWR_RDY);
}

/*==============================================================================
 * Charger Control
 *============================================================================*/

/**
 * @brief Enable the charger (CHG_CR1.EN).
 * @note CHG_CR1.EN is only effective when CHG_CR3.FORCE_CTRL is set
 *       (software-controlled mode), see reference manual page 47.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_charger_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CHG_CR1, PMUC_CHG_CR1_EN);
}

/**
 * @brief Disable the charger (CHG_CR1.EN).
 * @note See @ref ll_pmuc_charger_enable for the CHG_CR3.FORCE_CTRL requirement.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_charger_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CHG_CR1, PMUC_CHG_CR1_EN);
}

/**
 * @brief Set the charger constant-current target (CHG_CR1.CC_ICTRL[7:2]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] ictrl 6-bit current code (must be <= 0x3F).
 */
static inline void ll_pmuc_charger_set_cc_current(PMUC_TypeDef *PMUCx, uint32_t ictrl)
{
	MODIFY_REG(PMUCx->CHG_CR1, PMUC_CHG_CR1_CC_ICTRL,
		   MAKE_REG_VAL(ictrl, PMUC_CHG_CR1_CC_ICTRL_Msk, PMUC_CHG_CR1_CC_ICTRL_Pos));
}

/**
 * @brief Set the charger constant-voltage target (CHG_CR1.CV_VCTRL[31:26]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vctrl 6-bit voltage code (must be <= 0x3F).
 */
static inline void ll_pmuc_charger_set_cv_voltage(PMUC_TypeDef *PMUCx, uint32_t vctrl)
{
	MODIFY_REG(PMUCx->CHG_CR1, PMUC_CHG_CR1_CV_VCTRL,
		   MAKE_REG_VAL(vctrl, PMUC_CHG_CR1_CV_VCTRL_Msk, PMUC_CHG_CR1_CV_VCTRL_Pos));
}

/*==============================================================================
 * HXT48 Oscillator
 *============================================================================*/

/**
 * @brief Enable the HXT48 oscillator (HXT_CR1.EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HXT_CR1, PMUC_HXT_CR1_EN);
}

/**
 * @brief Disable the HXT48 oscillator (HXT_CR1.EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HXT_CR1, PMUC_HXT_CR1_EN);
}

/**
 * @brief Enable the HXT48 digital clock output buffer (HXT_CR1.BUF_DIG_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_enable_clock_out(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HXT_CR1, PMUC_HXT_CR1_BUF_DIG_EN);
}

/**
 * @brief Disable the HXT48 digital clock output buffer (HXT_CR1.BUF_DIG_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_disable_clock_out(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HXT_CR1, PMUC_HXT_CR1_BUF_DIG_EN);
}

/**
 * @brief Enable the HXT48 audio buffer (HXT_CR1.BUF_AUD_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_enable_audio_buf(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HXT_CR1, PMUC_HXT_CR1_BUF_AUD_EN);
}

/**
 * @brief Disable the HXT48 audio buffer (HXT_CR1.BUF_AUD_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_disable_audio_buf(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HXT_CR1, PMUC_HXT_CR1_BUF_AUD_EN);
}

/**
 * @brief Set the HXT48 digital buffer drive strength (HXT_CR1.BUF_DIG_STR[4:3]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] str 2-bit strength code (must be <= 0x3).
 */
static inline void ll_pmuc_hxt48_set_digital_buf_strength(PMUC_TypeDef *PMUCx, uint32_t str)
{
	MODIFY_REG(PMUCx->HXT_CR1, PMUC_HXT_CR1_BUF_DIG_STR,
		   MAKE_REG_VAL(str, PMUC_HXT_CR1_BUF_DIG_STR_Msk, PMUC_HXT_CR1_BUF_DIG_STR_Pos));
}

/**
 * @brief Set the HXT48 audio buffer drive strength (HXT_CR1.BUF_AUD_STR[10:9]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] str 2-bit strength code (must be <= 0x3).
 */
static inline void ll_pmuc_hxt48_set_audio_buf_strength(PMUC_TypeDef *PMUCx, uint32_t str)
{
	MODIFY_REG(PMUCx->HXT_CR1, PMUC_HXT_CR1_BUF_AUD_STR,
		   MAKE_REG_VAL(str, PMUC_HXT_CR1_BUF_AUD_STR_Msk, PMUC_HXT_CR1_BUF_AUD_STR_Pos));
}

/**
 * @brief Enable the HXT48 DLL buffer (HXT_CR1.BUF_DLL_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_enable_dll_buf(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HXT_CR1, PMUC_HXT_CR1_BUF_DLL_EN);
}

/**
 * @brief Disable the HXT48 DLL buffer (HXT_CR1.BUF_DLL_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_disable_dll_buf(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HXT_CR1, PMUC_HXT_CR1_BUF_DLL_EN);
}

/*==============================================================================
 * HRC48 Oscillator
 *============================================================================*/

/**
 * @brief Set the HRC48 frequency trim (HRC_CR.FREQ_TRIM[14:5], 10 bits).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] trim 10-bit frequency trim code (must be <= 0x3FF).
 */
static inline void ll_pmuc_hrc48_set_trim(PMUC_TypeDef *PMUCx, uint32_t trim)
{
	MODIFY_REG(PMUCx->HRC_CR, PMUC_HRC_CR_FREQ_TRIM,
		   MAKE_REG_VAL(trim, PMUC_HRC_CR_FREQ_TRIM_Msk, PMUC_HRC_CR_FREQ_TRIM_Pos));
}

/*==============================================================================
 * AON Bandgap / LDO
 *============================================================================*/

static inline void ll_pmuc_aon_bg_set_trim(PMUC_TypeDef *PMUCx, uint32_t trim, uint32_t step,
					   uint32_t polar)
{
	uint32_t val = MAKE_REG_VAL(trim, PMUC_AON_BG_BUF_VOS_TRIM_Msk, PMUC_AON_BG_BUF_VOS_TRIM_Pos) |
		       MAKE_REG_VAL(step, PMUC_AON_BG_BUF_VOS_STEP_Msk, PMUC_AON_BG_BUF_VOS_STEP_Pos) |
		       MAKE_REG_VAL(polar, PMUC_AON_BG_BUF_VOS_POLAR_Msk, PMUC_AON_BG_BUF_VOS_POLAR_Pos);
	MODIFY_REG(PMUCx->AON_BG,
		   PMUC_AON_BG_BUF_VOS_TRIM | PMUC_AON_BG_BUF_VOS_STEP | PMUC_AON_BG_BUF_VOS_POLAR,
		   val);
}

static inline void ll_pmuc_aon_ldo_set_vout(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_LDO_SET_VOUT,
		   MAKE_REG_VAL(vout, PMUC_AON_LDO_VBAT_LDO_SET_VOUT_Msk, PMUC_AON_LDO_VBAT_LDO_SET_VOUT_Pos));
}

/*==============================================================================
 * VRTC
 *============================================================================*/

static inline void ll_pmuc_vrtc_set_vbit(PMUC_TypeDef *PMUCx, uint32_t vbit)
{
	MODIFY_REG(PMUCx->VRTC_CR, PMUC_VRTC_CR_VRTC_VBIT,
		   MAKE_REG_VAL(vbit, PMUC_VRTC_CR_VRTC_VBIT_Msk, PMUC_VRTC_CR_VRTC_VBIT_Pos));
}

static inline void ll_pmuc_vrtc_enable_bor(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->VRTC_CR, PMUC_VRTC_CR_BOR_EN);
}

static inline void ll_pmuc_vrtc_disable_bor(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->VRTC_CR, PMUC_VRTC_CR_BOR_EN);
}

/*==============================================================================
 * Voltage Monitoring
 *============================================================================*/

/**
 * @brief Get the HPSYS LDO output voltage code (HPSYS_VOUT.VOUT[3:0]).
 * @param[in] PMUCx PMUC instance pointer.
 * @return 4-bit voltage code.
 */
static inline uint8_t ll_pmuc_get_hpsys_vout(PMUC_TypeDef *PMUCx)
{
	return (uint8_t)(READ_REG(PMUCx->HPSYS_VOUT) & PMUC_HPSYS_VOUT_VOUT_Msk);
}

/**
 * @brief Get the LPSYS LDO output voltage code (LPSYS_VOUT.VOUT[3:0]).
 * @param[in] PMUCx PMUC instance pointer.
 * @return 4-bit voltage code.
 */
static inline uint8_t ll_pmuc_get_lpsys_vout(PMUC_TypeDef *PMUCx)
{
	return (uint8_t)(READ_REG(PMUCx->LPSYS_VOUT) & PMUC_LPSYS_VOUT_VOUT_Msk);
}

/**
 * @brief Get the BUCK output voltage code (BUCK_VOUT.VOUT[3:0]).
 * @param[in] PMUCx PMUC instance pointer.
 * @return 4-bit voltage code.
 */
static inline uint8_t ll_pmuc_get_buck_vout(PMUC_TypeDef *PMUCx)
{
	return (uint8_t)(READ_REG(PMUCx->BUCK_VOUT) & PMUC_BUCK_VOUT_VOUT_Msk);
}

/*==============================================================================
 * Counters
 *============================================================================*/

/**
 * @brief Set the wakeup pin debounce counts (WKUP_CNT).
 * @note The value is packed as PIN0_CNT[15:0] | (PIN1_CNT[15:0] << 16),
 *       i.e. cnt = (pin1_cnt << 16) | pin0_cnt.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] cnt Packed 16-bit debounce counts for PIN0 and PIN1.
 */
static inline void ll_pmuc_set_wkup_count(PMUC_TypeDef *PMUCx, uint32_t cnt)
{
	WRITE_REG(PMUCx->WKUP_CNT, cnt);
}

/**
 * @brief Set the power-key reset debounce count (PWRKEY_CNT.RST_CNT[19:4]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] cnt 16-bit debounce count (must be <= 0xFFFF).
 */
static inline void ll_pmuc_set_pwrkey_count(PMUC_TypeDef *PMUCx, uint32_t cnt)
{
	WRITE_REG(PMUCx->PWRKEY_CNT, MAKE_REG_VAL(cnt, PMUC_PWRKEY_CNT_RST_CNT_Msk, PMUC_PWRKEY_CNT_RST_CNT_Pos));
}

#ifdef __cplusplus
}
#endif

#endif /* __LL_PMUC_H */
