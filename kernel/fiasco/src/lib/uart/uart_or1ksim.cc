/*
 * (c) 2011 Adam Lackorzynski <adam@os.inf.tu-dresden.de>
 *          Björn Döbel <doebel@os.inf.tu-dresden.de>
 *     economic rights: Technische Universität Dresden (Germany)
 *
 * This file is part of TUD:OS and distributed under the terms of the
 * GNU General Public License 2.
 * Please see the COPYING-GPL-2 file for details.
 */
#include "uart_or1ksim.h"
#include "poll_timeout_counter.h"


namespace L4
{
  enum {
		UART_RX = 0, /* In: Receive buffer (DLAB=0) */
		UART_TX = 0, /* Out: Transmit buffer (DLAB=0) */
		UART_DLL = 0, /* Out: Divisor Latch Low (DLAB=1) */
		UART_DLM = 1, /* Out: Divisor Latch High (DLAB=1) */
		UART_IER = 1, /* Out: Interrupt Enable Register */
		UART_IIR = 2, /* In: Interrupt ID Register */
		UART_FCR = 2, /* Out: FIFO Control Register */
		UART_EFR = 2, /* I/O: Extended Features Register */
/* (DLAB=1, 16C660 only) */
		UART_LCR = 3, /* Out: Line Control Register */
		UART_MCR = 4, /* Out: Modem Control Register */
		UART_LSR = 5, /* In: Line Status Register */
		UART_MSR = 6, /* In: Modem Status Register */
		UART_SCR = 7, /* I/O: Scratch Register */

		/*
		* These are the definitions for the FIFO Control Register
		* (16650 only)
		*/
		UART_FCR_ENABLE_FIFO = 0x01, /* Enable the FIFO */
		UART_FCR_CLEAR_RCVR = 0x02, /* Clear the RCVR FIFO */
		UART_FCR_CLEAR_XMIT = 0x04, /* Clear the XMIT FIFO */
		UART_FCR_DMA_SELECT = 0x08, /* For DMA applications */
		UART_FCR_TRIGGER_MASK = 0xC0, /* Mask for the FIFO trigger range */
		UART_FCR_TRIGGER_1 = 0x00, /* Mask for trigger set at 1 */
		UART_FCR_TRIGGER_4 = 0x40, /* Mask for trigger set at 4 */
		UART_FCR_TRIGGER_8 = 0x80, /* Mask for trigger set at 8 */
		UART_FCR_TRIGGER_14 = 0xC0, /* Mask for trigger set at 14 */
		/* 16650 redefinitions */
		UART_FCR6_R_TRIGGER_8 = 0x00, /* Mask for receive trigger set at 1 */
		UART_FCR6_R_TRIGGER_16 = 0x40, /* Mask for receive trigger set at 4 */
		UART_FCR6_R_TRIGGER_24 = 0x80, /* Mask for receive trigger set at 8 */
		UART_FCR6_R_TRIGGER_28 = 0xC0, /* Mask for receive trigger set at 14 */
		UART_FCR6_T_TRIGGER_16 = 0x00, /* Mask for transmit trigger set at 16 */
		UART_FCR6_T_TRIGGER_8 = 0x10, /* Mask for transmit trigger set at 8 */
		UART_FCR6_T_TRIGGER_24 = 0x20, /* Mask for transmit trigger set at 24 */
		UART_FCR6_T_TRIGGER_30 = 0x30, /* Mask for transmit trigger set at 30 */
		/*
		* These are the definitions for the Line Control Register
		*
		* Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting
		* UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
		*/
		UART_LCR_DLAB = 0x80, /* Divisor latch access bit */
		UART_LCR_SBC = 0x40, /* Set break control */
		UART_LCR_SPAR = 0x20, /* Stick parity (?) */
		UART_LCR_EPAR = 0x10, /* Even parity select */
		UART_LCR_PARITY = 0x08, /* Parity Enable */
		UART_LCR_STOP = 0x04, /* Stop bits: 0=1 stop bit, 1= 2 stop bits */
		UART_LCR_WLEN5 = 0x00, /* Wordlength: 5 bits */
		UART_LCR_WLEN6 = 0x01, /* Wordlength: 6 bits */
		UART_LCR_WLEN7 = 0x02, /* Wordlength: 7 bits */
		UART_LCR_WLEN8 = 0x03, /* Wordlength: 8 bits */

