# ------------------------------------------------------------------------------
# --
# -- Makefile for compiling the labRC monte-carlo simulator
# --
# ------------------------------------------------------------------------------

# Let's start with some usefull definition for colorize the echo 
RED='\x1b[0;31m'
GREEN='\x1b[0;32m'
YELLOW='\x1b[0;33m'
BLUE='\x1b[0;34m'
WHITE='\x1b[0;37m'
VIOLET='\x1b[0;35m'
CYAN='\x1b[0;36m'

# Reset the terminal
Reset=`tput sgr0`

dump:
	echo $(geomOBJ)
	echo $(trackOBJ)
	echo $(userOBJ)
	echo $(physOBJ)
	echo $(guiOBJ)

# -----------------------------------------------------------------------------------------------------------

CLHEPinc = -I ${CLHEP_INCLUDE_DIR}

CFLAGS = `root-config --cflags`
GLIBS = `root-config --glibs`

# ------------------------------------------------------------------------------------------------- libs
physSRC := $(wildcard phys/*.C)
physOBJ := $(patsubst %.C,bin/%.o,$(notdir $(physSRC)))
physINC := $(patsubst %.C,phys/%.h,$(notdir $(physSRC)))

geomSRC := $(wildcard geom/*.C)
geomOBJ := $(patsubst %.C,bin/%.o,$(notdir $(geomSRC)))
geomINC := $(patsubst %.C,geom/%.h,$(notdir $(geomSRC)))

trackSRC := $(wildcard track/*.C)
trackOBJ := $(patsubst %.C,bin/%.o,$(notdir $(trackSRC)))
trackINC := $(patsubst %.C,track/%.h,$(notdir $(trackSRC)))

userSRC := $(wildcard user/*.C)
userOBJ := $(patsubst %.C,bin/%.o,$(notdir $(userSRC)))
userINC := $(patsubst %.C,user/%.h,$(notdir $(userSRC)))

guiSRC := $(wildcard gui/*.C)
guiOBJ := $(patsubst %.C,bin/%.o,$(notdir $(guiSRC)))
guiINC := $(patsubst %.C,gui/%.h,$(notdir $(guiSRC)))

# ------------------------------------------ main

DrawGeom: bin/DrawGeom.exe 
TankSim:  bin/TankSim.exe 
LRCsim:   bin/LRCsim.exe 
test:     bin/tprop.exe bin/tstack.exe bin/tphys.exe bin/tDrawGeom.exe

# ----------------------------------------------------------------------------- exe
bin/r%.exe: main/%.C LIBS/libLMCgeom.a LIBS/libLMCtrack.a LIBS/libLMCuser.a
	@echo
	@echo -e $(BLUE) BUILD $@ $(Reset)
	g++ -o $@ $< -Igeom -Itrack -Iuser -Iphys -I`root-config --cflags` \
        -LLIBS -luser -lgeom -ltrack -luser -lphys `root-config --libs --glibs` -lGeom -lEG 

bin/t%.exe: test/t%.C libLMCgeom libLMCtrack libLMCuser libLMCphys libLMCgui
	@echo
	@echo -e $(BLUE) BUILD $@ $(Reset)
	g++ -o $@ $< -Igeom -Itrack -Iuser -Iphys -Igui -I`root-config --cflags` \
        -LLIBS -lLMCuser -lLMCgeom -lLMCtrack -lLMCphys -lLMCgui -lLMCuser `root-config --libs --glibs` -lGeom -lEG 

bin/g%.exe:  test/g%.C gui/LMCsimGUI.h  gui/LMC_LinkDef.h libLMCgui libLMCgeom libLMCtrack libLMCuser libLMCphys
	@echo
	@echo -e $(BLUE) BUILD $@ $(Reset)
	rootcint -f guiexDict.cxx -c gui/LMCsimGUI.h gui/LMC_LinkDef.h
	g++ -o $@ $< -Igeom -Itrack -Iuser -Iphys -Igui gui/LMCsimGUI.C guiexDict.cxx -I`root-config --cflags` \
        -LLIBS -lLMCuser -lLMCgeom -lLMCtrack -lLMCphys -lLMCgui -lLMCuser  `root-config --libs --glibs` -lGeom -lEG 
	@echo "Done!"

# -----------------------------------------------------------------------------------

libs: libLMCtrack libLMCgeom libLMCuser libLMCphys libLMCgui
liball: libLMCtrack libLMCgeom libLMCuser libLMCphys libLMCgui

libLMCuser: $(userOBJ)
	ar -cvq LIBS/libLMCuser.a $(userOBJ)

libLMCtrack: $(trackOBJ)
	ar -cvq LIBS/libLMCtrack.a $(trackOBJ)

libLMCgeom: $(geomOBJ)
	ar -cvq LIBS/libLMCgeom.a $(geomOBJ)

libLMCphys: $(physOBJ)
	ar -cvq LIBS/libLMCphys.a $(physOBJ)

libLMCgui: $(guiOBJ)
	ar -cvq LIBS/libLMCgui.a $(guiOBJ)


# ----------------------------------------------------------------------------- objects

bin/%.o: geom/%.C geom/%.h
	@echo -e compiling $(GREEN) $< $(Reset) to an object file $@
	g++ -g -Igeom -Iuser -Itrack -Iphys -Igui `root-config --cflags` -c $< -o $@

bin/%.o: track/%.C track/%.h
	@echo -e compiling $(GREEN) $< $(Reset) to an object file $@
	g++ -g -Itrack -Igeom -Iuser -Iphys -Igui `root-config --cflags` -c $< -o $@

bin/%.o: user/%.C user/%.h
	@echo -e compiling $(GREEN) $< $(Reset) to an object file $@
	g++ -g -Igeom -Iuser -Itrack -Iphys -Igui `root-config --cflags` -c $< -o $@

bin/%.o: phys/%.C phys/%.h
	@echo -e compiling $(GREEN) $< $(Reset) to an object file $@
	g++ -g -Itrack -Igeom -Iuser -Iphys -Igui `root-config --cflags` -c $< -o $@

bin/%.o: gui/%.C gui/%.h
	@echo -e compiling $(GREEN) $< $(Reset) to an object file $@
	g++ -g -Itrack -Igeom -Iuser -Iphys -Igui `root-config --cflags` -c $< -o $@

# ------------------------------------------ clean

clean: 
	rm -f LIBS/*.a
	rm -f bin/*
	rm -fv guiex*
