StringFix
=========

C++ helper for string manipulation (trim, to_lower, split, explode etc...). 
For in-depth explanation please see function description at: https://github.com/KjellKod/StringFix/blob/master/src/StringFix.cpp


##### Replace parts of string
_size_t replace(std::string& input, const std::string& from, const std::string& to);_


##### Trim the string based on whitespace or other character
_std::string trim(const std::string& str, const std::string& whitespace = " \t");_

##### To lower/upper
* _std::string to_lower(const std::string& str);_
* _std::string to_upper(const std::string& str);_

##### Bool to string
_std::string to_string(const bool& b);_

##### Split and Explode the string based on delimiters and match
* _std::vector<std::string> split(const std::string& split_on_any_delimiters, const std::string& stringToSplit);_
* _std::vector<std::string> explode(const std::string& complete_match, const std::string& stringToExplode);_
   
##### Get elements that are matching
_std::vector<std::string> extract(const std::string& complete_match_start, const std::string& complete_match_end, const std::string& content);_

##### Verify if vector contains an element
_bool ContainsElement(const std::vector<std::string>& v, const std::string& s);_
  
##### Extention handling
* _std::string remove_extension(const std::string& s);_
* _std::string get_extension(const std::string& s);_
