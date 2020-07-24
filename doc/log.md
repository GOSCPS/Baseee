# log
baseee提供了一个简单的log系统，可以简单的自定义地输出日志   
引用#include "Baseee/log/log.hpp"即可使用   
命名空间位于baseee::log   
提供了一个logger类，必须为其提供几个初始化参数   

logger(std::string name,std::string format,std::string out_format);   
name指程序名，你也可以根据需要更换  
format指日志格式，需要提供一个字符串   
out_format指输出，需要提供一个字符串  
format将以以下格式输出  
format log  

format提供几个变量：  
{name} logger构造函数提供的name   
{level}日志等级  
各种时间：  
{year},{mongth},{day},{hour},{min},{sec}  
如"{name}-{level} {hour}-{min}{sec} "打印error级别的日志"ERROR"可能会输出(name为test,现在为1时1分1秒)   
"test-error 1-1-1 ERROR"   

out_format可以设置两个选项：  
fiel=path   
lowest_level=level   
file设置log文件路径，所有log都会被打印到这里  
lowest_level设置最低打印等级，等于或高于这个等级的日志会被写入clog

有4个等级：info important error fatal  
分别用print_level(std::string)打印  