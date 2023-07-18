CC := gcc
BIN := bin/main.exe
DLL := bin/mem.dll
INCFLAGS := -IAPI
LINKFLAGS := -Lbin -lmem

all: $(BIN)

$(BIN): $(DLL) test/main.c 
	$(CC) test/main.c -g -o $(BIN) $(INCFLAGS) $(LINKFLAGS)

$(DLL): API/containers/darray.c API/containers/darray.h API/defines.h 
	$(CC) API/containers/darray.c -g -shared -DDLL_EXPORT -o $@ $(INCFLAGS) 

run:
	./$(BIN)

clean:
	@$(RM) -rv bin/*

.PHONY: clean run all 