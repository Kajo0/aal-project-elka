SRC_PATH=src/
HDR_PATH=hdrs/

HDRS= -I hdrs
OBJS=$(SRC_PATH)main.o $(SRC_PATH)Algorithm.o $(SRC_PATH)Classroom.o $(SRC_PATH)FirstAlgorithm.o $(SRC_PATH)FourthAlgorithm.o $(SRC_PATH)Generator.o $(SRC_PATH)Model.o $(SRC_PATH)Order.o $(SRC_PATH)Reader.o $(SRC_PATH)Result.o $(SRC_PATH)SecondAlgorithm.o $(SRC_PATH)ThirdAlgorithm.o $(SRC_PATH)Timer.o

aal: $(OBJS)
	@echo "\t\tMake them all now.."
	@g++ -Wall $^ $(CFLAGS) $(HDRS) -o $@

.cpp.o:
	@echo "\t$< => .o"
	@g++ -Wall $(CFLAGS) $(HDRS) -c $*.cpp -o $*.o

clean:
	@rm -rf src/*.o 2>/dev/null
	@rm -rf *.html 2>/dev/null

$(SRC_PATH)Algorithm.o: $(HDR_PATH)Algorithm.h
$(SRC_PATH)Classroom.o: $(HDR_PATH)Classroom.h
$(SRC_PATH)FirstAlgorithm.o: $(HDR_PATH)FirstAlgorithm.h $(HDR_PATH)Generator.h
$(SRC_PATH)FourthAlgorithm.o: $(HDR_PATH)FourthAlgorithm.h $(HDR_PATH)FirstAlgorithm.h $(HDR_PATH)SecondAlgorithm.h $(HDR_PATH)ThirdAlgorithm.h $(HDR_PATH)Generator.h $(HDR_PATH)Model.h
$(SRC_PATH)Generator.o: $(HDR_PATH)Generator.h $(HDR_PATH)Model.h
$(SRC_PATH)main.o: $(HDR_PATH)Timer.h $(HDR_PATH)Model.h $(HDR_PATH)Result.h $(HDR_PATH)FirstAlgorithm.h $(HDR_PATH)SecondAlgorithm.h $(HDR_PATH)ThirdAlgorithm.h $(HDR_PATH)FourthAlgorithm.h
$(SRC_PATH)Model.o: $(HDR_PATH)Model.h $(HDR_PATH)Reader.h $(HDR_PATH)Generator.h
$(SRC_PATH)Order.o: $(HDR_PATH)Order.h
$(SRC_PATH)Reader.o: $(HDR_PATH)Reader.h
$(SRC_PATH)Result.o: $(HDR_PATH)Result.h $(HDR_PATH)Model.h
$(SRC_PATH)SecondAlgorithm.o: $(HDR_PATH)SecondAlgorithm.h $(HDR_PATH)Generator.h
$(SRC_PATH)ThirdAlgorithm.o: $(HDR_PATH)ThirdAlgorithm.h $(HDR_PATH)Generator.h
$(SRC_PATH)Timer.o: $(HDR_PATH)Timer.h
