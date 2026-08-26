/*
 * SPDX-FileCopyrightText: 2026 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LL_HPSYS_CFG_H
#define __LL_HPSYS_CFG_H

#include <stdint.h>
#include "hpsys_cfg.h"
#include "cmsis_utils.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file ll_hpsys_cfg.h
 * @brief Header-only low-level HPSYS_CFG shared definitions for SF32LB52x.
 */

/**
 * @brief Get the boot mode (BMR.BOOT_MODE).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return 0 = normal mode, 1 = download mode.
 */
static inline uint32_t ll_cfg_get_boot_mode(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_BIT(CFGx->BMR, HPSYS_CFG_BMR_BOOT_MODE) ? 1UL : 0UL;
}

/**
 * @brief Get the chip ID register (IDR).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Raw IDR value.
 */
static inline uint32_t ll_cfg_get_id(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_REG(CFGx->IDR);
}

/**
 * @brief Get the series ID (IDR.SID[31:24]).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Series ID.
 */
static inline uint32_t ll_cfg_get_series_id(HPSYS_CFG_TypeDef *CFGx)
{
    return GET_REG_VAL2(CFGx->IDR, HPSYS_CFG_IDR_SID);
}

/**
 * @brief Get the chip ID (IDR.CID[23:16]).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Chip ID.
 */
static inline uint32_t ll_cfg_get_chip_id(HPSYS_CFG_TypeDef *CFGx)
{
    return GET_REG_VAL2(CFGx->IDR, HPSYS_CFG_IDR_CID);
}

/**
 * @brief Get the package ID (IDR.PID[15:8]).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Package ID.
 */
static inline uint32_t ll_cfg_get_package_id(HPSYS_CFG_TypeDef *CFGx)
{
    return GET_REG_VAL2(CFGx->IDR, HPSYS_CFG_IDR_PID);
}

/**
 * @brief Get the ECO revision ID (IDR.REVID[7:0]).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return ECO revision ID.
 */
static inline uint32_t ll_cfg_get_revision_id(HPSYS_CFG_TypeDef *CFGx)
{
    return GET_REG_VAL2(CFGx->IDR, HPSYS_CFG_IDR_REVID);
}

/**
 * @brief Select the host of the debug SWD interface (SWCR.SWSEL).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] sel  0 = SW connected to HCPU, 1 = SW connected to LCPU.
 */
static inline void ll_cfg_set_sw_selection(HPSYS_CFG_TypeDef *CFGx, uint32_t sel)
{
    MODIFY_REG(CFGx->SWCR, HPSYS_CFG_SWCR_SWSEL,
               MAKE_REG_VAL(sel, HPSYS_CFG_SWCR_SWSEL_Msk, HPSYS_CFG_SWCR_SWSEL_Pos));
}

/**
 * @brief Get the SWD host selection (SWCR.SWSEL).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return 0 = HCPU, 1 = LCPU.
 */
static inline uint32_t ll_cfg_get_sw_selection(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_BIT(CFGx->SWCR, HPSYS_CFG_SWCR_SWSEL) ? 1UL : 0UL;
}

/**
 * @brief Set the root key encryption mode (SCR.FKEY_MODE).
 * @param[in] CFGx  HPSYS_CFG instance pointer.
 * @param[in] mode  FKEY mode: 1 = AES uses dedicated algorithm for root key.
 */
static inline void ll_cfg_set_fkey_mode(HPSYS_CFG_TypeDef *CFGx, uint32_t mode)
{
    MODIFY_REG(CFGx->SCR, HPSYS_CFG_SCR_FKEY_MODE,
               MAKE_REG_VAL(mode, HPSYS_CFG_SCR_FKEY_MODE_Msk, HPSYS_CFG_SCR_FKEY_MODE_Pos));
}

/**
 * @brief Set the LDO voltage select shortcut (SYSCR.LDO_VSEL).
 * @param[in] CFGx  HPSYS_CFG instance pointer.
 * @param[in] vsel  LDO voltage select (1 bit).
 */
