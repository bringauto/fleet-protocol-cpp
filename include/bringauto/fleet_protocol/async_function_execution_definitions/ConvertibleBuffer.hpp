#pragma once

#include <fleet_protocol/common_headers/device_management.h>

#include <cstdint>
#include <span>
#include <vector>



namespace bringauto::fleet_protocol::async_function_execution_definitions {

/**
 * @brief ConvertibleBuffer is a helper class to convert a fleet_protocol 'buffer' struct
 * to/from a byte span for serialization/deserialization.
 */
struct ConvertibleBuffer final {
	struct ::buffer buffer {};
	ConvertibleBuffer() = default;
	explicit ConvertibleBuffer(struct ::buffer buff) : buffer(buff) {}

	ConvertibleBuffer(const ConvertibleBuffer& other) : buffer(other.buffer), data_(other.data_) {
		if(!data_.empty()) {
			buffer.data = data_.data();
			buffer.size_in_bytes = data_.size();
		}
	}
	ConvertibleBuffer& operator=(const ConvertibleBuffer& other) {
		if(this != &other) {
			buffer = other.buffer;
			data_ = other.data_;
			if(!data_.empty()) {
				buffer.data = data_.data();
				buffer.size_in_bytes = data_.size();
			}
		}
		return *this;
	}
	ConvertibleBuffer(ConvertibleBuffer&& other) noexcept : buffer(other.buffer), data_(std::move(other.data_)) {
		if(!data_.empty()) {
			buffer.data = data_.data();
			buffer.size_in_bytes = data_.size();
		}
		other.buffer.data = nullptr;
		other.buffer.size_in_bytes = 0;
	}
	ConvertibleBuffer& operator=(ConvertibleBuffer&& other) noexcept {
		if(this != &other) {
			buffer = other.buffer;
			data_ = std::move(other.data_);
			if(!data_.empty()) {
				buffer.data = data_.data();
				buffer.size_in_bytes = data_.size();
			}
			other.buffer.data = nullptr;
			other.buffer.size_in_bytes = 0;
		}
		return *this;
	}
	~ConvertibleBuffer() = default;

	std::span<const uint8_t> serialize() const {
		return std::span {reinterpret_cast<const uint8_t *>(buffer.data), buffer.size_in_bytes};
	}
	void deserialize(std::span<const uint8_t> bytes) {
		data_.assign(bytes.begin(), bytes.end());
		buffer.data = data_.data();
		buffer.size_in_bytes = data_.size();
	}

private:
	std::vector<uint8_t> data_ {};
};

}
