/*
 * SPDX-FileCopyrightText: 2026 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LL_ATIM_H
#define __LL_ATIM_H

#include <stdint.h>
#include "regs/atim.h"
#include "cmsis_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file ll_atim.h
 * @brief Header-only low-level Advanced Timer (ATIM) APIs for SF32LB52x.
 *
 * ATIM extends GPTIM with complementary outputs (CHxN), dead-time insertion,
 * break input, and 6 capture/compare channels.
 */

/*==============================================================================
 * Counter Mode (CR1.CMS)
 *============================================================================*/

/** @defgroup LL_ATIM_COUNTER_MODE Counter Alignment Mode */
/** @{ */
#define LL_ATIM_COUNTER_MODE_EDGE    (0x0UL)
#define LL_ATIM_COUNTER_MODE_CENTER1 (0x1UL)
#define LL_ATIM_COUNTER_MODE_CENTER2 (0x2UL)
#define LL_ATIM_COUNTER_MODE_CENTER3 (0x3UL)
/** @} */

/** @defgroup LL_ATIM_COUNTER_DIR Counter Direction */
/** @{ */
#define LL_ATIM_COUNTER_DIR_UP   (0x0UL)
#define LL_ATIM_COUNTER_DIR_DOWN (0x1UL)
/** @} */

/*==============================================================================
 * OC Mode (CCMRx.OCxM)
 *============================================================================*/

/** @defgroup LL_ATIM_OC_MODE Output Compare Mode */
/** @{ */
#define LL_ATIM_OC_MODE_FROZEN            (0x0UL)
#define LL_ATIM_OC_MODE_ACTIVE_ON_MATCH   (0x1UL)
#define LL_ATIM_OC_MODE_INACTIVE_ON_MATCH (0x2UL)
#define LL_ATIM_OC_MODE_TOGGLE            (0x3UL)
#define LL_ATIM_OC_MODE_FORCE_INACTIVE    (0x4UL)
#define LL_ATIM_OC_MODE_FORCE_ACTIVE      (0x5UL)
#define LL_ATIM_OC_MODE_PWM1              (0x6UL)
#define LL_ATIM_OC_MODE_PWM2              (0x7UL)
#define LL_ATIM_OC_MODE_RETRIG_OPM1       (0x8UL)
#define LL_ATIM_OC_MODE_RETRIG_OPM2       (0x9UL)
#define LL_ATIM_OC_MODE_COMBINED_PWM1     (0xCUL)
#define LL_ATIM_OC_MODE_COMBINED_PWM2     (0xDUL)
#define LL_ATIM_OC_MODE_ASYMMETRIC_PWM1   (0xEUL)
#define LL_ATIM_OC_MODE_ASYMMETRIC_PWM2   (0xFUL)
/** @} */

/*==============================================================================
 * Break / Lock (BDTR)
 *============================================================================*/

/** @defgroup LL_ATIM_LOCK_LEVEL Lock Protection Level */
/** @{ */
#define LL_ATIM_LOCK_LEVEL_OFF (0x0UL)
#define LL_ATIM_LOCK_LEVEL_1   (0x1UL)
#define LL_ATIM_LOCK_LEVEL_2   (0x2UL)
#define LL_ATIM_LOCK_LEVEL_3   (0x3UL)
/** @} */

/** @defgroup LL_ATIM_BREAK_POLARITY Break Input Polarity */
/** @{ */
#define LL_ATIM_BREAK_POL_LOW  (0x0UL)
#define LL_ATIM_BREAK_POL_HIGH (0x1UL)
/** @} */

/** @defgroup LL_ATIM_RCR Repetition Counter Mask */
/** @{ */
#define LL_ATIM_RCR_REP_Msk ATIM_RCR_REP_Msk
/** @} */

/*==============================================================================
 * Basic Control
 *============================================================================*/

static inline void ll_atim_enable(ATIM_TypeDef *tim)
{
	SET_BIT(tim->CR1, ATIM_CR1_CEN);
}

static inline void ll_atim_disable(ATIM_TypeDef *tim)
{
	CLEAR_BIT(tim->CR1, ATIM_CR1_CEN);
}

