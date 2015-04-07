#ifndef MANTLE_H
#define MANTLE_H

#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>

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
typedef uint32_t GR_SAMPLE_MASK; // Guess

typedef uint64_t GR_PHYSICAL_GPU;
typedef uint64_t GR_DEVICE;
typedef uint64_t GR_WSI_WIN_DISPLAY;
typedef uint64_t GR_QUEUE;
typedef uint64_t GR_IMAGE;
typedef uint64_t GR_GPU_MEMORY;
typedef uint64_t GR_CMD_BUFFER;
typedef uint64_t GR_FENCE;
typedef uint64_t GR_BASE_OBJECT;
typedef uint64_t GR_VIEWPORT_STATE_OBJECT;
typedef uint64_t GR_COLOR_TARGET_VIEW;
typedef uint64_t GR_DESCRIPTOR_SET;
typedef uint64_t GR_OBJECT;
typedef uint64_t GR_MSAA_STATE_OBJECT;
typedef uint64_t GR_SAMPLER;
typedef uint64_t GR_COLOR_BLEND_STATE_OBJECT;
typedef uint64_t GR_DEPTH_STENCIL_STATE_OBJECT;
typedef uint64_t GR_RASTER_STATE_OBJECT;
typedef uint64_t GR_SHADER;
typedef uint64_t GR_PIPELINE;
typedef uint64_t GR_IMAGE_VIEW;
typedef uint64_t GR_DEPTH_STENCIL_VIEW;
typedef uint64_t GR_STATE_OBJECT;

const uint64_t GR_NULL_HANDLE = 0;

const int GR_MAX_PHYSICAL_GPUS = 4;
const int GR_API_VERSION = 1;
const int GR_MAX_PHYSICAL_GPU_NAME = 255; // Guess
const int GR_MAX_VIEWPORTS = 16; // Guess
const int GR_MAX_MEMORY_HEAPS = 16; // Guess
const int GR_MAX_COLOR_TARGETS = 16; // Guess
const int GR_MAX_DESCRIPTOR_SETS = 2;

const GR_BOOL GR_TRUE = 1;
const GR_BOOL GR_FALSE = 0;

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

typedef enum _GR_MEMORY_PRIORITY {
	GR_MEMORY_PRIORITY_NORMAL = 0x1100,
	GR_MEMORY_PRIORITY_HIGH = 0x1101,
	GR_MEMORY_PRIORITY_LOW = 0x1102,
	GR_MEMORY_PRIORITY_UNUSED = 0x1103,
	GR_MEMORY_PRIORITY_VERY_HIGH = 0x1104,
	GR_MEMORY_PRIORITY_VERY_LOW = 0x1105,
} GR_MEMORY_PRIORITY;

typedef enum _GR_COMPARE_FUNC {
	GR_COMPARE_NEVER = 0x2500,
	GR_COMPARE_LESS = 0x2501,
	GR_COMPARE_EQUAL = 0x2502,
	GR_COMPARE_LESS_EQUAL = 0x2503,
	GR_COMPARE_GREATER = 0x2504,
	GR_COMPARE_NOT_EQUAL = 0x2505,
	GR_COMPARE_GREATER_EQUAL = 0x2506,
	GR_COMPARE_ALWAYS = 0x2507,
} GR_COMPARE_FUNC;

typedef struct _GR_DEPTH_STENCIL_OP {
	GR_ENUM stencilFailOp;
	GR_ENUM stencilPassOp;
	GR_ENUM stencilDepthFailOp;
	GR_ENUM stencilFunc;
	GR_UINT8 stencilRef;
} GR_DEPTH_STENCIL_OP;

typedef enum _GR_FILL_MODE {
	GR_FILL_SOLID = 0x2600,
	GR_FILL_WIREFRAME = 0x2601,
} GR_FILL_MODE;

typedef enum _GR_CULL_MODE {
	GR_CULL_NONE = 0x2700,
	GR_CULL_FRONT = 0x2701,
	GR_CULL_BACK = 0x2702,
} GR_CULL_MODE;

typedef enum _GR_FACE_ORIENTATION {
	GR_FRONT_FACE_CCW = 0x2800,
	GR_FRONT_FACE_CW = 0x2801,
} GR_FACE_ORIENTATION;

typedef enum _GR_DESCRIPTOR_SET_SLOT_TYPE {
	GR_SLOT_UNUSED = 0x1900,
	GR_SLOT_SHADER_RESOURCE,
	GR_SLOT_SHADER_UAV,
	GR_SLOT_SHADER_SAMPLER,
	GR_SLOT_NEXT_DESCRIPTOR_SET,
} GR_DESCRIPTOR_SET_SLOT_TYPE;

typedef enum _GR_STATE_BIND_POINT {
	GR_STATE_BIND_VIEWPORT = 0x1f00,
	GR_STATE_BIND_RASTER = 0x1f01,
	GR_STATE_BIND_DEPTH_STENCIL = 0x1f02,
	GR_STATE_BIND_COLOR_BLEND = 0x1f03,
	GR_STATE_BIND_MSAA = 0x1f04,
} GR_STATE_BIND_POINT;

