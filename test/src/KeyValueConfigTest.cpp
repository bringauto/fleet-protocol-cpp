#include <gtest/gtest.h>

#include <bringauto/fleet_protocol/cxx/KeyValueConfig.hpp>


using namespace bringauto::fleet_protocol::cxx;


TEST(KeyValueConfig_tests, Initialize) {
    ::config configData;
    configData.size = 3;
    //key_value params[3];
    //params[1].
    //KeyValueConfig kvConfig(configData);
}

/**
 * @brief Parameter structure containing the parameters key and its value in buffers
 */
//struct key_value {
//	buffer key;
//	buffer value;
//};

/**
 * @brief Configuration structure, containing key-value parameters and the number of them
 */
//struct config {
//	key_value* parameters;
//	size_t size;
//};