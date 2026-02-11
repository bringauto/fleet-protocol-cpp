#include <bringauto/fleet_protocol/async_function_execution_definitions/AsyncModuleFunctionDefinitions.hpp>

#include <gtest/gtest.h>

using namespace bringauto::fleet_protocol::async_function_execution_definitions;


TEST(AsyncModuleFunctionDefinitions_tests, FunctionDefinitionsExist) {
	EXPECT_EQ(getModuleNumberAsync.id.value, 0);
	EXPECT_EQ(isDeviceTypeSupportedAsync.id.value, 1);
	EXPECT_EQ(sendStatusConditionAsync.id.value, 2);
	EXPECT_EQ(generateCommandAsync.id.value, 3);
	EXPECT_EQ(aggregateStatusAsync.id.value, 4);
	EXPECT_EQ(aggregateErrorAsync.id.value, 5);
	EXPECT_EQ(generateFirstCommandAsync.id.value, 6);
	EXPECT_EQ(statusDataValidAsync.id.value, 7);
	EXPECT_EQ(commandDataValidAsync.id.value, 8);
}
