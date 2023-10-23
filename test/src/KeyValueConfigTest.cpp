#include <gtest/gtest.h>

#include <bringauto/fleet_protocol/cxx/KeyValueConfig.hpp>


using namespace bringauto::fleet_protocol::cxx;


TEST(KeyValueConfig_tests, Initialize) {
    ::config configData;
    configData.size = 3;
    key_value params[3];
    ::allocate(&params[0].key, 4);
    params[0].key.data = const_cast<char *>("Key1");
    ::allocate(&params[0].value, 6);
    params[0].value.data = const_cast<char *>("Value1");
    ::allocate(&params[1].key, 4);
    params[1].key.data = const_cast<char *>("Key2");
    ::allocate(&params[1].value, 6);
    params[1].value.data = const_cast<char *>("Value2");
    ::allocate(&params[2].key, 4);
    params[2].key.data = const_cast<char *>("Key3");
    ::allocate(&params[2].value, 6);
    params[2].value.data = const_cast<char *>("Value3");
    configData.parameters = params;
    KeyValueConfig kvConfig(configData);

    EXPECT_STREQ(kvConfig.cbegin()->first.c_str(), "Key1");
    EXPECT_STREQ(kvConfig.cbegin()->second.c_str(), "Value1");
    EXPECT_STREQ(std::prev(kvConfig.cend())->first.c_str(), "Key3");
    EXPECT_STREQ(std::prev(kvConfig.cend())->second.c_str(), "Value3");
}


TEST (KeyValueConfig_tests, Zero_size) {
    ::config configData;
    configData.size = 0;
    key_value params[1];
    ::allocate(&params[0].key, 3);
    params[0].key.data = const_cast<char *>("Key");
    ::allocate(&params[0].value, 5);
    params[0].value.data = const_cast<char *>("Value");
    configData.parameters = params;
    KeyValueConfig kvConfig(configData);

    EXPECT_EQ(kvConfig.cbegin(), kvConfig.cend());
}