/*
 * File:   ToolsStringFix.cpp
 * Author: kjell
 *
 * Created on August 2, 2013, 3:18 PM
 */

#include "StringFixTests.hpp"
#include "StringFix.h"
#include <string>
#include <vector>

TEST_F(StringFixTest, ReplaceFailed_WithEmptyFrom) {
   std::string content{"abcdefghijklmnopqrstuvxyz"};
   std::string copy = content;
   EXPECT_EQ(0, stringfix::replace(content, "", "Hello"));
   EXPECT_EQ(copy, content);
}

TEST_F(StringFixTest, ReplaceFailedWithNoMatchingContent) {
   std::string content{""};
   EXPECT_EQ(0, stringfix::replace(content, " ", "Hello"));
   EXPECT_EQ(content, "");
}

TEST_F(StringFixTest, ReplaceIntoEmty) {
   std::string content{"aaa"};
   EXPECT_EQ(1, stringfix::replace(content, "aaa", ""));
   EXPECT_EQ(content, "");
}

TEST_F(StringFixTest, ReplaceRepeatedly) {
   std::string content{"2:525MB:299GB:299GB:::lvm;"};
   ASSERT_EQ(6, stringfix::replace(content, ":", ": "));
   EXPECT_EQ(content, "2: 525MB: 299GB: 299GB: : : lvm;");
}

TEST_F(StringFixTest, ReplaceRepeatedlyAndRecursively) {
   std::string content{"2:525MB:299GB:299GB:::lvm;"};
   ASSERT_EQ(6, stringfix::replace(content, ":", "::"));
   EXPECT_EQ(content, "2::525MB::299GB::299GB::::::lvm;");
}

TEST_F(StringFixTest, NoTrim) {
   const std::string noSpaceAtEnd{"abcde efgh"};
   auto notTrimmed = stringfix::trim(noSpaceAtEnd);
   ASSERT_EQ(notTrimmed, noSpaceAtEnd);
}

TEST_F(StringFixTest, TrimEnds) {
   const std::string spaceAtEnd{"\n\t abcde efgh\n\t "};
   const std::string noSpaceAtEnd{"abcde efgh"};
   auto trimmed = stringfix::trim(noSpaceAtEnd, {"\n\t "});

   ASSERT_NE(trimmed, spaceAtEnd);
   ASSERT_EQ(trimmed, noSpaceAtEnd);
}


TEST_F(StringFixTest, NoSplit) {
   const std::string numbers{"1,2,3,4,5,6"};
   auto tokens = stringfix::split("", numbers);
   ASSERT_EQ(tokens.size(), 1);
   ASSERT_EQ(tokens[0], numbers);
}

TEST_F(StringFixTest, Split) {
   const std::string numbers{"1,2,3,4,5,6"};
   auto tokens = stringfix::split(",", numbers);
   ASSERT_EQ(tokens.size(), 6);
   size_t count = 1;
   for (auto t : tokens) {
      ASSERT_EQ(t, std::to_string(count++));
   }
}

TEST_F(StringFixTest, SplitAdvanced) {
   const std::string numbers{"1 2,3 4,5 6"};
   auto tokens = stringfix::split(", ", numbers);
   ASSERT_EQ(tokens.size(), 6);
   size_t count = 1;
   for (auto t : tokens) {
      ASSERT_EQ(t, std::to_string(count++));
   }
}

TEST_F(StringFixTest, ToLower) {
   const std::string lower("test");
   EXPECT_TRUE(lower.compare(stringfix::to_lower("test")) == 0);
   EXPECT_TRUE(lower.compare(stringfix::to_lower("TEST")) == 0);
   EXPECT_TRUE(lower.compare(stringfix::to_lower("Test")) == 0);
   EXPECT_TRUE(lower.compare(stringfix::to_lower("teST")) == 0);
   EXPECT_TRUE(lower.compare(stringfix::to_lower("tEst")) == 0);
   EXPECT_TRUE(!lower.compare(stringfix::to_lower("tests")) == 0);
   EXPECT_TRUE(!lower.compare(stringfix::to_lower("Tests")) == 0);
   EXPECT_TRUE(!lower.compare(stringfix::to_lower("aTest")) == 0);
}

