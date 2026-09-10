// ?Free_String@WideStringClass@@AAEXXZ
// partial score=0.95 date=2026-09-10
// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
//
// WideStringClass::Free_String, retail 0x00619B80, 121 bytes. Same lean
// FastCriticalSectionClass spin as wwstring_free_string.cpp so the lock is
// `mov ecx,&mutex; call spin` and the unlock is `mov [&mutex],0`. The ZH
// four-slot temp pointer tables are still the BFME2 shape.

#include "always.h"
#undef W3DNEWARRAY
void *__cdecl operator new[](unsigned int, unsigned int);
#define W3DNEWARRAY new(0x737472u)
#include "wwstring.h"
#include "win.h"
#include "wwmemlog.h"

inline void __cdecl operator delete[](void *p) { ::operator delete(p); }

class WideStringClass
{
	WCHAR *m_Buffer;

	typedef struct _HEADER
	{
		int allocated_length;
		int length;
	} HEADER;

	enum
	{
		MAX_TEMP_STRING = 4
	};

	static WCHAR *m_EmptyString;
	static WCHAR *m_FreeTempPtr[MAX_TEMP_STRING];
	static WCHAR *m_ResTempPtr[MAX_TEMP_STRING];
	static int m_UsedTempStringCount;
	static FastCriticalSectionClass m_TempMutex;

	void Free_String(void);
};

WCHAR *WideStringClass::m_EmptyString;
WCHAR *WideStringClass::m_FreeTempPtr[WideStringClass::MAX_TEMP_STRING];
WCHAR *WideStringClass::m_ResTempPtr[WideStringClass::MAX_TEMP_STRING];
int WideStringClass::m_UsedTempStringCount;
FastCriticalSectionClass WideStringClass::m_TempMutex;

void WideStringClass::Free_String(void)
{
	if (m_Buffer != m_EmptyString)
	{
		WCHAR *empty;
		for (int index = 0; index < MAX_TEMP_STRING; index++)
		{
			if (m_Buffer == m_ResTempPtr[index])
			{
						{
					FastCriticalSectionClass::LockClass lock(m_TempMutex);
					m_Buffer[0] = 0;
					m_FreeTempPtr[index] = m_Buffer;
					m_ResTempPtr[index] = 0;
					m_UsedTempStringCount -= 1;
					empty = m_EmptyString;
				}
				m_Buffer = empty;
				return;
			}
		}

		char *buffer = ((char *)m_Buffer) - sizeof(WideStringClass::_HEADER);
		delete[] buffer;
		empty = m_EmptyString;
		m_Buffer = empty;
	}
}
