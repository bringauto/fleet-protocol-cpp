#pragma once

#include <fleet_protocol/common_headers/device_management.h>

#include <cstdint>
#include <cstring>
#include <span>
#include <vector>



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

	ConvertibleBufferReturn(const ConvertibleBufferReturn& other)
		: returnCode(other.returnCode), buffer(other.buffer),
		  serialized_(other.serialized_), data_(other.data_) {
		if(!data_.empty()) {
			buffer.data = data_.data();
			buffer.size_in_bytes = data_.size();
		}
	}
	ConvertibleBufferReturn& operator=(const ConvertibleBufferReturn& other) {
		if(this != &other) {
			returnCode = other.returnCode;
			buffer = other.buffer;
			serialized_ = other.serialized_;
			data_ = other.data_;
			if(!data_.empty()) {
				buffer.data = data_.data();
				buffer.size_in_bytes = data_.size();
			}
		}
		return *this;
	}
	ConvertibleBufferReturn(ConvertibleBufferReturn&& other) noexcept
		: returnCode(other.returnCode), buffer(other.buffer),
		  serialized_(std::move(other.serialized_)), data_(std::move(other.data_)) {
		if(!data_.empty()) {
			buffer.data = data_.data();
			buffer.size_in_bytes = data_.size();
		}
		other.buffer.data = nullptr;
		other.buffer.size_in_bytes = 0;
	}
	ConvertibleBufferReturn& operator=(ConvertibleBufferReturn&& other) noexcept {
		if(this != &other) {
			returnCode = other.returnCode;
			buffer = other.buffer;
			serialized_ = std::move(other.serialized_);
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
	~ConvertibleBufferReturn() = default;

	std::span<const uint8_t> serialize() const {
		serialized_.resize(sizeof(int) + buffer.size_in_bytes);
		std::memcpy(serialized_.data(), &returnCode, sizeof(int));
		if(buffer.size_in_bytes > 0) {
			std::memcpy(serialized_.data() + sizeof(int), buffer.data, buffer.size_in_bytes);
		}
		return serialized_;
	}
	void deserialize(std::span<const uint8_t> bytes) {
		if(bytes.size() < sizeof(int)) {
			returnCode = 0;
			data_.clear();
			buffer.data = nullptr;
			buffer.size_in_bytes = 0;
			return;
		}
		std::memcpy(&returnCode, bytes.data(), sizeof(int));
		auto payload = bytes.subspan(sizeof(int));
		data_.assign(payload.begin(), payload.end());
		buffer.data = data_.data();
		buffer.size_in_bytes = data_.size();
	}

private:
	mutable std::vector<uint8_t> serialized_ {};
	std::vector<uint8_t> data_ {};
};

}
