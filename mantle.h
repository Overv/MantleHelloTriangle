#ifndef MANTLE_H
#define MANTLE_H

/*
	Types and constants
*/

typedef char GR_CHAR;
typedef int32_t GR_INT;
typedef uint32_t GR_UINT;
typedef uint8_t GR_UINT8;
typedef uint32_t GR_UINT32;
typedef uint64_t GR_UINT64;
typedef float GR_FLOAT;
typedef uint32_t GR_BOOL;
typedef void GR_VOID;

typedef size_t GR_SIZE;
typedef size_t GR_GPU_SIZE;

typedef int32_t GR_ENUM;
typedef int32_t GR_FLAGS;
typedef uint64_t GR_PHYSICAL_GPU;
typedef uint64_t GR_DEVICE;
typedef uint64_t GR_WSI_WIN_DISPLAY;
typedef uint64_t GR_QUEUE;
typedef uint64_t GR_IMAGE;
typedef uint64_t GR_GPU_MEMORY;
typedef uint64_t GR_CMD_BUFFER;
typedef uint64_t GR_FENCE;
typedef uint64_t GR_BASE_OBJECT;

const int GR_MAX_PHYSICAL_GPUS = 4;
const int GR_API_VERSION = 1;
const int GR_MAX_PHYSICAL_GPU_NAME = 255; // Guess

#define GR_STDCALL __stdcall

typedef enum _GR_RESULT {
	GR_SUCCESS = 0x10000,
	GR_UNSUPPORTED,
	GR_NOT_READY,
	GR_TIMEOUT,
	GR_EVENT_SET,
	GR_EVENT_RESET,

	GR_ERROR_UNKNOW = 0x11000,
	GR_ERROR_UNAVAILABLE,
	GR_ERROR_INITIALIZATION_FAILED,
	GR_ERROR_OUT_OF_MEMORY,
	GR_ERROR_OUT_OF_GPU_MEMORY,
	GR_ERROR_DEVICE_ALREADY_CREATED,
	GR_ERROR_DEVICE_LOST,
	GR_ERROR_INVALID_POINTER,
	GR_ERROR_INVALID_VALUE,
	GR_ERROR_INVALID_HANDLE,
	GR_ERROR_INVALID_ORDINAL,
	GR_ERROR_INVALID_MEMORY_SIZE,
	GR_ERROR_INVALID_EXTENSION,
	GR_ERROR_INVALID_FLAGS,
	GR_ERROR_INVALID_ALIGNMENT,
	GR_ERROR_INVALID_FORMAT,
	GR_ERROR_INVALID_IMAGE,
	GR_ERROR_INVALID_DESCRIPTOR_SET_DATA,
	GR_ERROR_INVALID_QUEUE_TYPE,
	GR_ERROR_INVALID_OBJECT_TYPE,
	GR_ERROR_UNSUPPORTED_SHADER_IL_VERSION,
	GR_ERROR_BAD_SHADER_CODE,
	GR_ERROR_BAD_PIPELINE_DATA,
	GR_ERROR_TOO_MANY_MEMORY_REFERENCES,
	GR_ERROR_NOT_MAPPABLE,
	GR_ERROR_MEMORY_MAP_FAILED,
	GR_ERROR_MEMORY_UNMAP_FAILED,
	GR_ERROR_INCOMPATIBLE_DEVICE,
	GR_ERROR_INCOMPATIBLE_DRIVER,
	GR_ERROR_INCOMPLETE_COMMAND_BUFFER,
	GR_ERROR_BUILDING_COMMAND_BUFFER,
	GR_ERROR_MEMORY_NOT_BOUND,
	GR_ERROR_INCOMPATIBLE_QUEUE,
	GR_ERROR_NOT_SHAREABLE
} GR_RESULT;

typedef enum _GR_INFO_TYPE {
	GR_INFO_TYPE_PHYSICAL_GPU_PROPERTIES = 0x6100,
	GR_INFO_TYPE_PHYSICAL_GPU_PERFORMANCE,
	GR_INFO_TYPE_PHYSICAL_GPU_QUEUE_PROPERTIES,
	GR_INFO_TYPE_PHYSICAL_GPU_MEMORY_PROPERTIES,
	GR_INFO_TYPE_PHYSICAL_GPU_IMAGE_PROPERTIES,
	GR_INFO_TYPE_MEMORY_HEAP_PROPERTIES = 0x6200,
	GR_INFO_TYPE_FORMAT_PROPERTIES = 0x6300,
	GR_INFO_TYPE_SUBRESOURCE_LAYOUT = 0x6400,
	GR_INFO_TYPE_MEMORY_REQUIREMENTS = 0x6800,
	GR_INFO_TYPE_PARENT_DEVICE,
	GR_INFO_TYPE_PARENT_PHYSICAL_GPU,
} GR_INFO_TYPE;