static inline uint32_t ll_atim_is_enabled(ATIM_TypeDef *tim)
{
	return READ_BIT(tim->CR1, ATIM_CR1_CEN) ? 1UL : 0UL;
}

static inline void ll_atim_enable_main_output(ATIM_TypeDef *tim)
{
	SET_BIT(tim->BDTR, ATIM_BDTR_MOE);
}

static inline void ll_atim_disable_main_output(ATIM_TypeDef *tim)
{
	CLEAR_BIT(tim->BDTR, ATIM_BDTR_MOE);
}

static inline void ll_atim_generate_update(ATIM_TypeDef *tim)
{
	WRITE_REG(tim->EGR, ATIM_EGR_UG);
}

/*==============================================================================
 * Counter Configuration
 *============================================================================*/

static inline void ll_atim_set_counter_mode(ATIM_TypeDef *tim, uint32_t mode)
{
	MODIFY_REG(tim->CR1, ATIM_CR1_CMS,
		   MAKE_REG_VAL(mode, ATIM_CR1_CMS_Msk, ATIM_CR1_CMS_Pos));
}

static inline void ll_atim_set_direction(ATIM_TypeDef *tim, uint32_t dir)
{
	MODIFY_REG(tim->CR1, ATIM_CR1_DIR,
		   MAKE_REG_VAL(dir, ATIM_CR1_DIR_Msk, ATIM_CR1_DIR_Pos));
}

static inline void ll_atim_enable_one_pulse(ATIM_TypeDef *tim)
{
	SET_BIT(tim->CR1, ATIM_CR1_OPM);
}

static inline void ll_atim_enable_auto_reload_preload(ATIM_TypeDef *tim)
{
	SET_BIT(tim->CR1, ATIM_CR1_ARPE);
}

/*==============================================================================
 * Prescaler, Auto-Reload, Repetition
 *============================================================================*/

static inline void ll_atim_set_prescaler(ATIM_TypeDef *tim, uint16_t psc)
{
	WRITE_REG(tim->PSC, psc);
}

static inline uint16_t ll_atim_get_prescaler(ATIM_TypeDef *tim)
{
	return (uint16_t)READ_REG(tim->PSC);
}

static inline void ll_atim_set_auto_reload(ATIM_TypeDef *tim, uint32_t arr)
{
	WRITE_REG(tim->ARR, arr);
}

static inline uint32_t ll_atim_get_auto_reload(ATIM_TypeDef *tim)
{
	return READ_REG(tim->ARR);
}

static inline void ll_atim_set_repetition(ATIM_TypeDef *tim, uint16_t rep)
{
	MODIFY_REG(tim->RCR, LL_ATIM_RCR_REP_Msk,
		   MAKE_REG_VAL(rep, LL_ATIM_RCR_REP_Msk, ATIM_RCR_REP_Pos));
}

/**
 * @brief Set the ATIM lock protection level.
 * @param[in] tim ATIM instance pointer.
 * @param[in] level Lock level, one of @ref LL_ATIM_LOCK_LEVEL.
 * @note A non-zero lock level can only be written once after reset and cannot
 *       be cleared or reduced.
 */
static inline void ll_atim_set_lock_level(ATIM_TypeDef *tim, uint32_t level)
{
	MODIFY_REG(tim->AF1, ATIM_AF1_LOCK,
		   MAKE_REG_VAL(level, ATIM_AF1_LOCK_Msk, ATIM_AF1_LOCK_Pos));
}

/*==============================================================================
 * Counter Value
 *============================================================================*/

static inline void ll_atim_set_counter(ATIM_TypeDef *tim, uint32_t cnt)
{
	WRITE_REG(tim->CNT, cnt);
}

static inline uint32_t ll_atim_get_counter(ATIM_TypeDef *tim)
{
	return READ_REG(tim->CNT);
}

/*==============================================================================
 * Capture/Compare Channels
 *============================================================================*/

/**
 * @brief Set compare/capture value for a channel.
 * @param[in] tim ATIM instance pointer.
 * @param[in] ch Channel number in the range 1 to 6.
 * @param[in] val Compare/capture value.
 * @note Invalid channel numbers are ignored.
 */