typedef enum _GR_BLEND {
	GR_BLEND_ZERO = 0x2900,
	GR_BLEND_ONE = 0x2901,
	GR_BLEND_SRC_COLOR = 0x2902,
	GR_BLEND_ONE_MINUS_SRC_COLOR = 0x2903,
	GR_BLEND_DEST_COLOR = 0x2904,
	GR_BLEND_ONE_MINUS_DEST_COLOR = 0x2905,
	GR_BLEND_SRC_ALPHA = 0x2906,
	GR_BLEND_ONE_MINUS_SRC_ALPHA = 0x2907,
	GR_BLEND_DEST_ALPHA = 0x2908,
	GR_BLEND_ONE_MINUS_DEST_ALPHA = 0x2909,
	GR_BLEND_CONSTANT_COLOR = 0x290a,
	GR_BLEND_ONE_MINUS_CONSTANT_COLOR = 0x290b,
	GR_BLEND_CONSTANT_ALPHA = 0x290c,
	GR_BLEND_ONE_MINUS_CONSTANT_ALPHA = 0x290d,
	GR_BLEND_SRC_ALPHA_SATURATE = 0x290e,
	GR_BLEND_SRC1_COLOR = 0x290f,
	GR_BLEND_ONE_MINUS_SRC1_COLOR = 0x2910,
	GR_BLEND_SRC1_ALPHA = 0x2911,
	GR_BLEND_ONE_MINUS_SRC1_ALPHA = 0x2912,
} GR_BLEND;

typedef enum _GR_BLEND_FUNC {
	GR_BLEND_FUNC_ADD = 0x2a00,
	GR_BLEND_FUNC_SUBTRACT = 0x2a01,
	GR_BLEND_FUNC_REVERSE_SUBTRACT = 0x2a02,
	GR_BLEND_FUNC_MIN = 0x2a03,
	GR_BLEND_FUNC_MAX = 0x2a04,
} GR_BLEND_FUNC;

typedef enum _GR_STENCIL_OP {
	GR_STENCIL_OP_KEEP = 0x2b00,
	GR_STENCIL_OP_ZERO = 0x2b01,
	GR_STENCIL_OP_REPLACE = 0x2b02,
	GR_STENCIL_OP_INC_CLAMP = 0x2b03,
	GR_STENCIL_OP_DEC_CLAMP = 0x2b04,
	GR_STENCIL_OP_INVERT = 0x2b05,
	GR_STENCIL_OP_INC_WRAP = 0x2b06,
	GR_STENCIL_OP_DEC_WRAP = 0x2b07,
} GR_STENCIL_OP;

typedef enum _GR_INDEX_TYPE {
	GR_INDEX_16 = 0x2100,
	GR_INDEX_32 = 0x2101,
} GR_INDEX_TYPE;

typedef enum _GR_PIPELINE_BIND_POINT {
	GR_PIPELINE_BIND_POINT_COMPUTE = 0x1e00,
	GR_PIPELINE_BIND_POINT_GRAPHICS = 0x1e01,
} GR_PIPELINE_BIND_POINT;

typedef enum _GR_PRIMITIVE_TOPOLOGY {
	GR_TOPOLOGY_POINT_LIST = 0x2000,
	GR_TOPOLOGY_LINE_LIST = 0x2001,
	GR_TOPOLOGY_LINE_STRIP = 0x2002,
	GR_TOPOLOGY_TRIANGLE_LIST = 0x2003,
	GR_TOPOLOGY_TRIANGLE_STRIP = 0x2004,
	GR_TOPOLOGY_RECT_LIST = 0x2005,
	GR_TOPOLOGY_QUAD_LIST = 0x2006,
	GR_TOPOLOGY_QUAD_STRIP = 0x2007,
	GR_TOPOLOGY_LINE_LIST_ADJ = 0x2008,
	GR_TOPOLOGY_LINE_STRIP_ADJ = 0x2009,
	GR_TOPOLOGY_TRIANGLE_LIST_ADJ = 0x200a,
	GR_TOPOLOGY_TRIANGLE_STRIP_ADJ = 0x200b,
	GR_TOPOLOGY_PATCH = 0x200c,
} GR_PRIMITIVE_TOPOLOGY;

typedef enum _GR_LOGIC_OP {
	GR_LOGIC_OP_COPY = 0x2c00,
	GR_LOGIC_OP_CLEAR = 0x2c01,
	GR_LOGIC_OP_AND = 0x2c02,
	GR_LOGIC_OP_AND_REVERSE = 0x2c03,
	GR_LOGIC_OP_AND_INVERTED = 0x2c04,
	GR_LOGIC_OP_NOOP = 0x2c05,
	GR_LOGIC_OP_XOR = 0x2c06,
	GR_LOGIC_OP_OR = 0x2c07,
	GR_LOGIC_OP_NOR = 0x2c08,
	GR_LOGIC_OP_EQUIV = 0x2c09,
	GR_LOGIC_OP_INVERT = 0x2c0a,
	GR_LOGIC_OP_OR_REVERSE = 0x2c0b,
	GR_LOGIC_OP_COPY_INVERTED = 0x2c0c,
	GR_LOGIC_OP_OR_INVERTED = 0x2c0d,
	GR_LOGIC_OP_NAND = 0x2c0e,
	GR_LOGIC_OP_SET = 0x2c0f,
} GR_LOGIC_OP;

typedef enum _GR_SHADER_CREATE_FLAGS {
	GR_SHADER_CREATE_ALLOW_RE_Z = 0x00000001,
} GR_SHADER_CREATE_FLAGS;

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

typedef struct _GR_EXTENT3D {
	GR_INT width;
	GR_INT height;
	GR_INT depth;
} GR_EXTENT3D;

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

