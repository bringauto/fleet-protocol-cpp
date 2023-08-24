
#pragma once

#include <string_view>
#include <string>

#include <memory_management.h>



namespace bringauto::fleet_protocol::cxx {

/**
 * It represents 'buffer' struct as a string.
 *
 */
class BufferAsString {
public:
	BufferAsString(const ::buffer& buff):
		buffer_(buff),
		bufferAsString_ {static_cast<char*>(buff.data), buff.size_in_bytes}
	{}

	BufferAsString(const ::buffer* buff):
			buffer_(*buff),
			bufferAsString_ {static_cast<char*>(buff->data), buff->size_in_bytes}
	{}

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
	void copyFromString(const std::string_view& data);

private:

	buffer buffer_ {};
	std::string_view bufferAsString_ {};
};

}