static inline void ll_cfg_set_ldo_vsel(HPSYS_CFG_TypeDef *CFGx, uint32_t vsel)
{
    MODIFY_REG(CFGx->SYSCR, HPSYS_CFG_SYSCR_LDO_VSEL,
               MAKE_REG_VAL(vsel, HPSYS_CFG_SYSCR_LDO_VSEL_Msk, HPSYS_CFG_SYSCR_LDO_VSEL_Pos));
}

/*==============================================================================
 * System Reset Control (SYSCR)
 *============================================================================*/

/**
 * @brief Get the RTC time shadow register (RTC_TR).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Raw RTC time value.
 */
static inline uint32_t ll_cfg_get_rtc_time(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_REG(CFGx->RTC_TR) &
           (HPSYS_CFG_RTC_TR_PM | HPSYS_CFG_RTC_TR_HT |
            HPSYS_CFG_RTC_TR_HU | HPSYS_CFG_RTC_TR_MNT |
            HPSYS_CFG_RTC_TR_MNU | HPSYS_CFG_RTC_TR_ST |
            HPSYS_CFG_RTC_TR_SU | HPSYS_CFG_RTC_TR_SS);
}

/**
 * @brief Get the RTC date shadow register (RTC_DR).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Raw RTC date value.
 */
static inline uint32_t ll_cfg_get_rtc_date(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_REG(CFGx->RTC_DR) &
           (HPSYS_CFG_RTC_DR_ERR | HPSYS_CFG_RTC_DR_CB |
            HPSYS_CFG_RTC_DR_YT | HPSYS_CFG_RTC_DR_YU |
            HPSYS_CFG_RTC_DR_WD | HPSYS_CFG_RTC_DR_MT |
            HPSYS_CFG_RTC_DR_MU | HPSYS_CFG_RTC_DR_DT |
            HPSYS_CFG_RTC_DR_DU);
}

/**
 * @brief Enable the ULP ROM retention mode (ULPMCR.ROM_RME).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_ulp_rom_rm_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_ROM_RME);
}

/**
 * @brief Disable the ULP ROM retention mode (ULPMCR.ROM_RME = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_ulp_rom_rm_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_ROM_RME);
}

/**
 * @brief Set the ULP ROM retention mode (ULPMCR.ROM_RM).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] rm   ROM retention mode (2 bits).
 */
static inline void ll_cfg_set_ulp_rom_rm(HPSYS_CFG_TypeDef *CFGx, uint32_t rm)
{
    MODIFY_REG(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_ROM_RM,
               MAKE_REG_VAL(rm, HPSYS_CFG_ULPMCR_ROM_RM_Msk, HPSYS_CFG_ULPMCR_ROM_RM_Pos));
}

/**
 * @brief Set the ULP SRAM write pulse width (ULPMCR.RAM_WPULSE).
 * @param[in] CFGx   HPSYS_CFG instance pointer.
 * @param[in] wpulse Write pulse width (3 bits).
 */
static inline void ll_cfg_set_ulp_ram_wpulse(HPSYS_CFG_TypeDef *CFGx, uint32_t wpulse)
{
    MODIFY_REG(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_RAM_WPULSE,
               MAKE_REG_VAL(wpulse, HPSYS_CFG_ULPMCR_RAM_WPULSE_Msk, HPSYS_CFG_ULPMCR_RAM_WPULSE_Pos));
}

/**
 * @brief Set the ULP SRAM wake address (ULPMCR.RAM_WA).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] wa   Wake address (3 bits).
 */
static inline void ll_cfg_set_ulp_ram_wa(HPSYS_CFG_TypeDef *CFGx, uint32_t wa)
{
    MODIFY_REG(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_RAM_WA,
               MAKE_REG_VAL(wa, HPSYS_CFG_ULPMCR_RAM_WA_Msk, HPSYS_CFG_ULPMCR_RAM_WA_Pos));
}

/**
 * @brief Set the ULP SRAM retention address (ULPMCR.RAM_RA).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] ra   Retention address (3 bits).
 */
