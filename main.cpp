#include <iostream>
#include <cstdint>

#include <Windows.h>
#include "mantle.h"

int main() {
	// Load Mantle library dynamically
	HMODULE libMantle = LoadLibrary(TEXT("mantle64.dll"));

	if (!libMantle) {
		std::cerr << "error: no Mantle runtime available" << std::endl;
		return 1;
	}

	// Locate function entry points
	grInitAndEnumerateGpusPtr grInitAndEnumerateGpus = (grInitAndEnumerateGpusPtr) GetProcAddress(libMantle, "grInitAndEnumerateGpus");
	grCreateDevicePtr grCreateDevice = (grCreateDevicePtr) GetProcAddress(libMantle, "grCreateDevice");

	if (!grInitAndEnumerateGpus || !grCreateDevice) {
		std::cerr << "error: couldn't locate (some) Mantle functions" << std::endl;
		return 1;
	}

	// Query for compatible gpus
	GR_APPLICATION_INFO appInfo = {};
	appInfo.apiVersion = GR_API_VERSION;

	GR_PHYSICAL_GPU gpus[GR_MAX_PHYSICAL_GPUS] = {};	GR_UINT gpuCount = 0;

	GR_RESULT result = grInitAndEnumerateGpus(&appInfo, nullptr, &gpuCount, gpus);

	if (result != GR_SUCCESS) {
		std::cerr << "grInitAndEnumerateGpus: error = " << std::hex << result << std::endl;
		return 1;
	} else if (gpuCount == 0) {
		std::cerr << "grInitAndEnumerateGpus: no compatible gpus found" << std::endl;
	} else {
		std::cout << "grInitAndEnumerateGpus: found " << gpuCount << " compatible gpu(s), using the first one with handle " << std::hex << gpus[0] << std::endl;
	}

	// Describe queue needed for device
	GR_DEVICE_QUEUE_CREATE_INFO queueInfo = {};
	queueInfo.queueType = GR_QUEUE_UNIVERSAL;
	queueInfo.queueCount = 1;

	// WSI extension needs to be initialized for presentation
	static const GR_CHAR* const ppExtensions[] = {
		"GR_WSI_WINDOWS",
	};

	// Setup device info
	GR_DEVICE_CREATE_INFO deviceInfo = {};
	deviceInfo.queueRecordCount = 1;
	deviceInfo.pRequestedQueues = &queueInfo;
	deviceInfo.extensionCount = 1;
	deviceInfo.ppEnabledExtensionNames = ppExtensions;

	// Enable validation layer
	deviceInfo.maxValidationLevel = GR_VALIDATION_LEVEL_4;
	deviceInfo.flags |= GR_DEVICE_CREATE_VALIDATION;

	// Create device
	GR_DEVICE device = GR_NULL_HANDLE;
	result = grCreateDevice(gpus[0], &deviceInfo, &device);

	if (result != GR_SUCCESS) {
		std::cerr << "grCreateDevice: error = " << std::hex << result << std::endl;
		return 1;
	} else {
		std::cout << "grCreateDevice: created device handle for physical gpu" << std::endl;
	}

	return 0;
}