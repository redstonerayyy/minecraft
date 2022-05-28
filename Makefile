.PHONY: build
build:
	cmake -B ./build
	make -C ./build
	cp ./build/opengl ./src
	./src/opengl

clean:
	rm -r ./build