static inline void ll_cfg_set_ulp_ram_ra(HPSYS_CFG_TypeDef *CFGx, uint32_t ra)
{
    MODIFY_REG(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_RAM_RA,
               MAKE_REG_VAL(ra, HPSYS_CFG_ULPMCR_RAM_RA_Msk, HPSYS_CFG_ULPMCR_RAM_RA_Pos));
}

/**
 * @brief Enable the ULP SRAM retention mode (ULPMCR.RAM_RME).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_ulp_ram_rm_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_RAM_RME);
}

/**
 * @brief Disable the ULP SRAM retention mode (ULPMCR.RAM_RME = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_ulp_ram_rm_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_RAM_RME);
}

/**
 * @brief Set the ULP SRAM retention mode (ULPMCR.RAM_RM).
 * @param[in] CFGx   HPSYS_CFG instance pointer.
 * @param[in] rm     SRAM retention mode (2 bits).
 */
static inline void ll_cfg_set_ulp_ram_rm(HPSYS_CFG_TypeDef *CFGx, uint32_t rm)
{
    MODIFY_REG(CFGx->ULPMCR, HPSYS_CFG_ULPMCR_RAM_RM,
               MAKE_REG_VAL(rm, HPSYS_CFG_ULPMCR_RAM_RM_Msk, HPSYS_CFG_ULPMCR_RAM_RM_Pos));
}

/**
 * @brief Swap the upper/lower byte of debug data (DBGR.SWAP).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] swap 1 = swap, 0 = no swap.
 */
static inline void ll_cfg_set_dbg_swap(HPSYS_CFG_TypeDef *CFGx, uint32_t swap)
{
    MODIFY_REG(CFGx->DBGR, HPSYS_CFG_DBGR_SWAP,
               MAKE_REG_VAL(swap, HPSYS_CFG_DBGR_SWAP_Msk, HPSYS_CFG_DBGR_SWAP_Pos));
}

/**
 * @brief Get the LP2HP NMI interrupt flag (DBGR.LP2HP_NMIF).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Non-zero when the LP2HP NMI flag is set.
 */
static inline uint32_t ll_cfg_get_dbg_lp2hp_nmi_flag(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_BIT(CFGx->DBGR, HPSYS_CFG_DBGR_LP2HP_NMIF) ? 1UL : 0UL;
}

/**
 * @brief Enable the LP2HP NMI interrupt (DBGR.LP2HP_NMIE).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_dbg_lp2hp_nmi_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->DBGR, HPSYS_CFG_DBGR_LP2HP_NMIE);
}

/**
 * @brief Disable the LP2HP NMI interrupt (DBGR.LP2HP_NMIE = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_dbg_lp2hp_nmi_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->DBGR, HPSYS_CFG_DBGR_LP2HP_NMIE);
}

/**
 * @brief Send an NMI to the LCPU (DBGR.HP2LP_NMI).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_dbg_hp2lp_nmi(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->DBGR, HPSYS_CFG_DBGR_HP2LP_NMI);
}

/**
 * @brief Clear the HP2LP NMI request (DBGR.HP2LP_NMI = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_dbg_hp2lp_nmi_clear(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->DBGR, HPSYS_CFG_DBGR_HP2LP_NMI);
}

/**
     * @brief Disable the ROM access (MDBGR.DIS_ROM).
     * @param[in] CFGx HPSYS_CFG instance pointer.
     */
static inline void ll_cfg_disable_rom(HPSYS_CFG_TypeDef *CFGx)
{
        SET_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_DIS_ROM);
}

/**
     * @brief Enable the ROM access (MDBGR.DIS_ROM).
     * @param[in] CFGx HPSYS_CFG instance pointer.
     */
static inline void ll_cfg_enable_rom(HPSYS_CFG_TypeDef *CFGx)
{
        CLEAR_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_DIS_ROM);
}

