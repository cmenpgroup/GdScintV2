# --------------------------------------------------------------
# GNUmakefile for Gd Neutron Scintillator.  M. H. Wood, 12/19/2022.
# --------------------------------------------------------------

name := GdScint
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