TEST_F(StringFixTest, ToUpper) {
   const std::string upper("TEST");
   EXPECT_TRUE(upper.compare(stringfix::to_upper("test")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_upper("TEST")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_upper("Test")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_upper("teST")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_upper("tEst")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_upper("tests")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_upper("Tests")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_upper("aTest")) == 0);
}

TEST_F(StringFixTest, ToLowerNums) {
   const std::string upper("123test456");
   EXPECT_TRUE(upper.compare(stringfix::to_lower("123test456")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_lower("123TEST456")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_lower("123teSt456")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_lower("123te3St456")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_lower("test")) == 0);
}

TEST_F(StringFixTest, ToLowerSpecialChars) {
   const std::string upper("<>123te!st45&6*");
   EXPECT_TRUE(upper.compare(stringfix::to_lower("<>123te!st45&6*")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_lower("<>123TE!ST45&6*")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_lower("<>123te!St45&6*")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_lower("123teSt456")) == 0);
}

TEST_F(StringFixTest, ToUpperNums) {
   const std::string upper("123TEST456");
   EXPECT_TRUE(upper.compare(stringfix::to_upper("123TEST456")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_upper("123test456")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_upper("123teSt456")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_upper("123te3St456")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_upper("test")) == 0);
}

TEST_F(StringFixTest, ToUpperSpecialChars) {
   const std::string upper("<>123TE!ST45&6*");
   EXPECT_TRUE(upper.compare(stringfix::to_upper("<>123te!st45&6*")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_upper("<>123TE!ST45&6*")) == 0);
   EXPECT_TRUE(upper.compare(stringfix::to_upper("<>123te!St45&6*")) == 0);
   EXPECT_TRUE(!upper.compare(stringfix::to_upper("123teSt456")) == 0);
}

TEST_F(StringFixTest, EmptyString) {
   const std::string empty("");
   EXPECT_TRUE(empty.compare(stringfix::to_upper("")) == 0);
   EXPECT_TRUE(empty.compare(stringfix::to_upper("t")) != 0);
   EXPECT_TRUE(empty.compare(stringfix::to_lower("")) == 0);
   EXPECT_TRUE(empty.compare(stringfix::to_lower("t")) != 0);
}

TEST_F(StringFixTest, NumbersOnlyString) {
   const std::string num("456");
   EXPECT_TRUE(num.compare(stringfix::to_upper("456")) == 0);
   EXPECT_TRUE(num.compare(stringfix::to_upper("456t")) != 0);
   EXPECT_TRUE(num.compare(stringfix::to_upper("")) != 0);
   EXPECT_TRUE(num.compare(stringfix::to_lower("456")) == 0);
   EXPECT_TRUE(num.compare(stringfix::to_lower("456t")) != 0);
   EXPECT_TRUE(num.compare(stringfix::to_lower("")) != 0);
}

TEST_F(StringFixTest, SplitAdvancedNoSpaceInBetween) {
   const std::string numbers{"1,,2,,3,,4,,5,,6"};
   auto tokens = stringfix::split(",", numbers);
   ASSERT_EQ(tokens.size(), 6);
   size_t count = 1;
   for (auto t : tokens) {
      ASSERT_EQ(t, std::to_string(count++));
   }
}

TEST_F(StringFixTest, SplitAndExplodeShouldNotBeSimilar) {
   const std::string numbers{"1,,2,,3,,4,,5,,6"};
   const std::vector<std::string> expected{{"1"}, {""}, {"2"}, {""}, {"3"}, {""}, {"4"}, {""}, {"5"}, {""}, {"6"}};
   auto tokens = stringfix::explode(",", numbers);
   ASSERT_EQ(tokens.size(), expected.size());
   size_t index = 0;
   for (auto t : tokens) {
      ASSERT_EQ(t, expected[index++]);
   }
}


