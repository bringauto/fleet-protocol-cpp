#pragma once

#include <fleet_protocol/common_headers/device_management.h>

#include <cstdint>
#include <span>
#include <vector>



namespace bringauto::fleet_protocol::async_function_execution_definitions {

/**
 * @brief ConvertibleBuffer is a RAII wrapper around the fleet_protocol 'buffer' struct
 * that manages the lifetime of the buffer data and supports conversion to/from a byte span.
 * Buffer data ownership is maintained internally via a std::vector; buffer.data always
 * points into that internal storage after deserialization.
 */
struct ConvertibleBuffer final {
	/**
	 * @brief The wrapped fleet_protocol buffer struct.
	 */
	struct ::buffer buffer {};
	/**
	 * @brief Default constructor. Creates an empty buffer.
	 */
	ConvertibleBuffer() = default;
	/**
	 * @brief Constructs from an existing ::buffer. Does not take ownership of buff.data.
	 */
	explicit ConvertibleBuffer(struct ::buffer buff) : buffer(buff) {}

	/**
	 * @brief Copy constructor. Rebinds buffer.data to the copied internal storage.
	 */
	ConvertibleBuffer(const ConvertibleBuffer& other) : buffer(other.buffer), data_(other.data_) {
		if(!data_.empty()) {
			buffer.data = data_.data();
			buffer.size_in_bytes = data_.size();
		}
	}
	/**
	 * @brief Copy assignment operator. Rebinds buffer.data to the copied internal storage.
	 */
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
	/**
	 * @brief Move constructor. Rebinds buffer.data to the moved-in internal storage.
	 */
	ConvertibleBuffer(ConvertibleBuffer&& other) noexcept : buffer(other.buffer), data_(std::move(other.data_)) {
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
	/**
	 * @brief Destructor.
	 */
	~ConvertibleBuffer() = default;

	/**
	 * @brief Returns a view of the buffer data as a byte span. Does not copy.
	 */
	std::span<const uint8_t> serialize() const {
		return std::span {reinterpret_cast<const uint8_t *>(buffer.data), buffer.size_in_bytes};
	}
	/**
	 * @brief Copies bytes into internal storage and rebinds buffer.data to it.
	 */
	void deserialize(std::span<const uint8_t> bytes) {
		data_.assign(bytes.begin(), bytes.end());
		buffer.data = data_.data();
		buffer.size_in_bytes = data_.size();
	}

private:
	std::vector<uint8_t> data_ {};
};

}
