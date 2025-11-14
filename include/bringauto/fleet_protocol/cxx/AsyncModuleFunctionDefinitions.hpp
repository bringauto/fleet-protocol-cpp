#pragma once

#include <bringauto/fleet_protocol/cxx/ConvertibleBuffer.hpp>
#include <bringauto/fleet_protocol/cxx/ConvertibleBufferReturn.hpp>

#include <bringauto/async_function_execution/AsyncFunctionExecutor.hpp>


namespace bringauto::fleet_protocol::cxx {

inline static const async_function_execution::FunctionDefinition getModuleNumberAsync {
	async_function_execution::FunctionId { 0 },
	async_function_execution::Return { int {} },
	async_function_execution::Arguments {}
};

inline static const async_function_execution::FunctionDefinition isDeviceTypeSupportedAsync {
	async_function_execution::FunctionId { 1 },
	async_function_execution::Return { int {} },
	async_function_execution::Arguments { uint32_t {} }
};

inline static const async_function_execution::FunctionDefinition sendStatusConditionAsync {
	async_function_execution::FunctionId { 2 },
	async_function_execution::Return { int {} },
	async_function_execution::Arguments { ConvertibleBuffer {}, ConvertibleBuffer {}, uint32_t {} }
};

inline static const async_function_execution::FunctionDefinition generateCommandAsync {
	async_function_execution::FunctionId { 3 },
	async_function_execution::Return { ConvertibleBufferReturn {} },
	async_function_execution::Arguments { ConvertibleBuffer {}, ConvertibleBuffer {}, uint32_t {} }
};

inline static const async_function_execution::FunctionDefinition aggregateStatusAsync {
	async_function_execution::FunctionId { 4 },
	async_function_execution::Return { ConvertibleBufferReturn {} },
	async_function_execution::Arguments { ConvertibleBuffer {}, ConvertibleBuffer {}, uint32_t {} }
};

inline static const async_function_execution::FunctionDefinition aggregateErrorAsync {
	async_function_execution::FunctionId { 5 },
	async_function_execution::Return { ConvertibleBufferReturn {} },
	async_function_execution::Arguments { ConvertibleBuffer {}, ConvertibleBuffer {}, uint32_t {} }
};

inline static const async_function_execution::FunctionDefinition generateFirstCommandAsync {
	async_function_execution::FunctionId { 6 },
	async_function_execution::Return { ConvertibleBufferReturn {} },
	async_function_execution::Arguments { uint32_t {} }
};

inline static const async_function_execution::FunctionDefinition statusDataValidAsync {
	async_function_execution::FunctionId { 7 },
	async_function_execution::Return { int {} },
	async_function_execution::Arguments { ConvertibleBuffer {}, uint32_t {} }
};

inline static const async_function_execution::FunctionDefinition commandDataValidAsync {
	async_function_execution::FunctionId { 8 },
	async_function_execution::Return { int {} },
	async_function_execution::Arguments { ConvertibleBuffer {}, uint32_t {} }
};

/**
 * @brief Type alias for an AsyncFunctionExecutor specialized with module-related functions.
 */
using ModuleFunctionExecutor = async_function_execution::AsyncFunctionExecutor<
    decltype(getModuleNumberAsync),
    decltype(isDeviceTypeSupportedAsync),
    decltype(sendStatusConditionAsync),
    decltype(generateCommandAsync),
    decltype(aggregateStatusAsync),
    decltype(aggregateErrorAsync),
    decltype(generateFirstCommandAsync),
    decltype(statusDataValidAsync),
    decltype(commandDataValidAsync)
>;

/**
 * @brief FunctionList containing all module-related function definitions.
 */
inline static const async_function_execution::FunctionList<
		decltype(getModuleNumberAsync),
		decltype(isDeviceTypeSupportedAsync),
		decltype(sendStatusConditionAsync),
		decltype(generateCommandAsync),
		decltype(aggregateStatusAsync),
		decltype(aggregateErrorAsync),
		decltype(generateFirstCommandAsync),
		decltype(statusDataValidAsync),
		decltype(commandDataValidAsync)
	> moduleFunctionList {
		getModuleNumberAsync,
		isDeviceTypeSupportedAsync,
		sendStatusConditionAsync,
		generateCommandAsync,
		aggregateStatusAsync,
		aggregateErrorAsync,
		generateFirstCommandAsync,
		statusDataValidAsync,
		commandDataValidAsync
	};

}
