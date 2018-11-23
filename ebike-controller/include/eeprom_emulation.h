/**
  ******************************************************************************
  * @file    EEPROM_Emulation/inc/eeprom.h
  * @author  MCD Application Team
   * @version V1.0.0
  * @date    10-October-2011
  * @brief   This file contains all the functions prototypes for the EEPROM
  *          emulation firmware library.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EEPROM_EMULATION_H_
#define EEPROM_EMULATION_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


/* From ST StdPeriph Flash ---------------------------------------------------*/
typedef enum
{
  FLASH_BUSY = 1,
  FLASH_ERROR_PGS,
  FLASH_ERROR_PGP,
  FLASH_ERROR_PGA,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_ERROR_OPERATION,
  FLASH_COMPLETE
}FLASH_Status;

#define VoltageRange_1        ((uint8_t)0x00)  /*!< Device operating range: 1.8V to 2.1V */
#define VoltageRange_2        ((uint8_t)0x01)  /*!<Device operating range: 2.1V to 2.7V */
#define VoltageRange_3        ((uint8_t)0x02)  /*!<Device operating range: 2.7V to 3.6V */
#define VoltageRange_4        ((uint8_t)0x03)  /*!<Device operating range: 2.7V to 3.6V + External Vpp */

#define SECTOR_MASK               ((uint32_t)0xFFFFFF07)
#define FLASH_Sector_0     ((uint16_t)0x0000) /*!< Sector Number 0 */
#define FLASH_Sector_1     ((uint16_t)0x0008) /*!< Sector Number 1 */
#define FLASH_Sector_2     ((uint16_t)0x0010) /*!< Sector Number 2 */
#define FLASH_Sector_3     ((uint16_t)0x0018) /*!< Sector Number 3 */
#define FLASH_Sector_4     ((uint16_t)0x0020) /*!< Sector Number 4 */
#define FLASH_Sector_5     ((uint16_t)0x0028) /*!< Sector Number 5 */
#define FLASH_Sector_6     ((uint16_t)0x0030) /*!< Sector Number 6 */
#define FLASH_Sector_7     ((uint16_t)0x0038) /*!< Sector Number 7 */
#define FLASH_Sector_8     ((uint16_t)0x0040) /*!< Sector Number 8 */
#define FLASH_Sector_9     ((uint16_t)0x0048) /*!< Sector Number 9 */
#define FLASH_Sector_10    ((uint16_t)0x0050) /*!< Sector Number 10 */
#define FLASH_Sector_11    ((uint16_t)0x0058) /*!< Sector Number 11 */

#define FLASH_FLAG_EOP                 ((uint32_t)0x00000001)  /*!< FLASH End of Operation flag */
#define FLASH_FLAG_OPERR               ((uint32_t)0x00000002)  /*!< FLASH operation Error flag */
#define FLASH_FLAG_WRPERR              ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_PGAERR              ((uint32_t)0x00000020)  /*!< FLASH Programming Alignment error flag */
#define FLASH_FLAG_PGPERR              ((uint32_t)0x00000040)  /*!< FLASH Programming Parallelism error flag  */
#define FLASH_FLAG_PGSERR              ((uint32_t)0x00000080)  /*!< FLASH Programming Sequence error flag  */
#define FLASH_FLAG_BSY                 ((uint32_t)0x00010000)  /*!< FLASH Busy flag */

#define FLASH_PSIZE_BYTE           ((uint32_t)0x00000000)
#define FLASH_PSIZE_HALF_WORD      ((uint32_t)0x00000100)
#define FLASH_PSIZE_WORD           ((uint32_t)0x00000200)
#define FLASH_PSIZE_DOUBLE_WORD    ((uint32_t)0x00000300)
#define CR_PSIZE_MASK              ((uint32_t)0xFFFFFCFF)

/* Exported constants --------------------------------------------------------*/
/* Define the size of the sectors to be used */
#define PAGE_SIZE               (uint32_t)0x4000  /* Page size = 16KByte */

/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
   be done by word  */
#define VOLTAGE_RANGE           (uint8_t)VoltageRange_3

/* EEPROM start address in Flash */
#define EEPROM_START_ADDRESS  ((uint32_t)0x08008000) /* EEPROM emulation start address:
                                                  from sector2 : after 16KByte of used
                                                  Flash memory */

/* Pages 0 and 1 base and end addresses */
#define PAGE0_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + 0x0000))
#define PAGE0_END_ADDRESS     ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1)))
#define PAGE0_ID               FLASH_Sector_2

