PKGDIR?= ../..
L4DIR ?= $(PKGDIR)/../..

# the name of your library
TARGET	= $(PKGNAME)_rsaref2.a
BUILD_PIC = $(TARGET)
SYSTEMS = x86 arm amd64
PC_FILENAME = $(PKGNAME)_rsaref2

# list your .c files here
SRC_C	= $(addprefix source/,desc.c digit.c md2c.c md5c.c nn.c prime.c \
                              rsa.c r_encode.c r_dh.c r_enhanc.c r_keygen.c \
			      r_random.c r_stdlib.c)

PRIVATE_INCDIR	= $(PKGDIR)/include/rsaref2

WARNINGS = -Wall -Wstrict-prototypes

include $(L4DIR)/mk/lib.mk