/**
 * @brief Power down the ROM during deep sleep (MDBGR.PD_ROM).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_pd_rom_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_PD_ROM);
}

/**
 * @brief Keep the ROM powered during deep sleep (MDBGR.PD_ROM = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_pd_rom_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_PD_ROM);
}

/**
 * @brief Force ROM into light sleep during active (MDBGR.LS_ROM).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_ls_rom_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_LS_ROM);
}

/**
 * @brief Release ROM light sleep force (MDBGR.LS_ROM = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_ls_rom_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_LS_ROM);
}

/**
 * @brief Force RAM2 into light sleep during active (MDBGR.LS_RAM2).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_ls_ram2_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_LS_RAM2);
}

/**
 * @brief Release RAM2 light sleep force (MDBGR.LS_RAM2 = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_ls_ram2_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_LS_RAM2);
}

/**
 * @brief Force RAM1 into light sleep during active (MDBGR.LS_RAM1).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_ls_ram1_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_LS_RAM1);
}

/**
 * @brief Release RAM1 light sleep force (MDBGR.LS_RAM1 = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_ls_ram1_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_LS_RAM1);
}

/**
 * @brief Force RAM0 into light sleep during active (MDBGR.LS_RAM0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_ls_ram0_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_LS_RAM0);
}

/**
 * @brief Release RAM0 light sleep force (MDBGR.LS_RAM0 = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_mdbg_ls_ram0_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->MDBGR, HPSYS_CFG_MDBGR_LS_RAM0);
}

/**
 * @brief Check whether the all-in-one BIST failed (BISTCR.BIST_FAIL).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Non-zero when BIST failed.
 */
static inline uint32_t ll_cfg_is_bist_failed(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_BIT(CFGx->BISTCR, HPSYS_CFG_BISTCR_BIST_FAIL) ? 1UL : 0UL;
}

/**
 * @brief Check whether the all-in-one BIST is done (BISTCR.BIST_DONE).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Non-zero when BIST is done.
 */
static inline uint32_t ll_cfg_is_bist_done(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_BIT(CFGx->BISTCR, HPSYS_CFG_BISTCR_BIST_DONE) ? 1UL : 0UL;
}

/**
 * @brief Enable the BIST mode (BISTCR.BIST_MODE).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_bist_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->BISTCR, HPSYS_CFG_BISTCR_BIST_MODE);
}

/**
 * @brief Disable the BIST mode (BISTCR.BIST_MODE = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_bist_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->BISTCR, HPSYS_CFG_BISTCR_BIST_MODE);
}

/**
 * @brief Get the BIST result (BISTR).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @return Raw BISTR value.
 */
static inline uint32_t ll_cfg_get_bist_result(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_REG(CFGx->BISTR) &
           (HPSYS_CFG_BISTR_BIST_FAIL_ROM | HPSYS_CFG_BISTR_BIST_FAIL_RAM |
            HPSYS_CFG_BISTR_BIST_FAIL_HCPU | HPSYS_CFG_BISTR_BIST_FAIL_EPIC |
            HPSYS_CFG_BISTR_BIST_FAIL_EZIP | HPSYS_CFG_BISTR_BIST_FAIL_SDMMC1 |
            HPSYS_CFG_BISTR_BIST_FAIL_USBC | HPSYS_CFG_BISTR_BIST_FAIL_AUD);
}

/**
 * @brief Set a ROM compare register by index (ROMCR0..ROMCR1).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] idx  ROM index, 0..1.
 * @param[in] val  Compare value.
 */
static inline void ll_cfg_set_rom_compare(HPSYS_CFG_TypeDef *CFGx, uint32_t idx, uint32_t val)
{
    if (idx < 2U) {
        (&CFGx->ROMCR0)[idx] = val;
    }
}

/**
 * @brief Get a ROM compare register by index (ROMCR0..ROMCR1).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] idx  ROM index, 0..1.
 * @return Compare value, or 0 if idx is out of range.
 */
static inline uint32_t ll_cfg_get_rom_compare(HPSYS_CFG_TypeDef *CFGx, uint32_t idx)
{
    return (idx < 2U) ? (&CFGx->ROMCR0)[idx] : 0UL;
}