#define PAGE1_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + 0x4000))
#define PAGE1_END_ADDRESS     ((uint32_t)(EEPROM_START_ADDRESS + (2 * PAGE_SIZE - 1)))
#define PAGE1_ID               FLASH_Sector_3

/* Used Flash pages for EEPROM emulation */
#define PAGE0                 ((uint16_t)0x0000)
#define PAGE1                 ((uint16_t)0x0001)

/* No valid page define */
#define NO_VALID_PAGE         ((uint16_t)0x00AB)

/* Page status definitions */
#define ERASED                ((uint16_t)0xFFFF)     /* Page is empty */
#define RECEIVE_DATA          ((uint16_t)0xEEEE)     /* Page is marked to receive data */
#define VALID_PAGE            ((uint16_t)0x0000)     /* Page containing valid data */

/* Valid pages in read and write defines */
#define READ_FROM_VALID_PAGE  ((uint8_t)0x00)
#define WRITE_IN_VALID_PAGE   ((uint8_t)0x01)

/* Page full define */
#define PAGE_FULL             ((uint8_t)0x80)

/* Variables' number */
#define NB_OF_VAR                 34
// FOC constants
#define EE_ADR_KP                 0x3001
#define EE_ADR_KI                 0x3002
#define EE_ADR_KD                 0x3002
#define EE_ADR_KC                 0x3003
#define EE_ADR_DT                 0x3004
// Motor constants
#define EE_ADR_PP                 0x4001
#define EE_ADR_RS                 0x4002
#define EE_ADR_LS                 0x4003
#define EE_ADR_FLUX               0x4004
#define EE_ADR_HALL1              0x4011
#define EE_ADR_HALL2              0x4012
#define EE_ADR_HALL3              0x4013
#define EE_ADR_HALL4              0x4014
#define EE_ADR_HALL5              0x4015
#define EE_ADR_HALL6              0x4016
// Controller constants
#define EE_ADR_IAGAIN             0x5001
#define EE_ADR_IBGAIN             0x5002
#define EE_ADR_ICGAIN             0x5003
#define EE_ADR_IAOFFSET           0x5004
#define EE_ADR_IBOFFSET           0x5005
#define EE_ADR_ICOFFSET           0x5006
#define EE_ADR_VBUSSCALE          0x5007
// Throttle constants
#define EE_ADR_TYPE1              0x6011
#define EE_ADR_MIN1               0x6012
#define EE_ADR_MAX1               0x6013
#define EE_ADR_HYST1              0x6014
#define EE_ADR_FILT1              0x6015
#define EE_ADR_RISE1              0x6016
#define EE_ADR_TYPE2              0x6021
#define EE_ADR_MIN2               0x6022
#define EE_ADR_MAX2               0x6023
#define EE_ADR_HYST2              0x6024
#define EE_ADR_FILT2              0x6025
#define EE_ADR_RISE2              0x6026

#define DEFAULT_ADDR_LIST {EE_ADR_KP, EE_ADR_KI, EE_ADR_KD, EE_ADR_KC, \
    EE_ADR_DT, EE_ADR_PP, EE_ADR_RS, EE_ADR_LS, EE_ADR_FLUX, EE_ADR_HALL1, \
    EE_ADR_HALL2, EE_ADR_HALL3, EE_ADR_HALL4, EE_ADR_HALL5, EE_ADR_HALL6, \
    EE_ADR_IAGAIN, EE_ADR_IBGAIN, EE_ADR_ICGAIN, EE_ADR_IAOFFSET, \
    EE_ADR_IBOFFSET, EE_ADR_ICOFFSET, EE_ADR_VBUSSCALE, EE_ADR_TYPE1, \
    EE_ADR_MIN1, EE_ADR_MAX1, EE_ADR_HYST1, EE_ADR_FILT1, EE_ADR_RISE1, \
    EE_ADR_TYPE2, EE_ADR_MIN2, EE_ADR_MAX2, EE_ADR_HYST2, EE_ADR_FILT2, \
    EE_ADR_RISE2 }

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint16_t EE_Init(void);
uint16_t EE_ReadVariable(uint16_t VirtAddress, uint16_t* Data);
uint16_t EE_WriteVariable(uint16_t VirtAddress, uint16_t Data);

#endif /* EEPROM_EMULATION_H_ */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/



