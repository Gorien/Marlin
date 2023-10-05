/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2023 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include "../../inc/MarlinConfig.h"

#if ENABLED(OTA_FIRMWARE_UPDATE)

#include "../gcode.h"
#include "../../libs/BL24CXX.h"

#if ENABLED(CREALITY_RTS)
  #include "../../lcd/rts/lcd_rts.h"
#endif

#define OTA_FLAG_EEPROM 90

//#define DEBUG_OUT 1
#include "../../core/debug_out.h"

/**
 * M936: Set one of the OTA update flags.
 *   V2 = Upgrade the motherboard firmware
 *   V3 = Upgrade the RTS controller firmware
 */
void GcodeSuite::M936() {
  static uint8_t ota_update_flag = 0x00;
  const int16_t ota = parser.intval('V', -1);
  switch (ota) {
    case 2:
      // Set the OTA board firmware upgrade flag ahead of reboot.
      ota_update_flag = 0x01;
      DEBUG_ECHOLNPGM("Motherboard upgrade flag set");
      TERN_(CREALITY_RTS, RTS_Error(Error_205));
      break;

    #if ENABLED(CREALITY_RTS)
      case 3:
        // Set the OTA screen firmware upgrade flag ahead of reboot.
        ota_update_flag = 0x02;
        DEBUG_ECHOLNPGM("DWIN upgrade flag set");
        TERN_(CREALITY_RTS, RTS_Error(Error_206));
        break;
    #endif
  }

  switch (ota) {
    case 2: TERN_(CREALITY_RTS, case 3:)
      BL24CXX::write(OTA_FLAG_EEPROM, &ota_update_flag, sizeof(ota_update_flag));
      safe_delay(100);
      hal.reboot();
  }
}

#endif // OTA_FIRMWARE_UPDATE


#if ENABLE_OTA 


#include "stdio.h"
#include "string.h"
#include "../gcode.h"
#include "../parser.h"
#include "../../core/serial.h"
#include "../../inc/MarlinConfig.h"
#include "../../lcd/extui/sermoon_v1_creality/lcdAutoUI.h"
#include "../../../Configuration.h"
#include "../../libs/BL24CXX.h"

#define COMMAND_STR_BOX_LED    "M936 LEDSET"

/**
 * [GcodeSuite::M936 :get command from WIFI board and response]
 * @Author Creality
 * @Time   2021-06-22
 */
void GcodeSuite::M936() 
{
    static unsigned char ota_updata_flag = 0X00;
    uint32_t lCmdVal = 0;

    if(parser.str_contain((char*)"V2"))
    {
        SERIAL_ECHOLN("\r\n 222222\r\n");
        /* 需要将OTA升级标志位设置成0x01，表示下次上电需要OTA升级 */
        ota_updata_flag=0X01;
        BL24CXX::write(EEPROM_ADDR_OTA_OFFSET, &ota_updata_flag, sizeof(ota_updata_flag));
        delay(10);
        SERIAL_ECHOLN("M936 V2");
        delay(50);
        SERIAL_ECHOLN("\r\n Motherboard upgrade \r\n");
        delay(50);
        /* MCU复位进入BOOTLOADER */
        NVIC_SystemReset();
    }
    else if(parser.str_contain((char*)"V3"))
    {
        SERIAL_ECHOLN("\r\n 333333333\r\n");
        /* 需要将OTA升级标志位设置成0x02，表示下次上电需要OTA升级 */
        ota_updata_flag=0X02;
        BL24CXX::write(EEPROM_ADDR_OTA_OFFSET, &ota_updata_flag, sizeof(ota_updata_flag));
        delay(10);
        SERIAL_ECHOLN("M936 V3");
        delay(50);
        SERIAL_ECHOLN("\r\n DIWIN upgrade！！ \r\n");
        delay(50);
        /* MCU复位进入BOOTLOADER */
        NVIC_SystemReset();
    }
    /* get the command value successfully */
    else if(parser.getDecValAfterTargetStr((char*)COMMAND_STR_BOX_LED, &lCmdVal))
    {
        #if 0
        SERIAL_ECHO("lCmdVal : ");
        SERIAL_PRINT(lCmdVal, DEC);
        SERIAL_ECHOLN(" ");
        #endif

        if(lCmdVal)
        {
            /* turn on box led */
            gLcdAutoUI.AutoUISetBoxLed(true);
        }   
        else
        {
            /* turn off box led */
            gLcdAutoUI.AutoUISetBoxLed(false);
        }   
    }
    else
    {
        SERIAL_ECHOLN("<warning> Failed to get command or command value from WIFI board \r\n");
    }
}

#endif
