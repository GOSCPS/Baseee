# baseee::log
baseee提供了一个简单的日志记录以供使用，它位于baseee::log命名空间内   
baseee::log::logger   
日志的默认构造函数和赋值构造函数是删除的，也请不要对logger进行类似操作   
它的构造参数如下：
```c++
logger& operator=(const logger&) = delete;
logger(const logger&) = delete;
logger() = delete;

logger(std::string_view &&LogFormat, std::string_view &&OutFile, std::ostream &os);
```
LogFormat用于指定日志格式。日志输出以 LogFormat + Log的形式输出。   
OutFile用于指定输出文件，如果为空则不输出到文件。   
os为输出日志的流：cin cerr clog等   

LogFormat和OutFile会经过处理，一些特殊的字符串会被替换：   
| 原字符串 | 被替换后的内容 |
| :------:|:-------------:|
| {year} | 系统时间 年 |
| {month}| 系统时间 月 |
| {day}  | 系统时间 日 |
| {hour} | 系统时间 时 |
| {min}  | 系统时间 分 |
| {sec}  | 系统时间 秒 |
| {threadId} | 当前线程ID |
| {level} | 输出日志等级 |

注意：{level}对OutFile无效，会被替换成空字符    
如果OutFile打开文件失败则会抛出异常    

日志等级：
```c++
enum class LogLevel : uint8_t
{
    //从低到高排列
	Level_Debug = 0,
	Level_Info = 1,
	Level_News = 2,
	Level_Note,
	Level_Warning,
	Level_Error,
	Level_Fatal
};
```

其他一些设置函数
```c++
void SetLowestLevelOutConsole(LogLevel level) noexcept;
void SetLowestLevelOutFile(LogLevel level) noexcept;
void SetDefaultOutLevel(LogLevel level) noexcept;
```
SetLowestLevelOutConsole设置一个等级，要输出的等级高于等于这个等级就输出到构造函数的os流中。   
SetLowestLevelOutFile设置一个等级，要输出的等级高于等于这个等级就输出到构造函数的文件中。（不输出到文件则忽略）  
SetDefaultOutLevel设置默认输出等级，即无指定等级的情况下输出的日志级别。

输出日志：
```c++
void PrintLog(std::string_view&& log) noexcept(_PrintLog);
void _PrintLog(LogLevel level, std::string_view&& log) noexcept;

logger &operator<<(std::string_view &&log) noexcept(PrintLog);

template<typename T>
logger &operator<<(T log) noexcept(PrintLog);
```
例子（来自unit-test.cpp）：
```c++
void LogTest() {
	baseee::log::logger logger("{year}-{month}-{day} at {hour}:{min}:{sec} {level}:","",std::cout);
	logger.SetLowestLevelOutConsole(baseee::log::LogLevel::Level_Debug);

	logger.SetDefaultOutLevel(baseee::log::LogLevel::Level_Debug);
	logger.PrintLog("Test:Log Print!");
	logger << "Hello World";

	logger._PrintLog(baseee::log::LogLevel::Level_Fatal, "Right!");
}
```
它应该输出（注意，时间并非一成不变）：
```console
2020-10-6 at 7:48:30 Debug:Test:Log Print!
2020-10-6 at 7:48:30 Debug:Hello World
2020-10-6 at 7:48:30 Fatal:Right!
```