TEST_F(StringFixTest, EmptyStringAsKey__ExpectingZeroExplode) {
   const std::string greeting{"Hello World! Hola El Mundo!"};
   auto tokens = stringfix::explode("", greeting);
   ASSERT_EQ(tokens.size(), 1);
   EXPECT_EQ(tokens[0], greeting); // same returned. no match
}

TEST_F(StringFixTest, TooBigStringAsKey__ExpectingZeroExplode) {
   const std::string greeting{"Hello World! Hola El Mundo!"};
   const std::string key = greeting + greeting;
   auto tokens = stringfix::explode(key, greeting);
   ASSERT_EQ(tokens.size(), 1);
   EXPECT_EQ(tokens[0], greeting); // same returned. no match
}

TEST_F(StringFixTest, NoMatch__ExpectingZeroExplode) {
   const std::string greeting{"Hello World! Hola El Mundo!"};
   auto tokens = stringfix::explode("Goodbye World!", greeting);
   ASSERT_EQ(tokens.size(), 1); // same returned. no match
   EXPECT_EQ(tokens[0], greeting); // same returned. no match
}

TEST_F(StringFixTest, ExplodeWithManyMatches__ExpecingAlsoEdgeSubString) {
   const std::string machine{":a:::b:"};
   const std::vector<std::string> expected{{""}, {"a"}, {""}, {""}, {"b"}};
   auto tokens = stringfix::explode(":", machine);

   ASSERT_EQ(tokens.size(), expected.size());
   size_t index = 0;
   for (auto t : tokens) {
      ASSERT_EQ(t, expected[index++]);
   }
}


TEST_F(StringFixTest, ExplodeWithCompleteMatch__Expecting__FullExplodeWithEmptyReturn) {
   const std::string greeting{"Hello World! Hola El Mundo!"};
   auto tokens = stringfix::explode(greeting, greeting);
   ASSERT_EQ(tokens.size(), 1);
   EXPECT_EQ(tokens[0], "");
}

TEST_F(StringFixTest, ExplodeWithOneCharacterMatch__ExpectingTwoReturns) {
   const std::string greeting{"Hello World! Hola El Mundo!"};
   auto tokens = stringfix::explode("!", greeting);
   ASSERT_EQ(tokens.size(), 2);
   EXPECT_EQ(tokens[0], "Hello World");
   EXPECT_EQ(tokens[1], " Hola El Mundo");
}

TEST_F(StringFixTest, ExplodeWithOneSpecialCharacterMatch__ExpectingTwoReturns) {
   const std::string greeting{"Hello World/Hola El Mundo!"};
   auto tokens = stringfix::explode("/", greeting);
   ASSERT_EQ(tokens.size(), 2);
   EXPECT_EQ(tokens[0], "Hello World");
   EXPECT_EQ(tokens[1], "Hola El Mundo!");
   EXPECT_EQ(tokens.back(), "Hola El Mundo!");
}


TEST_F(StringFixTest, extract_empty) {

   EXPECT_EQ(stringfix::extract("start_key", "stop_key", "").size(), 0);
   EXPECT_EQ(stringfix::extract("", "", "     ").size(), 0);
   EXPECT_EQ(stringfix::extract("", "stop_key", "  ").size(), 0);
}

TEST_F(StringFixTest, extract_spaces) {

   EXPECT_EQ(stringfix::extract(" ", " ", "  ").size(), 1);
   EXPECT_EQ(stringfix::extract(" ", " ", "    ").size(), 2);
   EXPECT_EQ(stringfix::extract(" ", " ", "      ").size(), 3);
}


