#pragma once

#include <fleet_protocol/common_headers/device_management.h>

#include <cstdint>
#include <span>



namespace bringauto::fleet_protocol::cxx {

/**
 * @brief ConvertibleBuffer is a helper class to convert a fleet_protocol 'buffer' struct
 * to/from a byte span for serialization/deserialization.
 */
struct ConvertibleBuffer final {
	struct ::buffer buffer {};
	ConvertibleBuffer() = default;
	ConvertibleBuffer(struct ::buffer buff) : buffer(buff) {}
	
	std::span<const uint8_t> serialize() const {
		return std::span {reinterpret_cast<const uint8_t *>(buffer.data), buffer.size_in_bytes};
	}
	void deserialize(std::span<const uint8_t> bytes) {
		buffer.data = const_cast<uint8_t *>(bytes.data());
		buffer.size_in_bytes = bytes.size();
	}
};

}
