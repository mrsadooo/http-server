CC = gcc
SOURCE  = ./src
DEST = ./dist
OBJ_DIR = ./obj
HEADERS = ./headers
ARTIFACTS = main.o \
            server.o \
            client.o \
            cgi.o

make: clean build

$(ARTIFACTS): %.o: $(SOURCE)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c -I$(HEADERS) $< -o $(OBJ_DIR)/$@

build: $(ARTIFACTS)
	mkdir -p $(DEST)
	$(CC) -pthread $(patsubst %,$(OBJ_DIR)/%,$(ARTIFACTS)) -o $(DEST)/server

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(DEST)/*