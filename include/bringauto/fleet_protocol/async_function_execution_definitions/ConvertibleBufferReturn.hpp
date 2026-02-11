#pragma once

#include <fleet_protocol/common_headers/device_management.h>

#include <cstdint>
#include <cstring>
#include <span>



namespace bringauto::fleet_protocol::async_function_execution_definitions {

/**
 * @brief ConvertibleBufferReturn is a helper class to convert a fleet_protocol 'buffer' struct
 * and a return code to/from a byte span for serialization/deserialization.
 * The first 4 bytes represent the return code (int), followed by the buffer data.
 */
struct ConvertibleBufferReturn final {
	int returnCode {};
	struct ::buffer buffer {};
	ConvertibleBufferReturn() = default;
	ConvertibleBufferReturn(int code, struct ::buffer buff) : returnCode(code), buffer(buff) {}

	std::span<const uint8_t> serialize() const {
		size_t total_size = sizeof(int) + buffer.size_in_bytes;
		uint8_t* data = new uint8_t[total_size];
		std::memcpy(data, &returnCode, sizeof(int));
		std::memcpy(data + sizeof(int), buffer.data, buffer.size_in_bytes);
		return {data, total_size};
	}
	void deserialize(std::span<const uint8_t> bytes) {
		auto size = bytes.size();
		if (size < sizeof(int)) return;
		std::memcpy(&returnCode, bytes.data(), sizeof(int));
		size -= sizeof(int);
		buffer.data = new uint8_t[size];
		buffer.size_in_bytes = size;
		std::memcpy(buffer.data, bytes.data() + sizeof(int), size);
	}
};

}
