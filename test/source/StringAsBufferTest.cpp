#include <gtest/gtest.h>

#include <bringauto/fleet_protocol/cxx/StringAsBuffer.hpp>
#include <fleet_protocol/common_headers/memory_management.h>


using namespace bringauto::fleet_protocol::cxx;


TEST(StringAsBuffer_tests, Create_buffer) {
	struct buffer buff;
	StringAsBuffer::createBufferAndCopyData(&buff, std::string("abcd"));

	EXPECT_EQ(buff.size_in_bytes, 4);
	std::string_view data(static_cast<char*>(buff.data), buff.size_in_bytes);
	EXPECT_STREQ(std::string(data).c_str(), "abcd");

	::deallocate(&buff);
}