typedef struct _GR_VIEWPORT {
	GR_FLOAT originX;
	GR_FLOAT originY;
	GR_FLOAT width;
	GR_FLOAT height;
	GR_FLOAT minDepth;
	GR_FLOAT maxDepth;
} GR_VIEWPORT;

typedef struct _GR_OFFSET2D {
	GR_INT x;
	GR_INT y;
} GR_OFFSET2D;

typedef struct _GR_OFFSET3D {
	GR_INT x;
	GR_INT y;
	GR_INT z;
} GR_OFFSET3D;

typedef struct _GR_RECT {
	GR_OFFSET2D offset;
	GR_EXTENT2D extent;
} GR_RECT;

typedef struct _GR_VIEWPORT_STATE_CREATE_INFO {
	GR_UINT viewportCount;
	GR_BOOL scissorEnable;
	GR_VIEWPORT viewports[GR_MAX_VIEWPORTS];
	GR_RECT scissors[GR_MAX_VIEWPORTS];
} GR_VIEWPORT_STATE_CREATE_INFO;

typedef struct _GR_COLOR_TARGET_VIEW_CREATE_INFO {
	GR_IMAGE image;
	GR_FORMAT format;
	GR_UINT mipLevel;
	GR_UINT baseArraySlice;
	GR_UINT arraySize;
} GR_COLOR_TARGET_VIEW_CREATE_INFO;

typedef struct _GR_MEMORY_ALLOC_INFO {
	GR_GPU_SIZE size;
	GR_GPU_SIZE alignment;
	GR_FLAGS flags;
	GR_UINT heapCount;
	GR_UINT heaps[GR_MAX_MEMORY_HEAPS];
	GR_ENUM memPriority;
} GR_MEMORY_ALLOC_INFO;

typedef struct _GR_DESCRIPTOR_SET_CREATE_INFO {
	GR_UINT slots;
} GR_DESCRIPTOR_SET_CREATE_INFO;

typedef struct _GR_FENCE_CREATE_INFO {
	GR_FLAGS flags;
} GR_FENCE_CREATE_INFO;

typedef struct _GR_MSAA_STATE_CREATE_INFO {
	GR_UINT samples;
	GR_SAMPLE_MASK sampleMask;
} GR_MSAA_STATE_CREATE_INFO;

typedef struct _GR_SAMPLER_CREATE_INFO {
	GR_ENUM filter;
	GR_ENUM addressU;
	GR_ENUM addressV;
	GR_ENUM addressW;
	GR_FLOAT mipLodBias;
	GR_UINT maxAnisotropy;
	GR_ENUM compareFunc;
	GR_FLOAT minLod;
	GR_FLOAT maxLod;
	GR_ENUM borderColor;
} GR_SAMPLER_CREATE_INFO;

typedef struct _GR_COLOR_TARGET_BLEND_STATE {
	GR_BOOL blendEnable;
	GR_ENUM srcBlendColor;
	GR_ENUM destBlendColor;
	GR_ENUM blendFuncColor;
	GR_ENUM srcBlendAlpha;
	GR_ENUM destBlendAlpha;
	GR_ENUM blendFuncAlpha;
} GR_COLOR_TARGET_BLEND_STATE;

typedef struct _GR_COLOR_BLEND_STATE_CREATE_INFO {
	GR_COLOR_TARGET_BLEND_STATE target[GR_MAX_COLOR_TARGETS];
	GR_FLOAT blendConst[4];
} GR_COLOR_BLEND_STATE_CREATE_INFO;

typedef struct _GR_DEPTH_STENCIL_STATE_CREATE_INFO {
	GR_BOOL depthEnable;
	GR_BOOL depthWriteEnable;
	GR_ENUM depthFunc;
	GR_BOOL depthBoundsEnable;
	GR_FLOAT minDepth;
	GR_FLOAT maxDepth;
	GR_BOOL stencilEnable;
	GR_UINT8 stencilReadMask;
	GR_UINT8 stencilWriteMask;
	GR_DEPTH_STENCIL_OP front;
	GR_DEPTH_STENCIL_OP back;
} GR_DEPTH_STENCIL_STATE_CREATE_INFO;

typedef struct _GR_RASTER_STATE_CREATE_INFO {
	GR_ENUM fillMode;
	GR_ENUM cullMode;
	GR_ENUM frontFace;
	GR_INT depthBias;
	GR_FLOAT depthBiasClamp;
	GR_FLOAT slopeScaledDepthBias;
} GR_RASTER_STATE_CREATE_INFO;

typedef struct _GR_SHADER_CREATE_INFO {
	GR_SIZE codeSize;
	const GR_VOID* pCode;
	GR_FLAGS flags;
} GR_SHADER_CREATE_INFO;

typedef struct _GR_DESCRIPTOR_SLOT_INFO {
	GR_ENUM slotObjectType;
	union {
		GR_UINT shaderEntityIndex;
		const struct _GR_DESCRIPTOR_SET_MAPPING* pNextLevelSet;
	};
} GR_DESCRIPTOR_SLOT_INFO;

typedef struct _GR_DESCRIPTOR_SET_MAPPING {
	GR_UINT descriptorCount;
	const GR_DESCRIPTOR_SLOT_INFO* pDescriptorInfo;
} GR_DESCRIPTOR_SET_MAPPING;

typedef struct _GR_LINK_CONST_BUFFER {
	GR_UINT bufferId;
	GR_SIZE bufferSize;
	const GR_VOID* pBufferData;
} GR_LINK_CONST_BUFFER;

