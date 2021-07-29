#! /bin/bash

cd prep
test_files=$(ls *.h)

output_dir="/tmp"

for f in $test_files; do
	gcc -E -P $f > "$output_dir/prep_${f}.gcc"
	cat $f > "$output_dir/prep_${f}.ucc"

	diff --color=always \
		"$output_dir/prep_${f}.ucc" \
		"$output_dir/prep_${f}.gcc"
	if [ ! "$?" -eq "0" ]; then
		exit 1
	fi
done

exit 0
