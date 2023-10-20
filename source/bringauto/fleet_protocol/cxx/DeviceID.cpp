

#include <bringauto/fleet_protocol/cxx/DeviceID.hpp>



namespace bringauto::fleet_protocol::cxx {

DeviceID::DeviceID(int module, unsigned int device_type, unsigned int priority,
				   const std::string_view device_role,
				   const std::string_view device_name) :
		device_role_(device_role),
		device_name_(device_name) {
	id_.device_type = device_type;
	id_.module = module;
	id_.priority = priority;
	id_.device_role.data = const_cast<char *> (device_role_.c_str());
	id_.device_role.size_in_bytes = device_role_.size();
	id_.device_name.data = const_cast<char *> (device_name_.c_str());
	id_.device_name.size_in_bytes = device_name_.size();
}

DeviceID::DeviceID(const device_identification& device_id):
		device_role_(static_cast<char*>(device_id.device_role.data), device_id.device_role.size_in_bytes),
		device_name_(static_cast<char*>(device_id.device_name.data), device_id.device_name.size_in_bytes)
{
	id_.device_type = device_id.device_type;
	id_.module      = device_id.module;
	id_.priority    = device_id.priority;
	id_.device_role.data          = const_cast<char *> (device_role_.c_str());
	id_.device_role.size_in_bytes = device_role_.size();
	id_.device_name.data          = const_cast<char *> (device_name_.c_str());
	id_.device_name.size_in_bytes = device_name_.size();
}

DeviceID::DeviceID(DeviceID &&c) noexcept:
		device_role_(std::move(c.device_role_)),
		device_name_(std::move(c.device_name_)),
		id_(c.id_)
{
	id_.device_role.data = const_cast<char *>(device_role_.c_str());
	id_.device_name.data = const_cast<char *>(device_name_.c_str());
}

}