
// Craftin_In_C (2023)
// GITHUB : https://github.com/CraftingInC/CRASHOS-EFI-Bootloader

/* This EFI Header is updated as of version 2.10 */

#ifndef EFI_H
#define EFI_H

#include <stdint.h>
#include <stdbool.h>

// DEFINES
#define CONST                                const
#define EFI_SUCCESS                          0x00000000000000
#define EFI_IMAGE_MACHINE_x64                0x8664

#define EFI_BLACK                            0x00
#define EFI_BLUE                             0x01
#define EFI_GREEN                            0x02
#define EFI_CYAN                             0x03
#define EFI_RED                              0x04
#define EFI_MAGENTA                          0x05
#define EFI_BROWN                            0x06
#define EFI_LIGHTGRAY                        0x07
#define EFI_BRIGHT                           0x08
#define EFI_LIGHTBLUE                        0x09
#define EFI_LIGHTGREEN                       0x0A
#define EFI_LIGHTCYAN                        0x0B
#define EFI_LIGHTRED                         0x0C
#define EFI_LIGHTMAGENTA                     0x0D
#define EFI_YELLOW                           0x0E
#define EFI_WHITE                            0x0F
#define EFI_BACKGROUND_BLACK                 0x00
#define EFI_BACKGROUND_BLUE                  0x10
#define EFI_BACKGROUND_GREEN                 0x20
#define EFI_BACKGROUND_CYAN                  0x30

#define EFI_FILE_MODE_READ    0x0000000000000001
#define EFI_FILE_MODE_WRITE   0x0000000000000002
#define EFI_FILE_MODE_CREATE  0x8000000000000000
//******************************************************
// File Attributes
//******************************************************
#define EFI_FILE_READ_ONLY    0x0000000000000001
#define EFI_FILE_HIDDEN       0x0000000000000002
#define EFI_FILE_SYSTEM       0x0000000000000004
#define EFI_FILE_RESERVED     0x0000000000000008
#define EFI_FILE_DIRECTORY    0x0000000000000010
#define EFI_FILE_ARCHIVE      0x0000000000000020
#define EFI_FILE_VALID_ATTR   0x0000000000000037

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000
//******************************************************
// File Attributes
//******************************************************
#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037


// TYPEDEFS
typedef void              VOID;
typedef void*             VOIDP;
typedef uint8_t           UINT8;
typedef uint16_t          UINT16;
typedef uint32_t          UINT32;
typedef uint64_t          UINT64;
typedef int32_t           INT32;
typedef long long         INTN;
typedef uint64_t          UINTN;
typedef uint_least16_t    CHAR16;
typedef bool              BOOLEAN;

typedef VOIDP             EFI_EVENT;
typedef VOIDP             EFI_HANDLE;
typedef UINT64            EFI_STATUS;
typedef UINTN             EFI_TPL;
typedef UINT64            EFI_PHYSICAL_ADDRESS;
typedef UINT64            EFI_VIRTUAL_ADDRESS;

