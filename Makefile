default:
	cd src/ && make
test:
	cd tests/ && make
win32:
	./win32_src_prepare
clean:
	rm -rf build/
	cd src/ && make clean
	cd tests/ && make clean
all: default win32 test
