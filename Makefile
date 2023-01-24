CC= g++
RS= windres
MAIN= PComS1701
MFILES = OnInit MainWndProc OnEnd
IFILES = CPPar CPMPar CPMascErro CPEpage CPMOpc CPMenu CPEixo CPCI CPPorta CPComm CPCtrl CLog CPDevMan
RCFILES =
DFiles = Define

MP_INC = Z:\0-Posijet\Programas\PC\Include
MP_LIB = Z:\0-Posijet\Programas\PC\library
MP_RES = Z:\0-Posijet\Programas\PC\resource
MP_OBJ = Z:\0-Posijet\Programas\PC\object
P_INC = Inc
P_LIB = lib
P_RES = res
P_SRC = src
P_OBJ = obj
P_BIN = bin

MOBJS  = $(patsubst %,%.o,$(MFILES))
IOBJS = $(patsubst %,%.o,$(IFILES))
IRC = $(patsubst %,%.o,$(RCFILES))

vpath %.o ${P_OBJ}

all: ${P_BIN}/${MAIN}.exe
	$<
	
${P_BIN}/${MAIN}.exe: ${P_OBJ}/${MAIN}.o ${MOBJS} ${IOBJS} ${IRC} 
	${CC}  -static-libgcc -static-libstdc++ -o $@ $< $(patsubst %,${P_OBJ}/%,$(MOBJS)) $(patsubst %,${P_OBJ}/%,$(IOBJS)) $(patsubst %,${P_RES}/%,$(IRC)) -lComdlg32 -lGdi32 -lcomctl32 -lUser32 -luxtheme 
	
${P_OBJ}/${MAIN}.o: ${MAIN}.cpp ${MAIN}.h ${DFiles}.h
	${CC}  -c $< -o $@

${MOBJS}: %.o:${P_SRC}/%.cpp ${MAIN}.h ${DFiles}.h 
	${CC}  -c $< -o ${P_OBJ}/$@
	
${IOBJS}: %.o:${P_LIB}/%.cpp ${P_INC}/%.h
	${CC}  -c $< -o ${P_OBJ}/$@
	
${IRC}:	%.o: ${P_RES}/%.rc
	${RS}  -i $< -o ${P_RES}/$@
	
