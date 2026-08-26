/*
 * SPDX-FileCopyrightText: 2026 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LL_PMUC_H
#define __LL_PMUC_H

#include <stdint.h>
#include "pmuc.h"
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
/* SF32LB57x removed CR.SEL_LPCLK; LRC32 select API is not available. */
/** @} */

/** @defgroup LL_PMUC_WKUP LL PMUC Wakeup Source Mask */
/** @{ */
#define LL_PMUC_WKUP_RTC    PMUC_WER_RTC
#define LL_PMUC_WKUP_WDT1   PMUC_WER_IWDT
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
	(PMUC_WER_RTC | PMUC_WER_IWDT | PMUC_WER_LOWBAT | PMUC_WER_CHG | PMUC_WER_PWRKEY)
/** @} */

/**
 * @brief PMUC VRET configuration.
 */
typedef struct {
	uint32_t dly;  /**< VRET startup delay for VRET_CR.DLY field. */
	uint32_t vbit; /**< VRET output setting for VRET_CR.VBIT field. */
	uint32_t trim; /**< VRET trim setting for VRET_CR.TRIM field. */
} ll_pmuc_vret_config_t;

/**
 * @brief Set CR.LPSYSRST.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_set_lpsysrst(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CR, PMUC_CR_LPSYSRST);
}

/**
 * @brief Clear CR.LPSYSRST.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_lpsysrst(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CR, PMUC_CR_LPSYSRST);
}

/**
 * @brief Get CR.LPSYSRST.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when set.
 */
static inline uint32_t ll_pmuc_is_lpsysrst_set(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->CR, PMUC_CR_LPSYSRST);
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
 * @brief Set CR.SEL_RTC.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_set_sel_rtc(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CR, PMUC_CR_SEL_RTC);
}

/**
 * @brief Clear CR.SEL_RTC.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_sel_rtc(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CR, PMUC_CR_SEL_RTC);
}

/**
 * @brief Get CR.SEL_RTC.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when set.
 */
static inline uint32_t ll_pmuc_is_sel_rtc_set(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->CR, PMUC_CR_SEL_RTC);
}

/**
 * @brief Set CR.SEL_WDT.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_set_sel_wdt(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CR, PMUC_CR_SEL_WDT);
}

/**
 * @brief Clear CR.SEL_WDT.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_sel_wdt(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CR, PMUC_CR_SEL_WDT);
}

/**
 * @brief Get CR.SEL_WDT.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when set.
 */
static inline uint32_t ll_pmuc_is_sel_wdt_set(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->CR, PMUC_CR_SEL_WDT);
}

/**
 * @brief Enable PMUC wakeup sources.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] src_mask Wakeup source mask, use @ref LL_PMUC_WKUP_RTC,
 * @ref LL_PMUC_WKUP_WDT1, @ref LL_PMUC_WKUP_LOWBAT, @ref LL_PMUC_WKUP_CHG.
 */
static inline void ll_pmuc_enable_wakeup_source(PMUC_TypeDef *PMUCx, uint32_t src_mask)
{
	SET_BIT(PMUCx->WER, (src_mask & LL_PMUC_WER_MASK));
}

/**
 * @brief Disable PMUC wakeup sources.
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] src_mask Wakeup source mask, use @ref LL_PMUC_WKUP_RTC,
 * @ref LL_PMUC_WKUP_WDT1, @ref LL_PMUC_WKUP_LOWBAT, @ref LL_PMUC_WKUP_CHG.
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
 * @brief Read PMUC wakeup status register.
 * @param[in] PMUCx PMUC instance pointer.
 * @return WSR register value.
 */
static inline uint32_t ll_pmuc_get_wakeup_status(PMUC_TypeDef *PMUCx)
{
	return READ_REG(PMUCx->WSR);
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
 * @brief Check LOWBAT wakeup status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.LOWBAT is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_lowbat(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_LOWBAT);
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
 * @brief Check IWDT status flag.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when WSR.IWDT is set.
 */
static inline uint32_t ll_pmuc_is_active_flag_wsr_iwdt(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->WSR, PMUC_WSR_IWDT);
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
 * @brief Clear PWRKEY status flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_pwrkey(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_PWRKEY);
}

/**
 * @brief Clear IWDT reset flag.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_clear_flag_wcr_iwdtrst(PMUC_TypeDef *PMUCx)
{
	WRITE_REG(PMUCx->WCR, PMUC_WCR_IWDTRST);
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
 * @brief Check LRC10 ready status.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when LRC10 is ready.
 */
static inline uint32_t ll_pmuc_is_lrc10_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LRC10_CR, PMUC_LRC10_CR_RDY);
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
 * @brief Check LRC32 ready status.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when LRC32 is ready.
 */
static inline uint32_t ll_pmuc_is_lrc32_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LRC32_CR, PMUC_LRC32_CR_RDY);
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
 * @brief Check LXT32 ready status.
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when LXT32 is ready.
 */
static inline uint32_t ll_pmuc_is_lxt32_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LXT_CR, PMUC_LXT_CR_RDY);
}

/**
 * @brief Configure and enable the LXT32 oscillator (LXT_CR) in one write.
 * @param[in] PMUCx   PMUC instance pointer.
 * @param[in] bm      Bias mode value (BM field).
 * @param[in] amp_bm  Amplifier bias value (AMP_BM field).
 * @param[in] cap_sel Capacitor select value (CAP_SEL field).
 * @param[in] rsn     Reset-while-standby enable (1 bit).
 */
static inline void ll_pmuc_config_lxt32(PMUC_TypeDef *PMUCx, uint32_t bm,
					uint32_t amp_bm, uint32_t cap_sel,
					uint32_t rsn)
{
	uint32_t value;

	value = MAKE_REG_VAL(bm, PMUC_LXT_CR_BM_Msk, PMUC_LXT_CR_BM_Pos) |
		MAKE_REG_VAL(amp_bm, PMUC_LXT_CR_AMP_BM_Msk, PMUC_LXT_CR_AMP_BM_Pos) |
		MAKE_REG_VAL(cap_sel, PMUC_LXT_CR_CAP_SEL_Msk, PMUC_LXT_CR_CAP_SEL_Pos) |
		(rsn ? PMUC_LXT_CR_RSN : 0U) | PMUC_LXT_CR_EN;
	MODIFY_REG(PMUCx->LXT_CR,
		   PMUC_LXT_CR_EN | PMUC_LXT_CR_RSN | PMUC_LXT_CR_CAP_SEL |
			   PMUC_LXT_CR_BM_Msk | PMUC_LXT_CR_AMP_BM_Msk,
		   value);
}

/**
 * @brief Disable the LXT32 oscillator clearing both EN and RSN (LXT_CR).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_disable_lxt32_rsn(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->LXT_CR, PMUC_LXT_CR_EN | PMUC_LXT_CR_RSN);
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

static inline void ll_pmuc_buck_set_vout_low(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->BUCK_CR2, PMUC_BUCK_CR2_SET_VOUT_L,
		   MAKE_REG_VAL(vout, PMUC_BUCK_CR2_SET_VOUT_L_Msk, PMUC_BUCK_CR2_SET_VOUT_L_Pos));
}

static inline void ll_pmuc_buck_set_vout_mid(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->BUCK_CR2, PMUC_BUCK_CR2_SET_VOUT_M,
		   MAKE_REG_VAL(vout, PMUC_BUCK_CR2_SET_VOUT_M_Msk, PMUC_BUCK_CR2_SET_VOUT_M_Pos));
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
 * @brief Set the HPSYS output voltage code (HPSYS_VOUT.VOUT[3:0]).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vout 4-bit voltage code (must be <= 0xF).
 */
static inline void ll_pmuc_set_hpsys_vout(PMUC_TypeDef *PMUCx, uint32_t vout)
{
        MODIFY_REG(PMUCx->HPSYS_VOUT, PMUC_HPSYS_VOUT_VOUT,
                   MAKE_REG_VAL(vout, PMUC_HPSYS_VOUT_VOUT_Msk, PMUC_HPSYS_VOUT_VOUT_Pos));
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


/**
 * @brief Set the VRTC reserved field (VRTC_CR.RESERVE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] value Reserved field value (7 bits).
 */
static inline void ll_pmuc_vrtc_set_reserve(PMUC_TypeDef *PMUCx, uint32_t value)
{
	MODIFY_REG(PMUCx->VRTC_CR, PMUC_VRTC_CR_RESERVE,
		   MAKE_REG_VAL(value, PMUC_VRTC_CR_RESERVE_Msk, PMUC_VRTC_CR_RESERVE_Pos));
}

static inline void ll_pmuc_vrtc_set_trim_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_VRTC_CR_BOR_VT_TRIM | PMUC_VRTC_CR_VRTC_TRIM;

	MODIFY_REG(PMUCx->VRTC_CR, mask, value & mask);
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
 * VRTC
 *============================================================================*/

static inline void ll_pmuc_vrtc_set_vbit(PMUC_TypeDef *PMUCx, uint32_t vbit)
{
	MODIFY_REG(PMUCx->VRTC_CR, PMUC_VRTC_CR_VRTC_VBIT,
		   MAKE_REG_VAL(vbit, PMUC_VRTC_CR_VRTC_VBIT_Msk, PMUC_VRTC_CR_VRTC_VBIT_Pos));
}

static inline uint32_t ll_pmuc_vret_is_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->VRET_CR, PMUC_VRET_CR_RDY);
}