typedef struct _GR_DYNAMIC_MEMORY_VIEW_SLOT_INFO {
	GR_ENUM slotObjectType;
	GR_UINT shaderEntityIndex;
} GR_DYNAMIC_MEMORY_VIEW_SLOT_INFO;

typedef struct _GR_PIPELINE_SHADER {
	GR_SHADER shader;
	GR_DESCRIPTOR_SET_MAPPING descriptorSetMapping[GR_MAX_DESCRIPTOR_SETS];
	GR_UINT linkConstBufferCount;
	const GR_LINK_CONST_BUFFER* pLinkConstBufferInfo;
	GR_DYNAMIC_MEMORY_VIEW_SLOT_INFO dynamicMemoryViewMapping;
} GR_PIPELINE_SHADER;

typedef struct _GR_PIPELINE_IA_STATE {
	GR_ENUM topology;
	GR_BOOL disableVertexReuse;
} GR_PIPELINE_IA_STATE;

typedef struct _GR_PIPELINE_TESS_STATE {
	GR_UINT patchControlPoints;
	GR_FLOAT optimalTessFactor;
} GR_PIPELINE_TESS_STATE;

typedef struct _GR_PIPELINE_RS_STATE {
	GR_BOOL depthClipEnable;
} GR_PIPELINE_RS_STATE;

typedef struct _GR_PIPELINE_CB_TARGET_STATE {
	GR_BOOL blendEnable;
	GR_FORMAT format;
	GR_UINT8 channelWriteMask;
} GR_PIPELINE_CB_TARGET_STATE;

typedef struct _GR_PIPELINE_CB_STATE {
	GR_BOOL alphaToCoverageEnable;
	GR_BOOL dualSourceBlendEnable;
	GR_ENUM logicOp;
	GR_PIPELINE_CB_TARGET_STATE target[GR_MAX_COLOR_TARGETS];
} GR_PIPELINE_CB_STATE;

typedef struct _GR_PIPELINE_DB_STATE {
	GR_FORMAT format;
} GR_PIPELINE_DB_STATE;

typedef struct _GR_GRAPHICS_PIPELINE_CREATE_INFO {
	GR_PIPELINE_SHADER vs;
	GR_PIPELINE_SHADER hs;
	GR_PIPELINE_SHADER ds;
	GR_PIPELINE_SHADER gs;
	GR_PIPELINE_SHADER ps;
	GR_PIPELINE_IA_STATE iaState;
	GR_PIPELINE_TESS_STATE tessState;
	GR_PIPELINE_RS_STATE rsState;
	GR_PIPELINE_CB_STATE cbState;
	GR_PIPELINE_DB_STATE dbState;
	GR_FLAGS flags;
} GR_GRAPHICS_PIPELINE_CREATE_INFO;

typedef struct _GR_COMPUTE_PIPELINE_CREATE_INFO {
	GR_PIPELINE_SHADER cs;
	GR_FLAGS flags;
} GR_COMPUTE_PIPELINE_CREATE_INFO;

typedef struct _GR_MEMORY_VIEW_ATTACH_INFO {
	GR_GPU_MEMORY mem;
	GR_GPU_SIZE offset;
	GR_GPU_SIZE range;
	GR_GPU_SIZE stride;
	GR_FORMAT format;
	GR_ENUM state;
} GR_MEMORY_VIEW_ATTACH_INFO;

typedef struct _GR_IMAGE_CREATE_INFO {
	GR_ENUM imageType;
	GR_FORMAT format;
	GR_EXTENT3D extent;
	GR_UINT mipLevels;
	GR_UINT arraySize;
	GR_UINT samples;
	GR_ENUM tiling;
	GR_FLAGS usage;
	GR_FLAGS flags;
} GR_IMAGE_CREATE_INFO;

typedef struct _GR_CHANNEL_MAPPING {
	GR_ENUM r;
	GR_ENUM g;
	GR_ENUM b;
	GR_ENUM a;
} GR_CHANNEL_MAPPING;

typedef struct _GR_IMAGE_VIEW_CREATE_INFO {
	GR_IMAGE image;
	GR_ENUM viewType;
	GR_FORMAT format;
	GR_CHANNEL_MAPPING channels;
	GR_IMAGE_SUBRESOURCE_RANGE subresourceRange;
	GR_FLOAT minLod;
} GR_IMAGE_VIEW_CREATE_INFO;

typedef struct _GR_IMAGE_VIEW_ATTACH_INFO {
	GR_IMAGE_VIEW view;
	GR_ENUM state;
} GR_IMAGE_VIEW_ATTACH_INFO;

typedef struct _GR_IMAGE_SUBRESOURCE {
	GR_ENUM aspect;
	GR_UINT mipLevel;
	GR_UINT arraySlice;
} GR_IMAGE_SUBRESOURCE;

typedef struct _GR_MEMORY_STATE_TRANSITION {
	GR_GPU_MEMORY mem;
	GR_ENUM oldState;
	GR_ENUM newState;
	GR_GPU_SIZE offset;
	GR_GPU_SIZE regionSize;
} GR_MEMORY_STATE_TRANSITION;

typedef struct _GR_MEMORY_COPY {
	GR_GPU_SIZE srcOffset;
	GR_GPU_SIZE destOffset;
	GR_GPU_SIZE copySize;
} GR_MEMORY_COPY;