typedef enum _GR_PHYSICAL_GPU_TYPE {
	GR_GPU_TYPE_OTHER = 0x3000,
	GR_GPU_TYPE_INTEGRATED,
	GR_GPU_TYPE_DISCRETE,
	GR_GPU_TYPE_VIRTUAL,
} GR_PHYSICAL_GPU_TYPE;

typedef enum _GR_QUEUE_TYPE {
	GR_QUEUE_UNIVERSAL = 0x1000,
	GR_QUEUE_COMPUTE,
	GR_EXT_QUEUE_DMA = 0x00300200,
	GR_EXT_QUEUE_TIMER
} GR_QUEUE_TYPE;

typedef enum _GR_VALIDATION_LEVEL {
	GR_VALIDATION_LEVEL_0 = 0x8000,
	GR_VALIDATION_LEVEL_1,
	GR_VALIDATION_LEVEL_2,
	GR_VALIDATION_LEVEL_3,
	GR_VALIDATION_LEVEL_4,
} GR_VALIDATION_LEVEL;

typedef enum _GR_DEVICE_CREATE_FLAGS {
	GR_DEVICE_CREATE_VALIDATION = 0x00000001,
} GR_DEVICE_CREATE_FLAGS;

typedef enum _GR_CHANNEL_FORMAT {
	GR_CH_FMT_UNDEFINED,
	GR_CH_FMT_R4G4,
	GR_CH_FMT_R4G4B4A4,
	GR_CH_FMT_R5G6B5,
	GR_CH_FMT_B5G6R5,
	GR_CH_FMT_R5G5B5A1,
	GR_CH_FMT_R8,
	GR_CH_FMT_R8G8,
	GR_CH_FMT_R8G8B8A8,
	GR_CH_FMT_B8G8R8A8,
	GR_CH_FMT_R10G11B11,
	GR_CH_FMT_R11G11B10,
	GR_CH_FMT_R10G10B10A2,
	GR_CH_FMT_R16,
	GR_CH_FMT_R16G16,
	GR_CH_FMT_R16G16B16A16,
	GR_CH_FMT_R32,
	GR_CH_FMT_R32G32,
	GR_CH_FMT_R32G32B32,
	GR_CH_FMT_R32G32B32A32,
	GR_CH_FMT_R16G8,
	GR_CH_FMT_R32G8,
	GR_CH_FMT_R9G9B9E5,
	GR_CH_FMT_BC1,
	GR_CH_FMT_BC2,
	GR_CH_FMT_BC3,
	GR_CH_FMT_BC4,
	GR_CH_FMT_BC5,
	GR_CH_FMT_BC6U,
	GR_CH_FMT_BC6S,
	GR_CH_FMT_BC7
} GR_CHANNEL_FORMAT;

typedef enum _GR_NUM_FORMAT {
	GR_NUM_FMT_UNDEFINED,
	GR_NUM_FMT_UNORM,
	GR_NUM_FMT_SNORM,
	GR_NUM_FMT_UINT,
	GR_NUM_FMT_SINT,
	GR_NUM_FMT_FLOAT,
	GR_NUM_FMT_SRGB,
	GR_NUM_FMT_DS
} GR_NUM_FORMAT;

typedef enum _GR_IMAGE_USAGE_FLAGS {
	GR_IMAGE_USAGE_SHADER_ACCESS_READ = 0x00000001,
	GR_IMAGE_USAGE_SHADER_ACCESS_WRITE = 0x00000002,
	GR_IMAGE_USAGE_COLOR_TARGET = 0x00000004,
	GR_IMAGE_USAGE_DEPTH_STENCIL = 0x00000008,
} GR_IMAGE_USAGE_FLAGS;

typedef enum _GR_WSI_WIN_IMAGE_CREATE_FLAGS {
	GR_WSI_WIN_IMAGE_CREATE_FULLSCREEN_PRESENT = 0x00000001,
	GR_WSI_WIN_IMAGE_CREATE_STEREO = 0x00000002,
} GR_WSI_WIN_IMAGE_CREATE_FLAGS;

