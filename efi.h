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

// Data types: UEFI Spec 2.10 section 2.3
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
#define EFI_SUCCESS 0ULL;
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

// EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL: UEFI Spec 2.10 section 12.4.1
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET                           Reset;
    EFI_TEXT_STRING                          OutputString;
    void                                     *TestString;
    void                                     *QueryMode;
    void                                     *SetMode;
    void                                     *SetAttribute;
    EFI_TEXT_CLEAR_SCREEN                    ClearScreen;
    void                                     *SetCursorPosition;
    void                                     *EnableCursor;
    void                                     *Mode;

} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// EFI_SYSTEM_TABLE: UEFI Spec 2.10 section 4.3.1
typedef struct {
    EFI_TABLE_HEADER                Hdr;
    CHAR16                          *FirmwareVendor;
    UINT32                          FirmwareRevision;
    EFI_HANDLE                      ConsoleInHandle;
    //EFI_SIMPLE_INPUT_PROTOCOL       *ConIn;
    VOID                            *ConIn;
    EFI_HANDLE                      ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE                      StandardErrorHandle;
    //EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    VOID                            *StdErr;
    //EFI_RUNTIME_SERVICES            *RuntimeServices;
    VOID                            *RuntimeServices;
    //EFI_BOOT_SERVICES               *BootServices;
    VOID                            *BootServices;
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
