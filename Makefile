# Makefile for CS300
# Shang-Chun, Lin 2020

CPP = g++
CPPFLAGS = -Wall -Werror -g
SRC = conway.cpp
OUT = conway

$(OUT): $(SRC)
	$(CPP) $(CPPFLAGS) -o $(OUT) $(SRC) -lncurses

clean:
	-rm -f $(OUT) $(OUT).zip

zip:
	zip -v $(OUT).zip *.cpp *.md Makefile