/**
 * @brief Get the LCPU interrupt status flag (LPIRQ.IF0/IF1).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] idx  Interrupt index, 0 or 1.
 * @return Non-zero when the flag is set.
 */
static inline uint32_t ll_cfg_get_lpirq_flag(HPSYS_CFG_TypeDef *CFGx, uint32_t idx)
{
    return READ_BIT(CFGx->LPIRQ,
                    (idx == 0U) ? HPSYS_CFG_LPIRQ_IF0 : HPSYS_CFG_LPIRQ_IF1) ? 1UL : 0UL;
}

/**
 * @brief Clear the LCPU interrupt status flag (LPIRQ.IF0/IF1, write 1 to clear).
 * @note The SEL bits are preserved; only the rw1c IF bit is written.
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] idx  Interrupt index, 0 or 1.
 */
static inline void ll_cfg_clear_lpirq_flag(HPSYS_CFG_TypeDef *CFGx, uint32_t idx)
{
    if (idx == 0U) {
        WRITE_REG(CFGx->LPIRQ,
                  (READ_REG(CFGx->LPIRQ) & HPSYS_CFG_LPIRQ_SEL0) | HPSYS_CFG_LPIRQ_IF0);
    } else {
        WRITE_REG(CFGx->LPIRQ,
                  (READ_REG(CFGx->LPIRQ) & HPSYS_CFG_LPIRQ_SEL1) | HPSYS_CFG_LPIRQ_IF1);
    }
}

/**
 * @brief Set the LCPU interrupt source selection (LPIRQ.SEL0/SEL1).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] idx  Interrupt index, 0 or 1.
 * @param[in] sel  Source select (6 bits).
 */
static inline void ll_cfg_set_lpirq_select(HPSYS_CFG_TypeDef *CFGx, uint32_t idx, uint32_t sel)
{
    if (idx == 0U) {
        MODIFY_REG(CFGx->LPIRQ, HPSYS_CFG_LPIRQ_SEL0,
                   MAKE_REG_VAL(sel, HPSYS_CFG_LPIRQ_SEL0_Msk, HPSYS_CFG_LPIRQ_SEL0_Pos));
    } else {
        MODIFY_REG(CFGx->LPIRQ, HPSYS_CFG_LPIRQ_SEL1,
                   MAKE_REG_VAL(sel, HPSYS_CFG_LPIRQ_SEL1_Msk, HPSYS_CFG_LPIRQ_SEL1_Pos));
    }
}

/**
 * @brief Set the USB DC test point and macro select (USBCR.DC_TR/DC_TE).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] tr   DC test point select (3 bits).
 * @param[in] te   DC test macro select (1 bit).
 */
static inline void ll_cfg_usb_set_dc_test(HPSYS_CFG_TypeDef *CFGx, uint32_t tr, uint32_t te)
{
    MODIFY_REG(CFGx->USBCR, HPSYS_CFG_USBCR_DC_TR | HPSYS_CFG_USBCR_DC_TE,
               MAKE_REG_VAL(tr, HPSYS_CFG_USBCR_DC_TR_Msk, HPSYS_CFG_USBCR_DC_TR_Pos) |
               MAKE_REG_VAL(te, HPSYS_CFG_USBCR_DC_TE_Msk, HPSYS_CFG_USBCR_DC_TE_Pos));
}

/**
 * @brief Set the USB TX output impedance tuning (USBCR.TX_RTUNE).
 * @param[in] CFGx  HPSYS_CFG instance pointer.
 * @param[in] rtune TX impedance tuning (3 bits).
 */
static inline void ll_cfg_usb_set_tx_rtune(HPSYS_CFG_TypeDef *CFGx, uint32_t rtune)
{
    MODIFY_REG(CFGx->USBCR, HPSYS_CFG_USBCR_TX_RTUNE,
               MAKE_REG_VAL(rtune, HPSYS_CFG_USBCR_TX_RTUNE_Msk, HPSYS_CFG_USBCR_TX_RTUNE_Pos));
}

