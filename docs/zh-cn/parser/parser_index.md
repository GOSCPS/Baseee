# baseee:parser
baseee目前有两个解析器：ini和json解析器    
他们分别位于baseee/inip.hpp和baseeee/jsonp.hpp文件内   

## ini 解析器
ini解析器为 baseee::parser::IniParser   
它的赋值构造函数被删除和赋值构造函数。请不要进行类似操作。

要使用Ini解析器很简单，它只有5个成员函数：
```c++
int Parser(std::string_view Ini) noexcept;

std::optional<int64_t> GetInt(std::string_view section, std::string_view name) noexcept;
std::optional<double> GetDouble(std::string_view section, std::string_view name) noexcept;
std::optional<std::string> GetString(std::string_view section, std::string_view name) noexcept;

std::set<std::string> GetSection() noexcept;
```
其中Parser用于解析字符串，如果Ini有错误，返回错误行号，否则返回0.     
GetType则用于获取数据，如果找不到数据则返回std::nullopt。    
GetSection用于获取Ini中的段的集合，没有段则为空。      
所有函数均为noexcept。    
  
注意： **这个解析器不支持把注释嵌入到语句**  
即
```ini
合法：
;set ip
ip=127.0.0.1 
不合法：
ip=127.0.0.1 ;set ip
```

例子（来自unit-test.cpp)：
```c++
void IniParserTest() {

	cout << "Test Parser Ini" << endl;

	baseee::parser::IniParser Parser;
	cout << Parser.Parser("[Test1]\nTestInt=-114514\nTestDouble=-114.514\nTestStr=\"Hello World\"\nTestSStr=Right!") << endl;

	if (Parser.GetInt("Test1", "TestInt").has_value()) {
		cout << "Int:" << Parser.GetInt("Test1", "TestInt").value() << endl;
	}
	if (Parser.GetDouble("Test1", "TestDouble").has_value()) {
		cout << "Double:" << Parser.GetDouble("Test1", "TestDouble").value() << endl;
	}

	if (Parser.GetString("Test1", "TestStr").has_value()) {
		cout << "Str:" << Parser.GetString("Test1", "TestStr").value() << endl;
	}

	if (Parser.GetString("Test1", "TestSStr").has_value()) {
		cout << Parser.GetString("Test1", "TestSStr").value() << endl;
	}

	return;
}
```
它应该输出：
```console
Test Parser Ini
0
Int:-114514
Double:-114.514
Str:Hello World
Right!
```

## Json解析器
Json解析器为 baseee::parser::JsonParser   
和Ini解析器一样，它的赋值构造函数和赋值构造函数被删除。   

Json解析器仅仅用于解析Json所以只需要使用到两个函数：
```c++
JsonErrCode Parser(std::string_view JsonStr) noexcept;
JsonData GetJsonData() noexcept;
```
Parser用于解析Json，返回Json代码  
```c++
//解析器错误代码
		enum class JsonParserErrorCode : int {
			Parse_OK = 0,//正常
			Parse_UnknowError,//未知错误
			Parse_MissVulan,//无值
			Parse_VulanError,//值错误
			Parse_MissToken//找不到对应Token {} [] "" ,
		};
        using JsonErrCode = JsonParserErrorCode;
```
如果解析成功，返回JsonErrCode::Parse_OK   
并且把Json树储存在类内，使用JsonData GetJsonData()获取   
JsonData储存Json树，结构如下：
```c++
        //Json类型
		enum class JsonType : int {
			JsonType_Null,
			JsonType_True,
			JsonType_False,
			JsonType_Number,
			JsonType_String,
			JsonType_Array,
			JsonType_Object
		};

		//Json数据结构
		class JsonData {
		public:
			std::variant<
				double,//数字
				std::string,//字符串
				std::vector<JsonData>,//数组
				std::multimap<std::string, JsonData>>//对象
				Data = 0.0;
			JsonType JsonT = JsonType::JsonType_Null;//类型
		};
```

## Json操作
Baseee提供了方便访问Json的各种操作：  
```c++
void JsonParserTest() {
	//获取新的空Json树
	baseee::parser::JsonDataBuilder Builder(baseee::parser::CreateNewJsonTree());

	//获取Json树字符串构造器
	baseee::parser::JsonStringBuilder JsonBuilder;
	//.SetBeautiful(true)可以让Json树字符串构造器输出更可读带空白的Json
	JsonBuilder.SetBeautiful(true);
	
	//通过[key] = value进行赋值
	Builder["String Test"] = "Hello World"sv;
	Builder["Number Test"] = 114.514;
	Builder["Boolean Test"] = true;

	//支持多重key
	Builder["Fisrst"]["Second"] = "Third"sv;

	//支持数组
	Builder["Arrat Test"] = { {"One"sv},2.0,true };

	//支持嵌套数组
	Builder["Fuck Array"] = { {{{{{{{{{{{ "Fucking Array"sv }}}}}}}}}}} };

	cout << "-------" << endl;
	//把Json树构建到字符串
	cout << JsonBuilder.Build(*Builder.GetJsonTree());
	//释放Json树
	Builder.Release();
	cout << "-------" << endl;

	return;
}
```   
以上代码输出:
```console
-------
{
"Arrat Test":[["One"],2.000000,true],
"Boolean Test":true,
"Fisrst":{
"Second":"Third"
},
"Fuck Array":[[[[[[[[[[[["Fucking Array"]]]]]]]]]]]],
"Number Test":114.514000,
"String Test":"Hello World"
}
-------
```

此外，还有一些操作:   
```c++
//删除子节点
void JsonDataBuilder::Delete(std::string_view String);

//查找节点
std::optional<JsonDataBuilder> JsonDataBuilder::FindChild(std::string_view Name);

//获取节点类型
JsonType GetJsonType() noexcept;

/*伪代码示例*/

baseee::parser::JsonDataBuilder Builder(baseee::parser::CreateNewJsonTree());

Builder["Test"]["Number"] = 1;
Builder.FindChild("Test"sv).value.Delete("Number");

//现在Builder应该为空
```