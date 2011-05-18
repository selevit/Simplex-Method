#/bin/bash

exe='../src/Simplex'

for _test in test*.txt; do
	test_name=${_test%\.*}
	rm -f ${test_name}.out
	echo -n "Running $test_name... "
	if eval $exe <$_test >$test_name.out && eval diff -q ${test_name}.out ${test_name}.correct.out; then
		echo "passed"
	else
		echo "failed"
	fi
done 
