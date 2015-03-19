#include <iostream>
#include <vector>
#include <cstdint>

#include <Windows.h>
#include "mantle.h"

const char* enumToString(int32_t type) {
	switch (type) {
	case GR_GPU_TYPE_OTHER: return "GR_GPU_TYPE_OTHER";
	case GR_GPU_TYPE_INTEGRATED: return "GR_GPU_TYPE_INTEGRATED";
	case GR_GPU_TYPE_DISCRETE: return "GR_GPU_TYPE_DISCRETE";
	case GR_GPU_TYPE_VIRTUAL: return "GR_GPU_TYPE_VIRTUAL";
	case GR_QUEUE_UNIVERSAL: return "GR_QUEUE_UNIVERSAL";
	case GR_QUEUE_COMPUTE: return "GR_QUEUE_COMPUTE";
	case GR_EXT_QUEUE_DMA: return "GR_EXT_QUEUE_DMA";
	case GR_EXT_QUEUE_TIMER: return "GR_EXT_QUEUE_TIMER";
	default: return "???";
	}
}

int main() {
	/*
		Load library and function entry points
	*/

	HMODULE mantleDll = LoadLibrary(TEXT("mantle64.dll"));

	if (!mantleDll) {
		std::cerr << "error: no Mantle runtime available" << std::endl;
		return 1;
	}

	grInitAndEnumerateGpusPtr grInitAndEnumerateGpus = (grInitAndEnumerateGpusPtr) GetProcAddress(mantleDll, "grInitAndEnumerateGpus");
	grGetGpuInfoPtr grGetGpuInfo = (grGetGpuInfoPtr) GetProcAddress(mantleDll, "grGetGpuInfo");
	grGetExtensionSupportPtr grGetExtensionSupport = (grGetExtensionSupportPtr) GetProcAddress(mantleDll, "grGetExtensionSupport");
	grCreateDevicePtr grCreateDevice = (grCreateDevicePtr) GetProcAddress(mantleDll, "grCreateDevice");

	if (!grInitAndEnumerateGpus || !grGetGpuInfo || !grGetExtensionSupport || !grCreateDevice) {
		std::cerr << "error: couldn't locate (some) Mantle functions" << std::endl;
		return 1;
	}

	/*
		Find Mantle compatible GPU
	*/

	GR_APPLICATION_INFO appInfo = {};
	appInfo.apiVersion = GR_API_VERSION;

	GR_PHYSICAL_GPU gpus[GR_MAX_PHYSICAL_GPUS] = {};	GR_UINT gpuCount = 0;

	GR_RESULT result = grInitAndEnumerateGpus(&appInfo, nullptr, &gpuCount, gpus);

	if (result != GR_SUCCESS) {
		std::cerr << "grInitAndEnumerateGpus:\n\terror = " << std::hex << result << std::endl;
		return 1;
	} else if (gpuCount == 0) {
		std::cerr << "grInitAndEnumerateGpus:\n\tno compatible gpus found" << std::endl;
		return 1;
	}

	/*
		Collect info on the first compatible GPU
	*/

	GR_PHYSICAL_GPU gpu = gpus[0];
	std::cout << "grInitAndEnumerateGpus:\n\tfound " << gpuCount << " compatible gpu(s), using the first one with handle " << std::hex << gpu << std::endl;

	// GPU properties
	std::cout << "grGetGpuInfo:" << std::endl;

	GR_PHYSICAL_GPU_PROPERTIES gpuProperties;
	GR_SIZE dataSize = sizeof(gpuProperties);
	result = grGetGpuInfo(gpu, GR_INFO_TYPE_PHYSICAL_GPU_PROPERTIES, &dataSize, &gpuProperties);

	std::cout << "\tGR_INFO_TYPE_PHYSICAL_GPU_PROPERTIES:" << std::endl;
	std::cout << "\t\tapiVersion = " << gpuProperties.apiVersion << std::endl;
	std::cout << "\t\tdriverVersion = " << gpuProperties.driverVersion << std::endl;
	std::cout << "\t\tvendorId = " << gpuProperties.vendorId << std::endl;
	std::cout << "\t\tdeviceId = " << gpuProperties.deviceId << std::endl;
	std::cout << "\t\tgpuType = " << enumToString(gpuProperties.gpuType) << std::endl;
	std::cout << "\t\tgpuName = \"" << gpuProperties.gpuName << "\"" << std::endl;
	std::cout << "\t\tmaxMemRefsPerSubmission = " << gpuProperties.maxMemRefsPerSubmission << std::endl;
	std::cout << "\t\tmaxInlineMemoryUpdateSize = " << gpuProperties.maxInlineMemoryUpdateSize << std::endl;
	std::cout << "\t\tmaxBoundDescriptorSets = " << gpuProperties.maxBoundDescriptorSets << std::endl;
	std::cout << "\t\tmaxThreadGroupSize = " << gpuProperties.maxThreadGroupSize << std::endl;
	std::cout << "\t\ttimestampFrequency = " << gpuProperties.timestampFrequency << std::endl;
	std::cout << "\t\tmultiColorTargetClears = " << std::boolalpha << gpuProperties.multiColorTargetClears << std::endl;

	// GPU performance
	GR_PHYSICAL_GPU_PERFORMANCE gpuPerformance;
	dataSize = sizeof(gpuPerformance);
	result = grGetGpuInfo(gpu, GR_INFO_TYPE_PHYSICAL_GPU_PERFORMANCE, &dataSize, &gpuPerformance);

	std::cout << "\tGR_INFO_TYPE_PHYSICAL_GPU_PERFORMANCE:" << std::endl;
	std::cout << "\t\tmaxGpuClock = " << gpuPerformance.maxGpuClock << std::endl;
	std::cout << "\t\taluPerClock = " << gpuPerformance.aluPerClock << std::endl;
	std::cout << "\t\ttexPerClock = " << gpuPerformance.texPerClock << std::endl;
	std::cout << "\t\tprimsPerClock = " << gpuPerformance.primsPerClock << std::endl;
	std::cout << "\t\tpixelsPerClock = " << gpuPerformance.pixelsPerClock << std::endl;

	// Query amount of supported queues
	result = grGetGpuInfo(gpu, GR_INFO_TYPE_PHYSICAL_GPU_QUEUE_PROPERTIES, &dataSize, nullptr);
	
	std::vector<GR_PHYSICAL_GPU_QUEUE_PROPERTIES> queues;
	queues.resize(dataSize / sizeof(GR_PHYSICAL_GPU_QUEUE_PROPERTIES));
	
	result = grGetGpuInfo(gpu, GR_INFO_TYPE_PHYSICAL_GPU_QUEUE_PROPERTIES, &dataSize, &queues[0]);

	std::cout << "\tGR_INFO_TYPE_PHYSICAL_GPU_QUEUE_PROPERTIES:" << std::endl;

	for (int q = 0; q < queues.size(); q++) {
		auto queue = queues[q];
		std::cout << "\t\tqueue #" << q << ":" << std::endl;
		std::cout << "\t\t\tqueueType = " << enumToString(queue.queueType) << std::endl;
		std::cout << "\t\t\tqueueCount = " << queue.queueCount << std::endl;
		std::cout << "\t\t\tmaxAtomicCounters = " << queue.maxAtomicCounters << std::endl;
		std::cout << "\t\t\tsupportsTimestamps = " << std::boolalpha << (bool) queue.supportsTimestamps << std::endl;
	}

	/*
		Check if the Windows extension is supported and locate its functions
	*/

	result = grGetExtensionSupport(gpu, "GR_WSI_WINDOWS");

	if (result != GR_SUCCESS) {
		std::cerr << "grGetExtensionSupport:\n\tWindows extension not supported!" << std::endl;
		return 1;
	} else {
		std::cout << "grGetExtensionSupport:\n\tWindows extension is supported" << std::endl;
	}

	grWsiWinGetDisplaysPtr grWsiWinGetDisplays = (grWsiWinGetDisplaysPtr) GetProcAddress(mantleDll, "grWsiWinGetDisplays");
	grWsiWinGetDisplayModeListPtr grWsiWinGetDisplayModeList = (grWsiWinGetDisplayModeListPtr) GetProcAddress(mantleDll, "grWsiWinGetDisplayModeList");

	/*
		Create device and queue
	*/

	// Describe queue needed for device
	GR_DEVICE_QUEUE_CREATE_INFO queueInfo = {};
	queueInfo.queueType = GR_QUEUE_UNIVERSAL;
	queueInfo.queueCount = 1;

	static const GR_CHAR* const ppExtensions[] = {
		"GR_WSI_WINDOWS",
	};

	// Setup device info
	GR_DEVICE_CREATE_INFO deviceInfo = {};
	deviceInfo.queueRecordCount = 1;
	deviceInfo.pRequestedQueues = &queueInfo;
	deviceInfo.extensionCount = 1;
	deviceInfo.ppEnabledExtensionNames = ppExtensions;

	deviceInfo.maxValidationLevel = GR_VALIDATION_LEVEL_4;
	deviceInfo.flags |= GR_DEVICE_CREATE_VALIDATION;

	GR_DEVICE device;
	result = grCreateDevice(gpu, &deviceInfo, &device);

	if (result != GR_SUCCESS) {
		std::cerr << "grCreateDevice:\n\terror = " << std::hex << result << std::endl;
		return 1;
	} else {
		std::cout << "grCreateDevice:\n\tcreated device handle for physical gpu" << std::endl;
	}

	/*
		Query available displays
	*/

	// Check amount of displays
	GR_UINT displayCount;
	grWsiWinGetDisplays(device, &displayCount, nullptr);

	std::vector<GR_WSI_WIN_DISPLAY> displayHandles;
	displayHandles.resize(displayCount);

	result = grWsiWinGetDisplays(device, &displayCount, &displayHandles[0]);

	std::cout << "grWsiWinGetDisplays:" << std::endl;

	// Show supported display modes per display
	for (int d = 0; d < displayCount; d++) {
		std::cout << "\tdisplay #" << std::dec << d << ":" << std::endl;

		GR_UINT displayModeCount;
		result = grWsiWinGetDisplayModeList(displayHandles[d], &displayModeCount, nullptr);

		std::cout << "\t\t" << displayModeCount << " supported modes" << std::endl;
	}

	return 0;
}