#!/bin/sh

cmd="./noxim -pir 0.01 poisson -sim 100000 -warmup 100 -size 8 8 -buffer 12 -pwr default_router.pwr -lpls -qos 0.5 -routing xy -dimx 4 -dimy 4 -traffic benchmark"
cmds="./noxim -pir 0.01 poisson -sim 100000 -warmup 100 -size 8 8 -buffer 12 -pwr default_router.pwr -lpls -qos 0.5 -routing xy -dimx 4 -dimy 4 -traffic benchmark -bench 1"

extension=.log.2
logname="$1$extension"
tracepath=/media/yaswanth/nasstore/approx_proj/traces/
tracedir="$tracepath$1"
echo $tracedir
echo $tracepath

cd bin_app_base
rm node\[*
rm mc\[*
echo "current dir $PWD"
find $tracedir -name "node\[*" -exec "cp" "{}" . ";"
find $tracedir -name "mc\[*" -exec "cp" "{}" . ";"
echo "copied traces to $PWD"
$cmd > $logname

cd ../bin_app_noc
rm node\[*
rm mc\[*
echo "current dir $PWD"
find $tracedir -name "node\[*" -exec "cp" "{}" . ";"
find $tracedir -name "mc\[*" -exec "cp" "{}" . ";"
echo "copied traces to $PWD"
$cmds > $logname

echo "Done."

cd ..
exit 0
