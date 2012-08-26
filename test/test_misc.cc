#include "misc.hh"
#include "gtest/gtest.h"

#include <iostream>
#include <string>

using namespace std;

TEST(Misc, ends_with) {
    ASSERT_TRUE(ends_with("test.bmp", ".bmp", false));
    ASSERT_TRUE(ends_with("test.bmp", ".bmp", true));
}

TEST(Misc, ends_with_ignore_case) {
    ASSERT_FALSE(ends_with("TeSt.BmP", ".bmp", false));
    ASSERT_TRUE(ends_with("TeSt.BmP", ".bmp", true));
}

TEST(Misc, ends_with_shorter) {
    ASSERT_FALSE(ends_with("abcd", "123abcd", false));
    ASSERT_FALSE(ends_with("abcd", "123abcd", true));
}

TEST(Misc, ends_with_empty) {
    ASSERT_FALSE(ends_with("", "123abcd", false));
    ASSERT_FALSE(ends_with("", "123abcd", true));

    ASSERT_TRUE(ends_with("123abcd", "", false));
    ASSERT_TRUE(ends_with("123abcd", "", true));

    ASSERT_TRUE(ends_with("", "", false));
    ASSERT_TRUE(ends_with("", "", true));
}

TEST(Misc, ends_with_problem) {
    ASSERT_FALSE(ends_with("/home/vila/Desktop/spitfire", ".bmp", false));
    ASSERT_FALSE(ends_with("/home/vila/Desktop/spitfire", ".bmp", true));
}