static inline void ll_pmuc_vret_set_control(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_VRET_CR_BM | PMUC_VRET_CR_EN;

	MODIFY_REG(PMUCx->VRET_CR, mask, value & mask);
}

/**
 * @brief Set the LRC10 LDO trim (LRC10_CR.LDO_TRIM).
 * @param[in] PMUCx  PMUC instance pointer.
 * @param[in] trim   LDO trim code.
 */
static inline void ll_pmuc_lrc10_set_ldo_trim(PMUC_TypeDef *PMUCx, uint32_t trim)
{
	MODIFY_REG(PMUCx->LRC10_CR, PMUC_LRC10_CR_LDO_TRIM,
		   MAKE_REG_VAL(trim, PMUC_LRC10_CR_LDO_TRIM_Msk, PMUC_LRC10_CR_LDO_TRIM_Pos));
}

/**
 * @brief Set the LRC10 LDO output (LRC10_CR.LDO_VBIT).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vbit LDO output code.
 */
static inline void ll_pmuc_lrc10_set_ldo_vbit(PMUC_TypeDef *PMUCx, uint32_t vbit)
{
	MODIFY_REG(PMUCx->LRC10_CR, PMUC_LRC10_CR_LDO_VBIT,
		   MAKE_REG_VAL(vbit, PMUC_LRC10_CR_LDO_VBIT_Msk, PMUC_LRC10_CR_LDO_VBIT_Pos));
}

/**
 * @brief Enable the LRC10 LDO (LRC10_CR.LDO_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_lrc10_ldo_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->LRC10_CR, PMUC_LRC10_CR_LDO_EN);
}

/**
 * @brief Disable the LRC10 LDO (LRC10_CR.LDO_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_lrc10_ldo_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->LRC10_CR, PMUC_LRC10_CR_LDO_EN);
}

static inline void ll_pmuc_lrc10_set_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_LRC10_CR_REFRES | PMUC_LRC10_CR_CHGCAP |
			      PMUC_LRC10_CR_CHGCRT | PMUC_LRC10_CR_CMPBM2 |
			      PMUC_LRC10_CR_CMPBM1;

	MODIFY_REG(PMUCx->LRC10_CR, mask, value & mask);
}

static inline void ll_pmuc_lrc32_set_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_LRC32_CR_RSEL | PMUC_LRC32_CR_CHGCRT |
			      PMUC_LRC32_CR_CMPBM2 | PMUC_LRC32_CR_CMPBM1;

	MODIFY_REG(PMUCx->LRC32_CR, mask, value & mask);
}

static inline void ll_pmuc_lxt32_set_analog_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_LXT_CR_EXT_EN | PMUC_LXT_CR_BMSTART |
			      PMUC_LXT_CR_BMSEL | PMUC_LXT_CR_AMPCTRL_ENB;

	MODIFY_REG(PMUCx->LXT_CR, mask, value & mask);
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

/**
 * @brief Check the AON VBUS ready flag (AON_LDO.VBUS_RDY).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when ready.
 */
static inline uint32_t ll_pmuc_aon_ldo_is_vbus_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->AON_LDO, PMUC_AON_LDO_VBUS_RDY) ? 1UL : 0UL;
}

/**
 * @brief Set the AON VBUS threshold N (AON_LDO.VBUS_SET_VTHN).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vthn  Threshold code.
 */
static inline void ll_pmuc_aon_ldo_set_vbus_vthn(PMUC_TypeDef *PMUCx, uint32_t vthn)
{
	MODIFY_REG(PMUCx->AON_LDO, PMUC_AON_LDO_VBUS_SET_VTHN,
		   MAKE_REG_VAL(vthn, PMUC_AON_LDO_VBUS_SET_VTHN_Msk, PMUC_AON_LDO_VBUS_SET_VTHN_Pos));
}

/**
 * @brief Set the AON VBUS threshold P (AON_LDO.VBUS_SET_VTHP).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vthp  Threshold code.
 */
static inline void ll_pmuc_aon_ldo_set_vbus_vthp(PMUC_TypeDef *PMUCx, uint32_t vthp)
{
	MODIFY_REG(PMUCx->AON_LDO, PMUC_AON_LDO_VBUS_SET_VTHP,
		   MAKE_REG_VAL(vthp, PMUC_AON_LDO_VBUS_SET_VTHP_Msk, PMUC_AON_LDO_VBUS_SET_VTHP_Pos));
}

/**
 * @brief Check the AON VBAT LDO ready flag (AON_LDO.VBAT_RDY).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when ready.
 */
static inline uint32_t ll_pmuc_aon_ldo_is_vbat_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_RDY) ? 1UL : 0UL;
}

/**
 * @brief Set the AON VBAT threshold N (AON_LDO.VBAT_SET_VTHN).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vthn  Threshold code.
 */
static inline void ll_pmuc_aon_ldo_set_vbat_vthn(PMUC_TypeDef *PMUCx, uint32_t vthn)
{
	MODIFY_REG(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_SET_VTHN,
		   MAKE_REG_VAL(vthn, PMUC_AON_LDO_VBAT_SET_VTHN_Msk, PMUC_AON_LDO_VBAT_SET_VTHN_Pos));
}

/**
 * @brief Set the AON VBAT threshold P (AON_LDO.VBAT_SET_VTHP).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vthp  Threshold code.
 */
static inline void ll_pmuc_aon_ldo_set_vbat_vthp(PMUC_TypeDef *PMUCx, uint32_t vthp)
{
	MODIFY_REG(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_SET_VTHP,
		   MAKE_REG_VAL(vthp, PMUC_AON_LDO_VBAT_SET_VTHP_Msk, PMUC_AON_LDO_VBAT_SET_VTHP_Pos));
}

/**
 * @brief Set the AON VBAT LDO switch-mode (AON_LDO.VBAT_LDO_SWMODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Switch-mode code.
 */
static inline void ll_pmuc_aon_ldo_set_vbat_swmode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_LDO_SWMODE,
		   MAKE_REG_VAL(mode, PMUC_AON_LDO_VBAT_LDO_SWMODE_Msk, PMUC_AON_LDO_VBAT_LDO_SWMODE_Pos));
}

/**
 * @brief Enable the AON VBAT LDO switch-mode control (AON_LDO.VBAT_LDO_EN_SWMODE).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_aon_ldo_vbat_swmode_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_LDO_EN_SWMODE);
}

/**
 * @brief Disable the AON VBAT LDO switch-mode control (AON_LDO.VBAT_LDO_EN_SWMODE = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_aon_ldo_vbat_swmode_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_LDO_EN_SWMODE);
}

/**
 * @brief Enable the AON VBAT LDO soft-start (AON_LDO.VBAT_LDO_EN_SS).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_aon_ldo_vbat_ss_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_LDO_EN_SS);
}

/**
 * @brief Disable the AON VBAT LDO soft-start (AON_LDO.VBAT_LDO_EN_SS = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_aon_ldo_vbat_ss_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_LDO_EN_SS);
}

/* SF32LB57x removed AON_LDO.VBAT_POR_TH; the POR-threshold API is not available. */

static inline void ll_pmuc_aon_ldo_set_vout(PMUC_TypeDef *PMUCx, uint32_t vout)
{
	MODIFY_REG(PMUCx->AON_LDO, PMUC_AON_LDO_VBAT_LDO_SET_VOUT,
		   MAKE_REG_VAL(vout, PMUC_AON_LDO_VBAT_LDO_SET_VOUT_Msk, PMUC_AON_LDO_VBAT_LDO_SET_VOUT_Pos));
}

static inline void ll_pmuc_buck_set_analog_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_BUCK_CR1_BG_BUF_VOS_POLAR |
			      PMUC_BUCK_CR1_BG_BUF_VOS_STEP |
			      PMUC_BUCK_CR1_BG_BUF_VOS_TRIM |
			      PMUC_BUCK_CR1_UVLO_X_BIAS | PMUC_BUCK_CR1_ZCD_AON |
			      PMUC_BUCK_CR1_OCP_AON | PMUC_BUCK_CR1_SEL_LX22 |
			      PMUC_BUCK_CR1_SEL_IOCP_HI | PMUC_BUCK_CR1_IOCP_TUNE |
			      PMUC_BUCK_CR1_COMP_IDYN_TUNE |
			      PMUC_BUCK_CR1_COMP_IQ_TUNE | PMUC_BUCK_CR1_COMP_BM_AHI |
			      PMUC_BUCK_CR1_COT_CTUNE | PMUC_BUCK_CR1_MOT_CTUNE;

	MODIFY_REG(PMUCx->BUCK_CR1, mask, value & mask);
}

