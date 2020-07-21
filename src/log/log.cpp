#ifndef _BASEEE_LOG_CPP_
#define _BASEEE_LOG_CPP_
/*Baseee::log
 *set_log and get_format
 *MIT License
 *coder:chhd 
 *time:2020-7-21
 *
 *history:carry out
 *
 * 
 */
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <ctime>
#include "log.hpp"

//set out format
void baseee::log::logger::set_log(){
    //split format
    std::regex ws_re("\\s+");
    std::vector<std::string> v(std::sregex_token_iterator(this->out_format.begin(), this->out_format.end(), ws_re, -1), std::sregex_token_iterator());

    //set file and lowest level
    for(auto s:v){
        if(s.size() > std::string("file=").size() && std::string(s.begin(),s.begin()+std::string("file=").size()) == "file="){
            this->out_file.open(std::string(s.begin()+std::string("file=").size(),s.end()),std::ios::out | std::ios::trunc);
            this->file_name = std::string(std::string(s.begin()+std::string("file=").size(),s.end()));
            continue;
        }

        if(s.size() > std::string("lowest_level=").size() && std::string(s.begin(),s.begin()+std::string("lowest_level=").size()) == "lowest_level="){
            this->Lowest_level = std::string(s.begin()+std::string("lowest_level=").size(),s.end());
            continue;
        }
    }
    return;
}


std::string baseee::log::logger::get_format(std::string level){
    std::string out = this->log_format;
    bool Tag = true;
    time_t now;
    

    while(Tag){
        const int tag_name = out.find("{name}");
        if(tag_name != out.npos){
            out = out.substr(0,tag_name) + this->name + out.substr(tag_name+(std::string("{name}").size()));
            continue;
        }

        const int tag_year = out.find("{year}");
        if(tag_year != out.npos){
            std::time(&now);
            auto tm = std::localtime(&now);
            out = out.substr(0,tag_year) + std::to_string(tm->tm_year+1900) + out.substr(tag_year+(std::string("{year}").size()));
            continue;
        }

        const int tag_month = out.find("{month}");
        if(tag_month != out.npos){
            std::time(&now);
            auto tm = std::localtime(&now);
            out = out.substr(0,tag_month) + std::to_string(tm->tm_mon+1) + out.substr(tag_month+std::string("{month}").size());
            continue;
        }


        const int tag_day = out.find("{day}");
        if(tag_day != out.npos){
            std::time(&now);
            auto tm = std::localtime(&now);
            out = out.substr(0,tag_day) + std::to_string(tm->tm_mday) + out.substr(tag_day+std::string("{day}").size());
            continue;
        }


        const int tag_hour = out.find("{hour}");
        if(tag_hour != out.npos){
            std::time(&now);
            auto tm = std::localtime(&now);
            out = out.substr(0,tag_hour) + std::to_string(tm->tm_hour) + out.substr(tag_hour+std::string("{hour}").size());
            continue;
        }

        const int tag_min = out.find("{min}");
        if(tag_min != out.npos){
            std::time(&now);
            auto tm = std::localtime(&now);
            out = out.substr(0,tag_min) + std::to_string(tm->tm_min) + out.substr(tag_min+std::string("{min}").size());
            continue;
        }


        const int tag_sec = out.find("{sec}");
        if(tag_sec != out.npos){
            std::time(&now);
            auto tm = std::localtime(&now);
            out = out.substr(0,tag_sec) + std::to_string(tm->tm_sec) + out.substr(tag_sec+std::string("{sec}").size());
            continue;
        }



        Tag = false;
    }




    return out;
}






#endif 