#include <gtest/gtest.h>

#include <bringauto/fleet_protocol/cxx/StringAsBuffer.hpp>
#include <memory_management.h>


using namespace bringauto::fleet_protocol::cxx;


TEST(StringAsBuffer_tests, Create_buffer) {
    struct buffer buff;
    StringAsBuffer::createBufferAndCopyData(&buff, const_cast<char*>("abcd"));

    EXPECT_EQ(buff.size_in_bytes, 5);
    EXPECT_STREQ(static_cast<char*>(buff.data), "abcd");

    ::deallocate(&buff);
}