default:
	cd src/ && make
test:
	cd tests/ && make
win32:
	(cd src && nmake win32)
clean:
	rm -rf build/
	cd src/ && make clean
	cd tests/ && make clean
all: default test
