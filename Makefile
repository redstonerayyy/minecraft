.PHONY: build
build:
	cmake -B ./build
	make -C ./build
	cp ./build/opengl ./src
	chmod +x ./src/opengl
	./src/opengl

clean:
	rm -r ./build
