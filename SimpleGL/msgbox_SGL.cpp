#include "msgbox_SGL.h"

#ifdef _WIN32 

#include <Windows.h>            // MessageBox

#endif


#ifdef __linux__

#include <SDL.h>

#endif

void MsgBox(const char * msg , const char * tittle )
{
  #ifdef _WIN32
	MessageBoxA(NULL, msg, tittle, MB_ICONERROR | MB_OK );    // Na windowsie pobieram messageoxa z WinApi
  #endif

  #ifdef __linux__
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,tittle,msg);
  #endif
}