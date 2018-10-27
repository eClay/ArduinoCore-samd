/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

const PinDescription g_APinDescription[] = {

/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  SAMD21G pin     |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 00         | 1                |  PA00  | XIN32           |   00   |     |     |     |     |         |   1/00  | TCC2/0 |        |          |          |
 | 01         | 2                |  PA01  | XOUT32          |   01   |     |     |     |     |         |   1/01  | TCC2/1 |        |          |          |
 | 02         | 3                |  PA02  |                 |   02   |  00 |     | Y00 | OUT |         |         |        |        |          |          |
 | 03         | 4                |  PA03  | ADC+DAC/VREFA   |   03   |  01 |     | Y01 |     |         |         |        |        |          |          |
 | 04         | 7                |  PB08  |                 |   08   |  02 |     | Y14 |     |         |   4/00  |  TC4/0 |        |          |          |
 | 05         | 8                |  PB09  |                 |   09   |  03 |     | Y15 |     |         |   4/01  |  TC4/1 |        |          |          |
 | 06         | 9                |  PA04  |                 |   04   |  04 |  00 | Y02 |     |         |   0/00  | TCC0/0 |        |          |          |
 | 07         | 10               |  PA05  |                 |   05   |  05 |  01 | Y03 |     |         |   0/01  | TCC0/1 |        |          |          |
 | 08         | 11               |  PA06  |                 |   06   |  06 |  02 | Y04 |     |         |   0/02  | TCC1/0 |        |          |          |
 | 09         | 12               |  PA07  |                 |   07   |  07 |  03 | Y05 |     |         |   0/03  | TCC1/1 |        | I2S/SD0  |          |
 | 10         | 13               |  PA08  | I2C SUPPORT     |   NMI  |  16 |     | X00 |     |   0/00  |   2/00  | TCC0/0 | TCC1/2 | I2S/SD1  |          |
 | 11         | 14               |  PA09  | I2C SUPPORT     |   09   |  17 |     | X01 |     |   0/01  |   2/01  | TCC0/1 | TCC1/3 | I2S/MCK0 |          |
 | 12         | 15               |  PA10  |                 |   10   |  18 |     | X02 |     |   0/02  |   2/02  | TCC1/0 | TCC0/2 | I2S/SCK0 | GCLK_IO4 |
 | 13         | 16               |  PA11  |                 |   11   |  19 |     | X03 |     |   0/03  |   2/03  | TCC1/1 | TCC0/3 | I2S/FS0  | GCLK_IO5 |
 | 14         | 19               |  PB10  |                 |   10   |     |     |     |     |         |   4/02  |  TC5/0 | TCC0/4 | I2S/MCK1 | GCLK_IO4 |
 | 15         | 20               |  PB11  |                 |   11   |     |     |     |     |         |   4/03  |  TC5/1 | TCC0/5 | I2S/SCK1 | GCLK_IO5 |
 | 16         | 21               |  PA12  | I2C SUPPORT     |   12   |     |     |     |     |   2/00  |   4/00  | TCC2/0 | TCC0/6 |          | AC/CMP0  |
 | 17         | 22               |  PA13  | I2C SUPPORT     |   13   |     |     |     |     |   2/01  |   4/01  | TCC2/1 | TCC0/7 |          | AC/CMP1  |
 | 18         | 23               |  PA14  | XIN             |   14   |     |     |     |     |   2/02  |   4/02  |  TC3/0 | TCC0/4 |          | GCLK_IO0 |
 | 19         | 24               |  PA15  | XOUT            |   15   |     |     |     |     |   2/03  |   4/03  |  TC3/1 | TCC0/5 |          | GCLK_IO1 |
 | 20         | 25               |  PA16  | I2C SUPPORT     |   00   |     |     | X04 |     |   1/00  |   3/00  | TCC2/0 | TCC0/6 |          | GCLK_IO2 |
 | 21         | 26               |  PA17  | I2C SUPPORT     |   01   |     |     | X05 |     |   1/01  |   3/01  | TCC2/1 | TCC0/7 |          | GCLK_IO3 |
 | 22         | 27               |  PA18  |                 |   02   |     |     | X06 |     |   1/02  |   3/02  |  TC3/0 | TCC0/2 |          | AC/CMP0  |
 | 23         | 28               |  PA19  |                 |   03   |     |     | X07 |     |   1/03  |   3/03  |  TC3/1 | TCC0/3 | I2S/SD0  | AC/CMP1  |
 | 24         | 29               |  PA20  |                 |   04   |     |     | X08 |     |   5/02  |   3/02  |        | TCC0/6 | I2S/SCK0 | GCLK_IO4 |
 | 25         | 30               |  PA21  |                 |   05   |     |     | X09 |     |   5/03  |   3/03  |        | TCC0/7 | I2S/FS0  | GCLK_IO5 |
 | 26         | 46               |  PA31  | LED_USB_ADAPTER |   11   |     |     |     |     |         |   1/03  | TCC1/1 |        | SWDIO    | GCLK_IO5 |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
  { PORTA,  0, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  1, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  2, PIO_DIGITAL,  (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG /*DAC*/        ), ADC_Channel0,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  3, PIO_DIGITAL, (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // DAC/VREFP
  { PORTB,  8, PIO_DIGITAL,    (PIN_ATTR_DIGITAL|PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTB,  9, PIO_DIGITAL,     (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER                  ), ADC_Channel3,   PWM4_CH1,   TC4_CH1,      EXTERNAL_INT_9    },
  { PORTA,  4, PIO_DIGITAL,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel4,   PWM0_CH0,   TCC0_CH0,     EXTERNAL_INT_NONE },
  { PORTA,  5, PIO_DIGITAL,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel5,   PWM0_CH1,   TCC0_CH1,     EXTERNAL_INT_NONE },
  { PORTA,  6, PIO_DIGITAL,  (PIN_ATTR_DIGITAL                                ), ADC_Channel6,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  7, PIO_DIGITAL,  (PIN_ATTR_DIGITAL                                ), ADC_Channel7,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  8, PIO_DIGITAL,  (PIN_ATTR_DIGITAL                                ), ADC_Channel16,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI  }, // SDA:  SERCOM0/PAD[0]
  { PORTA,  9, PIO_DIGITAL,  (PIN_ATTR_DIGITAL                                ), ADC_Channel17,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SCL:  SERCOM0/PAD[1]
  { PORTA, 10, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel18,  PWM1_CH0,   TCC1_CH0,     EXTERNAL_INT_NONE },
  { PORTA, 11, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel19,  PWM1_CH1,   TCC1_CH1,     EXTERNAL_INT_NONE },
  { PORTB, 10, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM5_CH0,   TC5_CH0,      EXTERNAL_INT_10   },
  { PORTB, 11, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM5_CH1,   TC5_CH1,      EXTERNAL_INT_11   },
  { PORTA, 12, PIO_DIGITAL,     (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MOSI: SERCOM2/PAD[0]
  { PORTA, 13, PIO_DIGITAL,     (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SCK:  SERCOM2/PAD[1]
  { PORTA, 14, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SS:   as GPIO
  { PORTA, 15, PIO_DIGITAL,     (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MISO: SERCOM2/PAD[3]
  { PORTA, 16, PIO_DIGITAL,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM2_CH0,   TCC2_CH0,     EXTERNAL_INT_0    }, // MOSI: SERCOM1/PAD[0]
  { PORTA, 17, PIO_DIGITAL,  (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1    }, // SCK:  SERCOM1/PAD[1]
  { PORTA, 18, PIO_DIGITAL, (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 19, PIO_DIGITAL,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM3_CH1,   TC3_CH1,      EXTERNAL_INT_NONE }, // MISO: SERCOM1/PAD[3]
  { PORTA, 20, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH6,   TCC0_CH6,     EXTERNAL_INT_4    },
  { PORTA, 21, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH7,   TCC0_CH7,     EXTERNAL_INT_5    },
  { PORTA, 31, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH7,   TCC0_CH7,     EXTERNAL_INT_5    },

/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  SAMD21G pin     |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |    eClay Bus    |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 27         | 39               |  PA27  | ECLAY_SYNC1     |   15   |     |     |     |     |         |         |        |        |          | GCLK_IO0 |
 | 28         | 32               |  PA23  | ECLAY_SYNC2     |   07   |     |     | X11 |     |   3/01  |   5/01  |  TC4/1 | TCC0/5 | USB/SOF  | GCLK_IO7 |
 | 29         | 31               |  PA22  | ECLAY_SYNC3     |   06   |     |     | X10 |     |   3/00  |   5/00  |  TC4/0 | TCC0/4 |          | GCLK_IO6 |
 | 30         | 47               |  PB02  | ECLAY_MISO      |   02   |  10 |     | Y08 |     |         |   5/00  |        |        |          |          |
 | 31         | 48               |  PB03  | ECLAY_SCK       |   03   |  11 |     | Y09 |     |         |   5/01  |        |        |          |          |
 | 32         | 37               |  PB22  | ECLAY_CS        |   06   |     |     |     |     |         |   5/02  |        |        |          | GCLK_IO0 |
 | 33         | 38               |  PB23  | ECLAY_MOSI      |   07   |     |     |     |     |         |   5/03  |        |        |          | GCLK_IO1 |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
  { PORTA, 27, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 23, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM4_CH1,   TC4_CH1,      EXTERNAL_INT_7    },
  { PORTA, 22, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM4_CH0,   TC4_CH0,      EXTERNAL_INT_6    },
                                                                                                                                               // DIPO=3 DOPO=0
  { PORTB,  2, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                             ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MISO: SERCOM5/PAD[0]
  { PORTB,  3, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                             ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SCK:  SERCOM5/PAD[1]
  { PORTB, 22, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                             ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // CS:   SERCOM5/PAD[2]
  { PORTB, 23, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                             ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MOSI: SERCOM5/PAD[3]

/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  SAMD21G pin     |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 |            |       USB        |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 34         |                  |  PA24  | USB N           |   12   |     |     |     |     |   3/02  |   5/02  |  TC5/0 | TCC1/2 | USB/DM   |          |
 | 35         |                  |  PA25  | USB P           |   13   |     |     |     |     |   3/03  |   5/03  |  TC5/1 | TCC1/3 | USB/DP   |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
  { PORTA, 24, PIO_COM,     (PIN_ATTR_NONE                                   ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DM
  { PORTA, 25, PIO_COM,     (PIN_ATTR_NONE                                   ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DP
};

const void* g_apTCInstances[TCC_INST_NUM + TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 };

// Multi-serial objects instantiation
SERCOM sercom0(SERCOM0);
SERCOM sercom1(SERCOM1);
SERCOM sercom2(SERCOM2);
SERCOM sercom3(SERCOM3);
SERCOM sercom4(SERCOM4);
SERCOM sercom5(SERCOM5);

// Serial1
Uart Serial1(&sercom5, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX);

void SERCOM5_Handler()
{
  Serial1.IrqHandler();
}

