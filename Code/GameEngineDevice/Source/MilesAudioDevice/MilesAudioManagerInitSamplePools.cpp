// cl: /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
// Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/MilesAudioDevice/
// MilesAudioManagerInitSamplePools.cpp. Function purpose/name carried from donor.
// Target: Ghidra boundary 0x00056746, 127 bytes. The AIL allocation, initialization
// and user-data import sequence independently supports 2D sample-pool identity.
// Retail loads settings +0x10 (count +0x64, streams +0x6C), driver +0x9DC,
// list +0xA38, sample count +0x67C and stream count +0x68C. These offsets are
// target facts; the unaccessed gaps are opaque, not recovered class members.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


// Retail calls the separately rowed four-byte-element append at 0x5548F.
// The list<void*> instance owned by the 3D pool TU is 0x526103 and calls
// a different insertion provider. Preserve it, but select the retail call.
// The int-element view selects that verified four-byte ABI instance.
// The target sample/record remains a pointer; no int-container identity is claimed.


typedef void *HSAMPLE;
typedef void *HDIGDRIVER;

extern "C" __declspec(dllimport) HSAMPLE __stdcall AIL_allocate_sample_handle(
	HDIGDRIVER driver);
extern "C" __declspec(dllimport) void __stdcall AIL_init_sample(
	HSAMPLE sample);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_user_data(
	HSAMPLE sample, int index, unsigned int value);

struct AudioSettings
{
	char m_pad00[0x64];
	int m_sampleCount2D;
	int m_sampleCount3D;
	int m_streamCount;
};

#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

void MilesAudioManager::initSamplePools(void)
{
	while (m_availableSamples.size() < (unsigned int)m_audioSettings->m_sampleCount2D)
	{
		register HSAMPLE sample = AIL_allocate_sample_handle(m_digitalHandle);
		if (!sample)
			break;
		AIL_init_sample(sample);
		AIL_set_sample_user_data(sample, 0,
			(unsigned int)m_availableSamples.size() + 1);
		m_availableSamples.push_back(reinterpret_cast<const int &>(sample));
		++m_67C;
	}

	m_68C = m_audioSettings->m_streamCount;
}