namespace {
   const char* kProcCpu1 =
      "      "
      "processor       : 0"
      "vendor_id       : GenuineIntel"
      "cpu family      : 6"
      "model           : 63"
      "model name      : Intel(R) Xeon(R) CPU E5-2670 v3 @ 2.30GHz"
      "stepping        : 2"
      "microcode       : 39"
      "cpu MHz         : 2300.103"
      "cache size      : 30720 KB"
      "physical id     : 0"
      "siblings        : 24"
      "core id         : 0"
      "cpu cores       : 12"
      "apicid          : 0"
      "initial apicid  : 0"
      "fpu             : yes"
      "fpu_exception   : yes"
      "cpuid level     : 15"
      "wp              : yes"
      "clflush size    : 64"
      "cache_alignment : 64"
      "address sizes   : 46 bits physical, 48 bits virtual"
      "power management:"
      "";
   const char* kProcCpu2 =
      " "
      "processor       : 1"
      "vendor_id       : GenuineIntel"
      "cpu family      : 6"
      "model           : 63"
      "model name      : Intel(R) Xeon(R) CPU E5-2670 v3 @ 2.30GHz"
      "stepping        : 2"
      "microcode       : 39"
      "cpu MHz         : 2300.103"
      "cache size      : 30720 KB"
      "physical id     : 1"
      "siblings        : 24"
      "core id         : 0"
      "cpu cores       : 12"
      "apicid          : 32"
      "initial apicid  : 32"
      "fpu             : yes"
      "clflush size    : 64"
      "cache_alignment : 64"
      "address sizes   : 46 bits physical, 48 bits virtual"
      "power management:"
      "";

   const char* kProcCpu3 = "processor";
   const std::string kProcCpu = std::string{kProcCpu1} + "\n bla bla bla " + kProcCpu2 + kProcCpu3;

} // anonymous

TEST_F(StringFixTest, extract_no_match) {
   EXPECT_EQ(stringfix::extract("processor", "nothing", kProcCpu).size(), 0);
}

TEST_F(StringFixTest, extract_one_match) {
   std::string rawCpu1 = kProcCpu1;
   auto result = stringfix::extract("processor", "power management", rawCpu1);
   auto expected_result  = stringfix::trim(rawCpu1.substr(0, rawCpu1.find_last_of(":")));

   ASSERT_EQ(result.size(), 1);
   EXPECT_EQ(result[0], expected_result);
}


TEST_F(StringFixTest, extract_multiple_matches) {
   auto result = stringfix::extract("processor", "power management", kProcCpu);
   ASSERT_EQ(result.size(), 2);
   std::string rawCpu1 = kProcCpu1;
   std::string rawCpu2 = kProcCpu2;
   auto expected_result_1 = stringfix::trim(rawCpu1.substr(0, rawCpu1.find_last_of(":")));
   auto expected_result_2 = stringfix::trim(rawCpu2.substr(0, rawCpu2.find_last_of(":")));


   ASSERT_EQ(result.size(), 2);
   EXPECT_EQ(expected_result_1, result[0]);
   EXPECT_EQ(expected_result_2, result[1]);
}

TEST_F(StringFixTest, convert_0_to_false) {
   bool f = false;
   EXPECT_EQ("false", stringfix::to_string(f));
}

TEST_F(StringFixTest, convert_1_to_true) {
   bool t = true;
   EXPECT_EQ("true", stringfix::to_string(t));
}

// This test is commented out purposefully.
//    The to_string function has two separate definitions
//    (see StringFix.h). If this test was uncommented,
//    there would be a compiler error. This is the 
//    expected behavior.
//
// TEST_F(StringFixTest, reject_nonboolean_types) {
//    int trueInt = 1;
//    EXPECT_EQ("false", stringfix::to_string(trueInt));
// }

TEST_F(StringFixTest, convert_true_string_to_bool) {
   std::string trueString = "true";
   EXPECT_TRUE(stringfix::to_bool(trueString));
}

TEST_F(StringFixTest, convert_false_string_to_bool) {
   std::string falseString = "false";
   EXPECT_FALSE(stringfix::to_bool(falseString));
}

TEST_F(StringFixTest, convert_wrong_string_to_bool) {
   std::string falseString = "this string contains the word false";
   EXPECT_FALSE(stringfix::to_bool(falseString));
}

TEST_F(StringFixTest, convert_wrong_string_to_bool_2) {
   std::string falseString = "this string contains the word true";
   EXPECT_FALSE(stringfix::to_bool(falseString));
}

TEST_F(StringFixTest, convert_uppercase_true_string_to_bool) {
   std::string uppercaseTrueString = "TRUE";
   EXPECT_TRUE(stringfix::to_bool(uppercaseTrueString));
} 

