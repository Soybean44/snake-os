#pragma once
#include <stdint.h>
#if __has_include(<uchar.h>)
#include <uchar.h>
#endif
// UEFI Spec 2.10 section 2.4
#define IN
#define OUT
#define OPTIONAL
#define CONST const
// EFIAPI defines the calling convention for EFI defined functions
// Taken from gnu-efi at
// https://github.com/vathpela/gnu-efi/blob/master/inc/x86_64/efibind.h
#define EFIAPI __attribute((ms_abi)) // x86_64 Microsoft calling convention

// Data types: UEFI Spec 2.10 section 2.3.1
typedef uint8_t BOOLEAN;
typedef int64_t INTN;
typedef uint64_t UINTN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef char CHAR8;

// UTF-16 equivalent-ish type, for UCS-2 characters
// codepoints <= 0xFFFF
#ifndef _UCHAR_H
typedef uint_least16_t char16_t;
#endif
typedef char16_t CHAR16;

typedef void VOID;
typedef struct EFI_GUID {
    UINT32 TimeLow;
    UINT16 TimeMid;
    UINT16 TimeHighAndVersion;
    UINT8  ClockSeqHighAndReserved;
    UINT8  ClockSeqLow;
    UINT8  Node[6];
} __attribute__ ((packed)) EFI_GUID;

typedef UINTN EFI_STATUS;
typedef VOID* EFI_HANDLE;
typedef VOID* EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;
typedef UINT8 EFI_MAC_ADDRESS[32];
typedef UINT8 EFI_IPv4_ADDRESS[4];
typedef UINT8 EFI_IPv6_ADDRESS[16];

// EFI_STATUS values - UEFI Spec 2.10 Appendix D
#define EFI_SUCCESS 0ULL
// TODO: Add EFI_ERROR() macro/other for checking if EFI_STATUS
//   high bit is set, if so it is an ERROR status

// EFI_TABLE_HEADER: UEFI Spec 2.10 section 4.2.1
typedef struct {
    UINT64 Singature;
    UINT32 Revision;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

// EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
{0x387477c2,0x69c7,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}

// EFI_TEXT_RESET: UEFI Spec 2.10 section 12.4.2
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_RESET) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL       *This,
    IN BOOLEAN                               ExtendedVerification
);

//******************************************************
// UNICODE DRAWING CHARACTERS
//******************************************************

#define BOXDRAW_HORIZONTAL             0x2500
#define BOXDRAW_VERTICAL               0x2502
#define BOXDRAW_DOWN_RIGHT             0x250c
#define BOXDRAW_DOWN_LEFT              0x2510
#define BOXDRAW_UP_RIGHT               0x2514
#define BOXDRAW_UP_LEFT                0x2518
#define BOXDRAW_VERTICAL_RIGHT         0x251c
#define BOXDRAW_VERTICAL_LEFT          0x2524
#define BOXDRAW_DOWN_HORIZONTAL        0x252c
#define BOXDRAW_UP_HORIZONTAL          0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL    0x253c

#define BOXDRAW_DOUBLE_HORIZONTAL      0x2550
#define BOXDRAW_DOUBLE_VERTICAL        0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE      0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT      0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT      0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE       0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT       0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT       0x2557

#define BOXDRAW_UP_RIGHT_DOUBLE        0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT        0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT        0x255a
#define BOXDRAW_UP_LEFT_DOUBLE         0x255b
#define BOXDRAW_UP_DOUBLE_LEFT         0x255c
#define BOXDRAW_DOUBLE_UP_LEFT         0x255d

#define BOXDRAW_VERTICAL_RIGHT_DOUBLE  0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT  0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT  0x2560

#define BOXDRAW_VERTICAL_LEFT_DOUBLE   0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT   0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT   0x2563

#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE 0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL 0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL 0x2566

#define BOXDRAW_UP_HORIZONTAL_DOUBLE   0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL   0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL   0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c

//******************************************************
// EFI Required Block Elements Code Chart
//******************************************************

#define BLOCKELEMENT_FULL_BLOCK        0x2588
#define BLOCKELEMENT_LIGHT_SHADE       0x2591