/**
 * @brief Enable the USB DP pull up/down (USBCR.DP_EN).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_usb_dp_en_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->USBCR, HPSYS_CFG_USBCR_DP_EN);
}

/**
 * @brief Disable the USB DP pull up/down (USBCR.DP_EN = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_usb_dp_en_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->USBCR, HPSYS_CFG_USBCR_DP_EN);
}

/**
 * @brief Enable the USB DM 15k pull-down (USBCR.DM_PD).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_usb_dm_pd_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->USBCR, HPSYS_CFG_USBCR_DM_PD);
}

/**
 * @brief Disable the USB DM 15k pull-down (USBCR.DM_PD = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_usb_dm_pd_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->USBCR, HPSYS_CFG_USBCR_DM_PD);
}

/**
 * @brief Enable the USB LDO low power mode (USBCR.LDO_LP_EN).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_usb_ldo_lp_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->USBCR, HPSYS_CFG_USBCR_LDO_LP_EN);
}

/**
 * @brief Disable the USB LDO low power mode (USBCR.LDO_LP_EN = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_usb_ldo_lp_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->USBCR, HPSYS_CFG_USBCR_LDO_LP_EN);
}

/**
 * @brief Set the USB 2.5V LDO output voltage (USBCR.LDO_VSEL).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] vsel LDO voltage select (3 bits).
 */
static inline void ll_cfg_usb_set_ldo_vsel(HPSYS_CFG_TypeDef *CFGx, uint32_t vsel)
{
    MODIFY_REG(CFGx->USBCR, HPSYS_CFG_USBCR_LDO_VSEL,
               MAKE_REG_VAL(vsel, HPSYS_CFG_USBCR_LDO_VSEL_Msk, HPSYS_CFG_USBCR_LDO_VSEL_Pos));
}

/**
 * @brief Enable the USB PHY (USBCR.USB_EN).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_usb_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->USBCR, HPSYS_CFG_USBCR_USB_EN);
}

/**
 * @brief Disable the USB PHY (USBCR.USB_EN = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_usb_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->USBCR, HPSYS_CFG_USBCR_USB_EN);
}

static inline uint32_t ll_cfg_get_sys_reserved(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_REG(CFGx->SYS_RSVD) &
           (HPSYS_CFG_SYS_RSVD_RESERVE0 | HPSYS_CFG_SYS_RSVD_RESERVE1 |
            HPSYS_CFG_SYS_RSVD_RESERVE2 | HPSYS_CFG_SYS_RSVD_RESERVE3);
}

static inline void ll_cfg_set_sys_reserved(HPSYS_CFG_TypeDef *CFGx, uint32_t value)
{
    uint32_t mask = HPSYS_CFG_SYS_RSVD_RESERVE0 |
                    HPSYS_CFG_SYS_RSVD_RESERVE1 |
                    HPSYS_CFG_SYS_RSVD_RESERVE2;

    MODIFY_REG(CFGx->SYS_RSVD, mask, value & mask);
}

/**
 * @brief Set the ANAU DC test mode (ANAU_CR.DC_MR).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] mr   DC test mode (3 bits).
 */
static inline void ll_cfg_set_anau_dc_mr(HPSYS_CFG_TypeDef *CFGx, uint32_t mr)
{
    MODIFY_REG(CFGx->ANAU_CR, HPSYS_CFG_ANAU_CR_DC_MR,
               MAKE_REG_VAL(mr, HPSYS_CFG_ANAU_CR_DC_MR_Msk, HPSYS_CFG_ANAU_CR_DC_MR_Pos));
}

/**
 * @brief Set the eFuse VDD pull-down (ANAU_CR.EFUSE_VDD_PD).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] pd   Pull-down enable (1 bit).
 */
