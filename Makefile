CXX=g++

DEBUG=-g
CPPFLAGS=$(DEBUG) -IC:\mingw-libs\include -LC:\mingw-libs\lib #-w -lmingw32 -lSDL2main -lSDL2 -lglew32
LDFLAGS=$(DEBUG) -Wall -std=c++11
#LDLIBS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW -I /usr/include/SDL2/
LDLIBS=-w -lmingw32 -lSDL2main -lSDL2 -lglew32 -lglu32 -lfreeGLUT -lOpenGL32 -LC:\mingw-libs\lib -mwindows -mconsole
#LDLIBS=-LC:\mingw-libs\lib -w -lmingw32 -lSDL2main -lSDL2 

# g++ 02_getting_an_image_on_the_screen.cpp -IC:\mingw-libs\include\SDL2 -LC:\mingw-libs\lib -w -lmingw32 -lSDL2main -lSDL2 -o program

SRC = $(shell find src/ -name "*.cpp")
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))
INCLUDE_DIR =include

.PHONY: all native wasm clean

all: native #wasm

# Prehaps something for the future?
wasm: 
	emcc $(SRC) -I $(INCLUDE_DIR) -Wall -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -std=c++11 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -O3 -o index.js --preload-file media/ --use-preload-plugins

native: build/Game


build/Game: $(OBJ)
	cmd.exe /C "$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@"

$(OBJ): build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	cmd.exe /C "$(CXX) $(CPPFLAGS) -c $< -o $@ -I $(INCLUDE_DIR)"

.depend: $(SRC)
	$(CXX) -MM $^ -I $(INCLUDE_DIR) > $@ && \
	sed -Ei 's#^(.*\.o: *)src/(.*/)?(.*\.cpp)#build/\2\1src/\2\3#' $@

clean:
	rm .depend
	rm build/*.o
	rm build/Game.exe

include .depend
