#pragma once

#include <bringauto/fleet_protocol/cxx/BufferAsString.hpp>


#include <fleet_protocol/common_headers/device_management.h>
#include <fleet_protocol/common_headers/general_error_codes.h>

#include <string_view>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>


namespace bringauto::fleet_protocol::cxx {

/**
 * @brief Class, which encapsulates device_identification c-like struct and replaces c strings in device_identification
 *        with c++ strings to avoid allocating on heap.
*/
struct DeviceID {

	/**
	 * @brief Constructs DeviceID from device_identification values and c strings for device_name and device_role.
	 *        Unsafe to use with non null terminated strings. Do not use when converting from device_identification
	 *        structure, use the other constructor.
	*/
	DeviceID(int module, unsigned int device_type, unsigned int priority, const std::string_view device_role,
			 const std::string_view device_name);

	/**
	 * @brief Construct the class from fleet-protocol device_identification
	 * @param device_id
	 */
	DeviceID(const device_identification& device_id);

	/**
	 * @brief Move constructor is the only one enabled to provide consistency
	*/
	DeviceID(DeviceID&& c) noexcept;

	/// Deleted copy constructor - idea is to avoid
	DeviceID(const DeviceID& c) = delete;

	/**
	 * It returns device_identification instance.
	 * device_identification instance is valid as long as the DeviceID instance
	 * which have returned the device_identification instance is valid at the time of evaluation.
	 * (of the dev_id instance)
	 * @return
	 */
	[[nodiscard]] const device_identification& getDeviceId() const { return id_; }

	/**
	 * It creates a device_identification instance which is valid
	 * even after the DeviceID instance which have created the device_identification
	 * instance is not valid anymore in time of evaluation (of the dev_id instance)
	 * @return device_identification
	 * @throw std::runtime_error if allocation of resources is not successful
	 */
	[[nodiscard]] device_identification createStandaloneDeviceId() const;

	/**
	 * It returns string containing device identification information
	 */
	[[nodiscard]] std::string serializeInfo() const {
		std::string ret {};
		ret += "Device Name: " + device_name_ + ", Device Role: " + device_role_ + ", Priority: " + std::to_string(id_.priority);
		return ret;
	}

private:
	device_identification id_ {};
	std::string device_role_ {};
	std::string device_name_ {};
};

}