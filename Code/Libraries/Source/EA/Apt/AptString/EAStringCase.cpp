// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define _CRTIMP	// the game links these CRT bodies and calls them directly
#include <string.h>

#include "../../../Apt/EAStringC.h"

EAStringC &EAStringC::MakeLower()
{
	const unsigned int size = data->m_uSize;
	ChangeBuffer(size, 0, size, CB_PUSH_ZERO, size);
	_strlwr(reinterpret_cast<char *>(data) + sizeof(StringDataC));
	return *this;
}

EAStringC &EAStringC::MakeUpper()
{
	const unsigned int size = data->m_uSize;
	ChangeBuffer(size, 0, size, CB_PUSH_ZERO, size);
	_strupr(reinterpret_cast<char *>(data) + sizeof(StringDataC));
	return *this;
}