typedef enum _GR_CMD_BUFFER_BUILD_FLAGS {
	GR_CMD_BUFFER_OPTIMIZE_GPU_SMALL_BATCH = 0x00000001,
	GR_CMD_BUFFER_OPTIMIZE_PIPELINE_SWITCH = 0x00000002,
	GR_CMD_BUFFER_OPTIMIZE_ONE_TIME_SUBMIT = 0x00000004,
	GR_CMD_BUFFER_OPTIMIZE_DESCRIPTOR_SET_SWITCH = 0x00000008,
} GR_CMD_BUFFER_BUILD_FLAGS;

typedef enum _GR_IMAGE_STATE {
	GR_IMAGE_STATE_DATA_TRANSFER = 0x1300,
	GR_IMAGE_STATE_GRAPHICS_SHADER_READ_ONLY = 0x1301,
	GR_IMAGE_STATE_GRAPHICS_SHADER_WRITE_ONLY = 0x1302,
	GR_IMAGE_STATE_GRAPHICS_SHADER_READ_WRITE = 0x1303,
	GR_IMAGE_STATE_COMPUTE_SHADER_READ_ONLY = 0x1304,
	GR_IMAGE_STATE_COMPUTE_SHADER_WRITE_ONLY = 0x1305,
	GR_IMAGE_STATE_COMPUTE_SHADER_READ_WRITE = 0x1306,
	GR_IMAGE_STATE_MULTI_SHADER_READ_ONLY = 0x1307,
	GR_IMAGE_STATE_TARGET_AND_SHADER_READ_ONLY = 0x1308,
	GR_IMAGE_STATE_UNINITIALIZED = 0x1309,
	GR_IMAGE_STATE_TARGET_RENDER_ACCESS_OPTIMAL = 0x130a,
	GR_IMAGE_STATE_TARGET_SHADER_ACCESS_OPTIMAL = 0x130b,
	GR_IMAGE_STATE_CLEAR = 0x130c,
	GR_IMAGE_STATE_RESOLVE_SOURCE = 0x130d,
	GR_IMAGE_STATE_RESOLVE_DESTINATION = 0x130e,
	GR_IMAGE_STATE_DISCARD = 0x131f,
	GR_IMAGE_STATE_DATA_TRANSFER_SOURCE = 0x1310,
	GR_IMAGE_STATE_DATA_TRANSFER_DESTINATION = 0x1311,
} GR_IMAGE_STATE;

typedef enum _GR_WSI_WIN_IMAGE_STATE {
	GR_WSI_WIN_IMAGE_STATE_PRESENT_WINDOWED = 0x00200000,
	GR_WSI_WIN_IMAGE_STATE_PRESENT_FULLSCREEN = 0x00200001,
} GR_WSI_WIN_IMAGE_STATE;

typedef enum _GR_IMAGE_ASPECT {
	GR_IMAGE_ASPECT_COLOR = 0x1700,
	GR_IMAGE_ASPECT_DEPTH = 0x1701,
	GR_IMAGE_ASPECT_STENCIL = 0x1702,
} GR_IMAGE_ASPECT;

typedef enum _GR_WSI_WIN_PRESENT_MODE {
	GR_WSI_WIN_PRESENT_MODE_WINDOWED = 0x00200200,
	GR_WSI_WIN_PRESENT_MODE_FULLSCREEN = 0x00200201,
} GR_WSI_WIN_PRESENT_MODE;

typedef enum _GR_WSI_WIN_PRESENT_FLAGS {
	GR_WSI_WIN_PRESENT_FULLSCREEN_DONOTWAIT = 0x00000001,
	GR_WSI_WIN_PRESENT_FULLSCREEN_STEREO = 0x00000002,
} GR_WSI_WIN_PRESENT_FLAGS;

/*
	Callback functions
*/

typedef GR_VOID* (GR_STDCALL *GR_ALLOC_FUNCTION)(
	GR_SIZE size,
	GR_SIZE alignment,
	GR_ENUM allocType);

typedef GR_VOID(GR_STDCALL *GR_FREE_FUNCTION)(
	GR_VOID* pMem);

typedef GR_VOID(GR_STDCALL *GR_DBG_MSG_CALLBACK_FUNCTION)(
	GR_ENUM msgType,
	GR_ENUM validationLevel,
	GR_BASE_OBJECT srcObject,
	GR_SIZE location,
	GR_ENUM msgCode,
	const GR_CHAR* pMsg,
	GR_VOID* pUserData);

/*
	Structures
*/