typedef struct _GR_IMAGE_COPY {
	GR_IMAGE_SUBRESOURCE srcSubresource;
	GR_OFFSET3D srcOffset;
	GR_IMAGE_SUBRESOURCE destSubresource;
	GR_OFFSET3D destOffset;
	GR_EXTENT3D extent;
} GR_IMAGE_COPY;

typedef struct _GR_COLOR_TARGET_BIND_INFO {
	GR_COLOR_TARGET_VIEW view;
	GR_ENUM colorTargetState;
} GR_COLOR_TARGET_BIND_INFO;

typedef struct _GR_DEPTH_STENCIL_BIND_INFO {
	GR_DEPTH_STENCIL_VIEW view;
	GR_ENUM depthState;
	GR_ENUM stencilState;
} GR_DEPTH_STENCIL_BIND_INFO;

typedef struct _GR_MEMORY_IMAGE_COPY {
	GR_GPU_SIZE memOffset;
	GR_IMAGE_SUBRESOURCE imageSubresource;
	GR_OFFSET3D imageOffset;
	GR_EXTENT3D imageExtent;
} GR_MEMORY_IMAGE_COPY;

typedef struct _GR_DESCRIPTOR_SET_ATTACH_INFO {
	GR_DESCRIPTOR_SET descriptorSet;
	GR_UINT slotOffset;
} GR_DESCRIPTOR_SET_ATTACH_INFO;

/*
API function pointers
*/

GR_RESULT(GR_STDCALL *grInitAndEnumerateGpus)(
	const GR_APPLICATION_INFO* pAppInfo,
	const GR_ALLOC_CALLBACKS* pAllocCb,
	GR_UINT* pGpuCount,
	GR_PHYSICAL_GPU gpus[GR_MAX_PHYSICAL_GPUS]);

GR_RESULT(GR_STDCALL *grGetGpuInfo)(
	GR_PHYSICAL_GPU gpu,
	GR_ENUM infoType,
	GR_SIZE* pDataSize,
	GR_VOID* pData);

GR_RESULT(GR_STDCALL *grGetExtensionSupport)(
	GR_PHYSICAL_GPU gpu,
	const GR_CHAR* pExtName);

GR_RESULT(GR_STDCALL *grCreateDevice)(
	GR_PHYSICAL_GPU gpu,
	const GR_DEVICE_CREATE_INFO* pCreateInfo,
	GR_DEVICE* pDevice);

GR_RESULT(GR_STDCALL *grWsiWinGetDisplays)(
	GR_DEVICE device,
	GR_UINT* pDisplayCount,
	GR_WSI_WIN_DISPLAY* pDisplayList);

GR_RESULT(GR_STDCALL *grWsiWinGetDisplayModeList)(
	GR_WSI_WIN_DISPLAY display,
	GR_UINT* pDisplayModeCount,
	GR_WSI_WIN_DISPLAY_MODE* pDisplayModeList);

GR_RESULT(GR_STDCALL *grGetDeviceQueue)(
	GR_DEVICE device,
	GR_ENUM queueType,
	GR_UINT queueId,
	GR_QUEUE* pQueue);

GR_RESULT(GR_STDCALL *grWsiWinCreatePresentableImage)(
	GR_DEVICE device,
	const GR_WSI_WIN_PRESENTABLE_IMAGE_CREATE_INFO* pCreateInfo,
	GR_IMAGE* pImage,
	GR_GPU_MEMORY* pMem);

GR_RESULT(GR_STDCALL *grCreateCommandBuffer)(
	GR_DEVICE device,
	const GR_CMD_BUFFER_CREATE_INFO* pCreateInfo,
	GR_CMD_BUFFER* pCmdBuffer);

GR_RESULT(GR_STDCALL *grBeginCommandBuffer)(
	GR_CMD_BUFFER cmdBuffer,
	GR_FLAGS flags);

GR_RESULT(GR_STDCALL *grEndCommandBuffer)(
	GR_CMD_BUFFER cmdBuffer);

GR_RESULT(GR_STDCALL *grQueueSubmit)(
	GR_QUEUE queue,
	GR_UINT cmdBufferCount,
	const GR_CMD_BUFFER* pCmdBuffers,
	GR_UINT memRefCount,
	const GR_MEMORY_REF* pMemRefs,
	GR_FENCE fence);

GR_VOID(GR_STDCALL *grCmdPrepareImages)(
	GR_CMD_BUFFER cmdBuffer,
	GR_UINT transitionCount,
	const GR_IMAGE_STATE_TRANSITION* pStateTransitions);

GR_VOID(GR_STDCALL *grCmdClearColorImage)(
	GR_CMD_BUFFER cmdBuffer,
	GR_IMAGE image,
	const GR_FLOAT color[4],
	GR_UINT rangeCount,
	const GR_IMAGE_SUBRESOURCE_RANGE* pRanges);

GR_RESULT(GR_STDCALL *grWsiWinQueuePresent)(
	GR_QUEUE queue,
	const GR_WSI_WIN_PRESENT_INFO* pPresentInfo);

GR_RESULT(GR_STDCALL *grDbgRegisterMsgCallback)(
	GR_DBG_MSG_CALLBACK_FUNCTION pfnMsgCallback,
	GR_VOID* pUserData);

GR_RESULT(GR_STDCALL *grCreateViewportState)(
	GR_DEVICE device,
	const GR_VIEWPORT_STATE_CREATE_INFO* pCreateInfo,
	GR_VIEWPORT_STATE_OBJECT* pState);