/**
 * @brief Enable BUCK BYPASS_UVLO bypass (BUCK_CR1.BYPASS_UVLO).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_buck_bypass_uvlo_set(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_BYPASS_UVLO);
}

/**
 * @brief Disable BUCK BYPASS_UVLO bypass (BUCK_CR1.BYPASS_UVLO = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_buck_bypass_uvlo_clear(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_BYPASS_UVLO);
}

/**
 * @brief Enable BUCK BYPASS_OCP bypass (BUCK_CR1.BYPASS_OCP).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_buck_bypass_ocp_set(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_BYPASS_OCP);
}

/**
 * @brief Disable BUCK BYPASS_OCP bypass (BUCK_CR1.BYPASS_OCP = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_buck_bypass_ocp_clear(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_BYPASS_OCP);
}

/**
 * @brief Enable BUCK BYPASS_PG bypass (BUCK_CR1.BYPASS_PG).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_buck_bypass_pg_set(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_BYPASS_PG);
}

/**
 * @brief Disable BUCK BYPASS_PG bypass (BUCK_CR1.BYPASS_PG = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_buck_bypass_pg_clear(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->BUCK_CR1, PMUC_BUCK_CR1_BYPASS_PG);
}

static inline void ll_pmuc_buck_set_transition_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_BUCK_CR2_TDIS | PMUC_BUCK_CR2_FORCE_RDY |
			      PMUC_BUCK_CR2_L2M_CNT |
			      PMUC_BUCK_CR2_L2H_CNT | PMUC_BUCK_CR2_M2H_CNT |
			      PMUC_BUCK_CR2_L2M_EN | PMUC_BUCK_CR2_M2L_EN |
			      PMUC_BUCK_CR2_H2L_EN | PMUC_BUCK_CR2_H2M_EN;

	MODIFY_REG(PMUCx->BUCK_CR2, mask, value & mask);
}

/**
 * @brief Set the BUCK power-switch driver bias mode (BUCK_CR3.PSWDRV_BM).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] bm    Driver bias mode.
 */
static inline void ll_pmuc_buck_set_pswdrv_bm(PMUC_TypeDef *PMUCx, uint32_t bm)
{
	MODIFY_REG(PMUCx->BUCK_CR3, PMUC_BUCK_CR3_PSWDRV_BM,
		   MAKE_REG_VAL(bm, PMUC_BUCK_CR3_PSWDRV_BM_Msk, PMUC_BUCK_CR3_PSWDRV_BM_Pos));
}

/**
 * @brief Set the BUCK OCP bias mode (BUCK_CR3.OCP_BM).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] bm    OCP bias mode.
 */
static inline void ll_pmuc_buck_set_ocp_bm(PMUC_TypeDef *PMUCx, uint32_t bm)
{
	MODIFY_REG(PMUCx->BUCK_CR3, PMUC_BUCK_CR3_OCP_BM,
		   MAKE_REG_VAL(bm, PMUC_BUCK_CR3_OCP_BM_Msk, PMUC_BUCK_CR3_OCP_BM_Pos));
}

/**
 * @brief Enable BUCK reference tracking (BUCK_CR3.EN_REFTRK).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_buck_ref_tracking_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->BUCK_CR3, PMUC_BUCK_CR3_EN_REFTRK);
}

/**
 * @brief Disable BUCK reference tracking (BUCK_CR3.EN_REFTRK = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_buck_ref_tracking_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->BUCK_CR3, PMUC_BUCK_CR3_EN_REFTRK);
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

static inline void ll_pmuc_charger_set_cc_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_CHG_CR1_CC_RANGE | PMUC_CHG_CR1_CC_MN |
			      PMUC_CHG_CR1_CC_MP | PMUC_CHG_CR1_CC_VCTRL |
			      PMUC_CHG_CR1_LOOP_EN;

	MODIFY_REG(PMUCx->CHG_CR1, mask, value & mask);
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
 * @brief Set the charger VBAT range (CHG_CR2.VBAT_RANGE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] range VBAT range (4 bits).
 */
static inline void ll_pmuc_charger_set_vbat_range(PMUC_TypeDef *PMUCx, uint32_t range)
{
	MODIFY_REG(PMUCx->CHG_CR2, PMUC_CHG_CR2_VBAT_RANGE,
		   MAKE_REG_VAL(range, PMUC_CHG_CR2_VBAT_RANGE_Msk, PMUC_CHG_CR2_VBAT_RANGE_Pos));
}

static inline void ll_pmuc_charger_set_bg_voltage(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_CHG_CR2_RANGE_EOC | PMUC_CHG_CR2_BG_PROG_V1P2;

	MODIFY_REG(PMUCx->CHG_CR2, mask, value & mask);
}

/**
 * @brief Set the charger end-of-charge bias mode (CHG_CR2.BM_EOC).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] bm    EOC bias mode (3 bits).
 */
static inline void ll_pmuc_charger_set_bm_eoc(PMUC_TypeDef *PMUCx, uint32_t bm)
{
	MODIFY_REG(PMUCx->CHG_CR2, PMUC_CHG_CR2_BM_EOC,
		   MAKE_REG_VAL(bm, PMUC_CHG_CR2_BM_EOC_Msk, PMUC_CHG_CR2_BM_EOC_Pos));
}

/**
 * @brief Set the charger high voltage (CHG_CR2.HIGH_VCTRL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vctrl High voltage control (6 bits).
 */
static inline void ll_pmuc_charger_set_high_voltage(PMUC_TypeDef *PMUCx, uint32_t vctrl)
{
	MODIFY_REG(PMUCx->CHG_CR2, PMUC_CHG_CR2_HIGH_VCTRL,
		   MAKE_REG_VAL(vctrl, PMUC_CHG_CR2_HIGH_VCTRL_Msk, PMUC_CHG_CR2_HIGH_VCTRL_Pos));
}

/**
 * @brief Set the charger reprog voltage (CHG_CR2.REP_VCTRL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vctrl Reprogramming voltage control (6 bits).
 */
static inline void ll_pmuc_charger_set_reprog_voltage(PMUC_TypeDef *PMUCx, uint32_t vctrl)
{
	MODIFY_REG(PMUCx->CHG_CR2, PMUC_CHG_CR2_REP_VCTRL,
		   MAKE_REG_VAL(vctrl, PMUC_CHG_CR2_REP_VCTRL_Msk, PMUC_CHG_CR2_REP_VCTRL_Pos));
}

/**
 * @brief Set the charger precharge current (CHG_CR2.PRECC_ICTRL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] ictrl Precharge current control (6 bits).
 */
static inline void ll_pmuc_charger_set_precc_current(PMUC_TypeDef *PMUCx, uint32_t ictrl)
{
	MODIFY_REG(PMUCx->CHG_CR2, PMUC_CHG_CR2_PRECC_ICTRL,
		   MAKE_REG_VAL(ictrl, PMUC_CHG_CR2_PRECC_ICTRL_Msk, PMUC_CHG_CR2_PRECC_ICTRL_Pos));
}

/**
 * @brief Set the charger precharge current range (CHG_CR2.PRECC_RANGE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] range Precharge current range (2 bits).
 */
static inline void ll_pmuc_charger_set_precc_range(PMUC_TypeDef *PMUCx, uint32_t range)
{
	MODIFY_REG(PMUCx->CHG_CR2, PMUC_CHG_CR2_PRECC_RANGE,
		   MAKE_REG_VAL(range, PMUC_CHG_CR2_PRECC_RANGE_Msk, PMUC_CHG_CR2_PRECC_RANGE_Pos));
}

/**
 * @brief Force charger control (CHG_CR3.FORCE_CTRL).
 * @note When FORCE_CTRL is set, the charger settings are controlled by the
 *       register fields instead of the automatic state machine.
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_charger_force_ctrl_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CHG_CR3, PMUC_CHG_CR3_FORCE_CTRL);
}

/**
 * @brief Release charger control to the state machine (CHG_CR3.FORCE_CTRL = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_charger_force_ctrl_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CHG_CR3, PMUC_CHG_CR3_FORCE_CTRL);
}

/**
 * @brief Force the charger reset (CHG_CR3.FORCE_RST).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_charger_force_reset_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CHG_CR3, PMUC_CHG_CR3_FORCE_RST);
}

/**
 * @brief Release the charger force reset (CHG_CR3.FORCE_RST = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_charger_force_reset_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CHG_CR3, PMUC_CHG_CR3_FORCE_RST);
}

/**
 * @brief Set the charger detection delay 2 (CHG_CR3.DLY2).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] dly   Delay value (5 bits).
 */
static inline void ll_pmuc_charger_set_dly2(PMUC_TypeDef *PMUCx, uint32_t dly)
{
	MODIFY_REG(PMUCx->CHG_CR3, PMUC_CHG_CR3_DLY2,
		   MAKE_REG_VAL(dly, PMUC_CHG_CR3_DLY2_Msk, PMUC_CHG_CR3_DLY2_Pos));
}

/**
 * @brief Set the charger detection delay 1 (CHG_CR3.DLY1).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] dly   Delay value (6 bits).
 */
static inline void ll_pmuc_charger_set_dly1(PMUC_TypeDef *PMUCx, uint32_t dly)
{
	MODIFY_REG(PMUCx->CHG_CR3, PMUC_CHG_CR3_DLY1,
		   MAKE_REG_VAL(dly, PMUC_CHG_CR3_DLY1_Msk, PMUC_CHG_CR3_DLY1_Pos));
}

/**
 * @brief Configure the charger interrupt mode bits (CHG_CR4.IM_*).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mask  ORed PMUC_CHG_CR4_IM_* masks (0 = high level, 1 = low level,
 *                  2 = pos edge, 3 = neg edge).
 */
static inline void ll_pmuc_charger_config_irq_mode(PMUC_TypeDef *PMUCx, uint32_t mask)
{
	MODIFY_REG(PMUCx->CHG_CR4, PMUC_CHG_CR4_IM_VBUS_RDY | PMUC_CHG_CR4_IM_VBAT_HIGH |
		   PMUC_CHG_CR4_IM_ABOVE_REP | PMUC_CHG_CR4_IM_ABOVE_CC |
		   PMUC_CHG_CR4_IM_CC_MODE | PMUC_CHG_CR4_IM_CV_MODE |
		   PMUC_CHG_CR4_IM_EOC_MODE,
		   mask);
}

