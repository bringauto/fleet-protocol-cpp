
#include <bringauto/fleet_protocol/cxx/StringAsBuffer.hpp>
#include <bringauto/fleet_protocol/cxx/BufferAsString.hpp>

#include <general_error_codes.h>

#include <stdexcept>



namespace bringauto::fleet_protocol::cxx {

void StringAsBuffer::createBufferAndCopyData(::buffer *buff, const std::string_view &data) {
	if(::allocate(buff, data.size()) != OK) {
		throw std::runtime_error("Cannot allocate memory for 'std::string' to 'buffer' conversion");
	}
	buff->size_in_bytes = data.size();
	BufferAsString strbuff { buff };
	strbuff.copyFromString(data);
}

}