GR_RESULT(GR_STDCALL *grGetMemoryHeapCount)(
	GR_DEVICE device,
	GR_UINT* pCount);

GR_RESULT(GR_STDCALL *grCreateColorTargetView)(
	GR_DEVICE device,
	const GR_COLOR_TARGET_VIEW_CREATE_INFO* pCreateInfo,
	GR_COLOR_TARGET_VIEW* pView);

GR_RESULT(GR_STDCALL *grGetMemoryHeapInfo)(
	GR_DEVICE device,
	GR_UINT heapId,
	GR_ENUM infoType,
	GR_SIZE* pDataSize,
	GR_VOID* pData);

GR_RESULT(GR_STDCALL *grAllocMemory)(
	GR_DEVICE device,
	const GR_MEMORY_ALLOC_INFO* pAllocInfo,
	GR_GPU_MEMORY* pMem);

GR_RESULT(GR_STDCALL *grCreateDescriptorSet)(
	GR_DEVICE device,
	const GR_DESCRIPTOR_SET_CREATE_INFO* pCreateInfo,
	GR_DESCRIPTOR_SET* pDescriptorSet);

GR_RESULT(GR_STDCALL *grGetObjectInfo)(
	GR_BASE_OBJECT object,
	GR_ENUM infoType,
	GR_SIZE* pDataSize,
	GR_VOID* pData);

GR_RESULT(GR_STDCALL *grBindObjectMemory)(
	GR_OBJECT object,
	GR_GPU_MEMORY mem,
	GR_GPU_SIZE offset);

GR_RESULT(GR_STDCALL *grCreateFence)(
	GR_DEVICE device,
	const GR_FENCE_CREATE_INFO* pCreateInfo,
	GR_FENCE* pFence);

GR_RESULT(GR_STDCALL *grCreateMsaaState)(
	GR_DEVICE device,
	const GR_MSAA_STATE_CREATE_INFO* pCreateInfo,
	GR_MSAA_STATE_OBJECT* pState);

GR_RESULT(GR_STDCALL *grCreateSampler)(
	GR_DEVICE device,
	const GR_SAMPLER_CREATE_INFO* pCreateInfo,
	GR_SAMPLER* pSampler);

GR_VOID(GR_STDCALL *grBeginDescriptorSetUpdate)(
	GR_DESCRIPTOR_SET descriptorSet);

GR_VOID(GR_STDCALL *grEndDescriptorSetUpdate)(
	GR_DESCRIPTOR_SET descriptorSet);

GR_VOID(GR_STDCALL *grAttachSamplerDescriptors)(
	GR_DESCRIPTOR_SET descriptorSet,
	GR_UINT startSlot,
	GR_UINT slotCount,
	const GR_SAMPLER* pSamplers);

GR_RESULT(GR_STDCALL *grCreateColorBlendState)(
	GR_DEVICE device,
	const GR_COLOR_BLEND_STATE_CREATE_INFO* pCreateInfo,
	GR_COLOR_BLEND_STATE_OBJECT* pState);

GR_RESULT(GR_STDCALL *grCreateDepthStencilState)(
	GR_DEVICE device,
	const GR_DEPTH_STENCIL_STATE_CREATE_INFO* pCreateInfo,
	GR_DEPTH_STENCIL_STATE_OBJECT* pState);

GR_RESULT(GR_STDCALL *grCreateRasterState)(
	GR_DEVICE device,
	const GR_RASTER_STATE_CREATE_INFO* pCreateInfo,
	GR_RASTER_STATE_OBJECT* pState);

GR_RESULT(GR_STDCALL *grMapMemory)(
	GR_GPU_MEMORY mem,
	GR_FLAGS flags,
	GR_VOID** ppData);

GR_RESULT(GR_STDCALL *grUnmapMemory)(
	GR_GPU_MEMORY mem);

GR_RESULT(GR_STDCALL *grCreateShader)(
	GR_DEVICE device,
	const GR_SHADER_CREATE_INFO* pCreateInfo,
	GR_SHADER* pShader);

GR_RESULT(GR_STDCALL *grCreateGraphicsPipeline)(
	GR_DEVICE device,
	const GR_GRAPHICS_PIPELINE_CREATE_INFO* pCreateInfo,
	GR_PIPELINE* pPipeline);

GR_RESULT(GR_STDCALL *grCreateComputePipeline)(
	GR_DEVICE device,
	const GR_COMPUTE_PIPELINE_CREATE_INFO* pCreateInfo,
	GR_PIPELINE* pPipeline);

GR_VOID(GR_STDCALL *grClearDescriptorSetSlots)(
	GR_DESCRIPTOR_SET descriptorSet,
	GR_UINT startSlot,
	GR_UINT slotCount);

GR_VOID(GR_STDCALL *grAttachMemoryViewDescriptors)(
	GR_DESCRIPTOR_SET descriptorSet,
	GR_UINT startSlot,
	GR_UINT slotCount,
	const GR_MEMORY_VIEW_ATTACH_INFO* pMemViews);

GR_RESULT(GR_STDCALL *grWaitForFences)(
	GR_DEVICE device,
	GR_UINT fenceCount,
	const GR_FENCE* pFences,
	GR_BOOL waitAll,
	GR_FLOAT timeout);

GR_RESULT(GR_STDCALL *grCreateImage)(
	GR_DEVICE device,
	const GR_IMAGE_CREATE_INFO* pCreateInfo,
	GR_IMAGE* pImage);