/**
 * @brief Configure the charger interrupt enable bits (CHG_CR4.IE_*).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mask  ORed PMUC_CHG_CR4_IE_* masks.
 */
static inline void ll_pmuc_charger_config_irq_enable(PMUC_TypeDef *PMUCx, uint32_t mask)
{
	MODIFY_REG(PMUCx->CHG_CR4, PMUC_CHG_CR4_IE_VBUS_RDY | PMUC_CHG_CR4_IE_VBAT_HIGH |
		   PMUC_CHG_CR4_IE_ABOVE_REP | PMUC_CHG_CR4_IE_ABOVE_CC |
		   PMUC_CHG_CR4_IE_CC_MODE | PMUC_CHG_CR4_IE_CV_MODE |
		   PMUC_CHG_CR4_IE_EOC_MODE | PMUC_CHG_CR4_IE_EOC,
		   mask);
}

/**
 * @brief Get the charger interrupt status (CHG_CR5.IS_*).
 * @param[in] PMUCx PMUC instance pointer.
 * @return ORed PMUC_CHG_CR5_IS_* flags.
 */
static inline uint32_t ll_pmuc_charger_get_irq_status(PMUC_TypeDef *PMUCx)
{
	return READ_REG(PMUCx->CHG_CR5) & (PMUC_CHG_CR5_IS_VBUS_RDY | PMUC_CHG_CR5_IS_VBAT_HIGH |
		PMUC_CHG_CR5_IS_ABOVE_REP | PMUC_CHG_CR5_IS_ABOVE_CC |
		PMUC_CHG_CR5_IS_CC_MODE | PMUC_CHG_CR5_IS_CV_MODE |
		PMUC_CHG_CR5_IS_EOC_MODE | PMUC_CHG_CR5_IS_EOC);
}

/**
 * @brief Clear the charger interrupt flags (CHG_CR5.IC_*, write 1 to clear).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mask  ORed PMUC_CHG_CR5_IC_* masks.
 */
static inline void ll_pmuc_charger_clear_irq(PMUC_TypeDef *PMUCx, uint32_t mask)
{
	const uint32_t valid_mask = PMUC_CHG_CR5_IC_EOC |
					PMUC_CHG_CR5_IC_EOC_MODE |
					PMUC_CHG_CR5_IC_CV_MODE |
					PMUC_CHG_CR5_IC_CC_MODE |
					PMUC_CHG_CR5_IC_ABOVE_CC |
					PMUC_CHG_CR5_IC_ABOVE_REP |
					PMUC_CHG_CR5_IC_VBAT_HIGH |
					PMUC_CHG_CR5_IC_VBUS_RDY;

	WRITE_REG(PMUCx->CHG_CR5, mask & valid_mask);
}

/**
 * @brief Get the charger status (CHG_SR).
 * @param[in] PMUCx PMUC instance pointer.
 * @return ORed PMUC_CHG_SR_* flags (VBUS_RDY_OUT, VBAT_HIGH_OUT, ... CHG_STATE).
 */
static inline uint32_t ll_pmuc_charger_get_status(PMUC_TypeDef *PMUCx)
{
	const uint32_t status_mask = PMUC_CHG_SR_CHG_STATE |
				     PMUC_CHG_SR_EOC_MODE | PMUC_CHG_SR_CV_MODE |
				     PMUC_CHG_SR_CC_MODE |
				     PMUC_CHG_SR_VBAT_ABOVE_CC_OUT |
				     PMUC_CHG_SR_VBAT_ABOVE_REP_OUT |
				     PMUC_CHG_SR_VBAT_HIGH_OUT |
				     PMUC_CHG_SR_VBUS_RDY_OUT;

	return READ_REG(PMUCx->CHG_SR) & status_mask;
}

static inline uint32_t ll_pmuc_hpsys_ldo_is_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->HPSYS_LDO, PMUC_HPSYS_LDO_RDY);
}

static inline void ll_pmuc_hpsys_ldo_set_control(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_HPSYS_LDO_DLY | PMUC_HPSYS_LDO_VREF2 |
			      PMUC_HPSYS_LDO_BP | PMUC_HPSYS_LDO_EN;

	MODIFY_REG(PMUCx->HPSYS_LDO, mask, value & mask);
}

static inline uint32_t ll_pmuc_lpsys_ldo_is_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LPSYS_LDO, PMUC_LPSYS_LDO_RDY);
}

static inline void ll_pmuc_lpsys_ldo_set_control(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_LPSYS_LDO_DLY | PMUC_LPSYS_LDO_VREF2 |
			      PMUC_LPSYS_LDO_BP | PMUC_LPSYS_LDO_EN;

	MODIFY_REG(PMUCx->LPSYS_LDO, mask, value & mask);
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

static inline void ll_pmuc_hpsys_swr_set_control(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_HPSYS_SWR_NORET | PMUC_HPSYS_SWR_DLY |
			      PMUC_HPSYS_SWR_PSW_RET;

	MODIFY_REG(PMUCx->HPSYS_SWR, mask, value & mask);
}

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
 * @brief Check the LPSYS power switch ready status (LPSYS_SWR.RDY).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the switch is ready.
 */
static inline uint32_t ll_pmuc_swr_lpsys_is_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->LPSYS_SWR, PMUC_LPSYS_SWR_RDY);
}

static inline void ll_pmuc_lpsys_swr_set_control(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_LPSYS_SWR_NORET | PMUC_LPSYS_SWR_DLY |
			      PMUC_LPSYS_SWR_PSW_RET;

	MODIFY_REG(PMUCx->LPSYS_SWR, mask, value & mask);
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

static inline void ll_pmuc_peri_ldo_set_control(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_PERI_LDO_VDD33_LDO3_PD_VOUT |
			      PMUC_PERI_LDO_EN_VDD33_LDO3 |
			      PMUC_PERI_LDO_VDD33_LDO2_PD_VOUT |
			      PMUC_PERI_LDO_EN_VDD33_LDO2 | PMUC_PERI_LDO_LDO18_PD_VOUT |
			      PMUC_PERI_LDO_EN_LDO18;

	MODIFY_REG(PMUCx->PERI_LDO, mask, value & mask);
}

/**
 * @brief Enable the PERI VDD33 LDO3 soft-start (PERI_LDO.VDD33_LDO3_EN_SS).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_peri_ldo_vdd33_ldo3_ss_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PERI_LDO, PMUC_PERI_LDO_VDD33_LDO3_EN_SS);
}

/**
 * @brief Disable the PERI VDD33 LDO3 soft-start (PERI_LDO.VDD33_LDO3_EN_SS = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_peri_ldo_vdd33_ldo3_ss_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->PERI_LDO, PMUC_PERI_LDO_VDD33_LDO3_EN_SS);
}

/**
 * @brief Enable the PERI VDD33 LDO2 soft-start (PERI_LDO.VDD33_LDO2_EN_SS).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_peri_ldo_vdd33_ldo2_ss_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PERI_LDO, PMUC_PERI_LDO_VDD33_LDO2_EN_SS);
}

/**
 * @brief Disable the PERI VDD33 LDO2 soft-start (PERI_LDO.VDD33_LDO2_EN_SS = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_peri_ldo_vdd33_ldo2_ss_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->PERI_LDO, PMUC_PERI_LDO_VDD33_LDO2_EN_SS);
}

/**
 * @brief Check the PERI LDO18 ready flag (PERI_LDO.LDO18_RDY).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when ready.
 */
static inline uint32_t ll_pmuc_peri_ldo_is_ldo18_ready(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PERI_LDO, PMUC_PERI_LDO_LDO18_RDY) ? 1UL : 0UL;
}

/**
 * @brief Enable the PERI LDO18 soft-start (PERI_LDO.LDO18_EN_SS).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_peri_ldo_ldo18_ss_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PERI_LDO, PMUC_PERI_LDO_LDO18_EN_SS);
}

/**
 * @brief Disable the PERI LDO18 soft-start (PERI_LDO.LDO18_EN_SS = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_peri_ldo_ldo18_ss_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->PERI_LDO, PMUC_PERI_LDO_LDO18_EN_SS);
}

/**
 * @brief Set the PMU DC test point and macro select (PMU_TR).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] tr    DC test point select (3 bits).
 * @param[in] mr    DC macro select (3 bits).
 */
static inline void ll_pmuc_set_dc_test(PMUC_TypeDef *PMUCx, uint32_t tr, uint32_t mr)
{
	MODIFY_REG(PMUCx->PMU_TR, PMUC_PMU_TR_PMU_DC_TR | PMUC_PMU_TR_PMU_DC_MR,
		   MAKE_REG_VAL(tr, PMUC_PMU_TR_PMU_DC_TR_Msk, PMUC_PMU_TR_PMU_DC_TR_Pos) |
		   MAKE_REG_VAL(mr, PMUC_PMU_TR_PMU_DC_MR_Msk, PMUC_PMU_TR_PMU_DC_MR_Pos));
}

static inline uint32_t ll_pmuc_get_pmu_reserved(PMUC_TypeDef *PMUCx)
{
	const uint32_t mask = PMUC_PMU_RSVD_RESERVE3 | PMUC_PMU_RSVD_RESERVE2 |
			      PMUC_PMU_RSVD_RESERVE1 | PMUC_PMU_RSVD_RESERVE0;

	return READ_REG(PMUCx->PMU_RSVD) & mask;
}