static inline void ll_cfg_set_efuse_vdd_pd(HPSYS_CFG_TypeDef *CFGx, uint32_t pd)
{
    MODIFY_REG(CFGx->ANAU_CR, HPSYS_CFG_ANAU_CR_EFUSE_VDD_PD,
               MAKE_REG_VAL(pd, HPSYS_CFG_ANAU_CR_EFUSE_VDD_PD_Msk, HPSYS_CFG_ANAU_CR_EFUSE_VDD_PD_Pos));
}

/**
 * @brief Enable the eFuse VDD (ANAU_CR.EFUSE_VDD_EN).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_efuse_vdd_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->ANAU_CR, HPSYS_CFG_ANAU_CR_EFUSE_VDD_EN);
}

/**
 * @brief Disable the eFuse VDD (ANAU_CR.EFUSE_VDD_EN = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_efuse_vdd_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->ANAU_CR, HPSYS_CFG_ANAU_CR_EFUSE_VDD_EN);
}

/**
 * @brief Enable the VBAT monitor (ANAU_CR.EN_VBAT_MON).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_vbat_mon_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->ANAU_CR, HPSYS_CFG_ANAU_CR_EN_VBAT_MON);
}

/**
 * @brief Disable the VBAT monitor (ANAU_CR.EN_VBAT_MON = 0).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_vbat_mon_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->ANAU_CR, HPSYS_CFG_ANAU_CR_EN_VBAT_MON);
}

/**
 * @brief Configure one per-field PINR value by register offset and field index.
 * @param[in] CFGx        HPSYS_CFG instance pointer.
 * @param[in] pinr_offset PINR register byte offset from the HPSYS_CFG base
 *                        (e.g. 0x48 for I2C1_PINR).
 * @param[in] pinr_field  PINR field index (0..3), one 8-bit slot per field.
 * @param[in] pad         PAD index (6 bits) to route into the field.
 * @note Used by the pinctrl driver for dynamic per-field PINR updates.
 */
/*==============================================================================
 * ANAU Bandgap (ANAU_CR)
 *============================================================================*/

/**
 * @brief Enable the ANAU bandgap (ANAU_CR.EN_BG).
 * @note Required before TSEN/GPADC analog measurement (see reference manual
 *       8.2.3.3); shared with GPADC, recommended to keep enabled.
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_anau_bandgap_enable(HPSYS_CFG_TypeDef *CFGx)
{
    SET_BIT(CFGx->ANAU_CR, HPSYS_CFG_ANAU_CR_EN_BG);
}

/**
 * @brief Disable the ANAU bandgap (ANAU_CR.EN_BG).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 */
static inline void ll_cfg_anau_bandgap_disable(HPSYS_CFG_TypeDef *CFGx)
{
    CLEAR_BIT(CFGx->ANAU_CR, HPSYS_CFG_ANAU_CR_EN_BG);
}

static inline uint32_t ll_cfg_get_anau_reserved(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_REG(CFGx->ANAU_RSVD) &
           (HPSYS_CFG_ANAU_RSVD_RESERVE0 | HPSYS_CFG_ANAU_RSVD_RESERVE1 |
            HPSYS_CFG_ANAU_RSVD_RESERVE2 | HPSYS_CFG_ANAU_RSVD_RESERVE3);
}

static inline void ll_cfg_set_anau_reserved(HPSYS_CFG_TypeDef *CFGx, uint32_t value)
{
    uint32_t mask = HPSYS_CFG_ANAU_RSVD_RESERVE0 |
                    HPSYS_CFG_ANAU_RSVD_RESERVE1 |
                    HPSYS_CFG_ANAU_RSVD_RESERVE2;

    MODIFY_REG(CFGx->ANAU_RSVD, mask, value & mask);
}

/**
 * @brief Set the analog test point (ANATR).
 * @param[in] CFGx     HPSYS_CFG instance pointer.
 * @param[in] te0      ATEST0 DC test enable.
 * @param[in] ur0      ATEST0 unit resistor select (3 bits).
 * @param[in] te1      ATEST1 DC test enable.
 * @param[in] ur1      ATEST1 unit resistor select (3 bits).
 */
