#ifndef VERBOSE

#include <SDL.h>
#include <SDL_syswm.h>

#include "mantle.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main(int argc, char *args[]) {
	// Initialize function pointers, much like GLEW in OpenGL
	mantleLoadFunctions();

	// Find Mantle compatible GPU handles
	GR_APPLICATION_INFO appInfo = {};
	appInfo.apiVersion = GR_API_VERSION;

	GR_PHYSICAL_GPU gpus[GR_MAX_PHYSICAL_GPUS] = {};	GR_UINT gpuCount = 0;

	grInitAndEnumerateGpus(&appInfo, nullptr, &gpuCount, gpus);

	// Create device from first compatible GPU
	GR_DEVICE_QUEUE_CREATE_INFO queueInfo = {};
	queueInfo.queueType = GR_QUEUE_UNIVERSAL;
	queueInfo.queueCount = 1;

	static const GR_CHAR* const ppExtensions[] = {
		"GR_WSI_WINDOWS",
	};

	GR_DEVICE_CREATE_INFO deviceInfo = {};
	deviceInfo.queueRecordCount = 1;
	deviceInfo.pRequestedQueues = &queueInfo;
	deviceInfo.extensionCount = 1;
	deviceInfo.ppEnabledExtensionNames = ppExtensions;
	deviceInfo.maxValidationLevel = GR_VALIDATION_LEVEL_0;

	GR_DEVICE device;
	grCreateDevice(gpus[0], &deviceInfo, &device);

	// Create image that can be presented
	GR_WSI_WIN_PRESENTABLE_IMAGE_CREATE_INFO imageCreateInfo = {};
	imageCreateInfo.format = {
		GR_CH_FMT_R8G8B8A8,
		GR_NUM_FMT_UNORM
	};
	imageCreateInfo.usage = GR_IMAGE_USAGE_COLOR_TARGET;
	imageCreateInfo.extent = {WIDTH, HEIGHT};

	GR_IMAGE image;
	GR_GPU_MEMORY imageMemory;
	grWsiWinCreatePresentableImage(device, &imageCreateInfo, &image, &imageMemory);

	GR_MEMORY_REF imageMemoryRef = {};
	imageMemoryRef.mem = imageMemory;

	GR_IMAGE_SUBRESOURCE_RANGE imageColorRange;
	imageColorRange.aspect = GR_IMAGE_ASPECT_COLOR;
	imageColorRange.baseMipLevel = 0;
	imageColorRange.mipLevels = 1;
	imageColorRange.baseArraySlice = 0;
	imageColorRange.arraySize = 1;

	// Get handle to universal queue
	GR_QUEUE universalQueue;
	grGetDeviceQueue(device, GR_QUEUE_UNIVERSAL, 0, &universalQueue);

	// Create and submit command buffer that transitions the image to being presentable
	GR_CMD_BUFFER_CREATE_INFO bufferCreateInfo = {};
	bufferCreateInfo.queueType = GR_QUEUE_UNIVERSAL;

	GR_CMD_BUFFER initCmdBuffer;
	grCreateCommandBuffer(device, &bufferCreateInfo, &initCmdBuffer);

	grBeginCommandBuffer(initCmdBuffer, 0);

		GR_IMAGE_STATE_TRANSITION initTransition = {};
		initTransition.image = image;
		initTransition.oldState = GR_IMAGE_STATE_UNINITIALIZED;
		initTransition.newState = GR_WSI_WIN_IMAGE_STATE_PRESENT_WINDOWED;
		initTransition.subresourceRange = imageColorRange;

		grCmdPrepareImages(initCmdBuffer, 1, &initTransition);

	grEndCommandBuffer(initCmdBuffer);

	grQueueSubmit(universalQueue, 1, &initCmdBuffer, 1, &imageMemoryRef, 0);

	// Create command buffer that clears the image to a color
	GR_CMD_BUFFER clearCmdBuffer;
	grCreateCommandBuffer(device, &bufferCreateInfo, &clearCmdBuffer);

	grBeginCommandBuffer(clearCmdBuffer, 0);

		GR_IMAGE_STATE_TRANSITION clearTransition = {};
		clearTransition.image = image;
		clearTransition.oldState = GR_WSI_WIN_IMAGE_STATE_PRESENT_WINDOWED;
		clearTransition.newState = GR_IMAGE_STATE_CLEAR;
		clearTransition.subresourceRange = imageColorRange;

		grCmdPrepareImages(clearCmdBuffer, 1, &clearTransition);

		float clearColor[] = {1.0, 0.0, 0.0, 1.0};
		grCmdClearColorImage(clearCmdBuffer, image, clearColor, 1, &imageColorRange);

		GR_IMAGE_STATE_TRANSITION presentTransition = {};
		presentTransition.image = image;
		presentTransition.oldState = GR_IMAGE_STATE_CLEAR;
		presentTransition.newState = GR_WSI_WIN_IMAGE_STATE_PRESENT_WINDOWED;
		presentTransition.subresourceRange = imageColorRange;

		grCmdPrepareImages(clearCmdBuffer, 1, &presentTransition);

	grEndCommandBuffer(clearCmdBuffer);

	// Create window to present to and retrieve its handle
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Mantle demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	HWND windowHandle = wmInfo.info.win.window;

	// Describe presenting from image to window
	GR_WSI_WIN_PRESENT_INFO presentInfo = {};
	presentInfo.hWndDest = windowHandle;
	presentInfo.srcImage = image;
	presentInfo.presentMode = GR_WSI_WIN_PRESENT_MODE_WINDOWED;

	// Main loop
	while (true) {
		SDL_Event windowEvent;
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) break;
		}

		// Submit command buffer that clears the image
		grQueueSubmit(universalQueue, 1, &clearCmdBuffer, 1, &imageMemoryRef, 0);

		// Present image to the window
		grWsiWinQueuePresent(universalQueue, &presentInfo);
	}

	return 0;
}

#endif