static inline void ll_pmuc_set_pmu_reserved(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_PMU_RSVD_RESERVE2 | PMUC_PMU_RSVD_RESERVE1 |
			      PMUC_PMU_RSVD_RESERVE0;

	MODIFY_REG(PMUCx->PMU_RSVD, mask, value & mask);
}

static inline void ll_pmuc_hxt48_set_analog_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_HXT_CR1_CBANK_SEL | PMUC_HXT_CR1_GM_EN |
			      PMUC_HXT_CR1_LDO_FLT_RSEL | PMUC_HXT_CR1_LDO_VREF |
			      PMUC_HXT_CR1_BUF_RF_STR | PMUC_HXT_CR1_BUF_DLL_STR |
			      PMUC_HXT_CR1_BUF_EN;

	MODIFY_REG(PMUCx->HXT_CR1, mask, value & mask);
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
 * @brief Enable the HXT48 sleep mode (HXT_CR2.SLEEP_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_sleep_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HXT_CR2, PMUC_HXT_CR2_SLEEP_EN);
}

/**
 * @brief Disable the HXT48 sleep mode (HXT_CR2.SLEEP_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_sleep_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HXT_CR2, PMUC_HXT_CR2_SLEEP_EN);
}

static inline void ll_pmuc_hxt48_set_clock_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_HXT_CR2_SDADC_CLKDIV2_SEL |
			      PMUC_HXT_CR2_SDADC_CLKDIV1_SEL |
			      PMUC_HXT_CR2_SDADC_CLKIN_EN | PMUC_HXT_CR2_BUF_SEL3 |
			      PMUC_HXT_CR2_BUF_SEL2 | PMUC_HXT_CR2_ACBUF_RSEL |
			      PMUC_HXT_CR2_AGC_ISTART_SEL;

	MODIFY_REG(PMUCx->HXT_CR2, mask, value & mask);
}

/**
 * @brief Set the HXT48 IDAC value (HXT_CR2.IDAC).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] idac  IDAC value (10 bits).
 */
static inline void ll_pmuc_hxt48_set_idac(PMUC_TypeDef *PMUCx, uint32_t idac)
{
	MODIFY_REG(PMUCx->HXT_CR2, PMUC_HXT_CR2_IDAC,
		   MAKE_REG_VAL(idac, PMUC_HXT_CR2_IDAC_Msk, PMUC_HXT_CR2_IDAC_Pos));
}

/**
 * @brief Enable the HXT48 IDAC (HXT_CR2.IDAC_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_idac_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HXT_CR2, PMUC_HXT_CR2_IDAC_EN);
}

/**
 * @brief Disable the HXT48 IDAC (HXT_CR2.IDAC_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_idac_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HXT_CR2, PMUC_HXT_CR2_IDAC_EN);
}

/**
 * @brief Set the HXT48 AC buffer select (HXT_CR2.ACBUF_SEL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] sel   AC buffer select (2 bits).
 */
static inline void ll_pmuc_hxt48_set_acbuf_sel(PMUC_TypeDef *PMUCx, uint32_t sel)
{
	MODIFY_REG(PMUCx->HXT_CR2, PMUC_HXT_CR2_ACBUF_SEL,
		   MAKE_REG_VAL(sel, PMUC_HXT_CR2_ACBUF_SEL_Msk, PMUC_HXT_CR2_ACBUF_SEL_Pos));
}

/**
 * @brief Set the HXT48 AGC VIN DC (HXT_CR2.AGC_VINDC).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vindc AGC VIN DC (2 bits).
 */
static inline void ll_pmuc_hxt48_set_agc_vindc(PMUC_TypeDef *PMUCx, uint32_t vindc)
{
	MODIFY_REG(PMUCx->HXT_CR2, PMUC_HXT_CR2_AGC_VINDC,
		   MAKE_REG_VAL(vindc, PMUC_HXT_CR2_AGC_VINDC_Msk, PMUC_HXT_CR2_AGC_VINDC_Pos));
}

/**
 * @brief Set the HXT48 AGC threshold (HXT_CR2.AGC_VTH).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vth   AGC threshold (4 bits).
 */
static inline void ll_pmuc_hxt48_set_agc_vth(PMUC_TypeDef *PMUCx, uint32_t vth)
{
	MODIFY_REG(PMUCx->HXT_CR2, PMUC_HXT_CR2_AGC_VTH,
		   MAKE_REG_VAL(vth, PMUC_HXT_CR2_AGC_VTH_Msk, PMUC_HXT_CR2_AGC_VTH_Pos));
}

/**
 * @brief Enable the HXT48 AGC (HXT_CR2.AGC_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_agc_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HXT_CR2, PMUC_HXT_CR2_AGC_EN);
}

/**
 * @brief Disable the HXT48 AGC (HXT_CR2.AGC_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hxt48_agc_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HXT_CR2, PMUC_HXT_CR2_AGC_EN);
}

/**
 * @brief Set the HXT48 delay (HXT_CR3.DLY).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] dly   Delay value (6 bits).
 */
static inline void ll_pmuc_hxt48_set_dly(PMUC_TypeDef *PMUCx, uint32_t dly)
{
	MODIFY_REG(PMUCx->HXT_CR3, PMUC_HXT_CR3_DLY,
		   MAKE_REG_VAL(dly, PMUC_HXT_CR3_DLY_Msk, PMUC_HXT_CR3_DLY_Pos));
}

/**
 * @brief Set the HXT48 buffer oscillator strength (HXT_CR3.BUF_OSLO_STR).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] str   Buffer strength (2 bits).
 */
static inline void ll_pmuc_hxt48_set_buf_oslo_str(PMUC_TypeDef *PMUCx, uint32_t str)
{
	MODIFY_REG(PMUCx->HXT_CR3, PMUC_HXT_CR3_BUF_OSLO_STR,
		   MAKE_REG_VAL(str, PMUC_HXT_CR3_BUF_OSLO_STR_Msk, PMUC_HXT_CR3_BUF_OSLO_STR_Pos));
}

/**
 * @brief Set the HXT48 buffer DAC strength (HXT_CR3.BUF_DAC_STR).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] str   Buffer strength (2 bits).
 */
static inline void ll_pmuc_hxt48_set_buf_dac_str(PMUC_TypeDef *PMUCx, uint32_t str)
{
	MODIFY_REG(PMUCx->HXT_CR3, PMUC_HXT_CR3_BUF_DAC_STR,
		   MAKE_REG_VAL(str, PMUC_HXT_CR3_BUF_DAC_STR_Msk, PMUC_HXT_CR3_BUF_DAC_STR_Pos));
}

static inline void ll_pmuc_hrc48_set_config(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_HRC_CR1_DLY | PMUC_HRC_CR1_CLKLP_STR |
			      PMUC_HRC_CR1_CLKLP_SEL | PMUC_HRC_CR1_CLKLP_EN |
			      PMUC_HRC_CR1_CLKHP_STR | PMUC_HRC_CR1_CLKHP_SEL |
			      PMUC_HRC_CR1_CLKHP_EN | PMUC_HRC_CR1_CLK96M_EN |
			      PMUC_HRC_CR1_TEMP_TRIM | PMUC_HRC_CR1_LDO_VREF |
			      PMUC_HRC_CR1_EN;

	MODIFY_REG(PMUCx->HRC_CR1, mask, value & mask);
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
	MODIFY_REG(PMUCx->HRC_CR1, PMUC_HRC_CR1_FREQ_TRIM,
		   MAKE_REG_VAL(trim, PMUC_HRC_CR1_FREQ_TRIM_Msk, PMUC_HRC_CR1_FREQ_TRIM_Pos));
}

/**
 * @brief Set the HRC48 SS FD-sel (HRC_CR2.SS_FD_SEL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] sel   FD select code.
 */
static inline void ll_pmuc_hrc48_set_ss_fd_sel(PMUC_TypeDef *PMUCx, uint32_t sel)
{
	MODIFY_REG(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_FD_SEL,
		   MAKE_REG_VAL(sel, PMUC_HRC_CR2_SS_FD_SEL_Msk, PMUC_HRC_CR2_SS_FD_SEL_Pos));
}

/**
 * @brief Enable the HRC48 SS FD-sel force (HRC_CR2.SS_FD_SEL_FRC_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hrc48_ss_fd_force_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_FD_SEL_FRC_EN);
}

/**
 * @brief Disable the HRC48 SS FD-sel force (HRC_CR2.SS_FD_SEL_FRC_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hrc48_ss_fd_force_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_FD_SEL_FRC_EN);
}

/**
 * @brief Enable the HRC48 SS average-0 (HRC_CR2.SS_AVG0_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hrc48_ss_avg0_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_AVG0_EN);
}

/**
 * @brief Disable the HRC48 SS average-0 (HRC_CR2.SS_AVG0_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hrc48_ss_avg0_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_AVG0_EN);
}

/**
 * @brief Set the HRC48 SS N-select (HRC_CR2.SS_NSEL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] nsel  N-select code.
 */
static inline void ll_pmuc_hrc48_set_ss_nsel(PMUC_TypeDef *PMUCx, uint32_t nsel)
{
	MODIFY_REG(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_NSEL,
		   MAKE_REG_VAL(nsel, PMUC_HRC_CR2_SS_NSEL_Msk, PMUC_HRC_CR2_SS_NSEL_Pos));
}