static inline void ll_atim_set_compare(ATIM_TypeDef *tim, uint32_t ch, uint32_t val)
{
	switch (ch) {
	case 1:
		WRITE_REG(tim->CCR1, val);
		break;
	case 2:
		WRITE_REG(tim->CCR2, val);
		break;
	case 3:
		WRITE_REG(tim->CCR3, val);
		break;
	case 4:
		WRITE_REG(tim->CCR4, val);
		break;
	case 5:
		WRITE_REG(tim->CCR5, val);
		break;
	case 6:
		WRITE_REG(tim->CCR6, val);
		break;
	default:
		break;
	}
}

/**
 * @brief Read capture value for a channel.
 * @param[in] tim ATIM instance pointer.
 * @param[in] ch Channel number in the range 1 to 4.
 * @return Capture value, or 0 for an invalid channel number.
 */
static inline uint32_t ll_atim_get_capture(ATIM_TypeDef *tim, uint32_t ch)
{
	switch (ch) {
	case 1:
		return READ_REG(tim->CCR1);
	case 2:
		return READ_REG(tim->CCR2);
	case 3:
		return READ_REG(tim->CCR3);
	case 4:
		return READ_REG(tim->CCR4);
	default:
		return 0U;
	}
}

/**
 * @brief Enable channel output (CCER.CCxE)
 * @param[in] tim ATIM instance pointer.
 * @param[in] ch Channel number in the range 1 to 6.
 * @note Invalid channel numbers are ignored.
 */
static inline void ll_atim_enable_channel(ATIM_TypeDef *tim, uint32_t ch)
{
	switch (ch) {
	case 1:
		SET_BIT(tim->CCER, ATIM_CCER_CC1E);
		break;
	case 2:
		SET_BIT(tim->CCER, ATIM_CCER_CC2E);
		break;
	case 3:
		SET_BIT(tim->CCER, ATIM_CCER_CC3E);
		break;
	case 4:
		SET_BIT(tim->CCER, ATIM_CCER_CC4E);
		break;
	case 5:
		SET_BIT(tim->CCER, ATIM_CCER_CC5E);
		break;
	case 6:
		SET_BIT(tim->CCER, ATIM_CCER_CC6E);
		break;
	default:
		break;
	}
}

/**
 * @brief Disable channel output (CCER.CCxE).
 * @param[in] tim ATIM instance pointer.
 * @param[in] ch Channel number in the range 1 to 6.
 * @note Invalid channel numbers are ignored.
 */
static inline void ll_atim_disable_channel(ATIM_TypeDef *tim, uint32_t ch)
{
	switch (ch) {
	case 1:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC1E);
		break;
	case 2:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC2E);
		break;
	case 3:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC3E);
		break;
	case 4:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC4E);
		break;
	case 5:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC5E);
		break;
	case 6:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC6E);
		break;
	default:
		break;
	}
}

/**
 * @brief Enable complementary output (CCER.CCxNE)
 * @param[in] tim ATIM instance pointer.
 * @param[in] ch Channel number in the range 1 to 3.
 * @note Invalid channel numbers are ignored.
 */
static inline void ll_atim_enable_complementary(ATIM_TypeDef *tim, uint32_t ch)
{
	switch (ch) {
	case 1:
		SET_BIT(tim->CCER, ATIM_CCER_CC1NE);
		break;
	case 2:
		SET_BIT(tim->CCER, ATIM_CCER_CC2NE);
		break;
	case 3:
		SET_BIT(tim->CCER, ATIM_CCER_CC3NE);
		break;
	default:
		break;
	}
}

/**
 * @brief Disable complementary output (CCER.CCxNE).
 * @param[in] tim ATIM instance pointer.
 * @param[in] ch Channel number in the range 1 to 3.
 * @note Invalid channel numbers are ignored.
 */
static inline void ll_atim_disable_complementary(ATIM_TypeDef *tim, uint32_t ch)
{
	switch (ch) {
	case 1:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC1NE);
		break;
	case 2:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC2NE);
		break;
	case 3:
		CLEAR_BIT(tim->CCER, ATIM_CCER_CC3NE);
		break;
	default:
		break;
	}
}