TEST_F(StringFixTest, convert_values_string_to_bool) {
   std::string zeroString = "0";
   std::string oneString = "1";
   std::string twoString = "2";

   EXPECT_TRUE(stringfix::to_bool(oneString));
   EXPECT_FALSE(stringfix::to_bool(zeroString));
   EXPECT_FALSE(stringfix::to_bool(twoString));
} 

TEST_F(StringFixTest, convert_mixedcase_true_string_to_bool) {
   std::string mixedCaseTrueString = "TruE";
   EXPECT_TRUE(stringfix::to_bool(mixedCaseTrueString));
}

TEST_F(StringFixTest, FindNonExistantElementInVector) {
   std::vector<std::string> v = {"1", "2", "3"};
   std::string testElement = "5";
   EXPECT_FALSE(stringfix::ContainsElement(v, testElement));
}

TEST_F(StringFixTest, FindTrueElementInVector) {
   std::vector<std::string> v = {"1", "2", "3"};
   std::string testElement = "3";
   EXPECT_TRUE(stringfix::ContainsElement(v, testElement));
}

TEST_F(StringFixTest, EmptyVectorReturnsFalse) {
   std::vector<std::string> v = {};
   std::string testElement = "3";
   EXPECT_FALSE(stringfix::ContainsElement(v, testElement));
}

TEST_F(StringFixTest, EmptyStringReturnsFalse) {
   std::vector<std::string> v = {"1", "2", "3"};
   std::string testElement = "";
   EXPECT_FALSE(stringfix::ContainsElement(v, testElement));
}

TEST_F(StringFixTest, EmptyStringAndVectorIsFalse) {
   std::vector<std::string> v = {};
   std::string testElement = "";
   EXPECT_FALSE(stringfix::ContainsElement(v, testElement));
}

TEST_F(StringFixTest, AlmostMatchingStringsInVector) {
   std::vector<std::string> v = {"5 ", " 5", "55"};
   std::string testElement = "5";
   EXPECT_FALSE(stringfix::ContainsElement(v, testElement));
}

TEST_F(StringFixTest, RemoveFileExtension_shortestExtension) {
   const std::string filename = "file";
   const std::string extension = ".a";
   EXPECT_EQ(filename, stringfix::remove_extension(filename+extension));
}

TEST_F(StringFixTest, RemoveFileExtension_NoExtension) {
   const std::string filename = "file";
   const std::string extension = "";
   EXPECT_EQ(filename, stringfix::remove_extension(filename+extension));
}

TEST_F(StringFixTest, RemoveFileExtension_LongExtension) {
   const std::string filename = "file";
   const std::string extension = ".thisIsAVeryLongExtension";
   EXPECT_EQ(filename, stringfix::remove_extension(filename+extension));
}

TEST_F(StringFixTest, RemoveFileExtension_MultipleExtensions) {
   const std::string filename = "file";
   const std::string extension1 = ".tar";
   const std::string extension2 = ".gz";
   EXPECT_EQ(filename+extension1, stringfix::remove_extension(filename+extension1+extension2));
}

TEST_F(StringFixTest, GetExtension) {
   const std::string filename = "file";
   const std::string extension = "tar";
   EXPECT_EQ(extension, stringfix::get_extension(filename+"."+extension));
}

TEST_F(StringFixTest, GetExtension_None) {
   const std::string filename = "file";
   const std::string emptyExtension = "";
   EXPECT_EQ(emptyExtension, stringfix::get_extension(filename+emptyExtension));
}

TEST_F(StringFixTest, GetExtension_MultipleExtensions) {
   const std::string filename = "file";
   const std::string extension1 = "tar";
   const std::string extension2 = "gz";
   EXPECT_EQ(extension2, stringfix::get_extension(filename+"."+extension1+"."+extension2));
}

TEST_F(StringFixTest, DirectoryDots) {
   const std::string filename = "..";
   const std::string emptyExtension = "";
   EXPECT_EQ(emptyExtension, stringfix::get_extension(filename));
}