default:
	#make -f src/Makefile
test:
	make -f tests/Makefile
win32:
	./win32_src_prepare
clean:
	rm -rf build/
	# make -f tests/Makefile clean
	# make -f src/Makefile clean