/**
 * @brief Set channel output polarity (CCER.CCxP)
 * @param[in] tim ATIM instance pointer.
 * @param[in] ch Channel number in the range 1 to 6.
 * @param[in] pol 0 for active high, 1 for active low.
 * @note Invalid channel numbers are ignored.
 */
static inline void ll_atim_set_channel_polarity(ATIM_TypeDef *tim, uint32_t ch, uint32_t pol)
{
	switch (ch) {
	case 1:
		MODIFY_REG(tim->CCER, ATIM_CCER_CC1P, pol ? ATIM_CCER_CC1P : 0UL);
		break;
	case 2:
		MODIFY_REG(tim->CCER, ATIM_CCER_CC2P, pol ? ATIM_CCER_CC2P : 0UL);
		break;
	case 3:
		MODIFY_REG(tim->CCER, ATIM_CCER_CC3P, pol ? ATIM_CCER_CC3P : 0UL);
		break;
	case 4:
		MODIFY_REG(tim->CCER, ATIM_CCER_CC4P, pol ? ATIM_CCER_CC4P : 0UL);
		break;
	case 5:
		MODIFY_REG(tim->CCER, ATIM_CCER_CC5P, pol ? ATIM_CCER_CC5P : 0UL);
		break;
	case 6:
		MODIFY_REG(tim->CCER, ATIM_CCER_CC6P, pol ? ATIM_CCER_CC6P : 0UL);
		break;
	default:
		break;
	}
}

/**
 * @brief Set channel output compare mode (CCMRx.OCxM).
 * @param[in] tim  ATIM instance pointer.
 * @param[in] ch   Channel number in the range 1 to 4.
 * @param[in] mode Output compare mode, see @ref LL_ATIM_OC_MODE_*.
 * @note Invalid channel numbers are ignored.
 */
static inline void ll_atim_set_channel_oc_mode(ATIM_TypeDef *tim, uint32_t ch, uint32_t mode)
{
	switch (ch) {
	case 1:
		MODIFY_REG(tim->CCMR1, ATIM_CCMR1_OC1M,
			   MAKE_REG_VAL(mode, ATIM_CCMR1_OC1M_Msk, ATIM_CCMR1_OC1M_Pos));
		break;
	case 2:
		MODIFY_REG(tim->CCMR1, ATIM_CCMR1_OC2M,
			   MAKE_REG_VAL(mode, ATIM_CCMR1_OC2M_Msk, ATIM_CCMR1_OC2M_Pos));
		break;
	case 3:
		MODIFY_REG(tim->CCMR2, ATIM_CCMR2_OC3M,
			   MAKE_REG_VAL(mode, ATIM_CCMR2_OC3M_Msk, ATIM_CCMR2_OC3M_Pos));
		break;
	case 4:
		MODIFY_REG(tim->CCMR2, ATIM_CCMR2_OC4M,
			   MAKE_REG_VAL(mode, ATIM_CCMR2_OC4M_Msk, ATIM_CCMR2_OC4M_Pos));
		break;
	default:
		break;
	}
}

/**
 * @brief Enable or disable channel output compare preload (CCMRx.OCxPE).
 * @param[in] tim    ATIM instance pointer.
 * @param[in] ch     Channel number in the range 1 to 4.
 * @param[in] enable 1 to enable preload, 0 to disable.
 * @note Invalid channel numbers are ignored.
 */
static inline void ll_atim_set_channel_preload(ATIM_TypeDef *tim, uint32_t ch, uint32_t enable)
{
	switch (ch) {
	case 1:
		MODIFY_REG(tim->CCMR1, ATIM_CCMR1_OC1PE, enable ? ATIM_CCMR1_OC1PE : 0UL);
		break;
	case 2:
		MODIFY_REG(tim->CCMR1, ATIM_CCMR1_OC2PE, enable ? ATIM_CCMR1_OC2PE : 0UL);
		break;
	case 3:
		MODIFY_REG(tim->CCMR2, ATIM_CCMR2_OC3PE, enable ? ATIM_CCMR2_OC3PE : 0UL);
		break;
	case 4:
		MODIFY_REG(tim->CCMR2, ATIM_CCMR2_OC4PE, enable ? ATIM_CCMR2_OC4PE : 0UL);
		break;
	default:
		break;
	}
}

