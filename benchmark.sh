#!/usr/bin/env sh

./ittybitty > /dev/null &
./siege/bin/siege localhost:3490 -b -r100 --log=siege.log --rc=./siege/etc/siegerc -c10 > /dev/null
killall ittybitty

