default:
	cd src/ && make
test:
	cd tests/ && ./run-tests.bash
clean:
	cd src/ && make clean
	cd tests/ && ./run-tests.bash clean
all: default test