static inline void ll_cfg_set_analog_test(HPSYS_CFG_TypeDef *CFGx, uint32_t te0, uint32_t ur0,
                                          uint32_t te1, uint32_t ur1)
{
    MODIFY_REG(CFGx->ANATR,
               HPSYS_CFG_ANATR_DC_TE_ATEST0 | HPSYS_CFG_ANATR_DC_UR_ATEST0 |
               HPSYS_CFG_ANATR_DC_TE_ATEST1 | HPSYS_CFG_ANATR_DC_UR_ATEST1,
               MAKE_REG_VAL(te0, HPSYS_CFG_ANATR_DC_TE_ATEST0_Msk, HPSYS_CFG_ANATR_DC_TE_ATEST0_Pos) |
               MAKE_REG_VAL(ur0, HPSYS_CFG_ANATR_DC_UR_ATEST0_Msk, HPSYS_CFG_ANATR_DC_UR_ATEST0_Pos) |
               MAKE_REG_VAL(te1, HPSYS_CFG_ANATR_DC_TE_ATEST1_Msk, HPSYS_CFG_ANATR_DC_TE_ATEST1_Pos) |
               MAKE_REG_VAL(ur1, HPSYS_CFG_ANATR_DC_UR_ATEST1_Msk, HPSYS_CFG_ANATR_DC_UR_ATEST1_Pos));
}

/**
 * @brief Set the CAU2 DC test mode (CAU2_CR.DC_MR).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] mr   DC test mode (3 bits).
 */
static inline void ll_cfg_set_cau2_dc_mr(HPSYS_CFG_TypeDef *CFGx, uint32_t mr)
{
    MODIFY_REG(CFGx->CAU2_CR, HPSYS_CFG_CAU2_CR_DC_MR,
               MAKE_REG_VAL(mr, HPSYS_CFG_CAU2_CR_DC_MR_Msk, HPSYS_CFG_CAU2_CR_DC_MR_Pos));
}

/**
 * @brief Set the CAU2 DC bias mode (CAU2_CR.DC_BR).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] br   DC bias mode (3 bits).
 */
static inline void ll_cfg_set_cau2_dc_br(HPSYS_CFG_TypeDef *CFGx, uint32_t br)
{
    MODIFY_REG(CFGx->CAU2_CR, HPSYS_CFG_CAU2_CR_DC_BR,
               MAKE_REG_VAL(br, HPSYS_CFG_CAU2_CR_DC_BR_Msk, HPSYS_CFG_CAU2_CR_DC_BR_Pos));
}

/**
 * @brief Set the CAU2 DC trim (CAU2_CR.DC_TR).
 * @param[in] CFGx HPSYS_CFG instance pointer.
 * @param[in] tr   DC trim (3 bits).
 */
static inline void ll_cfg_set_cau2_dc_tr(HPSYS_CFG_TypeDef *CFGx, uint32_t tr)
{
    MODIFY_REG(CFGx->CAU2_CR, HPSYS_CFG_CAU2_CR_DC_TR,
               MAKE_REG_VAL(tr, HPSYS_CFG_CAU2_CR_DC_TR_Msk, HPSYS_CFG_CAU2_CR_DC_TR_Pos));
}

static inline uint32_t ll_cfg_get_cau2_reserved(HPSYS_CFG_TypeDef *CFGx)
{
    return READ_REG(CFGx->CAU2_RSVD) &
           (HPSYS_CFG_CAU2_RSVD_RESERVE0 | HPSYS_CFG_CAU2_RSVD_RESERVE1 |
            HPSYS_CFG_CAU2_RSVD_RESERVE2);
}

static inline void ll_cfg_set_cau2_reserved(HPSYS_CFG_TypeDef *CFGx, uint32_t value)
{
    MODIFY_REG(CFGx->CAU2_RSVD, HPSYS_CFG_CAU2_RSVD_RESERVE0,
               value & HPSYS_CFG_CAU2_RSVD_RESERVE0);
}

#ifdef __cplusplus
}
#endif

#endif /* __LL_HPSYS_CFG_H */
