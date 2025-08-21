#ifndef PWR_H
#define PWR_H

/* includes */
#include "std_types.h"
#include "common_macros.h"
#include "stm32f4xx.h"

/* definitions */

#define __WFI() __asm("wfi") // wait for interrupts assembly instruction
#define __WFE() __asm("wfe") // wait for events assembly instruction
#define __NOP() __asm("nop") // no operation assembly instrcution
#define SCB_AIRCR_VECTKEY_MSK (0x5FAU << 16)
#define SCB_AIRCR_SYSRESETREQ_MSK (1 << 2)

/* RCC bit definitions */

#define RCC_APB1ENR_PWR_EN 28U
#define RCC_APB1RSTR_PWR_RSTR 28U

/* SCB bit definitions */

#define SCB_CR_DEEPSLEEP 2U

/* PWR_CR register bit definitions */
#define PWR_CR_LPDS 0U   // Low Power Sleep Deep Sleep
#define PWR_CR_PDDS 1U   // Power Down Deep Sleep
#define PWR_CR_CWUF 2U   // Clear Wakeup Flag
#define PWR_CR_CSBF 3U   // Clear Standby Flag
#define PWR_CR_PVDE 4U   // Power Voltage Detector Enable
#define PWR_CR_PLS 5U    // Power Voltage Level Selection
#define PWR_CR_DBP 8U    // disable backup domain write protection
#define PWR_CR_FPDEN 9U  // Fast Power Down Enable
#define PWR_CR_DBP 11U   // Disable Backup Domain Write Protection
#define PWR_CR_LPUDS 13U // Low Power Run Deep Sleep
#define PWR_CR_VOS 14U   // Voltage Scaling Selection

/* PWR_CSR register bit definitions */
#define PWR_CSR_WUF 0U     // Wakeup Flag
#define PWR_CSR_SBF 1U     // Standby Flag
#define PWR_CSR_PVDO 2U    // Power Voltage Detector Output
#define PWR_CSR_BRR 3U     // Backup Regulator Ready
#define PWR_CSR_EWUP 8U    // Enable WKUP pin
#define PWR_CSR_BRE 9U     // Backup Regulator Enable
#define PWR_CSR_VOSRDY 14U // Voltage Scaling Ready

/* types */

/* prototypes */
void mcu_sleep(void);
void mcu_stop(void);
void mcu_standby(void);
void mcu_software_reset(void);
#endif