#pragma once

#include <memory_management.h>

#include <string_view>



namespace bringauto::fleet_protocol::cxx {

/**
 *
 */
class StringAsBuffer {
public:
	/**
	 *
	 * @param buff
	 * @param data
	 */
	static void createBufferAndCopyData(::buffer* buff, const std::string_view& data);
};

}