// ENUMS
typedef enum {
	AllocateAnyPages,     // This is 0
	AllocateMaxAddress,
	AllocateAddress,      // 2
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiUnacceptedMemoryType,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef enum {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
} EFI_TIMER_DELAY;

typedef enum {
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef enum {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef enum {
	EfiBltVideoFill,
	EfiBltVideoToBltBuffer,
	EfiBltBufferToVideo,
	EfiBltVideoToVideo,
	EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;


// FORWARD DELCARES
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct EFI_INPUT_KEY;
struct EFI_MEMORY_DESCRIPTOR;
struct EFI_DEVICE_PATH_PROTOCOL;
struct EFI_GUID;
struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;
struct EFI_LOAD_FILE_PROTOCOL;
struct EFI_FILE_PROTOCOL;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
struct EFI_FILE_IO_TOKEN;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL;
struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;
struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL;


// FUNCTIONS
typedef EFI_STATUS (*EFI_INPUT_RESET) (struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);
typedef EFI_STATUS (*EFI_INPUT_READ_KEY) (struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, struct EFI_INPUT_KEY *Key);
typedef EFI_STATUS (*EFI_TEXT_RESET) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);
typedef EFI_STATUS (*EFI_TEXT_STRING) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);
typedef EFI_TPL    (*EFI_RAISE_TPL) (EFI_TPL NewTpl);
typedef VOID       (*EFI_RESTORE_TPL) (EFI_TPL OldTpl);
typedef EFI_STATUS (*EFI_ALLOCATE_PAGES) (EFI_ALLOCATE_TYPE Type, EFI_MEMORY_TYPE MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS *Memory);
typedef EFI_STATUS (*EFI_FREE_PAGES) (EFI_PHYSICAL_ADDRESS Memory, UINTN Pages);
typedef EFI_STATUS (*EFI_GET_MEMORY_MAP) (UINTN *MemoryMapSize, struct EFI_MEMORY_DESCRIPTOR *MemoryMap, UINTN *MapKey, UINTN *DescriptorSize, UINT32 *DescriptorVersion);
typedef EFI_STATUS (*EFI_ALLOCATE_POOL) (EFI_MEMORY_TYPE PoolType, UINTN Size, VOID **Buffer);
typedef EFI_STATUS (*EFI_FREE_POOL) (VOID *Buffer);
typedef VOID       (*EFI_EVENT_NOTIFY) (EFI_EVENT Event, VOID *Context);
typedef EFI_STATUS (*EFI_CREATE_EVENT) (UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, VOID *NotifyContext, EFI_EVENT *Event);
typedef EFI_STATUS (*EFI_SET_TIMER) (EFI_EVENT Event, EFI_TIMER_DELAY Type, UINT64 TriggerTime);
typedef EFI_STATUS (*EFI_WAIT_FOR_EVENT) (UINTN NumberOfEvents, EFI_EVENT *Event, UINTN *Index);
typedef EFI_STATUS (*EFI_TEXT_TEST_STRING) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);
typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber, UINTN *Columns, UINTN *Rows);
typedef EFI_STATUS (*EFI_TEXT_SET_MODE) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber);
typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Attribute);
typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Column, UINTN Row);
typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN Visible);
typedef EFI_STATUS (*EFI_SIGNAL_EVENT) (EFI_EVENT Event);
typedef EFI_STATUS (*EFI_CLOSE_EVENT) (EFI_EVENT Event);
typedef EFI_STATUS (*EFI_CHECK_EVENT) (EFI_EVENT Event);
typedef EFI_STATUS (*EFI_INSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE *Handle, struct EFI_GUID *Protocol, EFI_INTERFACE_TYPE InterfaceType, VOID *Interface);
typedef EFI_STATUS (*EFI_REINSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE Handle, struct EFI_GUID *Protocol, VOID *OldInterface, VOID *NewInterface);
typedef EFI_STATUS (*EFI_UNINSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE Handle, struct EFI_GUID *Protocol, VOID *Interface);
typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL) (EFI_HANDLE Handle, struct EFI_GUID *Protocol, VOID **Interface);
typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY) (struct EFI_GUID *Protocol, EFI_EVENT Event, VOID **Registration);
typedef EFI_STATUS (*EFI_LOCATE_HANDLE) (EFI_LOCATE_SEARCH_TYPE SearchType, struct EFI_GUID *Protocol, VOID *SearchKey, UINTN *BufferSize, EFI_HANDLE *Buffer);
typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH) (struct EFI_GUID *Protocol, struct EFI_DEVICE_PATH_PROTOCOL **DevicePath, EFI_HANDLE *Device);
typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE) (struct EFI_GUID *Guid, VOID *Table);
typedef EFI_STATUS (*EFI_IMAGE_UNLOAD) (EFI_HANDLE ImageHandle);
typedef EFI_STATUS (*EFI_IMAGE_START) (EFI_HANDLE ImageHandle, UINTN *ExitDataSize, CHAR16 **ExitData);
typedef EFI_STATUS (*EFI_EXIT) (EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus, UINTN ExitDataSize, CHAR16 *ExitData);
typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES) (EFI_HANDLE ImageHandle, UINTN MapKey);
typedef EFI_STATUS (*EFI_GET_NEXT_MONOTONIC_COUNT) (UINT64 *Count);
typedef EFI_STATUS (*EFI_STALL) (UINTN Microseconds);
typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER) (UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize, CHAR16 *WatchdogData);
typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER) (EFI_HANDLE ControllerHandle, EFI_HANDLE *DriverImageHandle, struct EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, BOOLEAN Recursive);
typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER) (EFI_HANDLE ControllerHandle, EFI_HANDLE DriverImageHandle, EFI_HANDLE ChildHandle);
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL) (EFI_HANDLE Handle, struct EFI_GUID *Protocol, VOID **Interface, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle, UINT32 Attributes);
typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL) (EFI_HANDLE Handle, struct EFI_GUID *Protocol, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle);
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION) (EFI_HANDLE Handle, struct EFI_GUID *Protocol, struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer, UINTN *EntryCount);
typedef EFI_STATUS (*EFI_PROTOCOLS_PER_HANDLE) (EFI_HANDLE Handle, struct EFI_GUID ***ProtocolBuffer, UINTN *ProtocolBufferCount);
typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER) (EFI_LOCATE_SEARCH_TYPE SearchType, struct EFI_GUID *Protocol, VOID *SearchKey, UINTN *NoHandles, EFI_HANDLE **Buffer);
typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL) (struct EFI_GUID *Protocol, VOID *Registration, VOID **Interface);
typedef EFI_STATUS (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (EFI_HANDLE Handle, ... );
typedef EFI_STATUS (*EFI_CALCULATE_CRC32) (VOID *Data, UINTN DataSize, UINT32 *Crc32);
typedef VOID       (*EFI_COPY_MEM) (VOID *Destination, VOID *Source, UINTN Length);
typedef VOID       (*EFI_SET_MEM) (VOID *Buffer, UINTN Size, UINT8 Value);
typedef EFI_STATUS (*EFI_CREATE_EVENT_EX) (UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, CONST VOID *NotifyContext, CONST struct EFI_GUID *EventGroup, EFI_EVENT *Event);
typedef EFI_STATUS (*EFI_LOAD_FILE) (struct EFI_LOAD_FILE_PROTOCOL *This, struct EFI_DEVICE_PATH_PROTOCOL *FilePath, BOOLEAN BootPolicy, UINTN *BufferSize, VOID *Buffer);
typedef EFI_STATUS (*EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME) (struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, struct EFI_FILE_PROTOCOL **Root);
typedef EFI_STATUS (*EFI_FILE_OPEN) (struct EFI_FILE_PROTOCOL *This, struct EFI_FILE_PROTOCOL **NewHandle, CHAR16 *FileName, UINT64 OpenMode, UINT64 Attributes);
typedef EFI_STATUS (*EFI_FILE_CLOSE) (struct EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS (*EFI_FILE_DELETE) (struct EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS (*EFI_FILE_READ) (struct EFI_FILE_PROTOCOL *This, UINTN *BufferSize, VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_WRITE) (struct EFI_FILE_PROTOCOL *This, UINTN *BufferSize, VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_GET_POSITION) (struct EFI_FILE_PROTOCOL *This, UINT64 *Position);
typedef EFI_STATUS (*EFI_FILE_SET_POSITION) (struct EFI_FILE_PROTOCOL *This, UINT64 Position);
typedef EFI_STATUS (*EFI_FILE_GET_INFO) (struct EFI_FILE_PROTOCOL *This, struct EFI_GUID *InformationType, UINTN *BufferSize, VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_SET_INFO) (struct EFI_FILE_PROTOCOL *This, struct EFI_GUID *InformationType, UINTN BufferSize, VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_FLUSH) (struct EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS (*EFI_FILE_OPEN_EX) (struct EFI_FILE_PROTOCOL *This, struct EFI_FILE_PROTOCOL **NewHandle, CHAR16 *FileName, UINT64 OpenMode, UINT64 Attributes, struct EFI_FILE_IO_TOKEN *Token);
typedef EFI_STATUS (*EFI_FILE_READ_EX) (struct EFI_FILE_PROTOCOL *This,struct EFI_FILE_IO_TOKEN *Token);
typedef EFI_STATUS (*EFI_FILE_WRITE_EX) (struct EFI_FILE_PROTOCOL *This, struct EFI_FILE_IO_TOKEN *Token);
typedef EFI_STATUS (*EFI_FILE_FLUSH_EX) (struct EFI_FILE_PROTOCOL *This, struct EFI_FILE_IO_TOKEN *Token);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, UINT32 ModeNumber, UINTN *SizeOfInfo, struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, UINT32 ModeNumber);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, UINTN SourceX, UINTN SourceY, UINTN DestinationX, UINTN DestinationY, UINTN Width, UINTN Height, UINTN Delta);


// STRUCTS
typedef struct EFI_INPUT_KEY
{
	UINT16   ScanCode;
	CHAR16   UnicodeChar;
} EFI_INPUT_KEY;

typedef struct EFI_TABLE_HEADER
{
	UINT64   Signature;
	UINT32   Revision;
	UINT32   HeaderSize;
	UINT32   CRC32;
	UINT32   Reserved;
} EFI_TABLE_HEADER;

typedef struct EFI_GUID
{
	UINT32   Data1;
	UINT16   Data2;
	UINT16   Data3;
	UINT8    Data4[8];
} EFI_GUID;

typedef struct EFI_DEVICE_PATH_PROTOCOL
{
	UINT8    Type;
	UINT8    SubType;
	UINT8    Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct EFI_FILE_IO_TOKEN
{
	EFI_EVENT    Event;
	EFI_STATUS   Status;
	UINTN        BufferSize;
	VOIDP        Buffer;
} EFI_FILE_IO_TOKEN;

typedef struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
{
	EFI_HANDLE   AgentHandle;
	EFI_HANDLE   ControllerHandle;
	UINT32       Attributes;
	UINT32       OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef struct EFI_MEMORY_DESCRIPTOR
{
	UINT32                 Type;
	EFI_PHYSICAL_ADDRESS   PhysicalStart;
	EFI_VIRTUAL_ADDRESS    VirtualStart;
	UINT64                 NumberOfPages;
	UINT64                 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET       Reset;
	EFI_INPUT_READ_KEY    ReadKeyStroke;
	EFI_EVENT             WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct SIMPLE_TEXT_OUTPUT_MODE
{
	INT32       MaxMode;
	// current settings
	INT32       Mode;
	INT32       Attribute;
	INT32       CursorColumn;
	INT32       CursorRow;
	BOOLEAN     CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
	EFI_TEXT_RESET                Reset;
	EFI_TEXT_STRING               OutputString;
 	EFI_TEXT_TEST_STRING          TestString;
 	EFI_TEXT_QUERY_MODE           QueryMode;
 	EFI_TEXT_SET_MODE             SetMode;
 	EFI_TEXT_SET_ATTRIBUTE        SetAttribute;
	EFI_TEXT_CLEAR_SCREEN         ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION  SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR        EnableCursor;
	SIMPLE_TEXT_OUTPUT_MODE       *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct EFI_RUNTIME_SERVICES   // PLaced here for now. Just neede to be able to compile.
{
	EFI_TABLE_HEADER Hdr;
	//
	// Time Services
	//
//	EFI_GET_TIME GetTime;
//	EFI_SET_TIME SetTime;
//	EFI_GET_WAKEUP_TIME GetWakeupTime;
//	EFI_SET_WAKEUP_TIME SetWakeupTime;
//	//
//	// Virtual Memory Services
//	//
//	EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
//	EFI_CONVERT_POINTER ConvertPointer;
//	//
//	// Variable Services
//	//
//	EFI_GET_VARIABLE GetVariable;
//	EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
//	EFI_SET_VARIABLE SetVariable;
//	//
//	// Miscellaneous Services
//	//
//	EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
//	EFI_RESET_SYSTEM ResetSystem;
//	//
//	// UEFI 2.0 Capsule Services
//	//
//	EFI_UPDATE_CAPSULE UpdateCapsule;
//	EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;
//	EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

typedef struct EFI_CONFIGURATION_TABLE
{
	EFI_GUID   VendorGuid;
	VOIDP      VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct EFI_FILE_PROTOCOL
{
	UINT64                    Revision;
	EFI_FILE_OPEN             Open;
	EFI_FILE_CLOSE            Close;
	EFI_FILE_DELETE           Delete;
	EFI_FILE_READ             Read;
	EFI_FILE_WRITE            Write;
	EFI_FILE_GET_POSITION     GetPosition;
	EFI_FILE_SET_POSITION     SetPosition;
	EFI_FILE_GET_INFO         GetInfo;
	EFI_FILE_SET_INFO         SetInfo;
	EFI_FILE_FLUSH            Flush;
	EFI_FILE_OPEN_EX          OpenEx; // Added for revision 2
	EFI_FILE_READ_EX          ReadEx; // Added for revision 2
	EFI_FILE_WRITE_EX         WriteEx; // Added for revision 2
	EFI_FILE_FLUSH_EX         FlushEx; // Added for revision 2
} EFI_FILE_PROTOCOL;

typedef struct EFI_LOAD_FILE_PROTOCOL
{
    EFI_LOAD_FILE                              LoadFile;
} EFI_LOAD_FILE_PROTOCOL;

typedef EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE2_PROTOCOL;

typedef struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL                  // PAGE 449  Come back to this
{
    UINT64                                        Revision;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME   OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef struct EFI_BOOT_SERVICES
{
    EFI_TABLE_HEADER                            Hdr;
    //
    // Task Priority Services
    //
    EFI_RAISE_TPL                               RaiseTPL;
    EFI_RESTORE_TPL                             RestoreTPL;
    //
    // Memory Services
    //
    EFI_ALLOCATE_PAGES                          AllocatePages;
    EFI_FREE_PAGES                              FreePages;
    EFI_GET_MEMORY_MAP                          GetMemoryMap;
    EFI_ALLOCATE_POOL                           AllocatePool;
    EFI_FREE_POOL                               FreePool;
    //
    // Event & Timer Services
    //
    EFI_CREATE_EVENT                            CreateEvent;
    EFI_SET_TIMER                               SetTimer;
    EFI_WAIT_FOR_EVENT                          WaitForEvent;
	EFI_SIGNAL_EVENT                            SignalEvent;
	EFI_CLOSE_EVENT                             CloseEvent;
	EFI_CHECK_EVENT                             CheckEvent;
	//
	// Protocol Handler Services
	//
	EFI_INSTALL_PROTOCOL_INTERFACE              InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE            ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE            UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL                         HandleProtocol;
	VOID*                                       Reserved;
	EFI_REGISTER_PROTOCOL_NOTIFY                RegisterProtocolNotify;
	EFI_LOCATE_HANDLE                           LocateHandle;
	EFI_LOCATE_DEVICE_PATH                      LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE             InstallConfigurationTable;
	//
	// Image Services
	//
	EFI_IMAGE_UNLOAD                            LoadImage;
	EFI_IMAGE_START                             StartImage;
	EFI_EXIT                                    Exit;
	EFI_IMAGE_UNLOAD                            UnloadImage;
	EFI_EXIT_BOOT_SERVICES                      ExitBootServices;
	//
	// Miscellaneous Services
	//
	EFI_GET_NEXT_MONOTONIC_COUNT                GetNextMonotonicCount;
	EFI_STALL                                   Stall;
	EFI_SET_WATCHDOG_TIMER                      SetWatchdogTimer;
	//
	// DriverSupport Services
	//
	EFI_CONNECT_CONTROLLER                      ConnectController;
	EFI_DISCONNECT_CONTROLLER                   DisconnectController;
	EFI_OPEN_PROTOCOL                           OpenProtocol;
	EFI_CLOSE_PROTOCOL                          CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION               OpenProtocolInformation;
	//
	// Library Services
	//
	EFI_PROTOCOLS_PER_HANDLE                    ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER                    LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL                         LocateProtocol;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  UninstallMultipleProtocolInterfaces;
	//
	// 32-bit CRC Services
	//
	EFI_CALCULATE_CRC32                         CalculateCrc32;
	//
	// Miscellaneous Services
	//
	EFI_COPY_MEM                                CopyMem;
	EFI_SET_MEM                                 SetMem;
	EFI_CREATE_EVENT_EX                         CreateEventEx;
} EFI_BOOT_SERVICES;

typedef struct EFI_SYSTEM_TABLE
{
	EFI_TABLE_HEADER                   Hdr;
	CHAR16                             *FirmwareVendor;
	UINT32                             FirmwareRevision;
	EFI_HANDLE                         ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL     *ConIn;
	EFI_HANDLE                         ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *ConOut;
	EFI_HANDLE                         StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *StdErr;
	EFI_RUNTIME_SERVICES               *RuntimeServices;
	EFI_BOOT_SERVICES                  *BootServices;
	UINTN                              NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE            *ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef struct EFI_LOADED_IMAGE_PROTOCOL
{
	UINT32                         Revision;
	EFI_HANDLE                     ParentHandle;
	EFI_SYSTEM_TABLE               *SystemTable;
	// Source location of the image
	EFI_HANDLE                     DeviceHandle;
	EFI_DEVICE_PATH_PROTOCOL       *FilePath;
	VOID                           *Reserved;
	// Image’s load options
	UINT32                         LoadOptionsSize;
	VOID                           *LoadOptions;
	VOID                           *ImageBase;
	UINT64                         ImageSize;
	EFI_MEMORY_TYPE                ImageCodeType;
	EFI_MEMORY_TYPE                ImageDataType;
	EFI_IMAGE_UNLOAD               Unload;
} EFI_LOADED_IMAGE_PROTOCOL;


// GRAPHICS
typedef struct EFI_PIXEL_BITMASK
{
	UINT32 RedMask;
	UINT32 GreenMask;
	UINT32 BlueMask;
	UINT32 ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
{
	UINT32                         Version;
	UINT32                         HorizontalResolution;
	UINT32                         VerticalResolution;
	EFI_GRAPHICS_PIXEL_FORMAT      PixelFormat;
	EFI_PIXEL_BITMASK              PixelInformation;
	UINT32                         PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE
{
	UINT32                                MaxMode;
	UINT32                                Mode;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *Info;
	UINTN                                 SizeOfInfo;
	EFI_PHYSICAL_ADDRESS                  FrameBufferBase;
	UINTN                                 FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct {
	UINT8          Blue;
	UINT8          Green;
	UINT8          Red;
	UINT8          Reserved;      // This technically should be ALPHA... but meh.
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL
{
	EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE   QueryMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE     SetMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT          Blt;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE         *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL ;


// GUID
struct EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID    = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
struct EFI_GUID EFI_LOADED_IMAGE_PROTOCOL_GUID       = {0x5B1B31A1, 0x9562, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}};
struct EFI_GUID EFI_DEVICE_PATH_PROTOCOL_GUID        = {0x09576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
struct EFI_GUID EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID = {0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
struct EFI_GUID EFI_ACPI_20_TABLE_GUID               = {0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};

#endif