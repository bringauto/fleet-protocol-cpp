#pragma once

#include <external_server_structures.h>

#include <bringauto/fleet_protocol/cxx/BufferAsString.hpp>

#include <map>
#include <string>



namespace bringauto::fleet_protocol::cxx {

class KeyValueConfig {
public:
	using map_type = std::map<std::string, std::string>;

	KeyValueConfig(const ::config configData) {
		const int size                 = configData.size;
		const ::key_value* keyValuePtr = configData.parameters;
		if(size <= 0) {
			return;
		}

		for(int i = configData.size; i > 0; i--) {
			BufferAsString key   { &keyValuePtr->key };
			BufferAsString value { &keyValuePtr->value };
			keyValue.insert({ std::string(key.getStringView()), std::string(value.getStringView()) });
			keyValuePtr++;
		}
	}

	map_type::const_iterator cbegin() const { return keyValue.cbegin(); }

	map_type::const_iterator cend() const { return keyValue.cend(); }

private:
	map_type keyValue;

};

}