default:
	cd src/ && nmake
test:
	cd tests/ && call run-tests.bat
clean:
	cd src/ && nmake clean
	cd tests/ && @for %%f in (*.out) do @del %%f >nul
	cd tests/ && @for %%f in (*.table) do @del %%f >nul
all: clean default test