//******************************************************
// EFI Required Geometric Shapes Code Chart
//******************************************************

#define GEOMETRICSHAPE_UP_TRIANGLE     0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE  0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE   0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE   0x25c4

//******************************************************
// EFI Required Arrow shapes
//******************************************************

#define ARROW_UP                       0x2191
#define ARROW_DOWN                     0x2193

// EFI_TEXT_STRING: UEFI Spec 2.10 section 12.4.3
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_STRING) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This,
    IN CHAR16                             *String
);

// EFI_TEXT_CLEAR_SCREEN: UEFI Spec 2.10 section 12.4.8
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_CLEAR_SCREEN) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL             *This
);

// EFI_TEXT_SET_MODE: UEFI Spec 2.10 section 12.4.6
typedef
EFI_STATUS
(* EFIAPI EFI_TEXT_SET_MODE) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL          *This,
    IN UINTN                                    ModeNumber
);

//*******************************************************
// Attributes
//*******************************************************
#define EFI_BLACK                              0x00
#define EFI_BLUE                               0x01
#define EFI_GREEN                              0x02
#define EFI_CYAN                               0x03
#define EFI_RED                                0x04
#define EFI_MAGENTA                            0x05
#define EFI_BROWN                              0x06
#define EFI_LIGHTGRAY                          0x07
#define EFI_BRIGHT                             0x08
#define EFI_LIGHTBLUE                          0x09
#define EFI_LIGHTGREEN                         0x0A
#define EFI_LIGHTCYAN                          0x0B
#define EFI_LIGHTRED                           0x0C
#define EFI_LIGHTMAGENTA                       0x0D
#define EFI_YELLOW                             0x0E
#define EFI_WHITE                              0x0F

#define EFI_BACKGROUND_BLACK                   0x00
#define EFI_BACKGROUND_BLUE                    0x10
#define EFI_BACKGROUND_GREEN                   0x20
#define EFI_BACKGROUND_CYAN                    0x30
#define EFI_BACKGROUND_RED                     0x40
#define EFI_BACKGROUND_MAGENTA                 0x50
#define EFI_BACKGROUND_BROWN                   0x60
#define EFI_BACKGROUND_LIGHTGRAY               0x70

// EFI_TEXT_SET_ATTRIBUTE: UEFI Spec 2.10 section 12.4.7
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
    IN UINTN                                  Attribute
);

// EFI_TEXT_SET_CURSOR_POSITION: UEFI Spec 2.10 section 12.4.9
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL             *This,
    IN UINTN                                       Column,
    IN UINTN                                       Row
);

// EFI_TEXT_ENABLE_CURSOR: UEFI Spec 2.10 section 12.4.10
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_ENABLE_CURSOR) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL             *This,
    IN BOOLEAN                                     Visible
);

// EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL: UEFI Spec 2.10 section 12.4.1
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET                           Reset;
    EFI_TEXT_STRING                          OutputString;
    void                                     *TestString;
    void                                     *QueryMode;
    EFI_TEXT_SET_MODE                        SetMode;
    EFI_TEXT_SET_ATTRIBUTE                   SetAttribute;
    EFI_TEXT_CLEAR_SCREEN                    ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION             SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR                   EnableCursor;
    void                                     *Mode;

} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
typedef struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

// EFI_INPUT_RESET_EX: UEFI Spec 2.10 section 12.2.2
typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET_EX) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL        *This,
    IN BOOLEAN                                  ExtendedVerification
);

#define EFI_SHIFT_STATE_VALID          0x80000000
#define EFI_RIGHT_SHIFT_PRESSED        0x00000001
#define EFI_LEFT_SHIFT_PRESSED         0x00000002
#define EFI_RIGHT_CONTROL_PRESSED      0x00000004
#define EFI_LEFT_CONTROL_PRESSED       0x00000008
#define EFI_RIGHT_ALT_PRESSED          0x00000010
#define EFI_LEFT_ALT_PRESSED           0x00000020
#define EFI_RIGHT_LOGO_PRESSED         0x00000040
#define EFI_LEFT_LOGO_PRESSED          0x00000080
#define EFI_MENU_KEY_PRESSED           0x00000100
#define EFI_SYS_REQ_PRESSED            0x00000200