		/*
		* These are the definitions for the Line Status Register
		*/
		UART_LSR_TEMT = 0x40, /* Transmitter empty */
		UART_LSR_THRE = 0x20, /* Transmit-hold-register empty */
		UART_LSR_BI = 0x10, /* Break interrupt indicator */
		UART_LSR_FE = 0x08, /* Frame error indicator */
		UART_LSR_PE = 0x04, /* Parity error indicator */
		UART_LSR_OE = 0x02, /* Overrun error indicator */
		UART_LSR_DR = 0x01, /* Receiver data ready */
  };


  bool Uart_or1ksim::startup(Io_register_block const *regs)
  {

		unsigned int divisor;
		unsigned int _board_clk_freq = 50000000;
		unsigned int _board_uart_baud = 115200;

    _regs = regs;

		/* Reset receiver and transmiter */
		_regs->write<unsigned char>(UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR  | UART_FCR_CLEAR_XMIT  | UART_FCR_TRIGGER_14);

		/* Disable all interrupts */
		_regs->write<unsigned char>(UART_IER, 0x00);

		/* Set 8 bit char, 1 stop bit, no parity */
		_regs->write<unsigned char>(UART_LCR, UART_LCR_WLEN8 & ~(UART_LCR_STOP | UART_LCR_PARITY)); 

		/* Set baud rate */
		divisor = (_board_clk_freq / _board_uart_baud + 8) / 16;

		_regs->write<unsigned char>(UART_LCR, UART_LCR | UART_LCR_DLAB);
		_regs->write<unsigned char>(UART_DLL, divisor & 0x000000ff);
		_regs->write<unsigned char>(UART_DLM, (divisor >> 8) & 0x000000ff);
		_regs->write<unsigned char>(UART_LCR, UART_LCR & ~(UART_LCR_DLAB));


    return true;
  }

  void Uart_or1ksim::shutdown()
  { }

  bool Uart_or1ksim::change_mode(Transfer_mode, Baud_rate r)
  {
		// for simulation no changes are necessary
		// tell calling function everything work ok, otherwise it will fail to go on
    return true;
  }

  int Uart_or1ksim::get_char(bool blocking) const
  {
		unsigned char lsr;
/*		do { */
			lsr = _regs->read<unsigned char>(UART_LSR);
/*		} while ((lsr & UART_LSR_DR) != UART_LSR_DR); */
    return _regs->read<unsigned char>(UART_RX);
  }

  int Uart_or1ksim::char_avail() const
  {
    return 0;
  }

  void Uart_or1ksim::out_char(char c) const
  {
      asm __volatile__("l.addi r3,%0,0": :"r" (c) : "r3");
      asm __volatile__("l.nop 0x4");
      return;
		unsigned char lsr;
/*		do */
/*		{ */
			lsr = _regs->read<unsigned char>(UART_LSR);
/*		} */
/*		while ((lsr & UART_LSR_THRE) != UART_LSR_THRE); */

    _regs->write<unsigned char>(UART_TX, c);

/*		do */
/*		{ */
			lsr = _regs->read<unsigned char>(UART_LSR);
/*		} */
/*		while ((lsr & UART_LSR_TEMT | UART_LSR_THRE) != UART_LSR_TEMT | UART_LSR_THRE); */
  }

  int Uart_or1ksim::write(char const *s, unsigned long count) const
  {
    Poll_timeout_counter cnt(5000000);
    unsigned long c = count;
    while (c--)
		{
      cnt.set(5000000);
      while (cnt.test(!(_regs->read<unsigned char>(UART_LSR) & UART_LSR_THRE)))
				;

      out_char(*s++);
		}

		cnt.set(5000000);
    return count;
  }
};
