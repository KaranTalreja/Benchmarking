OUT = bin/exec
OBJECTS = obj/source.o

$(OUT) : $(OBJECTS)
	@echo "source.o --> bin/exec"
	@g++ -o bin/exec obj/source.o -L../Utils/lib -lUtils -g
	
obj/source.o : source/source.cpp
	@mkdir -p bin obj
	@echo "source/source.cpp --> source.o"
	@g++ -g -Wall -c source/source.cpp -o obj/source.o -I../Utils/IO/include