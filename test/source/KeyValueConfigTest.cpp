#include <gtest/gtest.h>

#include <bringauto/fleet_protocol/cxx/KeyValueConfig.hpp>
#include <fleet_protocol/common_headers/memory_management.h>


using namespace bringauto::fleet_protocol::cxx;


TEST(KeyValueConfig_tests, Initialize) {
	::config configData;
	configData.size = 3;
	key_value params[3];
	::allocate(&params[0].key, 4);
	std::memcpy(params[0].key.data, "Key1", 4);
	::allocate(&params[0].value, 6);
	std::memcpy(params[0].value.data, "Value1", 6);
	::allocate(&params[1].key, 4);
	std::memcpy(params[1].key.data, "Key2", 4);
	::allocate(&params[1].value, 6);
	std::memcpy(params[1].value.data, "Value2", 6);
	::allocate(&params[2].key, 4);
	std::memcpy(params[2].key.data, "Key3", 4);
	::allocate(&params[2].value, 6);
	std::memcpy(params[2].value.data, "Value3", 6);
	configData.parameters = params;
	KeyValueConfig kvConfig(configData);

	EXPECT_STREQ(kvConfig.cbegin()->first.c_str(), "Key1");
	EXPECT_STREQ(kvConfig.cbegin()->second.c_str(), "Value1");
	EXPECT_STREQ(std::prev(kvConfig.cend())->first.c_str(), "Key3");
	EXPECT_STREQ(std::prev(kvConfig.cend())->second.c_str(), "Value3");

	::deallocate(&params[0].key);
	::deallocate(&params[0].value);
	::deallocate(&params[1].key);
	::deallocate(&params[1].value);
	::deallocate(&params[2].key);
	::deallocate(&params[2].value);
}


TEST(KeyValueConfig_tests, Zero_size) {
	::config configData;
	configData.size = 0;
	key_value params[1];
	::allocate(&params[0].key, 3);
	std::memcpy(params[0].key.data, "Key", 3);
	::allocate(&params[0].value, 5);
	std::memcpy(params[0].value.data, "Value", 5);
	configData.parameters = params;
	KeyValueConfig kvConfig(configData);

	EXPECT_EQ(kvConfig.cbegin(), kvConfig.cend());

	::deallocate(&params[0].key);
	::deallocate(&params[0].value);
}
