#!/bin/bash

if [ "$#" -eq "0" ] || [ "$#" -ge "4" ]; then
    echo "USAGE: $(basename $0) <INPUT_DATA_TXT_FILE> <LINE_SEARCH_STRING>"
    echo "       (produces a plot with filename out.png)"
    echo "   OR: $(basename $0) <INPUT_DATA_TXT_FILE>"
    echo "       (lists most sensible search strings in the file)"
    echo "   OR: $(basename $0) <INPUT_DATA_TXT_FILE> <LINE_SEARCH_STRING> <OUTPUT_PNG>"
    echo "       (produces a plot with filename <OUTPUT_PNG>)"
    exit 1
fi

if [ "$#" -eq "1" ]; then
    fname=$1
    grep -E "^(log_hist[^=]*|lin_hist[^=]*|[^=]*_by_thread)=([0-9.:]+[ ]+)*[0-9.:]+$" $fname | cut -d"=" -f1
    exit 0
fi

fname=$1
searchstr=$2
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
export PATH=$SCRIPTPATH/../tools:$SCRIPTPATH:$PATH
outfile=out.png
if [ "$#" -eq "3" ]; then
    outfile=$3
fi

line=$(cat "$fname" | grep "$searchstr" | tail -1)

if [[ "$line" == *"_by_thread"* ]] || [[ "$line" == *"_by_index"* ]]; then
    echo "$line" \
            | cut -d"=" -f2 | tr " " "\n" \
            | awk '{print NR, $1}' \
            | plotbar.py -o $outfile -t "$searchstr"
else
    echo "$line" \
            | cut -d"=" -f2 | tr " " "\n" | tr ":" " " \
            | awk '{print "line", 1+log($1)/log(2), $2}' \
            | plotbars.py -o $outfile --log  -t "$searchstr" --font-size 12
fi
