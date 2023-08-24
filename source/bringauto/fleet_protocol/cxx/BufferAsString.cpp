
#include <bringauto/fleet_protocol/cxx/BufferAsString.hpp>

#include <cstring>
#include <stdexcept>



namespace bringauto::fleet_protocol::cxx {

void BufferAsString::copyFromString(const std::string_view& data) {
	if(data.size() > buffer_.size_in_bytes) {
		throw std::out_of_range("Cannot copy larger data into smaller buffer");
	}
	std::memcpy(buffer_.data, data.begin(), data.size());
}

}
