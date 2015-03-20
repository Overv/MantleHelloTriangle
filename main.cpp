#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

#include <Windows.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include "mantle.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

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

int main(int argc, char *args[]) {
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
	grGetDeviceQueuePtr grGetDeviceQueue = (grGetDeviceQueuePtr) GetProcAddress(mantleDll, "grGetDeviceQueue");
	grCreateCommandBufferPtr grCreateCommandBuffer = (grCreateCommandBufferPtr) GetProcAddress(mantleDll, "grCreateCommandBuffer");
	grBeginCommandBufferPtr grBeginCommandBuffer = (grBeginCommandBufferPtr) GetProcAddress(mantleDll, "grBeginCommandBuffer");
	grEndCommandBufferPtr grEndCommandBuffer = (grEndCommandBufferPtr) GetProcAddress(mantleDll, "grEndCommandBuffer");
	grQueueSubmitPtr grQueueSubmit = (grQueueSubmitPtr) GetProcAddress(mantleDll, "grQueueSubmit");
	grCmdPrepareImagesPtr grCmdPrepareImages = (grCmdPrepareImagesPtr) GetProcAddress(mantleDll, "grCmdPrepareImages");
	grCmdClearColorImagePtr grCmdClearColorImage = (grCmdClearColorImagePtr) GetProcAddress(mantleDll, "grCmdClearColorImage");

	grWsiWinGetDisplaysPtr grWsiWinGetDisplays = (grWsiWinGetDisplaysPtr) GetProcAddress(mantleDll, "grWsiWinGetDisplays");
	grWsiWinGetDisplayModeListPtr grWsiWinGetDisplayModeList = (grWsiWinGetDisplayModeListPtr) GetProcAddress(mantleDll, "grWsiWinGetDisplayModeList");
	grWsiWinCreatePresentableImagePtr grWsiWinCreatePresentableImage = (grWsiWinCreatePresentableImagePtr) GetProcAddress(mantleDll, "grWsiWinCreatePresentableImage");
	grWsiWinQueuePresentPtr grWsiWinQueuePresent = (grWsiWinQueuePresentPtr) GetProcAddress(mantleDll, "grWsiWinQueuePresent");

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

	/*
		Create a presentable image
	*/

	GR_WSI_WIN_PRESENTABLE_IMAGE_CREATE_INFO imageCreateInfo = {};

	imageCreateInfo.format = {
		GR_CH_FMT_R8G8B8A8,
		GR_NUM_FMT_UNORM
	};
	imageCreateInfo.usage = GR_IMAGE_USAGE_COLOR_TARGET;
	imageCreateInfo.extent = {WIDTH, HEIGHT};
	imageCreateInfo.display = 0;

	GR_IMAGE image;
	GR_GPU_MEMORY imageMemory;
	result = grWsiWinCreatePresentableImage(device, &imageCreateInfo, &image, &imageMemory);

	if (result != GR_SUCCESS) {
		std::cerr << "grWsiWinCreatePresentableImage:\n\terror = " << std::hex << result << std::endl;
		return 1;
	} else {
		std::cout << "grWsiWinCreatePresentableImage:\n\tcreated a presentable image" << std::endl;
	}

	/*
		Get a handle for the universal queue
	*/

	GR_QUEUE universalQueue;;
	result = grGetDeviceQueue(device, GR_QUEUE_UNIVERSAL, 0, &universalQueue);

	if (result != GR_SUCCESS) {
		std::cerr << "grGetDeviceQueue:\n\terror = " << std::hex << result << std::endl;
		return 1;
	} else {
		std::cout << "grGetDeviceQueue:\n\tretrieved handle for universal queue" << std::endl;
	}

	/*
		Create command buffer that initialises the image
	*/

	GR_CMD_BUFFER_CREATE_INFO bufferCreateInfo = {};
	bufferCreateInfo.queueType = GR_QUEUE_UNIVERSAL;

	GR_CMD_BUFFER initCmdBuffer;
	assert(grCreateCommandBuffer(device, &bufferCreateInfo, &initCmdBuffer) == GR_SUCCESS);

	assert(grBeginCommandBuffer(initCmdBuffer, 0) == GR_SUCCESS);

		GR_IMAGE_SUBRESOURCE_RANGE colorRange;
		colorRange.aspect = GR_IMAGE_ASPECT_COLOR;
		colorRange.baseMipLevel = 0;
		colorRange.mipLevels = 1;
		colorRange.baseArraySlice = 0;
		colorRange.arraySize = 1;

		GR_IMAGE_STATE_TRANSITION initTransition = {};
		initTransition.image = image;
		initTransition.oldState = GR_IMAGE_STATE_UNINITIALIZED;
		initTransition.newState = GR_WSI_WIN_IMAGE_STATE_PRESENT_WINDOWED;
		initTransition.subresourceRange = colorRange;

		grCmdPrepareImages(initCmdBuffer, 1, &initTransition);

	assert(grEndCommandBuffer(initCmdBuffer) == GR_SUCCESS);

	GR_MEMORY_REF imageMemoryRef = {};
	imageMemoryRef.mem = imageMemory;

	result = grQueueSubmit(universalQueue, 1, &initCmdBuffer, 1, &imageMemoryRef, 0);

	if (result != GR_SUCCESS) {
		std::cerr << "grQueueSubmit:\n\terror = " << std::hex << result << std::endl;
		return 1;
	} else {
		std::cout << "grQueueSubmit:\n\tsubmitted command to initialize image as presentable" << std::endl;
	}

	/*
		Create command buffer to clear image to a color
	*/

	GR_CMD_BUFFER clearCmdBuffer;
	assert(grCreateCommandBuffer(device, &bufferCreateInfo, &clearCmdBuffer) == GR_SUCCESS);

	assert(grBeginCommandBuffer(clearCmdBuffer, 0) == GR_SUCCESS);

		// Transition image to clearable state
		GR_IMAGE_STATE_TRANSITION clearTransition = {};
		clearTransition.image = image;
		clearTransition.oldState = GR_WSI_WIN_IMAGE_STATE_PRESENT_WINDOWED;
		clearTransition.newState = GR_IMAGE_STATE_CLEAR;
		clearTransition.subresourceRange = colorRange;

		grCmdPrepareImages(clearCmdBuffer, 1, &clearTransition);

		// Clear image
		float clearColor[] = {1.0, 0.0, 0.0, 1.0};

		GR_IMAGE_SUBRESOURCE_RANGE range;
		range.aspect = GR_IMAGE_ASPECT_COLOR;
		range.baseMipLevel = 0;
		range.mipLevels = 1;
		range.baseArraySlice = 0;
		range.arraySize = 1;

		grCmdClearColorImage(clearCmdBuffer, image, clearColor, 1, &range);

		// Transition image back into presentable state
		GR_IMAGE_STATE_TRANSITION presentTransition = {};
		presentTransition.image = image;
		presentTransition.oldState = GR_IMAGE_STATE_CLEAR;
		presentTransition.newState = GR_WSI_WIN_IMAGE_STATE_PRESENT_WINDOWED;
		presentTransition.subresourceRange = colorRange;

		grCmdPrepareImages(clearCmdBuffer, 1, &presentTransition);

	result = grEndCommandBuffer(clearCmdBuffer);

	if (result != GR_SUCCESS) {
		std::cerr << "grEndCommandBuffer:\n\terror = " << std::hex << result << std::endl;
		return 1;
	} else {
		std::cout << "grEndCommandBuffer:\n\tbuilt command buffer to clear screen to color" << std::endl;
	}

	/*
		Create window to draw on
	*/

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Mantle demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

	// Retrieve HWND to pass to Mantle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);

	HWND windowHandle = wmInfo.info.win.window;
	std::cout << "Created window using SDL:\n\tHWND = " << windowHandle << std::endl;

	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) break;
		}

		// Submit command buffer that clears the image
		assert(grQueueSubmit(universalQueue, 1, &clearCmdBuffer, 1, &imageMemoryRef, 0) == GR_SUCCESS);

		// Present image to the window
		GR_WSI_WIN_PRESENT_INFO presentInfo = {};
		presentInfo.hWndDest = windowHandle;
		presentInfo.srcImage = image;
		presentInfo.presentMode = GR_WSI_WIN_PRESENT_MODE_WINDOWED;
		presentInfo.presentInterval = 0;

		assert(grWsiWinQueuePresent(universalQueue, &presentInfo) == GR_SUCCESS);
	}

	SDL_Quit();

	return 0;
}