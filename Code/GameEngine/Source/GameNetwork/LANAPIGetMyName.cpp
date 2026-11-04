// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// Retail 0x00449B8F, 27 bytes. The target LANAPI pointer table at 0x83E680
// places this getter at slot 55; BFME1 identifies the corresponding slot 47
// as GetMyName. Retail copies the UnicodeString at LANAPI +0x14 through the
// pinned StringBase<wchar_t> copy constructor at 0x37050.

#include "unicode_string.h"
#include "../../Include/GameNetwork/LANAPI.h"

UnicodeString LANAPI::GetMyName( void )
{
	return m_name;
}
