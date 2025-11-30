#TADS
TAD1 = lista_ini
TAD2 = lista_encadeada

#APPS
APP1 = app_lista_ini#lista encadeada com nós alocados estaticamente
APP2 = app_lista_encadeada#lista simplesmente encadeada, alocada dinamicamente
APP_EXEC = $(APP2)

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
FLAGS_EXE =      -O3 -Wall -Wextra -std=gnu11 -Wno-unused-result -Wpedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIC  -fsanitize=undefined #-Werror -Wuninitialized

#não usar flag -fsanitize=address para depurar
FLAGS_DEBUG = -g -O0 -Wall -Wextra -std=gnu11 -Wno-unused-result -Wpedantic -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIC  -fsanitize=undefined #-Werror -fsanitize=undefined -Wuninitialized -fsanitize=address

all: clean tads exec _debug tree
	@echo "\n#Executáveis em $(BIN)\n"
	tree $(BIN) -f --si -C 
	@echo "\n\n#Executáveis para depuração em $(DEBUG)\n"
	tree $(DEBUG) -f --si -C

tads:
	@echo "\n\n#Compilação dos TADS (Tipos abstratos de dados)..."
	gcc -c $(FLAGS_EXE) $(SRC)/$(TAD1).c -I $(INCLUDE) -o $(OBJ)/$(TAD1).o
	@echo " "
	gcc -c $(FLAGS_EXE) $(SRC)/$(TAD2).c -I $(INCLUDE) -o $(OBJ)/$(TAD2).o
	@echo " "
	#@sleep 1

exec:
	@echo "\n\n#Compilação dos Aplicativos (Executáveis)..."
	gcc $(FLAGS_EXE) $(APPS)/$(APP1).c $(OBJ)/$(TAD1).o -I $(INCLUDE) -o $(BIN)/$(APP1)	
	@echo " "
	#@sleep 1
	gcc $(FLAGS_EXE) $(APPS)/$(APP2).c $(OBJ)/* -I $(INCLUDE) -o $(BIN)/$(APP2)	
	@echo " "
	#@sleep 1

run:
	$(BIN)/$(APP_EXEC)

_debug:
	@echo "\n\n#Compilação dos Aplicativos com opção de depuração..."
	gcc $(FLAGS_DEBUG) $(APPS)/$(APP1).c $(SRC)/$(TAD1).c -I $(INCLUDE) -o $(DEBUG)/$(APP1)	
	gcc $(FLAGS_DEBUG) $(APPS)/$(APP2).c $(SRC)/$(TAD2).c $(OBJ)/ec_rgb_colors.o -I $(INCLUDE) -o $(DEBUG)/$(APP2)	
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
	rm -rf $(OBJ)/$(TAD2).o
	rm -rf $(BIN)/$(APP2)
	rm -rf $(DEBUG)/$(APP2)
	@echo " "
#tree -I $(SRC_BKP)

tree:
	tree . -I $(SRC_BKP) -C --filesfirst 
	#@sleep 1