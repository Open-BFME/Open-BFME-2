// cl: /DNDEBUG /MD /Oy- /EHsc

// Open-BFME5: Debug::operator<<(bool). const char* stream at vtable +0x38.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
#include "../../../../GameEngine/Source/Common/debug.h"

// ??6Debug@@UAEAAV0@_N@Z
Debug &Debug::operator<<(bool value)
{
	const char *text;
	if (value)
		text = "true";
	else
		text = "false";
	return (*this) << text;
}