/**
 * @brief Set the HRC48 SS clock select (HRC_CR2.SS_CLK_SEL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] sel   Clock select code.
 */
static inline void ll_pmuc_hrc48_set_ss_clk_sel(PMUC_TypeDef *PMUCx, uint32_t sel)
{
	MODIFY_REG(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_CLK_SEL,
		   MAKE_REG_VAL(sel, PMUC_HRC_CR2_SS_CLK_SEL_Msk, PMUC_HRC_CR2_SS_CLK_SEL_Pos));
}

/**
 * @brief Enable the HRC48 spread-spectrum (HRC_CR2.SS_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hrc48_ss_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_EN);
}

/**
 * @brief Disable the HRC48 spread-spectrum (HRC_CR2.SS_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hrc48_ss_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HRC_CR2, PMUC_HRC_CR2_SS_EN);
}

/**
 * @brief Set the HRC48 IDWN select (HRC_CR2.IDWN_SEL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] sel   IDWN select code.
 */
static inline void ll_pmuc_hrc48_set_idwn_sel(PMUC_TypeDef *PMUCx, uint32_t sel)
{
	MODIFY_REG(PMUCx->HRC_CR2, PMUC_HRC_CR2_IDWN_SEL,
		   MAKE_REG_VAL(sel, PMUC_HRC_CR2_IDWN_SEL_Msk, PMUC_HRC_CR2_IDWN_SEL_Pos));
}

/**
 * @brief Enable the HRC48 clock doubler (HRC_CR2.CLKX2_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hrc48_clkx2_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->HRC_CR2, PMUC_HRC_CR2_CLKX2_EN);
}

/**
 * @brief Disable the HRC48 clock doubler (HRC_CR2.CLKX2_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_hrc48_clkx2_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->HRC_CR2, PMUC_HRC_CR2_CLKX2_EN);
}

/**
 * @brief Set the LPSYS bandgap 1.2V reference (CAU_BGR.LPBG_VREF12).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vref  Reference trim (4 bits).
 */
static inline void ll_pmuc_cau_set_lpbg_vref12(PMUC_TypeDef *PMUCx, uint32_t vref)
{
	MODIFY_REG(PMUCx->CAU_BGR, PMUC_CAU_BGR_LPBG_VREF12,
		   MAKE_REG_VAL(vref, PMUC_CAU_BGR_LPBG_VREF12_Msk, PMUC_CAU_BGR_LPBG_VREF12_Pos));
}

/**
 * @brief Set the LPSYS bandgap 0.6V reference (CAU_BGR.LPBG_VREF06).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] vref  Reference trim (4 bits).
 */
static inline void ll_pmuc_cau_set_lpbg_vref06(PMUC_TypeDef *PMUCx, uint32_t vref)
{
	MODIFY_REG(PMUCx->CAU_BGR, PMUC_CAU_BGR_LPBG_VREF06,
		   MAKE_REG_VAL(vref, PMUC_CAU_BGR_LPBG_VREF06_Msk, PMUC_CAU_BGR_LPBG_VREF06_Pos));
}

/**
 * @brief Enable the LPSYS bandgap (CAU_BGR.LPBG_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_cau_lpbg_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CAU_BGR, PMUC_CAU_BGR_LPBG_EN);
}

/**
 * @brief Disable the LPSYS bandgap (CAU_BGR.LPBG_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_cau_lpbg_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CAU_BGR, PMUC_CAU_BGR_LPBG_EN);
}

/**
 * @brief Enable the HPSYS bandgap (CAU_BGR.HPBG_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_cau_hpbg_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CAU_BGR, PMUC_CAU_BGR_HPBG_EN);
}

/**
 * @brief Disable the HPSYS bandgap (CAU_BGR.HPBG_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_cau_hpbg_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CAU_BGR, PMUC_CAU_BGR_HPBG_EN);
}

/**
 * @brief Enable the HPSYS bandgap VDDPSW (CAU_BGR.HPBG_VDDPSW_EN).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_cau_hpbg_vddpsw_enable(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->CAU_BGR, PMUC_CAU_BGR_HPBG_VDDPSW_EN);
}

/**
 * @brief Disable the HPSYS bandgap VDDPSW (CAU_BGR.HPBG_VDDPSW_EN = 0).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_cau_hpbg_vddpsw_disable(PMUC_TypeDef *PMUCx)
{
	CLEAR_BIT(PMUCx->CAU_BGR, PMUC_CAU_BGR_HPBG_VDDPSW_EN);
}

/**
 * @brief Set the CAU DC test (CAU_TR).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] tr    DC test point select (3 bits).
 * @param[in] br    DC test block select (3 bits).
 * @param[in] mr    DC test macro select (3 bits).
 */
static inline void ll_pmuc_cau_set_dc_test(PMUC_TypeDef *PMUCx, uint32_t tr, uint32_t br,
					   uint32_t mr)
{
	MODIFY_REG(PMUCx->CAU_TR, PMUC_CAU_TR_CAU_DC_TR | PMUC_CAU_TR_CAU_DC_BR |
		   PMUC_CAU_TR_CAU_DC_MR,
		   MAKE_REG_VAL(tr, PMUC_CAU_TR_CAU_DC_TR_Msk, PMUC_CAU_TR_CAU_DC_TR_Pos) |
		   MAKE_REG_VAL(br, PMUC_CAU_TR_CAU_DC_BR_Msk, PMUC_CAU_TR_CAU_DC_BR_Pos) |
		   MAKE_REG_VAL(mr, PMUC_CAU_TR_CAU_DC_MR_Msk, PMUC_CAU_TR_CAU_DC_MR_Pos));
}

static inline uint32_t ll_pmuc_get_cau_reserved(PMUC_TypeDef *PMUCx)
{
const uint32_t mask = PMUC_CAU_RSVD_RESERVE1 |
			      PMUC_CAU_RSVD_RESERVE0;

	return READ_REG(PMUCx->CAU_RSVD) & mask;
}

