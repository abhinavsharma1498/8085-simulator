ODIR = build/

CXX = g++

CXXFLAG = -Iheaders/ -g

OBJ = build/ADD.o build/ADI.o build/DAD.o build/DCR.o build/DCX.o build/INR.o build/INX.o build/SUB.o build/SUI.o build/LDA.o build/LDAX.o build/LHLD.o build/LXI.o build/MOV.o build/MVI.o build/SHLD.o build/STA.o build/STAX.o build/XCHG.o build/JC.o build/JMP.o build/JNC.o build/JNZ.o build/JZ.o build/CMA.o build/CMP.o build/CPI.o build/HLT.o build/execute.o build/generalOperations.o build/instructionValidation.o build/main.o build/read.o build/set.o build/debug.o build/executeSingle.o build/ANA.o build/ANI.o build/ORA.o build/ORI.o build/XRA.o build/XRI.o

SRC = source/arithmetic/ADD.cpp source/arithmetic/ADI.cpp source/arithmetic/DAD.cpp source/arithmetic/DCR.cpp source/arithmetic/DCX.cpp source/arithmetic/INR.cpp source/arithmetic/INX.cpp source/arithmetic/SUB.cpp source/arithmetic/SUI.cpp source/dataTransfer/LDA.cpp source/dataTransfer/LDAX.cpp source/dataTransfer/LHLD.cpp source/dataTransfer/LXI.cpp source/dataTransfer/MOV.cpp source/dataTransfer/MVI.cpp source/dataTransfer/SHLD.cpp source/dataTransfer/STA.cpp source/dataTransfer/STAX.cpp source/dataTransfer/XCHG.cpp source/jump/JC.cpp source/jump/JMP.cpp source/jump/JNC.cpp source/jump/JNZ.cpp source/jump/JZ.cpp source/logical/CMA.cpp source/logical/CMP.cpp source/logical/CPI.cpp source/machineControl/HLT.cpp source/execute.cpp source/generalOperations.cpp source/instructionValidation.cpp source/main.cpp source/read.cpp source/set.cpp source/debugger/debug.cpp source/debugger/executeSingle.cpp source/logical/ANA.cpp source/logical/ANI.cpp source/logical/ORA.cpp source/logical/ORI.cpp source/logical/XRA.cpp source/logical/XRI.cpp

8085: $(OBJ)
	$(CXX) $(OBJ) -o $@

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAG) -c $(SRC)
	mv *.o $(ODIR)

clean:
	rm $(ODIR)*.o
