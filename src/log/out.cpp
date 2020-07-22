#ifndef _BASEEE_OUT_CPP_
#define _BASEEE_OUT_CPP_
/*baseee::log
 *print_XXXXX and out_log
 *MIT License
 *coder:chhd 
 *update ime:2020-7-21
 *
 *history:carry out
 *
 * 
 */
#include "log.hpp"
#include <string>
#include <fstream>
#include <iostream>

void baseee::log::logger::out_log(std::string level,std::string log){
    mtx.lock();

    //Print to file
    if(this->out_file.is_open())
        out_file << get_format(level) + log + "\n";

    //Print to clog(error) stream
    if(this->Lowest_level == "info")
        std::clog << get_format(level) + log  << std::endl;
    

    else if(this->Lowest_level == "important"){
        if(level == "important" || level == "error" || level == "fatal")
            std::clog << get_format(level) + log  << std::endl;
    }
        
    

    else if(this->Lowest_level == "error"){
         if(level == "error" || level == "fatal")
            std::clog << get_format(level) + log  << std::endl;
    }
        
    

    else if(this->Lowest_level == "fatal"){
        if(level == "fatal")
            std::clog << get_format(level) + log  << std::endl;
    }
    

    mtx.unlock();

}


void baseee::log::logger::print_info(std::string log){
    out_log("info",log);
}

void baseee::log::logger::print_important(std::string log){
    out_log("important",log);
}

void baseee::log::logger::print_error(std::string log){
    out_log("error",log);
}

void baseee::log::logger::print_fatal(std::string log){
    out_log("fatal",log);
}



#endif