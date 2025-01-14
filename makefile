# Cible par défaut
all: simu

# Détection du système
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    CC = g++
    CFLAGS = -I/opt/homebrew/Cellar/raylib/5.0/include -Wall -std=c++17
    LDFLAGS = -L/opt/homebrew/Cellar/raylib/5.0/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
else
    CC = g++
    CFLAGS = -I$(HOME)/raylib/src -Wall -std=c++17
    LDFLAGS = -L$(HOME)/raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Nom de l'exécutable
OUTPUT = simu

# Liste des fichiers objets
OBJS = maze_affichage.o

# Compilation des fichiers objets
%.o: %.cpp
	$(CC) -c $< $(CFLAGS) -o $@

# Lier les fichiers objets en un exécutable
$(OUTPUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT) $(LDFLAGS)

# Nettoyage
clean:
	rm -f $(OUTPUT) *.o

.PHONY: all clean