//*****************************************************
// EFI_KEY_TOGGLE_STATE
//*****************************************************
typedef UINT8 EFI_KEY_TOGGLE_STATE;

//*****************************************************
// EFI_KEY_STATE
//*****************************************************
//
// Any Shift or Toggle State that is valid should have
// high order bit set.
//
typedef struct EFI_KEY_STATE {
    UINT32                       KeyShiftState;
    EFI_KEY_TOGGLE_STATE         KeyToggleState;
} EFI_KEY_STATE;

//******************************************************
// EFI_INPUT_KEY
//******************************************************
typedef struct {
    UINT16                             ScanCode;
    CHAR16                             UnicodeChar;
} EFI_INPUT_KEY;

//******************************************
// EFI_KEY_DATA
//******************************************
typedef struct {
    EFI_INPUT_KEY           Key;
    EFI_KEY_STATE           KeyState;
} EFI_KEY_DATA;

// EFI_INPUT_READ_KEY_EX: UEFI Spec 2.10 section 12.2.3
typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY_EX) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *This,
    OUT EFI_KEY_DATA                         *KeyData
);

//******************************************************
// EFI_KEY_NOTIFY
//******************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_KEY_NOTIFY_FUNCTION) (
    IN EFI_KEY_DATA                          *KeyData
);

// The following two functions register a function to be run on key press
// EFI_REGISTER_KEYSTROKE_NOTIFY: UEFI Spec 2.10 section 12.2.5
typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL            *This,
    IN EFI_KEY_DATA                                 *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION                      KeyNotificationFunction,
    OUT VOID                                        **NotifyHandle
);

// EFI_UNREGISTER_KEYSTROKE_NOTIFY: UEFI Spec 2.10 section 12.2.5
typedef
EFI_STATUS
(EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN VOID                              *NotificationHandle
);

// EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL: UEFI Spec 2.10 section 12.2.1
#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID \
 {0xdd9e7534, 0x7762, 0x4698, \
  {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}}

typedef struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
    EFI_INPUT_RESET_EX                          Reset;
    EFI_INPUT_READ_KEY_EX                       ReadKeyStrokeEx;
    EFI_EVENT                                   WaitForKeyEx;
    //EFI_SET_STATE                               SetState;
    void*                               SetState;
    EFI_REGISTER_KEYSTROKE_NOTIFY               RegisterKeyNotify;
    EFI_UNREGISTER_KEYSTROKE_NOTIFY             UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

//************************************************
//EFI_TIME
//************************************************
// This represents the current time information
typedef struct {
    UINT16    Year;              // 1900 - 9999
    UINT8     Month;             // 1 - 12
    UINT8     Day;               // 1 - 31
    UINT8     Hour;              // 0 - 23
    UINT8     Minute;            // 0 - 59
    UINT8     Second;            // 0 - 59
    UINT8     Pad1;
    UINT32    Nanosecond;        // 0 - 999,999,999
    INT16     TimeZone;          // —1440 to 1440 or 2047
    UINT8     Daylight;
    UINT8     Pad2;
}   EFI_TIME;

//******************************************************
// EFI_TIME_CAPABILITIES
//******************************************************
// This provides the capabilities of the
// real time clock device as exposed through the EFI interfaces.
typedef struct {
    UINT32                  Resolution;
    UINT32                  Accuracy;
    BOOLEAN                 SetsToZero;
}   EFI_TIME_CAPABILITIES;

// EFI_GET_TIME: UEFI Spec 2.10 section 8.3.1
typedef
EFI_STATUS
EFI_GET_TIME (
    OUT EFI_TIME                  *Time,
    OUT EFI_TIME_CAPABILITIES     *Capabilities OPTIONAL // NULL is allowed
);

//******************************************************
// EFI_RESET_TYPE
//******************************************************
typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
}   EFI_RESET_TYPE;

