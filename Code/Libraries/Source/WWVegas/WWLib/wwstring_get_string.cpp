// ?Get_String@StringClass@@AAEXH_N@Z
// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath

// Completes the banked donor reconstruction using the existing lean lock wrapper
// and the retail tagged array allocator. All359 bytes are verified, including
// normal and exceptional release of the temporary-string pool lock.
#include "always.h"
#undef W3DNEWARRAY
void* __cdecl operator new[](unsigned int,unsigned int);
#define W3DNEWARRAY new(0x737472u)
#include "wwstring.h"
#include "win.h"
#include "wwmemlog.h"

void StringClass::Get_String(int length, bool is_temp)
{
	WWMEMLOG(MEM_STRINGS);

	if (!is_temp && length == 0) {
		m_Buffer = m_EmptyString;
		return;
	}

	TCHAR *string = NULL;

	if (is_temp && length <= MAX_TEMP_LEN && ReservedMask!=ALL_TEMP_STRINGS_USED_MASK) {
		FastCriticalSectionClass::LockClass m(m_Mutex);

		unsigned mask=1;
		for (int index = 0; index < MAX_TEMP_STRING; index ++, mask<<=1) {
			unsigned mask=1<<index;
			if (!(ReservedMask&mask)) {
				ReservedMask|=mask;

				unsigned temp_string=reinterpret_cast<unsigned>(m_TempStrings);
				temp_string+=MAX_TEMP_BYTES*MAX_TEMP_STRING;
				temp_string&=~(MAX_TEMP_BYTES*MAX_TEMP_STRING-1);
				temp_string+=index*MAX_TEMP_BYTES;
				temp_string+=sizeof(_HEADER);
				string=reinterpret_cast<char*>(temp_string);

				Set_Buffer_And_Allocated_Length(string, MAX_TEMP_LEN);
				break;
			}
		}
	}

	if (string == NULL) {
		if (length > 0) {
			Set_Buffer_And_Allocated_Length(Allocate_Buffer(length), length);
		} else {
			Free_String();
		}
	}
}
