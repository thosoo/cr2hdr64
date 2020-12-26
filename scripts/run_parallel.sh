#!/bin/bash
if [ "${2}" != "" ]; then
	threads=${2}
	echo "Using $threads threads"
else
	threads=`nproc`
	echo "Using number of cores: $threads"
fi

find ${1} -type f -iname '*.cr2' -print | parallel -j$threads cr2hdr