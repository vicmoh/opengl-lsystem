

# framework information for older version of MACOS
#INCLUDES = -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

# frameworks for newer MACOS, where include files are moved 
INCLUDES = -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/ -framework OpenGL -framework GLUT -lm -Wno-deprecated-declarations
TARGET = -mmacosx-version-min=10.8
BIN = ./bin/
SRC = ./src/
CC = gcc
FLAGS = -Wall -std=c11 -Iinclude -Wno-nullability-completeness
m = [AUTO]

run: compile
	./a1 $(FILE)

compile:
	$(CC) $(FLAGS) $(SRC)*.c -o a1 $(INCLUDES) $(TARGET)

git:
	git add -A
	git commit -m "$(m)"
	git push

clean:
	rm a1
