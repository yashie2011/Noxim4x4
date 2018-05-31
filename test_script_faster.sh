#!/bin/sh

cmd="./noxim -pir 0.01 poisson -sim 100000 -warmup 100 -size 8 8 -buffer 12 -pwr default_router.pwr -lpls -qos 0.5 -routing xy -dimx 4 -dimy 4 -traffic benchmark"
cmds="./noxim -pir 0.01 poisson -sim 100000 -warmup 100 -size 8 8 -buffer 12 -pwr default_router.pwr -lpls -qos 0.5 -routing xy -dimx 4 -dimy 4 -traffic benchmark -bench $2"
cmdg= "./noxim -pir 0.01 poisson -sim 100000 -warmup 100 -size 8 8 -buffer 12000 -pwr default_router.pwr -lpls -qos 0.5 -routing xy -dimx 4 -dimy 4 -traffic benchmark"

extension=.log
logname="$1$extension"
tracepath=/home/rama/Downloads/
tracedir="$tracepath$1"
echo $tracedir
echo $tracepath

cd bin_app_base
echo "current dir $PWD"
find $tracedir -name "node\[*" -exec "cp" "{}" . ";"
find $tracedir -name "mc\[*" -exec "cp" "{}" . ";"
echo "copied traces to $PWD"
$cmd > $logname
rm node\[*
rm mc\[*

cd ../bin_app_noc
echo "current dir $PWD"
find $tracedir -name "node\[*" -exec "cp" "{}" . ";"
find $tracedir -name "mc\[*" -exec "cp" "{}" . ";"
echo "copied traces to $PWD"
$cmds > $logname
rm node\[*
rm mc\[*

cd ../bin_new_gpu
echo "current dir $PWD"
find $tracedir -name "node\[*" -exec "cp" "{}" . ";"
find $tracedir -name "mc\[*" -exec "cp" "{}" . ";"
echo "copied traces to $PWD"
$cmdg > $logname
rm node\[*
rm mc\[*

cd ../bin_new_gpu_2
echo "current dir $PWD"
find $tracedir -name "node\[*" -exec "cp" "{}" . ";"
find $tracedir -name "mc\[*" -exec "cp" "{}" . ";"
echo "copied traces to $PWD"
$cmdg > $logname
rm node\[*
rm mc\[*

cd ../bin_new_gpu_3
echo "current dir $PWD"
find $tracedir -name "node\[*" -exec "cp" "{}" . ";"
find $tracedir -name "mc\[*" -exec "cp" "{}" . ";"
echo "copied traces to $PWD"
$cmdg > $logname
rm node\[*
rm mc\[*


echo "Done."

cd ..
exit 0
