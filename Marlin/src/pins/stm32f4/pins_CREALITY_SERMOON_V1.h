
/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
#pragma once

#include "env_validate.h"

#if HAS_MULTI_HOTEND || E_STEPPERS > 1
  #error "Sermoon V1 only supports 1 hotend / E stepper."
#endif

#if HAS_TMC220x
  #error "Sermoon V1 only supports TMC220x STANDALONE."
#endif

#define BOARD_INFO_NAME      "Sermoon V1"

#if NO_EEPROM_SELECTED
  // FLASH
  // #define FLASH_EEPROM_EMULATION
  // #define SDCARD_EEPROM_EMULATION
  // #define USE_WIRED_EEPROM
  // I2C
  #define IIC_BL24CXX_EEPROM                      // EEPROM on I2C-0 used only for display settings
  #if ENABLED(IIC_BL24CXX_EEPROM)
    #define IIC_EEPROM_SDA                  PA11
    #define IIC_EEPROM_SCL                  PA12
    #define MARLIN_EEPROM_SIZE             0x800  // 2Kb (24C16)
  #else
    #define SDCARD_EEPROM_EMULATION               // SD EEPROM until all EEPROM is BL24CXX
    #define MARLIN_EEPROM_SIZE             0x800  // 2Kb
  #endif
#endif


//
// Limit Switches
//
#define X_MAX_PIN                           PC4
#define Y_MIN_PIN                           PB13

#ifdef BLTOUCH
  #define Z_MIN_PIN                         PC3   // BLTouch IN PIN
  #define SERVO0_PIN                        PC2   // BLTouch OUT PIN
#elif ENABLED(FIX_MOUNTED_PROBE)
  #define Z_MIN_PIN                         PA4
  #define COM_PIN                           PA5
#else
  #define Z_MAX_PIN                         PB3
#endif

//
// Steppers
//
#define X_ENABLE_PIN                        PB8
#define X_STEP_PIN                          PA7
#define X_DIR_PIN                           PA4

#define Y_ENABLE_PIN                        PB8
#define Y_STEP_PIN                          PB0
#define Y_DIR_PIN                           PB10

#define Z_ENABLE_PIN                        PB8
#define Z_STEP_PIN                          PB7
#define Z_DIR_PIN                           PB6

#define E0_ENABLE_PIN                       PB8
#define E0_STEP_PIN                         PB1
#define E0_DIR_PIN                          PB12

//
// Temperature Sensors
//
#define TEMP_0_PIN                          PC1
#define TEMP_BED_PIN                        PC0

//
// Heaters / Fans
//
#ifndef HEATER_0_PIN
  #define HEATER_0_PIN                      PC5   // Heater0
#endif
#ifndef HEATER_BED_PIN
  #define HEATER_BED_PIN                    PB9   // Hotbed
#endif
#ifndef FAN0_PIN
  #define FAN0_PIN                          PA5   // Fan
  #define FAN_SOFT_PWM
#endif
#ifndef BOX_FAN_PIN
  #define BOX_FAN_PIN                      PC15   // Box fan
#endif

//
// SD Card
//
#define SD_DETECT_PIN                      PC7
#define ON_BOARD_SPI_DEVICE                1
#define SDIO_SUPPORT
#define NO_SD_HOST_DRIVE

//
// Onboard SD support
//
#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION              ONBOARD
#endif

#if SD_CONNECTION_IS(ONBOARD)
  #define ONBOARD_SDIO                            // Use SDIO for onboard SD
  #if DISABLED(ONBOARD_SDIO)
    #define SOFTWARE_SPI                          // Use soft SPI for onboard SD
    #define SDSS                            PC11
    #define SD_SCK_PIN                      PC12
    #define SD_MISO_PIN                     PC8
    #define SD_MOSI_PIN                     PD2
  #endif
#endif

#define SDIO_D0_PIN                         PC8    // PC8   SDIO_D0
#define SDIO_D1_PIN                         PC9    // PC9   SDIO_D1
#define SDIO_D2_PIN                         PC10   // PC10  SDIO_D2
#define SDIO_D3_PIN                         PC11   // PC11  SDIO_D3
#define SDIO_CK_PIN                         PC12   // PC12  SDIO_CK
#define SDIO_CMD_PIN                        PD2    // PD2   SDIO_CMD


//
// LCD / Controller
//


//
// OTHE
//
#define LED_CONTROL_PIN                     PC14
#define CHECK_MATWEIAL                      PC6
#if ENABLE_DOOR_OPEN_CHECK
  #define CHECK_DOOR_PIN                    PB14   // Open the door to detect (is high)
#endif
