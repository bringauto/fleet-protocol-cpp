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
 * The first 4 bytes represent the return code (std::int32_t), followed by the buffer data.
 */
struct ConvertibleBufferReturn final {
	/**
	 * @brief The return code associated with the buffer.
	 */
	std::int32_t returnCode {};
	/**
	 * @brief The wrapped fleet_protocol buffer struct.
	 */
	struct ::buffer buffer {};
	/**
	 * @brief Default constructor. Creates an empty buffer with return code 0.
	 */
	ConvertibleBufferReturn() = default;
	/**
	 * @brief Constructs from a return code and an existing ::buffer. Does not take ownership of buff.data.
	 */
	ConvertibleBufferReturn(std::int32_t code, struct ::buffer buff) : returnCode(code), buffer(buff) {}

	/**
	 * @brief Copy constructor. Rebinds buffer.data to the copied internal storage.
	 */
	ConvertibleBufferReturn(const ConvertibleBufferReturn& other)
		: returnCode(other.returnCode), buffer(other.buffer),
		  serialized_(other.serialized_), data_(other.data_) {
		if(!data_.empty()) {
			buffer.data = data_.data();
			buffer.size_in_bytes = data_.size();
		}
	}
	/**
	 * @brief Copy assignment operator. Rebinds buffer.data to the copied internal storage.
	 */
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
	/**
	 * @brief Move constructor. Rebinds buffer.data to the moved-in internal storage.
	 */
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
	/**
	 * @brief Move assignment operator. Rebinds buffer.data to the moved-in internal storage.
	 */
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
	/**
	 * @brief Destructor.
	 */
	~ConvertibleBufferReturn() = default;

	/**
	 * @brief Serializes returnCode and buffer data into a contiguous byte span.
	 * The first 4 bytes are the return code in native byte order, followed by buffer data.
	 */
	std::span<const uint8_t> serialize() const {
		serialized_.resize(sizeof(std::int32_t) + buffer.size_in_bytes);
		std::memcpy(serialized_.data(), &returnCode, sizeof(std::int32_t));
		if(buffer.size_in_bytes > 0) {
			std::memcpy(serialized_.data() + sizeof(std::int32_t), buffer.data, buffer.size_in_bytes);
		}
		return serialized_;
	}
	/**
	 * @brief Deserializes a byte span into returnCode and buffer data.
	 * Resets to empty state if bytes is smaller than sizeof(std::int32_t).
	 */
	void deserialize(std::span<const uint8_t> bytes) {
		if(bytes.size() < sizeof(std::int32_t)) {
			returnCode = 0;
			data_.clear();
			buffer.data = nullptr;
			buffer.size_in_bytes = 0;
			return;
		}
		std::memcpy(&returnCode, bytes.data(), sizeof(std::int32_t));
		auto payload = bytes.subspan(sizeof(std::int32_t));
		data_.assign(payload.begin(), payload.end());
		buffer.data = data_.data();
		buffer.size_in_bytes = data_.size();
	}

private:
	mutable std::vector<uint8_t> serialized_ {};
	std::vector<uint8_t> data_ {};
};

}
