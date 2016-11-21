GPP = g++ -Wall -c -g
GPC = g++ -Wall
OBJECTS =  parser.o scanner.o sishCommands.o variableList.o main.o #lex.yy.o

sish : $(OBJECTS)
	$(GPC) $(OBJECTS) -o sish
#lex.yy.o : sish_global.h lex.yy.cpp
#	$(GPP) lex.yy.cpp -lfl
parser.o : sish_global.h parser.cpp
	$(GPP) parser.cpp
scanner.o : sish_global.h scanner.cpp
	$(GPP) scanner.cpp
sishCommands.o : sish_global.h sishCommands.cpp
	$(GPP) sishCommands.cpp
variableList.o : sish_global.h variableList.h variableList.cpp
	$(GPP) variableList.cpp
main.o : sish_global.h main.cpp
	$(GPP) main.cpp
#lex.yy.cpp : sish_global.h pa4Scanner.l
#	flex pa4Scanner.l

clean:
	rm -f $(OBJECTS) sish
