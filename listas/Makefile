#TADS
TAD1 = lista_ini

#APPS
APP1 = app_lista_ini#lista encadeada com nós alocados estaticamente
APP_EXEC = $(APP1)

#DIRETÓRIOS
APPS = ./apps
INCLUDE = ./include
SRC=./src
OBJ = ./obj
BIN = ./bin
SRC = ./src
DEBUG = ./src/bin_debug
BKP = ./src/src_bkp
SRC_BKP = src_bkp

#FLAGS
FLAGS_EXE =      -O3 -Wall -Wextra -std=gnu11 -Wno-unused-result -Wpedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIC  #-Werror -fsanitize=address -fsanitize=undefined -Wuninitialized

#não usar flag -fsanitize=address para depurar
FLAGS_DEBUG = -g -O0 -Wall -Wextra -std=gnu11 -Wno-unused-result -Wpedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIC -Wuninitialized #-Werror -fsanitize=undefined

all: clean tads exec _debug tree
	@echo "\n#Executáveis em $(BIN)\n"
	tree $(BIN) -f --si -C 
	@echo "\n\n#Executáveis para depuração em $(DEBUG)\n"
	tree $(DEBUG) -f --si -C

tads:
	@echo "\n\n#Compilação dos TADS (Tipos abstratos de dados)..."
	gcc -c $(FLAGS_EXE) $(SRC)/$(TAD1).c -I $(INCLUDE) -o $(OBJ)/$(TAD1).o
	@echo " "

exec:
	@echo "\n\n#Compilação dos Aplicativos (Executáveis)..."
	gcc $(FLAGS_EXE) $(APPS)/$(APP1).c $(OBJ)/$(TAD1).o -I $(INCLUDE) -o $(BIN)/$(APP1)	
	@echo " "

run:
	$(BIN)/$(APP_EXEC)

_debug:
	@echo "\n\n#Compilação dos Aplicativos com opção de depuração..."
	gcc $(FLAGS_DEBUG) $(APPS)/$(APP1).c $(SRC)/$(TAD1).c -I $(INCLUDE) -o $(DEBUG)/$(APP1)	
	@echo " "

ddd:
	ddd $(DEBUG)/$(APP_EXEC)

debug:
	gdb -ex 'start'   $(DEBUG)/$(APP_EXEC) # -ex 'rbreak lista_encadeada.c:.'

clean:  
	rm -rf $(OBJ)/$(TAD1).o
	rm -rf $(BIN)/$(APP1)
	rm -rf $(DEBUG)/$(APP1)
	@echo " "	

tree:
	tree . -I $(SRC_BKP) -C --filesfirst 