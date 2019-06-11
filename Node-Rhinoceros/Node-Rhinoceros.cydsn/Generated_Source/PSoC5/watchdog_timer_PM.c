/*******************************************************************************
* File Name: watchdog_timer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "watchdog_timer.h"

static watchdog_timer_backupStruct watchdog_timer_backup;


/*******************************************************************************
* Function Name: watchdog_timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  watchdog_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void watchdog_timer_SaveConfig(void) 
{
    #if (!watchdog_timer_UsingFixedFunction)
        watchdog_timer_backup.TimerUdb = watchdog_timer_ReadCounter();
        watchdog_timer_backup.InterruptMaskValue = watchdog_timer_STATUS_MASK;
        #if (watchdog_timer_UsingHWCaptureCounter)
            watchdog_timer_backup.TimerCaptureCounter = watchdog_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!watchdog_timer_UDB_CONTROL_REG_REMOVED)
            watchdog_timer_backup.TimerControlRegister = watchdog_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: watchdog_timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  watchdog_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void watchdog_timer_RestoreConfig(void) 
{   
    #if (!watchdog_timer_UsingFixedFunction)

        watchdog_timer_WriteCounter(watchdog_timer_backup.TimerUdb);
        watchdog_timer_STATUS_MASK =watchdog_timer_backup.InterruptMaskValue;
        #if (watchdog_timer_UsingHWCaptureCounter)
            watchdog_timer_SetCaptureCount(watchdog_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!watchdog_timer_UDB_CONTROL_REG_REMOVED)
            watchdog_timer_WriteControlRegister(watchdog_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: watchdog_timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  watchdog_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void watchdog_timer_Sleep(void) 
{
    #if(!watchdog_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(watchdog_timer_CTRL_ENABLE == (watchdog_timer_CONTROL & watchdog_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            watchdog_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            watchdog_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    watchdog_timer_Stop();
    watchdog_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: watchdog_timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  watchdog_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void watchdog_timer_Wakeup(void) 
{
    watchdog_timer_RestoreConfig();
    #if(!watchdog_timer_UDB_CONTROL_REG_REMOVED)
        if(watchdog_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                watchdog_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
