StringFix
=========

C++ helper for string manipulation (trim, to_lower, split, explode etc...). 
For in-depth explanation please see function description at: https://github.com/KjellKod/StringFix/blob/master/src/StringFix.cpp


##### Replace parts of string
```cpp
size_t replace(std::string& input, const std::string& from, const std::string& to);
```


##### Trim the string based on whitespace or other character
```cpp
std::string trim(const std::string& str, const std::string& whitespace = " \t");
```

##### To lower/upper
```cpp
std::string to_lower(const std::string& str);
std::string to_upper(const std::string& str);
```


##### Bool to string
```cpp
std::string to_string(const bool& b);
```

##### Split and Explode the string based on delimiters and match
```cpp
std::vector<std::string> split(const std::string& split_on_any_delimiters, 
                               const std::string& stringToSplit)

std::vector<std::string> explode(const std::string& complete_match, 
                                 const std::string& stringToExplode);
```
   
##### Get elements that are matching
```cpp
std::vector<std::string> extract(const std::string& complete_match_start, 
                                 const std::string& complete_match_end, const std::string& content);
```

##### Verify if vector contains an element
```cpp
bool ContainsElement(const std::vector<std::string>& v, const std::string& s);
```
  
##### Extension handling
```cpp
std::string remove_extension(const std::string& s);
std::string get_extension(const std::string& s);
```
