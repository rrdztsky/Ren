EXE=ren

SRC=\
main.cpp\
App.cpp\
Camera.cpp\
Matrix3x3.cpp\
Matrix4x4.cpp\
Quat.cpp

SRCFILES=$(addprefix src/, $(SRC))

INC=-Wno-deprecated-declarations

LIBD=-framework OpenGL -framework GLUT -framework ApplicationServices

LIBR=-framework OpenGL -framework GLUT -framework ApplicationServices

OBJFILESD=$(addprefix Debug/, $(patsubst %.cpp, %.o, $(SRC)))
DEPFILESD=$(addprefix Debug/, $(patsubst %.cpp, %.d, $(SRC)))
OBJFILESR=$(addprefix Release/, $(patsubst %.cpp, %.o, $(SRC)))
DEPFILESD=$(addprefix Release/, $(patsubst %.cpp, %.d, $(SRC)))

all: debug

Debug/%.o: src/%.cpp Makefile
	c++ -std=c++14 -c -g -MMD -o $@ $(INC) $<

Release/%.o: src/%.cpp Makefile
	c++ -std=c++14 -O3 -c -MMD -o $@ $(INC) $<

debug: prepare Debug/$(EXE)

release: prepare Release/$(EXE)

Debug/$(EXE): $(OBJFILESD)
	c++ -std=c++14 -o $@ $(OBJFILESD) $(LIBD)
	cp $@ $(EXE)

Release/$(EXE): $(OBJFILESR)
	c++ -std=c++14 -o $@ $(OBJFILESR) $(LIBD)
	cp $@ $(EXE)

clean:
	rm -rf Debug Release $(EXE)

prepare:
	@mkdir -p $(sort $(dir $(OBJFILESD)))
	@mkdir -p $(sort $(dir $(OBJFILESR)))

tags:
	ctags -R src

-include $(DEPFILESD)
-include $(DEPFILESR)

.PHONY: all debug release clean prepare tags

