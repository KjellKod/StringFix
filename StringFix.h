/* 
 * File:   StringFix.h
 * Author: kjell/ryan
 * https://github.com/KjellKod/StringFix
 *
 * Created on July 30, 2013, 10:46 AM
 */

#pragma once
#include <string>
#include <vector>

namespace stringfix {
   size_t replace(std::string& input, const std::string& from, const std::string& to);
   std::string trim(const std::string& str, const std::string& whitespace = " \t");
   std::string to_lower(const std::string& str);
   std::string to_upper(const std::string& str);
   std::vector<std::string> split(const std::string& split_on_any_delimiters, const std::string& stringToSplit);
   std::vector<std::string> explode(const std::string& complete_match, const std::string& stringToExplode);
};