GR_RESULT(GR_STDCALL *grDestroyObject)(
	GR_OBJECT object);

GR_RESULT(GR_STDCALL *grCreateImageView)(
	GR_DEVICE device,
	const GR_IMAGE_VIEW_CREATE_INFO* pCreateInfo,
	GR_IMAGE_VIEW* pView);

GR_VOID(GR_STDCALL *grAttachImageViewDescriptors)(
	GR_DESCRIPTOR_SET descriptorSet,
	GR_UINT startSlot,
	GR_UINT slotCount,
	const GR_IMAGE_VIEW_ATTACH_INFO* pImageViews);

GR_RESULT(GR_STDCALL *grGetImageSubresourceInfo)(
	GR_IMAGE image,
	const GR_IMAGE_SUBRESOURCE* pSubresource,
	GR_ENUM infoType,
	GR_SIZE* pDataSize,
	GR_VOID* pData);

GR_RESULT(GR_STDCALL *grResetCommandBuffer)(
	GR_CMD_BUFFER cmdBuffer);

GR_VOID(GR_STDCALL *grCmdPrepareMemoryRegions)(
	GR_CMD_BUFFER cmdBuffer,
	GR_UINT transitionCount,
	const GR_MEMORY_STATE_TRANSITION* pStateTransitions);

GR_VOID(GR_STDCALL *grCmdCopyMemory)(
	GR_CMD_BUFFER cmdBuffer,
	GR_GPU_MEMORY srcMem,
	GR_GPU_MEMORY destMem,
	GR_UINT regionCount,
	const GR_MEMORY_COPY* pRegions);

GR_VOID(GR_STDCALL *grCmdCopyImage)(
	GR_CMD_BUFFER cmdBuffer,
	GR_IMAGE srcImage,
	GR_IMAGE destImage,
	GR_UINT regionCount,
	const GR_IMAGE_COPY* pRegions);

GR_VOID(GR_STDCALL *grCmdBindTargets)(
	GR_CMD_BUFFER cmdBuffer,
	GR_UINT colorTargetCount,
	const GR_COLOR_TARGET_BIND_INFO* pColorTargets,
	const GR_DEPTH_STENCIL_BIND_INFO* pDepthTarget);

GR_VOID(GR_STDCALL *grCmdBindStateObject)(
	GR_CMD_BUFFER cmdBuffer,
	GR_ENUM stateBindPoint,
	GR_STATE_OBJECT state);

GR_RESULT(GR_STDCALL *grFreeMemory)(
	GR_GPU_MEMORY mem);

GR_VOID(GR_STDCALL *grCmdCopyMemoryToImage)(
	GR_CMD_BUFFER cmdBuffer,
	GR_GPU_MEMORY srcMem,
	GR_IMAGE destImage,
	GR_UINT regionCount,
	const GR_MEMORY_IMAGE_COPY* pRegions);

GR_VOID(GR_STDCALL *grAttachNestedDescriptors)(
	GR_DESCRIPTOR_SET descriptorSet,
	GR_UINT startSlot,
	GR_UINT slotCount,
	const GR_DESCRIPTOR_SET_ATTACH_INFO* pNestedDescriptorSets);

GR_VOID(GR_STDCALL *grCmdBindDescriptorSet)(
	GR_CMD_BUFFER cmdBuffer,
	GR_ENUM pipelineBindPoint,
	GR_UINT index,
	GR_DESCRIPTOR_SET descriptorSet,
	GR_UINT slotOffset);

GR_VOID(GR_STDCALL *grCmdBindIndexData)(
	GR_CMD_BUFFER cmdBuffer,
	GR_GPU_MEMORY mem,
	GR_GPU_SIZE offset,
	GR_ENUM indexType);

GR_VOID(GR_STDCALL *grCmdBindPipeline)(
	GR_CMD_BUFFER cmdBuffer,
	GR_ENUM pipelineBindPoint,
	GR_PIPELINE pipeline);

GR_VOID(GR_STDCALL *grCmdDrawIndexed)(
	GR_CMD_BUFFER cmdBuffer,
	GR_UINT firstIndex,
	GR_UINT indexCount,
	GR_INT vertexOffset,
	GR_UINT firstInstance,
	GR_UINT instanceCount);

GR_VOID(GR_STDCALL *grCmdBindDynamicMemoryView)(
	GR_CMD_BUFFER cmdBuffer,
	GR_ENUM pipelineBindPoint,
	const GR_MEMORY_VIEW_ATTACH_INFO* pMemView);

GR_VOID(GR_STDCALL *grCmdDispatch)(
	GR_CMD_BUFFER cmdBuffer,
	GR_UINT x,
	GR_UINT y,
	GR_UINT z);

GR_VOID(GR_STDCALL *grCmdDraw)(
	GR_CMD_BUFFER cmdBuffer,
	GR_UINT firstVertex,
	GR_UINT vertexCount,
	GR_UINT firstInstance,
	GR_UINT instanceCount);

