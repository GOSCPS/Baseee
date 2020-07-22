#ifndef _BASEEE_LOH_HPP_
#define _BASEEE_LOH_HPP_
/*baseee::log
 *log moudle
 *MIT License
 *coder:chhd 
 *update time:2020-7-21
 *
 *history:carry out
 *add protected
 * 
 */
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <fstream>

namespace baseee{
    namespace log{
        class logger{
            public:
            //name:program name
            //format:set log format
            //out_format:set log out
            logger(std::string name,std::string format,std::string out_format);

            //print log for four level
            void print_info(std::string log);
            void print_important(std::string log);
            void print_error(std::string log);
            void print_fatal(std::string log);

            //operator



            protected:
            std::string name;
            std::string log_format;
            std::string out_format;

            std::mutex mtx;

            //std::vector<std::string> log_list;

            std::fstream out_file;
            std::string Lowest_level="error";
            std::string file_name;


            //format to string
            std::string get_format(std::string level);
            //set out format
            void set_log();
            //print log to file or clog
            void out_log(std::string level,std::string log);
        };
    }
}

baseee::log::logger::logger(std::string name,std::string format,std::string out_format){
    this->name = name;
    this->log_format = format;
    this->out_format = out_format;
    set_log();
    return;
}

#include "log.cpp"
#include "out.cpp"


#endif