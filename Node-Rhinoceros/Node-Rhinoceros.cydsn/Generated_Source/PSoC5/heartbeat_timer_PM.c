/*******************************************************************************
* File Name: heartbeat_timer_PM.c
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

#include "heartbeat_timer.h"

static heartbeat_timer_backupStruct heartbeat_timer_backup;


/*******************************************************************************
* Function Name: heartbeat_timer_SaveConfig
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
*  heartbeat_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void heartbeat_timer_SaveConfig(void) 
{
    #if (!heartbeat_timer_UsingFixedFunction)
        heartbeat_timer_backup.TimerUdb = heartbeat_timer_ReadCounter();
        heartbeat_timer_backup.InterruptMaskValue = heartbeat_timer_STATUS_MASK;
        #if (heartbeat_timer_UsingHWCaptureCounter)
            heartbeat_timer_backup.TimerCaptureCounter = heartbeat_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!heartbeat_timer_UDB_CONTROL_REG_REMOVED)
            heartbeat_timer_backup.TimerControlRegister = heartbeat_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: heartbeat_timer_RestoreConfig
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
*  heartbeat_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void heartbeat_timer_RestoreConfig(void) 
{   
    #if (!heartbeat_timer_UsingFixedFunction)

        heartbeat_timer_WriteCounter(heartbeat_timer_backup.TimerUdb);
        heartbeat_timer_STATUS_MASK =heartbeat_timer_backup.InterruptMaskValue;
        #if (heartbeat_timer_UsingHWCaptureCounter)
            heartbeat_timer_SetCaptureCount(heartbeat_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!heartbeat_timer_UDB_CONTROL_REG_REMOVED)
            heartbeat_timer_WriteControlRegister(heartbeat_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: heartbeat_timer_Sleep
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
*  heartbeat_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void heartbeat_timer_Sleep(void) 
{
    #if(!heartbeat_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(heartbeat_timer_CTRL_ENABLE == (heartbeat_timer_CONTROL & heartbeat_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            heartbeat_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            heartbeat_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    heartbeat_timer_Stop();
    heartbeat_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: heartbeat_timer_Wakeup
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
*  heartbeat_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void heartbeat_timer_Wakeup(void) 
{
    heartbeat_timer_RestoreConfig();
    #if(!heartbeat_timer_UDB_CONTROL_REG_REMOVED)
        if(heartbeat_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                heartbeat_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
