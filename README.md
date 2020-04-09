StringFix
=========

C++ helper for string manipulation (trim, to_lower, split, explode etc...)

##### Replace parts of string
`size_t replace(std::string& input, const std::string& from, const std::string& to);`


##### Trim the string based on whitespace or other character
`std::string trim(const std::string& str, const std::string& whitespace = " \t");`

##### To lower/upper
`std::string to_lower(const std::string& str);`
`std::string to_upper(const std::string& str);`

##### Bool to string
`std::string to_string(const bool& b);`

##### Split and Explode the string based on delimiters and match
`std::vector<std::string> split(const std::string& split_on_any_delimiters, const std::string& stringToSplit);`

`std::vector<std::string> explode(const std::string& complete_match, const std::string& stringToExplode);`
   
##### Get elements that are matching
`std::vector<std::string> extract(const std::string& complete_match_start, const std::string& complete_match_end, const std::string& content);`

##### Verify if vector contains an element
`bool ContainsElement(const std::vector<std::string>& v, const std::string& s);`
  
##### Extention handling
`std::string remove_extension(const std::string& s);`
`std::string get_extension(const std::string& s);`
