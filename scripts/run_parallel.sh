#!/bin/bash

if [ "${1}" != "" ]; then
	echo "Processing images at ${1}"
else
	echo "Usage:"
	echo "./run_parallel.sh (PATH TO dual_iso .cr2) (number of threads)"
	echo "You can define how many threads should be used. Number of cores will be used if not defined."
	echo "This script depends on the GNU parallel Application."
    exit 1
fi

if [ "${2}" != "" ]; then
	threads=${2}
	echo "Using $threads threads"
else
	threads=`nproc`
	echo "Using number of cores: $threads"
fi

find ${1} -type f -iname '*.cr2' -print | parallel -j$threads cr2hdr