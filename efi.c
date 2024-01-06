#include "efi.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
  // TODO: remove this line when using input params
  (void)ImageHandle;

  // Initialize I/O
  SystemTable->ConOut->SetMode(SystemTable->ConOut, 0); // Screen is 80x25 characters
  SystemTable->ConOut->Reset(SystemTable->ConOut, 1);
  SystemTable->ConIn->Reset(SystemTable->ConIn, 1);
  SystemTable->ConOut->EnableCursor(SystemTable->ConOut, 0);
  SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
  SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_WHITE);
  char16_t* vert_border = u"################################################################################";
  char16_t* horiz_border = u"#                                                                              #";
  SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 1);
  SystemTable->ConOut->OutputString(SystemTable->ConOut, vert_border);
  SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 24);
  SystemTable->ConOut->OutputString(SystemTable->ConOut, vert_border);
  for(UINT8 i=1;i<23;i++){
    SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, i);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, horiz_border);
  }

  //Snake pos can be within (1,1) and (78,22)
  UINTN X = 1, Y = 1;
  SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
  SystemTable->ConOut->OutputString(SystemTable->ConOut, u"P");
  EFI_KEY_DATA keyData;
  while(1) {
    UINTN idx;
    SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKeyEx, &idx);
    SystemTable->ConIn->ReadKeyStrokeEx(SystemTable->ConIn, &keyData);
    if (keyData.Key.UnicodeChar == u'w') {
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u" ");
      Y -= 1;
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u"P");
    }
    if (keyData.Key.UnicodeChar == u's') {
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u" ");
      Y += 1;
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u"P");
    }
    if (keyData.Key.UnicodeChar == u'a') {
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u" ");
      X -= 1;
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u"P");
    }
    if (keyData.Key.UnicodeChar == u'd') {
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u" ");
      X += 1;
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, X, Y);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u"P");
    }
    if (X < 1 || X > 78 || Y < 1 || Y > 22) {
      SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 0);
      SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
      SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
      SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Game Over");
      break;
    }
  }

  SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, 0);
  return EFI_SUCCESS;
}
