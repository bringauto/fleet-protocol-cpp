#include <gtest/gtest.h>

#include <bringauto/fleet_protocol/cxx/DeviceID.hpp>
#include <fleet_protocol/common_headers/memory_management.h>


using namespace bringauto::fleet_protocol::cxx;


TEST(DeviceID_tests, Constructor_from_values) {
	DeviceID device(1, 2, 3, "Slave", "Device");
	device_identification deviceID = device.getDeviceId();

	EXPECT_EQ(deviceID.module, 1);
	EXPECT_EQ(deviceID.device_type, 2);
	EXPECT_EQ(deviceID.priority, 3);
	std::string role(static_cast<char*>(deviceID.device_role.data));
	EXPECT_STREQ(role.c_str(), "Slave");
	std::string name(static_cast<char*>(deviceID.device_name.data));
	EXPECT_STREQ(name.c_str(), "Device");
	EXPECT_STREQ(device.serializeInfo().c_str(), "Device Name: Device, Device Role: Slave, Priority: 3");
}


TEST(DeviceID_tests, Constructor_from_device_id) {
	device_identification deviceID1;
	deviceID1.module = 1;
	deviceID1.device_type = 2;
	deviceID1.priority = 3;
	::allocate(&deviceID1.device_role, 5);
	::allocate(&deviceID1.device_name, 6);
	std::memcpy(deviceID1.device_role.data, "Slave", 5);
	std::memcpy(deviceID1.device_name.data, "Device", 6);

	DeviceID device(deviceID1);
	device_identification deviceID2 = device.getDeviceId();

	EXPECT_EQ(deviceID2.module, 1);
	EXPECT_EQ(deviceID2.device_type, 2);
	EXPECT_EQ(deviceID2.priority, 3);
	std::string role(static_cast<char*>(deviceID2.device_role.data));
	EXPECT_STREQ(role.c_str(), "Slave");
	std::string name(static_cast<char*>(deviceID2.device_name.data));
	EXPECT_STREQ(name.c_str(), "Device");
	EXPECT_STREQ(device.serializeInfo().c_str(), "Device Name: Device, Device Role: Slave, Priority: 3");

	::deallocate(&deviceID1.device_role);
	::deallocate(&deviceID1.device_name);
}


TEST(DeviceID_tests, Constructor_move) {
	DeviceID device1(1, 2, 3, "Slave", "Device");
	DeviceID device2 = std::move(device1);
	device_identification deviceID = device2.getDeviceId();

	EXPECT_EQ(deviceID.module, 1);
	EXPECT_EQ(deviceID.device_type, 2);
	EXPECT_EQ(deviceID.priority, 3);
	std::string role(static_cast<char*>(deviceID.device_role.data));
	EXPECT_STREQ(role.c_str(), "Slave");
	std::string name(static_cast<char*>(deviceID.device_name.data));
	EXPECT_STREQ(name.c_str(), "Device");
	EXPECT_STREQ(device2.serializeInfo().c_str(), "Device Name: Device, Device Role: Slave, Priority: 3");
}


TEST(DeviceID_tests, Standalone_device_id) {
	DeviceID device(1, 2, 3, "Slave", "Device");
	device_identification deviceID = device.createStandaloneDeviceId();

	EXPECT_EQ(deviceID.module, 1);
	EXPECT_EQ(deviceID.device_type, 2);
	EXPECT_EQ(deviceID.priority, 3);
	std::string_view role(static_cast<char*>(deviceID.device_role.data), deviceID.device_role.size_in_bytes);
	EXPECT_STREQ(std::string(role).c_str(), "Slave");
	std::string_view name(static_cast<char*>(deviceID.device_name.data), deviceID.device_name.size_in_bytes);
	EXPECT_STREQ(std::string(name).c_str(), "Device");

	::deallocate(&deviceID.device_role);
	::deallocate(&deviceID.device_name);
}
