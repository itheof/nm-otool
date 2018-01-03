#!/bin/sh

set -e

TEST_PATH="$( pwd )/test"

log () {
	>&2 python <<- EOF
	s = '$@'
	pad_left = ( 80 - len(s) - 2 ) / 2
	pad_right = 80 - pad_left - len(s) - 2
	out = '>' * pad_left + ' ' + s + ' ' + '<' * pad_right
	print out
EOF
}

cleanup() {
	rm -f "${TEST_PATH}"/ref_{out,err}.log "${TEST_PATH}"/test_{out,err}.log
}

assert () {
	[ $1 -eq $2 ] || (echo "Return values differ: $1 != $2 !" >&2 ; exit 1)
}

compare () { # 1: Ref binary 2: Test binary 3+: Options
	files=$(find "${TEST_PATH}" -not -name "*.c" -not -type d)
	for file in $files;
	do
		log Running \`"$1" $3 "$file"\`
		"$1" $3 "$file" \
			> "${TEST_PATH}/ref_out.log" \
			2> "${TEST_PATH}/ref_err.log" \
			&& ret_ref=$? || ret_ref=$?

		log Running \`"$2" $3 "$file"\`
		"$2" $3 "$file" \
			> "${TEST_PATH}/test_out.log" \
			2> "${TEST_PATH}/test_err.log" \
			&& ret_test=$? || ret_test=$?
		diff "${TEST_PATH}"/{ref,test}_out.log
		assert $ret_ref $ret_test
		cleanup
	done
}

trap cleanup EXIT
compare nm ./ft_nm
compare otool ./ft_otool -t

log All tests passed.