typedef struct _GR_APPLICATION_INFO {
	const GR_CHAR* pAppName;
	GR_UINT32 appVersion;
	const GR_CHAR* pEngineName;
	GR_UINT32 engineVersion;
	GR_UINT32 apiVersion;
} GR_APPLICATION_INFO;

typedef struct _GR_ALLOC_CALLBACKS {
	GR_ALLOC_FUNCTION pfnAlloc;
	GR_FREE_FUNCTION pfnFree;
} GR_ALLOC_CALLBACKS;

typedef struct _GR_PHYSICAL_GPU_PROPERTIES {
	GR_UINT32 apiVersion;
	GR_UINT32 driverVersion;
	GR_UINT32 vendorId;
	GR_UINT32 deviceId;
	GR_ENUM gpuType;
	GR_CHAR gpuName[GR_MAX_PHYSICAL_GPU_NAME];
	GR_UINT maxMemRefsPerSubmission;
	GR_GPU_SIZE reserved;
	GR_GPU_SIZE maxInlineMemoryUpdateSize;
	GR_UINT maxBoundDescriptorSets;
	GR_UINT maxThreadGroupSize;
	GR_UINT64 timestampFrequency;
	GR_BOOL multiColorTargetClears;
} GR_PHYSICAL_GPU_PROPERTIES;

typedef struct _GR_PHYSICAL_GPU_PERFORMANCE {
	GR_FLOAT maxGpuClock;
	GR_FLOAT aluPerClock;
	GR_FLOAT texPerClock;
	GR_FLOAT primsPerClock;
	GR_FLOAT pixelsPerClock;
} GR_PHYSICAL_GPU_PERFORMANCE;

typedef struct _GR_PHYSICAL_GPU_QUEUE_PROPERTIES {
	GR_ENUM queueType;
	GR_UINT queueCount;
	GR_UINT maxAtomicCounters;
	GR_BOOL supportsTimestamps;
} GR_PHYSICAL_GPU_QUEUE_PROPERTIES;

typedef struct _GR_DEVICE_QUEUE_CREATE_INFO {
	GR_ENUM queueType;
	GR_UINT queueCount;
} GR_DEVICE_QUEUE_CREATE_INFO;

typedef struct _GR_DEVICE_CREATE_INFO {
	GR_UINT queueRecordCount;
	const GR_DEVICE_QUEUE_CREATE_INFO* pRequestedQueues;
	GR_UINT extensionCount;
	const GR_CHAR*const* ppEnabledExtensionNames;
	GR_ENUM maxValidationLevel;
	GR_FLAGS flags;
} GR_DEVICE_CREATE_INFO;

typedef struct _GR_EXTENT2D {
	GR_INT width;
	GR_INT height;
} GR_EXTENT2D;

typedef struct _GR_FORMAT {
	GR_UINT32 channelFormat : 16;
	GR_UINT32 numericFormat : 16;
} GR_FORMAT;

typedef struct _GR_WSI_WIN_DISPLAY_MODE {
	GR_EXTENT2D extent;
	GR_FORMAT format;
	GR_UINT refreshRate;
	GR_BOOL stereo;
	GR_BOOL crossDisplayPresent;
} GR_WSI_WIN_DISPLAY_MODE;

typedef struct _GR_WSI_WIN_PRESENTABLE_IMAGE_CREATE_INFO {
	GR_FORMAT format;
	GR_FLAGS usage;
	GR_EXTENT2D extent;
	GR_WSI_WIN_DISPLAY display;
	GR_FLAGS flags;
} GR_WSI_WIN_PRESENTABLE_IMAGE_CREATE_INFO;

typedef struct _GR_CMD_BUFFER_CREATE_INFO {
	GR_ENUM queueType;
	GR_FLAGS flags;
} GR_CMD_BUFFER_CREATE_INFO;

typedef struct _GR_MEMORY_REF {
	GR_GPU_MEMORY mem;
	GR_FLAGS flags;
} GR_MEMORY_REF;

typedef struct _GR_IMAGE_SUBRESOURCE_RANGE {
	GR_ENUM aspect;
	GR_UINT baseMipLevel;
	GR_UINT mipLevels;
	GR_UINT baseArraySlice;
	GR_UINT arraySize;
} GR_IMAGE_SUBRESOURCE_RANGE;

typedef struct _GR_IMAGE_STATE_TRANSITION {
	GR_IMAGE image;
	GR_ENUM oldState;
	GR_ENUM newState;
	GR_IMAGE_SUBRESOURCE_RANGE subresourceRange;
} GR_IMAGE_STATE_TRANSITION;