#define LOAD_PROC(fnCheck, module, var)\
{\
    var = (decltype(var)) GetProcAddress(module, #var);\
    if (!var) fnCheck = false;\
}\

// Applications should call this at the beginning of the program
bool mantleLoadFunctions() {
	static bool loaded = false;
	if (loaded) return true;
	loaded = true;

	HMODULE mantleDll = LoadLibrary(TEXT("C:/Windows/System32/mantle64.dll"));
	if (!mantleDll) return false;

	bool fnCheck = true;

	LOAD_PROC(fnCheck, mantleDll, grCreateViewportState);
	LOAD_PROC(fnCheck, mantleDll, grDbgRegisterMsgCallback);
	LOAD_PROC(fnCheck, mantleDll, grInitAndEnumerateGpus);
	LOAD_PROC(fnCheck, mantleDll, grGetGpuInfo);
	LOAD_PROC(fnCheck, mantleDll, grGetExtensionSupport);
	LOAD_PROC(fnCheck, mantleDll, grCreateDevice);
	LOAD_PROC(fnCheck, mantleDll, grGetDeviceQueue);
	LOAD_PROC(fnCheck, mantleDll, grCreateCommandBuffer);
	LOAD_PROC(fnCheck, mantleDll, grBeginCommandBuffer);
	LOAD_PROC(fnCheck, mantleDll, grEndCommandBuffer);
	LOAD_PROC(fnCheck, mantleDll, grQueueSubmit);
	LOAD_PROC(fnCheck, mantleDll, grCmdPrepareImages);
	LOAD_PROC(fnCheck, mantleDll, grCmdClearColorImage);
	LOAD_PROC(fnCheck, mantleDll, grGetMemoryHeapCount);
	LOAD_PROC(fnCheck, mantleDll, grCreateColorTargetView);
	LOAD_PROC(fnCheck, mantleDll, grGetMemoryHeapInfo);
	LOAD_PROC(fnCheck, mantleDll, grAllocMemory);
	LOAD_PROC(fnCheck, mantleDll, grCreateDescriptorSet);
	LOAD_PROC(fnCheck, mantleDll, grGetObjectInfo);
	LOAD_PROC(fnCheck, mantleDll, grBindObjectMemory);
	LOAD_PROC(fnCheck, mantleDll, grCreateFence);
	LOAD_PROC(fnCheck, mantleDll, grCreateMsaaState);
	LOAD_PROC(fnCheck, mantleDll, grCreateSampler);
	LOAD_PROC(fnCheck, mantleDll, grBeginDescriptorSetUpdate);
	LOAD_PROC(fnCheck, mantleDll, grEndDescriptorSetUpdate);
	LOAD_PROC(fnCheck, mantleDll, grAttachSamplerDescriptors);
	LOAD_PROC(fnCheck, mantleDll, grCreateColorBlendState);
	LOAD_PROC(fnCheck, mantleDll, grCreateDepthStencilState);
	LOAD_PROC(fnCheck, mantleDll, grCreateRasterState);
	LOAD_PROC(fnCheck, mantleDll, grMapMemory);
	LOAD_PROC(fnCheck, mantleDll, grUnmapMemory);
	LOAD_PROC(fnCheck, mantleDll, grCreateShader);
	LOAD_PROC(fnCheck, mantleDll, grCreateGraphicsPipeline);
	LOAD_PROC(fnCheck, mantleDll, grCreateComputePipeline);
	LOAD_PROC(fnCheck, mantleDll, grClearDescriptorSetSlots);
	LOAD_PROC(fnCheck, mantleDll, grAttachMemoryViewDescriptors);
	LOAD_PROC(fnCheck, mantleDll, grWaitForFences);
	LOAD_PROC(fnCheck, mantleDll, grCreateImage);
	LOAD_PROC(fnCheck, mantleDll, grDestroyObject);
	LOAD_PROC(fnCheck, mantleDll, grCreateImageView);
	LOAD_PROC(fnCheck, mantleDll, grAttachImageViewDescriptors);
	LOAD_PROC(fnCheck, mantleDll, grGetImageSubresourceInfo);
	LOAD_PROC(fnCheck, mantleDll, grResetCommandBuffer);
	LOAD_PROC(fnCheck, mantleDll, grCmdPrepareMemoryRegions);
	LOAD_PROC(fnCheck, mantleDll, grCmdCopyMemory);
	LOAD_PROC(fnCheck, mantleDll, grCmdCopyImage);
	LOAD_PROC(fnCheck, mantleDll, grCmdBindTargets);
	LOAD_PROC(fnCheck, mantleDll, grCmdBindStateObject);
	LOAD_PROC(fnCheck, mantleDll, grFreeMemory);
	LOAD_PROC(fnCheck, mantleDll, grCmdCopyMemoryToImage);
	LOAD_PROC(fnCheck, mantleDll, grAttachNestedDescriptors);
	LOAD_PROC(fnCheck, mantleDll, grCmdBindDescriptorSet);
	LOAD_PROC(fnCheck, mantleDll, grCmdBindIndexData);
	LOAD_PROC(fnCheck, mantleDll, grCmdBindPipeline);
	LOAD_PROC(fnCheck, mantleDll, grCmdDrawIndexed);
	LOAD_PROC(fnCheck, mantleDll, grCmdBindDynamicMemoryView);
	LOAD_PROC(fnCheck, mantleDll, grCmdDispatch);
	LOAD_PROC(fnCheck, mantleDll, grCmdDraw);

	LOAD_PROC(fnCheck, mantleDll, grWsiWinGetDisplays);
	LOAD_PROC(fnCheck, mantleDll, grWsiWinGetDisplayModeList);
	LOAD_PROC(fnCheck, mantleDll, grWsiWinCreatePresentableImage);
	LOAD_PROC(fnCheck, mantleDll, grWsiWinQueuePresent);

	return fnCheck;
}

#endif
