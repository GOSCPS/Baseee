#ifndef _BASEEE_INI_CPP_
#define _BASEEE_INI_CPP_
/*baseee::ini
 *ini parser moudle source
 *MIT License
 *coder:chhdao 
 */
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include "../Baseee.hpp"
#include "ini.hpp"
#include "../string/string.hpp"




        void baseee::ini::IniParser::Parser(){

            std::string now_section("_BASEEE_INI_PASPER_ERROR_");

            for(auto s:source){
                s = baseee::string::trim(s);
                if(s.empty()) continue;
                if(s[0] == ';') continue;
                if(s[0] == '[') {
                    now_section = s.substr(1,s.find(']')-1);
                    continue;
                }
                std::string name(s.substr(0,s.find('=')));
                std::string var;

                if(s.find(';') != s.npos){
                    var = s.substr(s.find('=')+1,s.find(';'));
                    var = baseee::string::trim(var);
                }
                else{
                    var = s.substr(s.find('=')+1);
                    var = baseee::string::trim(var);
                }

                Push(now_section,name,var);
                std::cout << now_section << ":" << name << ":" << var << std::endl;
                continue;
            }

            return;
        }

        void baseee::ini::IniParser::Push(std::string section,std::string name,std::string var){
                if(var.empty() || name.empty() || section.empty()) return;

                //number
                {
                bool num=true;

                for(auto c:var){
                if(!(std::isdigit(c) || c == '-' || c == '+')) num = false;
                }

                if(num){
                std::cout << "Number" << std::endl;
                int i=std::stoi(var);
                Int_list[section].insert({name,i});
                return;
                }
                }

                //double
                {
                    bool point=true;

                    for(auto c:var){
                if(!(std::isdigit(c) || c == '+' || c == '-' || c == '.')) point = false;
                }

                if(point){
                std::cout << "point" << std::endl;
                double i=std::stod(var);
                Double_list[section].insert({name,i});
                return;
                }
                }

                //String
                {
                    std::string buf;
                    if(var.find('\'') != var.npos && var.find_last_of('\'') != var.npos){
                        buf = var.substr(var.find('\'')+1,var.find_last_of('\'') - var.find('\'')-1);
                        std::cout << "string" << std::endl;
                        String_list[section].insert({name,buf});
                        return;
                    }

                }


                //boolean
                {
                if(var == "true") {
                Boolean_list[section].insert({name,true});
                std::cout << "boolean" << std::endl;}
                else if(var == "false") {Boolean_list[section].insert({name,false});
                std::cout << "boolean" << std::endl;}
                return;
                }
                
                throw std::runtime_error("Ini pasping error");
                return;
            }



            int baseee::ini::IniParser::getNumber(std::string section,std::string name){
                auto i = Int_list.find(section);
                if(i != Int_list.cend()){
                    auto b = i->second.find(name);
                    if(b != i->second.end()){
                        return b->second;
                    }
                }
                throw std::runtime_error("Ini not found");
                return baseee::RUNTIME_ERROR;
            }
            double baseee::ini::IniParser::getDouble(std::string section,std::string name){
                auto i = Double_list.find(section);
                if(i != Double_list.cend()){
                    auto b = i->second.find(name);
                    if(b != i->second.end()){
                        return b->second;
                    }
                }
                throw std::runtime_error("Ini not found");
                return baseee::RUNTIME_ERROR;
            }
            std::string baseee::ini::IniParser::getString(std::string section,std::string name){
                auto i = String_list.find(section);
                if(i != String_list.cend()){
                    auto b = i->second.find(name);
                    if(b != i->second.end()){
                        return b->second;
                    }
                }
                throw std::runtime_error("Ini not found");
                return "_BASEEE_INI_PASPER_ERROR_";
            }
            bool baseee::ini::IniParser::getBoolean(std::string section,std::string name){
                auto i = Boolean_list.find(section);
                if(i != Boolean_list.cend()){
                    auto b = i->second.find(name);
                    if(b != i->second.end()){
                        return b->second;
                    }
                }
                throw std::runtime_error("Ini not found");
                return -1;
            }


#endif