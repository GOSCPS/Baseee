# Code
baseee提供了一套算法供处理二进制数据  
目前包括Base64编码的转换及反转换  
位于baseee::code命名空间中  
函数原型：  
int binToBase64(const char in[],const int in_length,char out[],const int out_length);  
        int base64ToBin(const char in[],const int in_length,char out[],const int out_length);  