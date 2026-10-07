// Reconstructed pooled-string release; ordinary array delete forwards to scalar delete.
// Pool membership uses the same aligned block and DIR32 addend as Get_String.
// Complete111-byte retail extent includes both RET paths; all75 concrete bytes exact.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath

// The data word keeps its existing FastCriticalSectionClass spelling.
// Retail acquires these string pools through the pool backend at 0x6577F;
// use its shared guard rather than emit the event-backend constructor name.
#include "mutex.h"
#include "bfme_pool_critical_section.h"
#include "always.h"
#undef W3DNEWARRAY
void* __cdecl operator new[](unsigned int,unsigned int);
#define W3DNEWARRAY new('str')
#include "wwstring.h"
#include "win.h"
#include "wwmemlog.h"


static inline void __cdecl operator delete[](void*p) {::operator delete(p);}
void
StringClass::Free_String (void)
{
	if (m_Buffer != m_EmptyString) {

		unsigned buffer_base=reinterpret_cast<unsigned>(m_Buffer-sizeof (StringClass::_HEADER));
		unsigned temp_base=reinterpret_cast<unsigned>(m_TempStrings+MAX_TEMP_BYTES*MAX_TEMP_STRING);

		if ((buffer_base>>11)==(temp_base>>11)) {
			m_Buffer[0] = 0;

			//
			//	Make sure no one else is changing the reserved mask
			// at the same time we are.
			//
			BFMEPoolCriticalSection::LockClass m(*reinterpret_cast<BFMEPoolCriticalSection *>(&m_Mutex));

			unsigned index=(buffer_base/MAX_TEMP_BYTES)&(MAX_TEMP_STRING-1);
			unsigned mask=1<<index;
			ReservedMask&=~mask;
		}
		else {

			//
			//	String wasn't temporary, so free the memory
			//
			char *buffer = ((char *)m_Buffer) - sizeof (StringClass::_HEADER);
			delete [] buffer;
		}

		//
		//	Reset the buffer
		//
		m_Buffer = m_EmptyString;
	}

	return ;
}
