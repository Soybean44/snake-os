#include "efi.h"

// GLOBAL VARIABLES //
typedef enum {
  UP,DOWN,LEFT,RIGHT
} DIRECTION;
EFI_SYSTEM_TABLE* ST;
UINTN X = 1, Y = 1;
DIRECTION dir = RIGHT;

VOID init_board(VOID){
  // Initialize I/O
  ST->ConOut->SetMode(ST->ConOut, 0); // Screen is 80x25 characters
  ST->ConOut->Reset(ST->ConOut, 1);
  ST->ConIn->Reset(ST->ConIn, 1);
  ST->ConOut->EnableCursor(ST->ConOut, 0);
  // Draw borders
  ST->ConOut->ClearScreen(ST->ConOut);
  ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE);
  char16_t* vert_border = u"################################################################################";
  char16_t* horiz_border = u"#                                                                              #";
  ST->ConOut->SetCursorPosition(ST->ConOut, 0, 1);
  ST->ConOut->OutputString(ST->ConOut, vert_border);
  ST->ConOut->SetCursorPosition(ST->ConOut, 0, 24);
  ST->ConOut->OutputString(ST->ConOut, vert_border);
  for(UINT8 i=1;i<23;i++){
    ST->ConOut->SetCursorPosition(ST->ConOut, 0, i);
    ST->ConOut->OutputString(ST->ConOut, horiz_border);
  }
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
  // TODO: remove this line when using input params
  (void)ImageHandle;
  ST = SystemTable;

  init_board();
  //Snake pos can be within (1,1) and (78,22)
  ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
  ST->ConOut->OutputString(ST->ConOut, u"P");
  EFI_KEY_DATA keyData;
  while(1) {
    if (X < 1 || X > 78 || Y < 1 || Y > 22) {
      ST->ConOut->SetCursorPosition(ST->ConOut, 0, 0);
      ST->ConOut->ClearScreen(ST->ConOut);
      ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
      ST->ConOut->OutputString(ST->ConOut, u"Game Over");
      break;
    }
    UINTN idx;
    ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKeyEx, &idx);
    ST->ConIn->ReadKeyStrokeEx(ST->ConIn, &keyData);
    if (keyData.Key.UnicodeChar == u'w') {
      dir = UP;
    }
    else if (keyData.Key.UnicodeChar == u's') {
      dir = DOWN;
    }
    else if (keyData.Key.UnicodeChar == u'a') {
      dir = LEFT;
    }
    else if (keyData.Key.UnicodeChar == u'd') {
      dir = RIGHT;
    }
    else {
      continue;
    }
    if (dir==UP) {
      ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
      ST->ConOut->OutputString(ST->ConOut, u" ");
      Y -= 1;
      ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
      ST->ConOut->OutputString(ST->ConOut, u"P");
    }
    if (dir==DOWN) {
      ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
      ST->ConOut->OutputString(ST->ConOut, u" ");
      Y += 1;
      ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
      ST->ConOut->OutputString(ST->ConOut, u"P");
    }
    if (dir==LEFT) {
      ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
      ST->ConOut->OutputString(ST->ConOut, u" ");
      X -= 1;
      ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
      ST->ConOut->OutputString(ST->ConOut, u"P");
    }
    if (dir==RIGHT) {
      ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
      ST->ConOut->OutputString(ST->ConOut, u" ");
      X += 1;
      ST->ConOut->SetCursorPosition(ST->ConOut, X, Y);
      ST->ConOut->OutputString(ST->ConOut, u"P");
    }
  }

  ST->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, 0);
  return EFI_SUCCESS;
}