// EFI_RESET_SYSTEM: UEFI Spec 2.10 section 8.5.1
typedef
VOID
(EFIAPI *EFI_RESET_SYSTEM) (
    IN EFI_RESET_TYPE          ResetType,
    IN EFI_STATUS              ResetStatus,
    IN UINTN                   DataSize,
    IN VOID                    *ResetData OPTIONAL // NULL is allowed
);

// EFI_RUNTIME_SERVICES: UEFI Spec 2.10 section 4.5.1
#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION
typedef struct {
    EFI_TABLE_HEADER                 Hdr;

    //
    // Time Services
    //
    EFI_GET_TIME                     *GetTime;
    //EFI_SET_TIME                     SetTime;
    void*                     SetTime;
    //EFI_GET_WAKEUP_TIME              GetWakeupTime;
    void*              GetWakeupTime;
    //EFI_SET_WAKEUP_TIME              SetWakeupTime;
    void*              SetWakeupTime;

    //
    // Virtual Memory Services
    //
    //EFI_SET_VIRTUAL_ADDRESS_MAP      SetVirtualAddressMap;
    void*      SetVirtualAddressMap;
    //EFI_CONVERT_POINTER                ConvertPointer;
    void*                ConvertPointer;

    //
    // Variable Services
    //
    //EFI_GET_VARIABLE                 GetVariable;
    void*                 GetVariable;
    //EFI_GET_NEXT_VARIABLE_NAME       GetNextVariableName;
    void*       GetNextVariableName;
    //EFI_SET_VARIABLE                 SetVariable;
    void*                 SetVariable;

    //
    // Miscellaneous Services
    //
    //EFI_GET_NEXT_HIGH_MONO_COUNT     GetNextHighMonotonicCount;
    void*     GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM                 ResetSystem;

    //
    // UEFI 2.0 Capsule Services
    //
    //EFI_UPDATE_CAPSULE               UpdateCapsule;
    void*               UpdateCapsule;
    //EFI_QUERY_CAPSULE_CAPABILITIES   QueryCapsuleCapabilities;
    void*   QueryCapsuleCapabilities;

//
// Miscellaneous UEFI 2.0 Service
//
    //EFI_QUERY_VARIABLE_INFO          QueryVariableInfo;
    void*          QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

//******************************************************\*
// EFI_EVENT_NOTIFY
//******************************************************\*
typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY) (
    IN EFI_EVENT          Event,
    IN VOID              *Context
);

//******************************************************
// Task Priority Levels
//******************************************************
#define TPL_APPLICATION    4
#define TPL_CALLBACK       8
#define TPL_NOTIFY         16
#define TPL_HIGH_LEVEL     31

//******************************************************
// Event Types
//******************************************************
// These types can be "ORed" together as needed - for example,
// EVT_TIMER might be "Ored" with EVT_NOTIFY_WAIT or
// EVT_NOTIFY_SIGNAL.
#define EVT_TIMER                            0x80000000
#define EVT_RUNTIME                          0x40000000

#define EVT_NOTIFY_WAIT                      0x00000100
#define EVT_NOTIFY_SIGNAL                    0x00000200

#define EVT_SIGNAL_EXIT_BOOT_SERVICES        0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE    0x60000202

// EFI_CREATE_EVENT: UEFI Spec 2.10 section 7.1.1
typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
    IN UINT32                   Type,
    IN EFI_TPL                  NotifyTpl,
    IN EFI_EVENT_NOTIFY         NotifyFunction, OPTIONAL
    IN VOID                     *NotifyContext, OPTIONAL
    OUT EFI_EVENT               *Event
);

// EFI_CLOSE_EVENT: UEFI Spec 2.10 section 7.1.3
typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
    IN EFI_EVENT      Event
);

// EFI_WAIT_FOR_EVENT: UEFI Spec 2.10 section 7.1.5
typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
    IN UINTN             NumberOfEvents,
    IN EFI_EVENT         *Event,
    OUT UINTN            *Index
);
//******************************************************
//EFI_TIMER_DELAY
//******************************************************
typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

