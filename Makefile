dependency:
	cd build && cmake .. && make

prepare:
	rm -rf build
	mkdir build