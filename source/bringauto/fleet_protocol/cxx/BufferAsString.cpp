#include <bringauto/fleet_protocol/cxx/BufferAsString.hpp>

#include <cstring>
#include <stdexcept>


namespace bringauto::fleet_protocol::cxx {

template <FleetOsBufferCompatible T>
void BufferAsString<T>::copyFromString(const std::string_view& data, const std::size_t numberOfBytes) requires(!std::is_const_v<T>) {
	if (buffer_ptr_->data == nullptr) {
		throw std::out_of_range("Invalid buffer data section");
	}
	if (data.size() > buffer_ptr_->size_in_bytes) {
		throw std::out_of_range("Cannot copy larger data into smaller buffer");
	}
	std::memcpy(buffer_ptr_->data, data.begin(), data.size());
}

}
