target = bin/TinyServer

objects = src/*.o

$(target) : $(objects) 
	gcc $(objects) -lpthread -o $(target)

$(objects) : src/*.c
	make -C src


.PHONY : clean 
clean :
	rm -rf src/*.o bin/*