static inline void ll_pmuc_set_cau_reserved(PMUC_TypeDef *PMUCx, uint32_t value)
{
	const uint32_t mask = PMUC_CAU_RSVD_RESERVE1 | PMUC_CAU_RSVD_RESERVE0;

	MODIFY_REG(PMUCx->CAU_RSVD, mask, value & mask);
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

/**
 * @brief Set the PA27 wakeup mode (WKUP_MODE.PA27_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa27_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA27_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA27_MODE_Msk, PMUC_WKUP_MODE_PA27_MODE_Pos));
}

/**
 * @brief Get the PA27 wakeup mode (WKUP_MODE.PA27_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa27_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA27_MODE);
}

/**
 * @brief Set the PA26 wakeup mode (WKUP_MODE.PA26_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa26_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA26_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA26_MODE_Msk, PMUC_WKUP_MODE_PA26_MODE_Pos));
}

/**
 * @brief Get the PA26 wakeup mode (WKUP_MODE.PA26_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa26_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA26_MODE);
}

/**
 * @brief Set the PA25 wakeup mode (WKUP_MODE.PA25_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa25_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA25_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA25_MODE_Msk, PMUC_WKUP_MODE_PA25_MODE_Pos));
}

/**
 * @brief Get the PA25 wakeup mode (WKUP_MODE.PA25_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa25_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA25_MODE);
}

/*==============================================================================
 * Wakeup Pin Mode (WKUP_MODE)
 *============================================================================*/

/**
 * @brief Set the PA24 wakeup mode (WKUP_MODE.PA24_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa24_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA24_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA24_MODE_Msk, PMUC_WKUP_MODE_PA24_MODE_Pos));
}

/**
 * @brief Get the PA24 wakeup mode (WKUP_MODE.PA24_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa24_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA24_MODE);
}

/**
 * @brief Set the PA42 wakeup mode (WKUP_MODE.PA42_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa42_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA42_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA42_MODE_Msk, PMUC_WKUP_MODE_PA42_MODE_Pos));
}

/**
 * @brief Get the PA42 wakeup mode (WKUP_MODE.PA42_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa42_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA42_MODE);
}

/**
 * @brief Set the PA41 wakeup mode (WKUP_MODE.PA41_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa41_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA41_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA41_MODE_Msk, PMUC_WKUP_MODE_PA41_MODE_Pos));
}

/**
 * @brief Get the PA41 wakeup mode (WKUP_MODE.PA41_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa41_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA41_MODE);
}

/**
 * @brief Set the PA40 wakeup mode (WKUP_MODE.PA40_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa40_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA40_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA40_MODE_Msk, PMUC_WKUP_MODE_PA40_MODE_Pos));
}

/**
 * @brief Get the PA40 wakeup mode (WKUP_MODE.PA40_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa40_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA40_MODE);
}

/**
 * @brief Set the PA39 wakeup mode (WKUP_MODE.PA39_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa39_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA39_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA39_MODE_Msk, PMUC_WKUP_MODE_PA39_MODE_Pos));
}

/**
 * @brief Get the PA39 wakeup mode (WKUP_MODE.PA39_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa39_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA39_MODE);
}

/**
 * @brief Set the PA38 wakeup mode (WKUP_MODE.PA38_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa38_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA38_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA38_MODE_Msk, PMUC_WKUP_MODE_PA38_MODE_Pos));
}

/**
 * @brief Get the PA38 wakeup mode (WKUP_MODE.PA38_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa38_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA38_MODE);
}

/**
 * @brief Set the PA37 wakeup mode (WKUP_MODE.PA37_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa37_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA37_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA37_MODE_Msk, PMUC_WKUP_MODE_PA37_MODE_Pos));
}

/**
 * @brief Get the PA37 wakeup mode (WKUP_MODE.PA37_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa37_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA37_MODE);
}

/**
 * @brief Set the PA36 wakeup mode (WKUP_MODE.PA36_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa36_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA36_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA36_MODE_Msk, PMUC_WKUP_MODE_PA36_MODE_Pos));
}

/**
 * @brief Get the PA36 wakeup mode (WKUP_MODE.PA36_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa36_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA36_MODE);
}

/**
 * @brief Set the PA35 wakeup mode (WKUP_MODE.PA35_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa35_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA35_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA35_MODE_Msk, PMUC_WKUP_MODE_PA35_MODE_Pos));
}

/**
 * @brief Get the PA35 wakeup mode (WKUP_MODE.PA35_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa35_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA35_MODE);
}

/**
 * @brief Set the PA34 wakeup mode (WKUP_MODE.PA34_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa34_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA34_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA34_MODE_Msk, PMUC_WKUP_MODE_PA34_MODE_Pos));
}

/**
 * @brief Get the PA34 wakeup mode (WKUP_MODE.PA34_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa34_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA34_MODE);
}

/**
 * @brief Set the PA33 wakeup mode (WKUP_MODE.PA33_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] mode  Wakeup mode (2 bits).
 */
static inline void ll_pmuc_wkup_pa33_set_mode(PMUC_TypeDef *PMUCx, uint32_t mode)
{
	MODIFY_REG(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA33_MODE,
		   MAKE_REG_VAL(mode, PMUC_WKUP_MODE_PA33_MODE_Msk, PMUC_WKUP_MODE_PA33_MODE_Pos));
}

/**
 * @brief Get the PA33 wakeup mode (WKUP_MODE.PA33_MODE).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Wakeup mode (2 bits).
 */
static inline uint32_t ll_pmuc_wkup_pa33_get_mode(PMUC_TypeDef *PMUCx)
{
	return GET_REG_VAL2(PMUCx->WKUP_MODE, PMUC_WKUP_MODE_PA33_MODE);
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
	WRITE_REG(PMUCx->WKUP_CNT,
		  cnt & PMUC_WKUP_CNT_PIN_DLY);
}

/**
 * @brief Read the PA31 reset status (PRSR1.PA31).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa31(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA31) ? 1UL : 0UL;
}

/**
 * @brief Read the PA30 reset status (PRSR1.PA30).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa30(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA30) ? 1UL : 0UL;
}

/**
 * @brief Read the PA29 reset status (PRSR1.PA29).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa29(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA29) ? 1UL : 0UL;
}

/**
 * @brief Read the PA28 reset status (PRSR1.PA28).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa28(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA28) ? 1UL : 0UL;
}

/**
 * @brief Read the PA27 reset status (PRSR1.PA27).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa27(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA27) ? 1UL : 0UL;
}

/**
 * @brief Read the PA26 reset status (PRSR1.PA26).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa26(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA26) ? 1UL : 0UL;
}

/**
 * @brief Read the PA25 reset status (PRSR1.PA25).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa25(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA25) ? 1UL : 0UL;
}

/**
 * @brief Read the PA24 reset status (PRSR1.PA24).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa24(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA24) ? 1UL : 0UL;
}

/**
 * @brief Read the PA23 reset status (PRSR1.PA23).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa23(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA23) ? 1UL : 0UL;
}

/**
 * @brief Read the PA22 reset status (PRSR1.PA22).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa22(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA22) ? 1UL : 0UL;
}

/**
 * @brief Read the PA21 reset status (PRSR1.PA21).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa21(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA21) ? 1UL : 0UL;
}

/**
 * @brief Read the PA20 reset status (PRSR1.PA20).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa20(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA20) ? 1UL : 0UL;
}

/**
 * @brief Read the PA19 reset status (PRSR1.PA19).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa19(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA19) ? 1UL : 0UL;
}

/**
 * @brief Read the PA18 reset status (PRSR1.PA18).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa18(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA18) ? 1UL : 0UL;
}

/**
 * @brief Read the PA17 reset status (PRSR1.PA17).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa17(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA17) ? 1UL : 0UL;
}

/**
 * @brief Read the PA16 reset status (PRSR1.PA16).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa16(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA16) ? 1UL : 0UL;
}

/**
 * @brief Read the PA15 reset status (PRSR1.PA15).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa15(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA15) ? 1UL : 0UL;
}

/**
 * @brief Read the PA14 reset status (PRSR1.PA14).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa14(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA14) ? 1UL : 0UL;
}

/**
 * @brief Read the PA13 reset status (PRSR1.PA13).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa13(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA13) ? 1UL : 0UL;
}

/**
 * @brief Read the PA12 reset status (PRSR1.PA12).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa12(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA12) ? 1UL : 0UL;
}

/**
 * @brief Read the PA11 reset status (PRSR1.PA11).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa11(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA11) ? 1UL : 0UL;
}

/**
 * @brief Read the PA10 reset status (PRSR1.PA10).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa10(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA10) ? 1UL : 0UL;
}

/**
 * @brief Read the PA9 reset status (PRSR1.PA9).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa9(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA9) ? 1UL : 0UL;
}

/**
 * @brief Read the PA8 reset status (PRSR1.PA8).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa8(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA8) ? 1UL : 0UL;
}

/**
 * @brief Read the PA7 reset status (PRSR1.PA7).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa7(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA7) ? 1UL : 0UL;
}

/**
 * @brief Read the PA6 reset status (PRSR1.PA6).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa6(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA6) ? 1UL : 0UL;
}

/**
 * @brief Read the PA5 reset status (PRSR1.PA5).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa5(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA5) ? 1UL : 0UL;
}

/**
 * @brief Read the PA4 reset status (PRSR1.PA4).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa4(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA4) ? 1UL : 0UL;
}

/**
 * @brief Read the PA3 reset status (PRSR1.PA3).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa3(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA3) ? 1UL : 0UL;
}

/**
 * @brief Read the PA2 reset status (PRSR1.PA2).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa2(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA2) ? 1UL : 0UL;
}

/**
 * @brief Read the PA1 reset status (PRSR1.PA1).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa1(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA1) ? 1UL : 0UL;
}

/*==============================================================================
 * Pin Reset Status (PRSR1 / PRSR2)
 *============================================================================*/

/**
 * @brief Read the PA0 reset status (PRSR1.PA0).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr1_get_pa0(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR1, PMUC_PRSR1_PA0) ? 1UL : 0UL;
}

/**
 * @brief Read the PRSR2 SA flag (PRSR2.SA).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when set.
 */
static inline uint32_t ll_pmuc_prsr2_get_sa(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_SA) ? 1UL : 0UL;
}

/**
 * @brief Read the PRSR2 SB flag (PRSR2.SB).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when set.
 */
static inline uint32_t ll_pmuc_prsr2_get_sb(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_SB) ? 1UL : 0UL;
}

/**
 * @brief Read the PA57 reset status (PRSR2.PA57).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa57(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA57) ? 1UL : 0UL;
}

/**
 * @brief Read the PA56 reset status (PRSR2.PA56).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa56(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA56) ? 1UL : 0UL;
}

/**
 * @brief Read the PA55 reset status (PRSR2.PA55).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa55(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA55) ? 1UL : 0UL;
}

/**
 * @brief Read the PA54 reset status (PRSR2.PA54).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa54(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA54) ? 1UL : 0UL;
}

/**
 * @brief Read the PA53 reset status (PRSR2.PA53).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa53(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA53) ? 1UL : 0UL;
}

/**
 * @brief Read the PA52 reset status (PRSR2.PA52).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa52(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA52) ? 1UL : 0UL;
}

/**
 * @brief Read the PA51 reset status (PRSR2.PA51).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa51(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA51) ? 1UL : 0UL;
}

/**
 * @brief Read the PA50 reset status (PRSR2.PA50).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa50(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA50) ? 1UL : 0UL;
}

/**
 * @brief Read the PA49 reset status (PRSR2.PA49).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa49(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA49) ? 1UL : 0UL;
}

/**
 * @brief Read the PA48 reset status (PRSR2.PA48).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa48(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA48) ? 1UL : 0UL;
}

/**
 * @brief Read the PA47 reset status (PRSR2.PA47).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa47(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA47) ? 1UL : 0UL;
}

/**
 * @brief Read the PA46 reset status (PRSR2.PA46).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa46(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA46) ? 1UL : 0UL;
}

/**
 * @brief Read the PA45 reset status (PRSR2.PA45).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa45(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA45) ? 1UL : 0UL;
}

/**
 * @brief Read the PA44 reset status (PRSR2.PA44).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa44(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA44) ? 1UL : 0UL;
}

/**
 * @brief Read the PA43 reset status (PRSR2.PA43).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa43(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA43) ? 1UL : 0UL;
}

/**
 * @brief Read the PA42 reset status (PRSR2.PA42).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa42(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA42) ? 1UL : 0UL;
}

/**
 * @brief Read the PA41 reset status (PRSR2.PA41).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa41(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA41) ? 1UL : 0UL;
}

/**
 * @brief Read the PA40 reset status (PRSR2.PA40).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa40(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA40) ? 1UL : 0UL;
}

/**
 * @brief Read the PA39 reset status (PRSR2.PA39).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa39(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA39) ? 1UL : 0UL;
}

/**
 * @brief Read the PA38 reset status (PRSR2.PA38).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa38(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA38) ? 1UL : 0UL;
}

/**
 * @brief Read the PA37 reset status (PRSR2.PA37).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa37(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA37) ? 1UL : 0UL;
}

/**
 * @brief Read the PA36 reset status (PRSR2.PA36).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa36(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA36) ? 1UL : 0UL;
}

/**
 * @brief Read the PA35 reset status (PRSR2.PA35).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa35(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA35) ? 1UL : 0UL;
}

/**
 * @brief Read the PA34 reset status (PRSR2.PA34).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa34(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA34) ? 1UL : 0UL;
}

/**
 * @brief Read the PA33 reset status (PRSR2.PA33).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa33(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA33) ? 1UL : 0UL;
}

/**
 * @brief Read the PA32 reset status (PRSR2.PA32).
 * @param[in] PMUCx PMUC instance pointer.
 * @return Non-zero when the pin reset state is set.
 */
