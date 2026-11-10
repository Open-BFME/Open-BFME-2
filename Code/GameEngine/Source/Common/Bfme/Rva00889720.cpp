// cl: /DNDEBUG /MD /EHs-c-
// platformsdk

// Retail reaches kernel32 imports (import-ref verified); the BFME1 donor's
// Rva01358E74/54/CC aliases for the same slots fail the check here.
#include <windows.h>

// Native lock address 0x00DE0884 is the global defined in Debug_CrashDone.cpp.
struct DebugCriticalSection;
extern DebugCriticalSection g_bfmeCsDWC;

class Rva00889720Class
{
public:
	char m_pad0[0x9DF8];
	int m_field9DF8;
	int m_field9DFC;
	char m_pad9E00[0x15C];
	int m_field9F50;

	bool d_00889720( void );
};

bool Rva00889720Class::d_00889720( void )
{
	m_field9DFC = 0;
	LeaveCriticalSection( (CRITICAL_SECTION*)&g_bfmeCsDWC );
	InterlockedDecrement( (LONG*)&m_field9DF8 );
	ReleaseMutex( (HANDLE)m_field9F50 );
	return false;
}
