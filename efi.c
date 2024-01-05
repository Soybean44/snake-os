#include "efi.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
  // TODO: remove this line when using input params
  (void)ImageHandle;

  SystemTable->ConOut->Reset(SystemTable->ConOut, 1);
  SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
  SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Hello World!");
  // Infinite Loop
  while(1) ;

  return EFI_SUCCESS;
}
