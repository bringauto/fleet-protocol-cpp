#include <gtest/gtest.h>

#include <bringauto/fleet_protocol/cxx/KeyValueConfig.hpp>


using namespace bringauto::fleet_protocol::cxx;


TEST(KeyValueConfig_tests, Initialize) {
    ::config configData;
    configData.size = 3;
    key_value params[3];
    ::allocate(&params[0].key, 5);
    std::memcpy(params[0].key.data, "Key1", 5);
    ::allocate(&params[0].value, 7);
    std::memcpy(params[0].value.data, "Value1", 7);
    ::allocate(&params[1].key, 5);
    std::memcpy(params[1].key.data, "Key2", 5);
    ::allocate(&params[1].value, 7);
    std::memcpy(params[1].value.data, "Value2", 7);
    ::allocate(&params[2].key, 5);
    std::memcpy(params[2].key.data, "Key3", 5);
    ::allocate(&params[2].value, 7);
    std::memcpy(params[2].value.data, "Value3", 7);
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


TEST (KeyValueConfig_tests, Zero_size) {
    ::config configData;
    configData.size = 0;
    key_value params[1];
    ::allocate(&params[0].key, 4);
    std::memcpy(params[0].key.data, "Key", 4);
    ::allocate(&params[0].value, 6);
    std::memcpy(params[0].value.data, "Value", 6);
    configData.parameters = params;
    KeyValueConfig kvConfig(configData);

    EXPECT_EQ(kvConfig.cbegin(), kvConfig.cend());

    ::deallocate(&params[0].key);
    ::deallocate(&params[0].value);
}