#!/bin/bash

Error(){
    if test $1 != "0"
    then
    echo -e "\033[31mbuild error"
    exit
    fi 
}

echo -e "Baseee Build script...checking rely"
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
echo -e "check ok,build?...[Y\\N]"
read if_build
if test $if_build = "Y"
then
echo -e "Build Baseee lib!\n"
#Build command
mkdir Baseee

#build base
clang++ -c -std=c++17 -pthread -Wall -O3 -x c++-header -o Baseee/Baseee.hpp.pch src/Baseee.hpp
a=`echo $?`
Error $a 
echo -e "\033[32mBaseee base moudle build end\n\033[0m"


#build log
clang++ -c -std=c++17 -pthread -Wall -O3 -x c++-header -o Baseee/log.hpp.pch src/log/log.hpp
a=`echo $?`
Error $a 
echo -e "\033[32mBaseee log moudle build end\n\033[0m"


#build string
clang++ -c -std=c++17 -pthread -Wall -O3 -x c++-header -o Baseee/string.hpp.pch src/string/string.hpp
a=`echo $?`
Error $a 
echo -e "\033[32mBaseee string moudle build end\n\033[0m"

#Build code
clang++ -c -std=c++17 -pthread -Wall -O3 -x c++-header -o Baseee/code.hpp.pch src/code/code.hpp
a=`echo $?`
Error $a 
echo -e "\033[32mBaseee code moudle build end\n\033[0m"

#Build ini
clang++ -c -std=c++17 -pthread -Wall -O3 -x c++-header -o Baseee/ini.hpp.pch src/ini/ini.hpp
a=`echo $?`
Error $a 
echo -e "\033[32mBaseee code moudle build end\n\033[0m"



#build end
echo -e "Baseee Build Ok,enjoy using Baseee!\n"
exit
else
echo -e "No 'Y' Exit"
exit
fi

