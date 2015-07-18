#include "msgbox.h"

#ifdef _WIN32 || _WIN64

#include <Windows.h>            // MessageBox

#endif


#ifdef __linux__

#include <SDL.h>

#endif

void MsgBox(const char * msg , char * tittle )
{
  #ifdef __WIN32 || _WIN64
	MessageBoxA(NULL, msg, tittle, MB_ICONERROR | MB_OK );    // Na windowsie pobieram messageoxa z WinApi
  #endif

  #ifdef __linux__
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,tittle,msg);
  #endif
}