static inline uint32_t ll_pmuc_prsr2_get_pa32(PMUC_TypeDef *PMUCx)
{
	return READ_BIT(PMUCx->PRSR2, PMUC_PRSR2_PA32) ? 1UL : 0UL;
}

/**
 * @brief Clear the PA31 reset flag (PRCR1.PA31, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa31(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA31);
}

/**
 * @brief Clear the PA30 reset flag (PRCR1.PA30, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa30(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA30);
}

/**
 * @brief Clear the PA29 reset flag (PRCR1.PA29, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa29(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA29);
}

/**
 * @brief Clear the PA28 reset flag (PRCR1.PA28, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa28(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA28);
}

/**
 * @brief Clear the PA27 reset flag (PRCR1.PA27, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa27(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA27);
}

/**
 * @brief Clear the PA26 reset flag (PRCR1.PA26, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa26(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA26);
}

/**
 * @brief Clear the PA25 reset flag (PRCR1.PA25, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa25(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA25);
}

/**
 * @brief Clear the PA24 reset flag (PRCR1.PA24, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa24(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA24);
}

/**
 * @brief Clear the PA23 reset flag (PRCR1.PA23, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa23(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA23);
}

/**
 * @brief Clear the PA22 reset flag (PRCR1.PA22, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa22(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA22);
}

/**
 * @brief Clear the PA21 reset flag (PRCR1.PA21, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa21(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA21);
}

/**
 * @brief Clear the PA20 reset flag (PRCR1.PA20, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa20(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA20);
}

/**
 * @brief Clear the PA19 reset flag (PRCR1.PA19, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa19(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA19);
}

/**
 * @brief Clear the PA18 reset flag (PRCR1.PA18, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa18(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA18);
}

/**
 * @brief Clear the PA17 reset flag (PRCR1.PA17, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa17(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA17);
}

/**
 * @brief Clear the PA16 reset flag (PRCR1.PA16, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa16(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA16);
}

/**
 * @brief Clear the PA15 reset flag (PRCR1.PA15, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa15(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA15);
}

/**
 * @brief Clear the PA14 reset flag (PRCR1.PA14, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa14(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA14);
}

/**
 * @brief Clear the PA13 reset flag (PRCR1.PA13, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa13(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA13);
}

/**
 * @brief Clear the PA12 reset flag (PRCR1.PA12, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa12(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA12);
}

/**
 * @brief Clear the PA11 reset flag (PRCR1.PA11, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa11(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA11);
}

/**
 * @brief Clear the PA10 reset flag (PRCR1.PA10, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa10(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA10);
}

/**
 * @brief Clear the PA9 reset flag (PRCR1.PA9, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa9(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA9);
}

/**
 * @brief Clear the PA8 reset flag (PRCR1.PA8, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa8(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA8);
}

/**
 * @brief Clear the PA7 reset flag (PRCR1.PA7, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa7(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA7);
}

/**
 * @brief Clear the PA6 reset flag (PRCR1.PA6, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa6(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA6);
}

/**
 * @brief Clear the PA5 reset flag (PRCR1.PA5, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa5(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA5);
}

/**
 * @brief Clear the PA4 reset flag (PRCR1.PA4, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa4(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA4);
}

/**
 * @brief Clear the PA3 reset flag (PRCR1.PA3, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa3(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA3);
}

/**
 * @brief Clear the PA2 reset flag (PRCR1.PA2, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa2(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA2);
}

/**
 * @brief Clear the PA1 reset flag (PRCR1.PA1, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa1(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA1);
}

/*==============================================================================
 * Pin Reset Clear (PRCR1 / PRCR2)
 *============================================================================*/

/**
 * @brief Clear the PA0 reset flag (PRCR1.PA0, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr1_clear_pa0(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR1, PMUC_PRCR1_PA0);
}

/**
 * @brief Clear the PRCR2 SA flag (PRCR2.SA, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_sa(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_SA);
}

/**
 * @brief Clear the PRCR2 SB flag (PRCR2.SB, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_sb(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_SB);
}

/**
 * @brief Clear the PA57 reset flag (PRCR2.PA57, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa57(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA57);
}

/**
 * @brief Clear the PA56 reset flag (PRCR2.PA56, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa56(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA56);
}

/**
 * @brief Clear the PA55 reset flag (PRCR2.PA55, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa55(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA55);
}

/**
 * @brief Clear the PA54 reset flag (PRCR2.PA54, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa54(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA54);
}

/**
 * @brief Clear the PA53 reset flag (PRCR2.PA53, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa53(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA53);
}

/**
 * @brief Clear the PA52 reset flag (PRCR2.PA52, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa52(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA52);
}

/**
 * @brief Clear the PA51 reset flag (PRCR2.PA51, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa51(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA51);
}

/**
 * @brief Clear the PA50 reset flag (PRCR2.PA50, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa50(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA50);
}

/**
 * @brief Clear the PA49 reset flag (PRCR2.PA49, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa49(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA49);
}

/**
 * @brief Clear the PA48 reset flag (PRCR2.PA48, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa48(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA48);
}

/**
 * @brief Clear the PA47 reset flag (PRCR2.PA47, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa47(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA47);
}

/**
 * @brief Clear the PA46 reset flag (PRCR2.PA46, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa46(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA46);
}

/**
 * @brief Clear the PA45 reset flag (PRCR2.PA45, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa45(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA45);
}

/**
 * @brief Clear the PA44 reset flag (PRCR2.PA44, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa44(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA44);
}

/**
 * @brief Clear the PA43 reset flag (PRCR2.PA43, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa43(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA43);
}

/**
 * @brief Clear the PA42 reset flag (PRCR2.PA42, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa42(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA42);
}

/**
 * @brief Clear the PA41 reset flag (PRCR2.PA41, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa41(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA41);
}

/**
 * @brief Clear the PA40 reset flag (PRCR2.PA40, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa40(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA40);
}

/**
 * @brief Clear the PA39 reset flag (PRCR2.PA39, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa39(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA39);
}

/**
 * @brief Clear the PA38 reset flag (PRCR2.PA38, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa38(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA38);
}

/**
 * @brief Clear the PA37 reset flag (PRCR2.PA37, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa37(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA37);
}

/**
 * @brief Clear the PA36 reset flag (PRCR2.PA36, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa36(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA36);
}

/**
 * @brief Clear the PA35 reset flag (PRCR2.PA35, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa35(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA35);
}

/**
 * @brief Clear the PA34 reset flag (PRCR2.PA34, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa34(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA34);
}

/**
 * @brief Clear the PA33 reset flag (PRCR2.PA33, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa33(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA33);
}

/**
 * @brief Clear the PA32 reset flag (PRCR2.PA32, write 1).
 * @param[in] PMUCx PMUC instance pointer.
 */
static inline void ll_pmuc_prcr2_clear_pa32(PMUC_TypeDef *PMUCx)
{
	SET_BIT(PMUCx->PRCR2, PMUC_PRCR2_PA32);
}

/**
 * @brief Set the PBR debug select (PBRCR.DBG_SEL).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] sel   Debug select (4 bits).
 */
static inline void ll_pmuc_pbr_set_dbg_sel(PMUC_TypeDef *PMUCx, uint32_t sel)
{
	MODIFY_REG(PMUCx->PBRCR, PMUC_PBRCR_DBG_SEL,
		   MAKE_REG_VAL(sel, PMUC_PBRCR_DBG_SEL_Msk, PMUC_PBRCR_DBG_SEL_Pos));
}

/**
 * @brief Set the PBR sense bit (PBRCR.SNS).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] en    Non-zero to set, zero to clear.
 */
static inline void ll_pmuc_pbr_set_sns(PMUC_TypeDef *PMUCx, uint32_t en)
{
	MODIFY_REG(PMUCx->PBRCR, PMUC_PBRCR_SNS, en ? PMUC_PBRCR_SNS : 0UL);
}

/*==============================================================================
 * PBR Control (PBRCR)
 *============================================================================*/

/**
 * @brief Set the PBR reset-toggle bit (PBRCR.RTO).
 * @param[in] PMUCx PMUC instance pointer.
 * @param[in] en    Non-zero to set, zero to clear.
 */
static inline void ll_pmuc_pbr_set_rto(PMUC_TypeDef *PMUCx, uint32_t en)
{
	MODIFY_REG(PMUCx->PBRCR, PMUC_PBRCR_RTO, en ? PMUC_PBRCR_RTO : 0UL);
}

#ifdef __cplusplus
}
#endif

#endif /* __LL_PMUC_H */