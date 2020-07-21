#!/bin/bash
echo -e "Build Baseee c++ lib\n"

#prepare clang
clang=`clang`

if [[ $clang =~ ^c+?l+?a+?n+?g+?.*$ ]]
then
echo -e "clang checking ok\n"
else
echo -e "clang uninstall!\n"
exit
fi


#Build
echo -e "continue?...[Y\\N]"
read if_build
if test $if_build = "Y"
then
echo -e "Build Baseee lib!\n"
#Build command
mkdir Baseee
clang++ -c -std=c++17 -pthread -Wall -O3 -o Baseee/Baseee.pch src/Baseee.hpp
clang++ -c -std=c++17 -pthread -Wall -O3 -o Baseee/log.pch src/log/log.hpp


echo -e "Baseee Build Ok,enjoy using Baseee\n"
else
echo -e "No 'Y' Exit"
exit
fi
