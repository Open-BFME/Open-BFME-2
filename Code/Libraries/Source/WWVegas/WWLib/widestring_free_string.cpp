// Dedicated TU for WideStringClass::Free_String. Do not edit widestring.cpp;
// that unit already holds matched bodies.
// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath

#include "always.h"
#undef W3DNEWARRAY
void* __cdecl operator new[](unsigned int,unsigned int);
#define W3DNEWARRAY new(0x737472u)
#include "widestring.h"

inline void __cdecl operator delete[](void *p) { ::operator delete(p); }

void WideStringClass::Free_String(void)
{
	if (m_Buffer != m_EmptyString) {
		bool found = false;
		for (int index = 0; index < MAX_TEMP_STRING; index++) {
			if (m_Buffer == m_ResTempPtr[index]) {
				FastCriticalSectionClass::LockClass lock(m_TempMutex);

				m_Buffer[0] = 0;
				m_FreeTempPtr[index] = m_Buffer;
				m_ResTempPtr[index] = 0;
				m_UsedTempStringCount--;
				found = true;
				break;
			}
		}

		if (found == false) {
			char *buffer = ((char *)m_Buffer) - sizeof(WideStringClass::_HEADER);
			delete[] buffer;
		}

		m_Buffer = m_EmptyString;
	}
}
