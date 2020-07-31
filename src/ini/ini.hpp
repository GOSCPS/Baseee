#ifndef _BASEEE_INI_HPP_
#define _BASEEE_INI_HPP_
#include <string>
#include <vector>
#include "../Baseee.hpp"
#include <set>
#include <map>
/*baseee::ini
 *ini parser moudle
 *MIT License
 *coder:chhdao 
 */

namespace baseee{
    namespace ini{

        class IniParser{
            public:
            int getNumber(std::string,std::string);
            double getDouble(std::string,std::string);
            std::string getString(std::string,std::string);
            bool getBoolean(std::string,std::string);

            IniParser(std::vector<std::string> in) : source(in) {Parser();}
            //IniParser() = default;
            //IniParser & IniParser(Iniparser&) = delete;
            //IniParser & operator=

            private:
            std::vector<std::string> source;
            void Parser();
            void Push(std::string section,std::string name,std::string var);

            std::map<std::string,std::map<std::string,int>> Int_list;
            std::map<std::string,std::map<std::string,double>> Double_list;
            std::map<std::string,std::map<std::string,std::string>> String_list;
            std::map<std::string,std::map<std::string,bool>> Boolean_list;
        };
        


    }
}


#include "ini.cpp"





#endif