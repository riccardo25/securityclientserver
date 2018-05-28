#Makefile previsto per il progetto C client server
#written by Riccardo Fontanini
OBJECTS=

#compiler
CC=gcc

#general flags
CFLAGS= -std=gnu99

#libs

ARGS=fontanini,$(D)

NAMEFILE = main.c


LIBS =  



cclient: 
	#@mkdir -p build/linux
	$(CC) $(CFLAGS) client/main.c -o cl $(OBJECTS) $(LIBS) -D$(ARGS)
	@echo " "
	@echo "Compilazione completata! il file si trova nella cartella . !"
	@echo " "


cserver: 
	#@mkdir -p build/linux
	$(CC) $(CFLAGS) server/main.c -o ser $(OBJECTS) $(LIBS) -D$(ARGS)
	@echo " "
	@echo "Compilazione completata! il file si trova nella cartella . !"
	@echo " "

all: cclient cserver