typedef struct _GR_WSI_WIN_PRESENT_INFO {
	HWND hWndDest;
	GR_IMAGE srcImage;
	GR_ENUM presentMode;
	GR_UINT presentInterval;
	GR_FLAGS flags;
} GR_WSI_WIN_PRESENT_INFO;

/*
	API function pointers
*/

typedef GR_RESULT (GR_STDCALL *grInitAndEnumerateGpusPtr)(
	const GR_APPLICATION_INFO* pAppInfo,
	const GR_ALLOC_CALLBACKS* pAllocCb,
	GR_UINT* pGpuCount,
	GR_PHYSICAL_GPU gpus[GR_MAX_PHYSICAL_GPUS]);

typedef GR_RESULT (GR_STDCALL *grGetGpuInfoPtr)(
	GR_PHYSICAL_GPU gpu,
	GR_ENUM infoType,
	GR_SIZE* pDataSize,
	GR_VOID* pData);

typedef GR_RESULT (GR_STDCALL *grGetExtensionSupportPtr)(
	GR_PHYSICAL_GPU gpu,
	const GR_CHAR* pExtName);

typedef GR_RESULT (GR_STDCALL *grCreateDevicePtr)(
	GR_PHYSICAL_GPU gpu,
	const GR_DEVICE_CREATE_INFO* pCreateInfo,
	GR_DEVICE* pDevice);

typedef GR_RESULT (GR_STDCALL *grWsiWinGetDisplaysPtr)(
	GR_DEVICE device,
	GR_UINT* pDisplayCount,
	GR_WSI_WIN_DISPLAY* pDisplayList);

typedef GR_RESULT (GR_STDCALL *grWsiWinGetDisplayModeListPtr)(
	GR_WSI_WIN_DISPLAY display,
	GR_UINT* pDisplayModeCount,
	GR_WSI_WIN_DISPLAY_MODE* pDisplayModeList);

typedef GR_RESULT (GR_STDCALL *grGetDeviceQueuePtr)(
	GR_DEVICE device,
	GR_ENUM queueType,
	GR_UINT queueId,
	GR_QUEUE* pQueue);

typedef GR_RESULT (GR_STDCALL *grWsiWinCreatePresentableImagePtr)(
	GR_DEVICE device,
	const GR_WSI_WIN_PRESENTABLE_IMAGE_CREATE_INFO* pCreateInfo,
	GR_IMAGE* pImage,
	GR_GPU_MEMORY* pMem);

typedef GR_RESULT (GR_STDCALL *grCreateCommandBufferPtr)(
	GR_DEVICE device,
	const GR_CMD_BUFFER_CREATE_INFO* pCreateInfo,
	GR_CMD_BUFFER* pCmdBuffer);typedef GR_RESULT (GR_STDCALL *grBeginCommandBufferPtr)(
	GR_CMD_BUFFER cmdBuffer,
	GR_FLAGS flags);

typedef GR_RESULT (GR_STDCALL *grEndCommandBufferPtr)(
	GR_CMD_BUFFER cmdBuffer);

typedef GR_RESULT (GR_STDCALL *grQueueSubmitPtr)(
	GR_QUEUE queue,
	GR_UINT cmdBufferCount,
	const GR_CMD_BUFFER* pCmdBuffers,
	GR_UINT memRefCount,
	const GR_MEMORY_REF* pMemRefs,
	GR_FENCE fence);

typedef GR_VOID (GR_STDCALL *grCmdPrepareImagesPtr)(
	GR_CMD_BUFFER cmdBuffer,
	GR_UINT transitionCount,
	const GR_IMAGE_STATE_TRANSITION* pStateTransitions);

typedef GR_VOID(GR_STDCALL *grCmdClearColorImagePtr)(
	GR_CMD_BUFFER cmdBuffer,
	GR_IMAGE image,
	const GR_FLOAT color[4],
	GR_UINT rangeCount,
	const GR_IMAGE_SUBRESOURCE_RANGE* pRanges);

typedef GR_RESULT (GR_STDCALL *grWsiWinQueuePresentPtr)(
	GR_QUEUE queue,
	const GR_WSI_WIN_PRESENT_INFO* pPresentInfo);

typedef GR_RESULT (GR_STDCALL *grDbgRegisterMsgCallbackPtr)(
	GR_DBG_MSG_CALLBACK_FUNCTION pfnMsgCallback,
	GR_VOID* pUserData);

#endif