// EFI_SET_TIMER: UEFI Spec 2.10 section 7.1.7
typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
    IN EFI_EVENT               Event,
    IN EFI_TIMER_DELAY         Type,
    IN UINT64                  TriggerTime
);

// EFI_BOOT_SERVICES: UEFI Spec 2.10 section 4.4.1
#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

typedef struct {
    EFI_TABLE_HEADER     Hdr;

    //
    // Task Priority Services
    //
    //EFI_RAISE_TPL        RaiseTPL;       // EFI 1.0+
    void*        RaiseTPL;       // EFI 1.0+
    //EFI_RESTORE_TPL      RestoreTPL;     // EFI 1.0+
    void*      RestoreTPL;     // EFI 1.0+

    //
    // Memory Services
    //
    //EFI_ALLOCATE_PAGES   AllocatePages;  // EFI 1.0+
    void*   AllocatePages;  // EFI 1.0+
    //EFI_FREE_PAGES       FreePages;      // EFI 1.0+
    void*       FreePages;      // EFI 1.0+
    //EFI_GET_MEMORY_MAP   GetMemoryMap;   // EFI 1.0+
    void*   GetMemoryMap;   // EFI 1.0+
    //EFI_ALLOCATE_POOL    AllocatePool;   // EFI 1.0+
    void*    AllocatePool;   // EFI 1.0+
    //EFI_FREE_POOL        FreePool;       // EFI 1.0+
    void*        FreePool;       // EFI 1.0+

    //
    // Event & Timer Services
    //
    EFI_CREATE_EVENT     CreateEvent;    // EFI 1.0+
    EFI_SET_TIMER        SetTimer;       // EFI 1.0+
    EFI_WAIT_FOR_EVENT   WaitForEvent;   // EFI 1.0+
    //EFI_SIGNAL_EVENT     SignalEvent;    // EFI 1.0+
    void*     SignalEvent;    // EFI 1.0+
    EFI_CLOSE_EVENT      CloseEvent;     // EFI 1.0+
    //EFI_CHECK_EVENT      CheckEvent;     // EFI 1.0+
    void*      CheckEvent;     // EFI 1.0+

    //
    // Protocol Handler Services
    //
    //EFI_INSTALL_PROTOCOL_INTERFACE     InstallProtocolInterface;            // EFI 1.0+
    void*     InstallProtocolInterface;            // EFI 1.0+
    //EFI_REINSTALL_PROTOCOL_INTERFACE   ReinstallProtocolInterface;          // EFI 1.0+
    void*   ReinstallProtocolInterface;          // EFI 1.0+
    //EFI_UNINSTALL_PROTOCOL_INTERFACE   UninstallProtocolInterface;          // EFI 1.0+
    void*   UninstallProtocolInterface;          // EFI 1.0+
    //EFI_HANDLE_PROTOCOL                HandleProtocol;                      // EFI 1.0+
    void*                HandleProtocol;                      // EFI 1.0+
    VOID*   Reserved;    // EFI 1.0+
    //EFI_REGISTER_PROTOCOL_NOTIFY       RegisterProtocolNotify;              // EFI  1.0+
    void*       RegisterProtocolNotify;              // EFI  1.0+
    //EFI_LOCATE_HANDLE                  LocateHandle;                        // EFI 1.0+
    void*                  LocateHandle;                        // EFI 1.0+
    //EFI_LOCATE_DEVICE_PATH             LocateDevicePath;                    // EFI 1.0+
    void*             LocateDevicePath;                    // EFI 1.0+
    //EFI_INSTALL_CONFIGURATION_TABLE       InstallConfigurationTable;           // EFI 1.0+
    void*       InstallConfigurationTable;           // EFI 1.0+

    //
    // Image Services
    //
    //EFI_IMAGE_UNLOAD               LoadImage;        // EFI 1.0+
    void*               LoadImage;        // EFI 1.0+
    //EFI_IMAGE_START                StartImage;       // EFI 1.0+
    void*                StartImage;       // EFI 1.0+
    //EFI_EXIT                       Exit;             // EFI 1.0+
    void*                       Exit;             // EFI 1.0+
    //EFI_IMAGE_UNLOAD               UnloadImage;      // EFI 1.0+
    void*               UnloadImage;      // EFI 1.0+
    //EFI_EXIT_BOOT_SERVICES         ExitBootServices; // EFI 1.0+
    void*         ExitBootServices; // EFI 1.0+

    //
    // Miscellaneous Services
    //
    //EFI_GET_NEXT_MONOTONIC_COUNT   GetNextMonotonicCount; // EFI 1.0+
    void*   GetNextMonotonicCount; // EFI 1.0+
    //EFI_STALL                      Stall;                 // EFI 1.0+
    void*                      Stall;                 // EFI 1.0+
    //EFI_SET_WATCHDOG_TIMER         SetWatchdogTimer;      // EFI 1.0+
    void*         SetWatchdogTimer;      // EFI 1.0+

    //
    // DriverSupport Services
    //
    //EFI_CONNECT_CONTROLLER         ConnectController;     // EFI 1.1
    void*         ConnectController;     // EFI 1.1
    //EFI_DISCONNECT_CONTROLLER      DisconnectController;  // EFI 1.1+
    void*      DisconnectController;  // EFI 1.1+

    //
    // Open and Close Protocol Services
    //
    //EFI_OPEN_PROTOCOL              OpenProtocol;           // EFI 1.1+
    void*              OpenProtocol;           // EFI 1.1+
    //EFI_CLOSE_PROTOCOL             CloseProtocol;          // EFI 1.1+
    void*             CloseProtocol;          // EFI 1.1+
    //EFI_OPEN_PROTOCOL_INFORMATION     OpenProtocolInformation;// EFI 1.1+
    void*     OpenProtocolInformation;// EFI 1.1+

    //
    // Library Services
    //
    //EFI_PROTOCOLS_PER_HANDLE       ProtocolsPerHandle;     // EFI 1.1+
    void*       ProtocolsPerHandle;     // EFI 1.1+
    //EFI_LOCATE_HANDLE_BUFFER       LocateHandleBuffer;     // EFI 1.1+
    void*       LocateHandleBuffer;     // EFI 1.1+
    //EFI_LOCATE_PROTOCOL            LocateProtocol;         // EFI 1.1+
    void*            LocateProtocol;         // EFI 1.1+
    //EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  InstallMultipleProtocolInterfaces;    // EFI 1.1+
    void*  InstallMultipleProtocolInterfaces;    // EFI 1.1+
    //EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;   // EFI 1.1+*
    void* UninstallMultipleProtocolInterfaces;   // EFI 1.1+*

    //
    // 32-bit CRC Services
    //
    //EFI_CALCULATE_CRC32    CalculateCrc32;     // EFI 1.1+
    void*    CalculateCrc32;     // EFI 1.1+

    //
    // Miscellaneous Services
    //
    //EFI_COPY_MEM           CopyMem;        // EFI 1.1+
    void*           CopyMem;        // EFI 1.1+
    //EFI_SET_MEM            SetMem;         // EFI 1.1+
    void*            SetMem;         // EFI 1.1+
    //EFI_CREATE_EVENT_EX    CreateEventEx;  // UEFI 2.0+
    void*    CreateEventEx;  // UEFI 2.0+
} EFI_BOOT_SERVICES;

// EFI_SYSTEM_TABLE: UEFI Spec 2.10 section 4.3.1
typedef struct {
    EFI_TABLE_HEADER                Hdr;
    CHAR16                          *FirmwareVendor;
    UINT32                          FirmwareRevision;
    EFI_HANDLE                      ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL       *ConIn;
    EFI_HANDLE                      ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE                      StandardErrorHandle;
    //EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    VOID                            *StdErr;
    EFI_RUNTIME_SERVICES            *RuntimeServices;
    EFI_BOOT_SERVICES               *BootServices;
    UINTN                           NumberOfTableEntries;
    //EFI_CONFIGURATION_TABLE         *ConfigurationTable;
    VOID                            *ConfigurationTable;
} EFI_SYSTEM_TABLE;

// EFI_IMAGE_ENTRY_POINT: UEFI Spec 2.10 section 4.1.1
typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_ENTRY_POINT) (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
);
