#pragma once

#include <memory_management.h>

#include <string_view>
#include <string>
#include <type_traits>

#include <stdexcept>
#include <cstring>


namespace bringauto::fleet_protocol::cxx {

template<typename T>
concept FleetOsBufferCompatible = requires(T a)
{
	{ a.data };
	{ a.size_in_bytes };
};

/**
 * It represents 'buffer' struct as a string.
 *
 */
template <FleetOsBufferCompatible T>
class BufferAsString {
public:
	BufferAsString(T* buff):
		buffer_ptr_{ buff },
		bufferAsString_ { static_cast<char*>(buffer_ptr_->data), buffer_ptr_->size_in_bytes}
	{};

	/**
	 * It returns std::string_view.
	 * std::string_view instance is valid as long as the instance of BufferAsString which belongs to
	 * is valid.
	 * @return std::string_view::iterator
	 */
	[[nodiscard]] std::string_view getStringView() const { return bufferAsString_; }

	/**
	 * It returns constant iterator to the begin of the string.
	 * Iterator is valid as long as the instance of BufferAsString which belongs to
	 * is valid.
	 * @return std::string_view::iterator
	 */
	[[nodiscard]] std::string_view::iterator cbegin() const { return bufferAsString_.cbegin(); }

	/**
	 * It return constant iterator to the end of the string.
	 * Iterator is valid as long as the instance of BufferAsString which belongs to
	 * is valid
	 * @return std::string_view::iterator
	 */
	[[nodiscard]] std::string_view::iterator cend() const { return bufferAsString_.cend(); }

	/**
	 *
	 * @param data
	 */
	void copyFromString(const std::string_view& data, std::size_t numberOfBytes = 0) requires(!std::is_const_v<T>);

private:

	T* buffer_ptr_ { nullptr };
	std::string_view bufferAsString_ {};
};

}