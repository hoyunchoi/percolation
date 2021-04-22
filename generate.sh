#!/bin/bash

srcDir=src
libDir=lib
binDir=bin
common=../library

networkSize=$1
prob=$2
ensembleSize=$3
coreNum=$4

name=N${networkSize}P${prob}E${ensembleSize}C${coreNum}

function debugBuild {
	g++ -std=c++17 -Wall -g -fsanitize=leak -I ${common} -I ${libDir}\
	    ${srcDir}/main-site1d.cpp\
        -o ${binDir}/${name}
}

function build {
	g++ -std=c++17 -O3 -flto -march=native -I ${common} -I ${libDir} -o ${binDir}/${name} \
		${srcDir}/main-site1d.cpp
}

#* Compile the source files
build
# debugBuild

#* Run
cd ${binDir}
./${name} ${networkSize} ${prob} ${ensembleSize} ${coreNum} >> ../log/generate.log
rm ${name}