/*==============================================================================
 * Dead-Time (BDTR)
 *============================================================================*/

/**
 * @brief Set the raw dead-time generator value.
 * @param[in] tim ATIM instance pointer.
 * @param[in] dtg Dead-time generator value in the range 0 to 1023.
 * @note A value of zero disables dead-time. For non-zero values, dead-time is
 *       (dtg + 1) timer clock cycles, or 16 times that value when DTPSC is set.
 */
static inline void ll_atim_set_dead_time(ATIM_TypeDef *tim, uint16_t dtg)
{
	MODIFY_REG(tim->BDTR, ATIM_BDTR_DTG,
		   MAKE_REG_VAL(dtg, ATIM_BDTR_DTG_Msk, ATIM_BDTR_DTG_Pos));
}

static inline void ll_atim_enable_dead_time_prescaler(ATIM_TypeDef *tim)
{
	SET_BIT(tim->BDTR, ATIM_BDTR_DTPSC);
}

static inline void ll_atim_disable_dead_time_prescaler(ATIM_TypeDef *tim)
{
	CLEAR_BIT(tim->BDTR, ATIM_BDTR_DTPSC);
}

/*==============================================================================
 * Break Control (BDTR)
 *============================================================================*/

static inline void ll_atim_enable_break(ATIM_TypeDef *tim)
{
	SET_BIT(tim->BDTR, ATIM_BDTR_BKE);
}

static inline void ll_atim_disable_break(ATIM_TypeDef *tim)
{
	CLEAR_BIT(tim->BDTR, ATIM_BDTR_BKE);
}

/*==============================================================================
 * Interrupt
 *============================================================================*/

static inline void ll_atim_enable_update_interrupt(ATIM_TypeDef *tim)
{
	SET_BIT(tim->DIER, ATIM_DIER_UIE);
}

static inline void ll_atim_disable_update_interrupt(ATIM_TypeDef *tim)
{
	CLEAR_BIT(tim->DIER, ATIM_DIER_UIE);
}

static inline uint32_t ll_atim_get_update_flag(ATIM_TypeDef *tim)
{
	return READ_BIT(tim->SR, ATIM_SR_UIF) ? 1UL : 0UL;
}

static inline void ll_atim_clear_update_flag(ATIM_TypeDef *tim)
{
	WRITE_REG(tim->SR, ~ATIM_SR_UIF);
}

static inline void ll_atim_enable_break_interrupt(ATIM_TypeDef *tim)
{
	SET_BIT(tim->DIER, ATIM_DIER_BIE);
}

static inline uint32_t ll_atim_get_break_flag(ATIM_TypeDef *tim)
{
	return READ_BIT(tim->SR, ATIM_SR_BIF) ? 1UL : 0UL;
}

static inline void ll_atim_clear_break_flag(ATIM_TypeDef *tim)
{
	WRITE_REG(tim->SR, ~ATIM_SR_BIF);
}

/*==============================================================================
 * Frequency Calculation
 *============================================================================*/

static inline uint32_t ll_atim_calc_update_freq(uint32_t clk_freq, uint16_t psc, uint32_t arr)
{
	return (uint32_t)(clk_freq / (((uint64_t)psc + 1U) * ((uint64_t)arr + 1U)));
}

/**
 * @brief Calculate the compare value for a PWM duty cycle.
 * @param[in] arr Auto-reload value.
 * @param[in] permille Duty cycle in the range 0 to 1000.
 * @return Compare value corresponding to @p permille.
 */
static inline uint32_t ll_atim_calc_pwm_duty(uint32_t arr, uint32_t permille)
{
	return (uint32_t)((((uint64_t)arr + 1U) * permille) / 1000U);
}

#ifdef __cplusplus
}
#endif

#endif /* __LL_ATIM_H */
