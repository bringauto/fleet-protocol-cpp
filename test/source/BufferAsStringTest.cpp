#include <gtest/gtest.h>

#include <fleet_protocol/common_headers/memory_management.h>
#include <bringauto/fleet_protocol/cxx/BufferAsString.hpp>

using namespace bringauto::fleet_protocol::cxx;


TEST(BufferAsString_tests, Initialize) {
    struct buffer buff;
    ::allocate(&buff, 5);
    std::memcpy(buff.data, "abcd", 5);
    BufferAsString buffAsString(&buff);

    EXPECT_EQ(buff.size_in_bytes, 5);
    EXPECT_STREQ(std::string(buffAsString.getStringView()).c_str(), "abcd");
    EXPECT_TRUE(*buffAsString.cbegin() == 'a');
    EXPECT_STREQ(std::prev(buffAsString.cend()), "");
    
    ::deallocate(&buff);
}


TEST(BufferAsString_tests, Copy_string) {
    struct buffer buff;
    ::allocate(&buff, 3);
    std::memcpy(buff.data, "ab", 3);
    BufferAsString buffAsString(&buff);
    EXPECT_EQ(buff.size_in_bytes, 3);
    EXPECT_STREQ(std::string(buffAsString.getStringView()).c_str(), "ab");

    try {
		buffAsString.copyFromString(std::string_view(const_cast<char *>("cd")));
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    EXPECT_EQ(buff.size_in_bytes, 3);
    EXPECT_STREQ(std::string(buffAsString.getStringView()).c_str(), "cd");

    ::deallocate(&buff);
}


TEST(BufferAsString_tests, Copy_string_buffer_no_data) {
    struct buffer buff;
    buff.data = nullptr;
    buff.size_in_bytes = 5;
    BufferAsString buffAsString(&buff);

    bool failed = false;
    try {
		buffAsString.copyFromString(std::string("abcd"));
    } catch(std::exception& e) {
        EXPECT_STREQ(e.what(), "Invalid buffer data section");
        failed = true;
    }
    EXPECT_TRUE(failed);
}


TEST(BufferAsString_tests, Copy_string_too_much_data) {
    struct buffer buff;
    ::allocate(&buff, 5);
    std::memcpy(buff.data, "abcd", 5);
    BufferAsString buffAsString(&buff);

    bool failed = false;
    try {
		buffAsString.copyFromString(std::string("abcdefgh"));
    } catch(std::exception& e) {
        EXPECT_STREQ(e.what(), "Cannot copy larger data into smaller buffer");
        failed = true;
    }
    EXPECT_TRUE(failed);

    ::deallocate(&buff);
}