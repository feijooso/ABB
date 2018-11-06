EXEC = abb
OBJ_FILES = abb.c main_abb.c testing.c pruebas_alumno.c
C_FLAGS = -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror

all:
	gcc -g $(C_FLAGS) -o $(EXEC) $(OBJ_FILES)

run:	all
	clear
	./$(EXEC)

valgrind:	all
	clear
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(EXEC)

debug:	all
	clear
	gdb ./$(EXEC) -tui

zip: 
	zip -r $(EXEC) . -x "*.zip"
