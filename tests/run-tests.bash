#/bin/bash

exe='../src/Simplex'

if [[ $1 != "" ]] && [[ $1 != "update" ]] && [[ $1 != "clean" ]]; then
	if ! echo $1 | grep -q "^[0-9]*$"; then
		echo "What does \"$1\" mean? What do you want?"
		exit 1
	fi
fi

if [[ $1 == "" ]] || [[ $1 == "update" ]]; then
	if [[ ! -e "$exe" ]]; then
		echo "No such file \"$exe\", nothing to test. Aborting."
		exit 1
	fi
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
	
	if [[ $1 == "clean" ]]; then
		rm -fv "${test_name}.out" "${test_name}.table"
		continue
	fi

	if [[ $1 == "update" ]]; then
		if [[ $2 != "" ]] && [[ "test${2}" != $test_name ]]; then
			continue
		fi 
		echo "Updating answers for $test_name"
		$exe <$test_txt >${test_name}.out
		mv -f table.txt "${test_name}.table.txt.correct"
		mv -f ${test_name}.out "${test_name}.out.correct"
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
