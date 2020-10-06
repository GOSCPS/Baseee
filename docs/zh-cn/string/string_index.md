# baseee::string
baseee::string中提供了一些字符串操作，以及Unicode支持   
```c++
//删除字符串头尾的空白字符
//T 传入参数，字符串
//OUT 传出的std::basic_string类型：
//如std::string = std::basic_string<char>
template<typename T,typename OUT>
std::basic_string<OUT> Trim(T s) noexcept;

//split，根据正则表达式分割字符串，返回结果集
//s字符串，r正则表达式
std::vector<std::string> Split(const std::string& s, const std::string& r);
std::vector<std::string> Split(const std::string& s, const std::regex& r);


//ExpandsTabs 将tab转化为空格
//默认一个tab为8空格
std::string ExpandsTabs(const std::string& s, const int TabSizes = 8)noexcept;

//With判断字符串是否以end/start结尾/开头
bool StartsWith(const std::string& s, const std::string &start)noexcept;
bool EndWith(const std::string& s, const std::string& end)noexcept;

//Center 将字符串居中
//SurplusSpaceLeft控制是否将多余的空格分配在左侧(begin)，否则分配在右侧(end)(默认true)
std::string Center(const std::string& s,const bool SurplusSpaceLeft = true)noexcept;

//大写转小写，小写转大写
std::string SwapCase(const std::string& s)noexcept;

//格式化字符串
//返回string的vsnprintf
std::string Format(const char * fmt, ...)noexcept;
```

# baseee::coder
baseee还提供了Unicode编码的转换器
```c++
template<typename I, typename O>
int Utf8ToUtf32(I b, I e, O ob, O oe) noexcept;

template<typename I, typename O>
int Utf32ToUtf8(I b, I e, O ob, O oe) noexcept;

template<typename I, typename O>
int Utf8ToUtf16(I b, I e, O ob, O oe) noexcept;

template<typename I, typename O>
int Utf16ToUtf8(I b, I e, O ob, O oe) noexcept;

```
输入一对迭代器(b,e)  
输出一对迭代器(ob,oe)  
错误返回非0，否则返回0。