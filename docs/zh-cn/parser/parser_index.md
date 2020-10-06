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
```
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
要根据Json树获取Json对象，可以使用
```c++
//查找Object
std::optional<baseee::parser::JsonData> 
JsonParser::FindChildren(std::string_view Name) noexcept;
```
如果找不到名称对应对象则返回std::nullopt，否则返回找到的JsonData   

## JsonBuilder
除了解析器，jsonp.hpp还提供了一些辅助操作JsonData的类   
baseee::parser::JsonBuilder 可以用JsonData生成字符串  
它仅仅有两个成员函数
```c++
std::string Build(JsonData jt) noexcept;
void SetBeautiful(bool b) noexcept;
```
你只需要把Json树放进Build的jt参数即可使用    
如果把SetBeautiful设置为true，那么它会输出一些换行来让json更加可读，默认为false。

## JsonDataBuilder
baseee::parser::JsonDataBuilder提供了一组操作JsonData的方法：
```c++
//返回Json Tree Root的引用
JsonData GetJsonData() noexcept;
//在p处添加一个JsonData
static std::optional<baseee::parser::JsonData>
AddJsonData(
JsonData p,
std::string_view name,
const JsonData d) noexcept;
```
其中GetJsonData()用于获取Json树根。   
AddJsonData是一个静态函数，它要做的就是把参数d放到根p内，参数name即为d的key   
返回操作后的参数p

以下是Json解析器的例子（来自unit-test.cpp）：
```c++
void JsonParserTest() {
	baseee::parser::JsonParser JsonParser;

/*
{ 
"people":[ 
{
"firstName": "Brett",            
"lastName":"McLaughlin"        
},      
{        
"firstName":"Jason",
"lastName":"Hunter"
}
]
}
*/
	std::string JsonTest = "{ \"people\":[ { \"firstName\": \"Brett\", \"lastName\":\"McLaughlin\"},{\"firstName\":\"Jason\",\"lastName\" : \"Hunter\"}]}";
	JsonParser.Parser(JsonTest);

	baseee::parser::JsonDataBuilder Builder;
	auto root = Builder.GetJsonData();

	baseee::parser::JsonData data;
	data.Data = "Hello Json Builder";
	data.JsonT = baseee::parser::JsonType::JsonType_String;

    //BASEEE_assert为断言
	BASEEE_assert(Builder.AddJsonData(root, "Test", data).has_value());
	root = Builder.AddJsonData(root, "Test", data).value();

	baseee::parser::JsonBuilder JsonBuilder;
	JsonBuilder.SetBeautiful(true);

	cout << JsonBuilder.Build(root) << endl;
	cout << "----------------------" << endl;
	cout << JsonBuilder.Build(JsonParser.GetJsonData()) << endl;

}
```
它应该输出：
```json
{
"Test":"Hello Json Builder"}

----------------------
{
"people":[{
"firstName":"Brett",
"lastName":"McLaughlin"},{
"firstName":"Jason",
"lastName":"Hunter"}]}
```