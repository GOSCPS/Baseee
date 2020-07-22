#ifndef _BASEEE_STRING_HPP_
#define _BASEEE_STRING_HPP_
/*baseee::string
 *string moudle
 *MIT License
 *coder:chhd 
 *update time:2020-7-22
 *
 *history:add trim and regex
 *
 * 
 */
#include <string>
#include <vector>
#include <regex>

namespace baseee{
    namespace string{
        
        std::string trim(const std::string &s){
            //erase head and end space
            unsigned int head = 0,end = 0;
            unsigned int ptr = 0;
            while(ptr != s.size() && std::isspace(s[ptr])){
                ++head;
                ++ptr;
            }
            ptr = s.size()-1;
            while(ptr >= 0 && ptr < s.size() && std::isspace(s[ptr])){
                ++end;
                --ptr;
            }
            std::string out(s);
            out.erase(out.end()-end,out.end());
            out.erase(out.begin(),out.begin()+head);
            /*while(end != 0){
                out.erase(out.end()-1);
                end--;
            }
            while(head != 0){
                head--;
                out.erase(out.begin());
            }*/
            return out;
        }

        std::vector<std::string> split(const std::string &regex_str,const std::string &s){
            std::regex regex(regex_str);
            std::vector<std::string> out(std::sregex_token_iterator(s.begin(),s.end(),regex,-1),std::sregex_token_iterator());
            return out;
        }

        std::vector<std::string> split(const std::regex &regex,const std::string &s){
            std::vector<std::string> out(std::sregex_token_iterator(s.begin(),s.end(),regex,-1),std::sregex_token_iterator());
            return out;
        }

    }
}

#endif