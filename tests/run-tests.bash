#/bin/bash

key="$1"

exe='../src/Simplex'
if [[ ! -e "$exe" ]] && [[ $key != "clean" ]]; then
	echo "No such file \"$exe\", nothing to test. Aborting."
	exit 1
fi

fail()
{
	echo "failed ($1)"
}

_diff()
{
	diff_out=`diff -q "$1" "$2"`
	if [[ $? != 0 ]]; then
		fail "$diff_out"
		false
	fi
}

for test_txt in test*.txt; do
	test_name=${test_txt%\.*}
	
	if [[ $key == "clean" ]]; then
		rm -fv "${test_name}.out" "${test_name}.table"
		continue
	fi

	echo -n "Running $test_name... "

	$exe <$test_txt >${test_name}.out
	mv -f table.txt "${test_name}.table"
	retval=$?
	if [[ $retval != 0 ]]; then
		fail "Program exited with code $retval"
		continue
	fi

	_diff "${test_name}.out" "${test_name}.out.correct" || continue
	_diff "${test_name}.table" "${test_name}.table.txt.correct" || continue

	echo "passed"
done 
