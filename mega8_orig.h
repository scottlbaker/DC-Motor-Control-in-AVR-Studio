/*
 * $Id: mega8.h,v 1.1 2004/02/02 01:49:25 troth Exp $
 *
 ****************************************************************************
 *
 * simulavr - A simulator for the Atmel AVR family of microcontrollers.
 * Copyright (C) 2004  Theodore A. Roth
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 ****************************************************************************
 */

#if defined (IN_DEVSUPP_C)
/* *INDENT-OFF* */

static DevSuppDefn defn_atmega8 = {
    .name           = "atmega8",
    .stack_type     = STACK_MEMORY,
    .irq_vect_idx   = VTAB_ATMEGA8,

    .size = {
        .pc         = 2,
        .stack      = 0,
        .flash      = 8 * 1024,
        .sram       = 1 * 1024,
        .eeprom     = 512
    },

    .io_reg = {
        { .addr = 0x20, .name = "TWBR", },
        { .addr = 0x21, .name = "TWSR", },
        { .addr = 0x22, .name = "TWAR", },
        { .addr = 0x23, .name = "TWDR", },
        { .addr = 0x24, .name = "ADCL", },
        { .addr = 0x25, .name = "ADCH", },
        { .addr = 0x26, .name = "ADCSRA", },
        { .addr = 0x27, .name = "ADMUX", },
        { .addr = 0x28, .name = "ACSR", },
        { .addr = 0x29, .name = "UBRRL", },
        { .addr = 0x2a, .name = "UCSRB", },
        { .addr = 0x2b, .name = "UCSRA", },
        { .addr = 0x2c, .name = "UDR", },
        { .addr = 0x2d, .name = "SPCR", },
        { .addr = 0x2e, .name = "SPSR", },
        { .addr = 0x2f, .name = "SPDR", },
        {
            .addr = 0x30,
            .name = "PIND",
            .vdev_create = port_create,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x31,
            .name = "DDRD",
            .ref_addr = 0x30,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x32,
            .name = "PORTD",
            .ref_addr = 0x30,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x33,
            .name = "PINC",
            .vdev_create = port_create,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x34,
            .name = "DDRC",
            .ref_addr = 0x33,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x35,
            .name = "PORTC",
            .ref_addr = 0x33,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x36,
            .name = "PINB",
            .vdev_create = port_create,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x37,
            .name = "DDRB",
            .ref_addr = 0x36,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x38,
            .name = "PORTB",
            .ref_addr = 0x36,
            .reset_value = 0x00,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        { .addr = 0x40, .name = "UBRRH", },
        { .addr = 0x41, .name = "WDTCR", },
        { .addr = 0x42, .name = "ASSR", },
        { .addr = 0x43, .name = "OCR2", },
        { .addr = 0x44, .name = "TCNT2", },
        { .addr = 0x45, .name = "TCCR2", },
        { .addr = 0x46, .name = "ICR1L", },
        { .addr = 0x47, .name = "ICR1H", },
        { .addr = 0x48, .name = "OCR1BL", },
        { .addr = 0x49, .name = "OCR1BH", },
        { .addr = 0x4a, .name = "OCR1AL", },
        { .addr = 0x4b, .name = "OCR1AH", },
        { .addr = 0x4c, .name = "TCNT1L", },
        { .addr = 0x4d, .name = "TCNT1H", },
        { .addr = 0x4e, .name = "TCCR1B", },
        { .addr = 0x4f, .name = "TCCR1A", },
        { .addr = 0x50, .name = "SFIOR", },
        { .addr = 0x51, .name = "OSCCAL", },
        { .addr = 0x52, .name = "TCNT0", },
        { .addr = 0x53, .name = "TCCR0", },
        { .addr = 0x54, .name = "MCUCSR", },
        { .addr = 0x55, .name = "MCUCR", },
        { .addr = 0x56, .name = "TWCR", },
        { .addr = 0x57, .name = "SPMCR", },
        { .addr = 0x58, .name = "TIFR", },
        { .addr = 0x59, .name = "TIMSK", },
        { .addr = 0x5a, .name = "GIFR", },
        { .addr = 0x5b, .name = "GICR", },
        {
            .addr = 0x5d,
            .name = "SPL", 
            .vdev_create = sp_create,
            .reset_value = 0,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x5e,
            .name = "SPH",
            .ref_addr = 0x5d,
            .reset_value = 0,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        {
            .addr = 0x5f,
            .name = "SREG",
            .vdev_create = sreg_create,
            .reset_value = 0,
            .rd_mask = 0xff,
            .wr_mask = 0xff,
        },
        IO_REG_DEFN_TERMINATOR
    }
};

/* *INDENT-ON* */
#endif /* IN_DEVSUPP_C */

