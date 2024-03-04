#include <bringauto/fleet_protocol/cxx/StringAsBuffer.hpp>
#include <bringauto/fleet_protocol/cxx/BufferAsString.hpp>

#include <fleet_protocol/common_headers/general_error_codes.h>

#include <stdexcept>
#include <iostream>


namespace bringauto::fleet_protocol::cxx {

void StringAsBuffer::createBufferAndCopyData(::buffer* buff, const std::string_view& data) {
	if(::allocate(buff, data.size() + 1) != OK) {
		throw std::runtime_error("Cannot allocate memory for 'std::string' to 'buffer' conversion");
	}
	std::cout << "createBufferAndCOpyData Data size: " << data.size() + 1 << std::endl;
	BufferAsString strbuff{buff};
	strbuff.copyFromString(data);
}
}
