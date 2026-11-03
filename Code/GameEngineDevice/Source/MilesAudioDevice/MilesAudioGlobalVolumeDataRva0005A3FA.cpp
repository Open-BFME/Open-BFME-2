// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?rva0005A3FA@GlobalVolumeData@MilesAudioManager@@QAEXPAXM@Z, retail
// 0x0005A3FA (87 bytes, RET8). Name unknown; spelled as the existing pin the
// sole caller MilesAudioManager::rva0005CA03 (0x0005CA41) binds, on the
// +0x12C 0x1C4-stride GlobalVolumeData element.
//
// Body: insert (key, value) into the AsciiString -> float map at +0x1B8 --
// the pair temporary is built by the pinned StringBase copy 0x000365F0 and a
// movss of the float, passed to the rowed map<AsciiString,float>
// _Rb_tree::insert_unique 0x00058CB3, then released through 0x00036410. The
// first argument is the key string the caller hands through as its slot
// pointer.
#include <map>
#include "ascii_string.h"

// insert_unique otherwise emits this unit's own copy, which differs from the
// kept one; the call links to the rowed tree insert (0x00058CB3).
namespace _STL {
template <> pair<_Rb_tree<AsciiString, pair<const AsciiString, float>, _Select1st<pair<const AsciiString, float> >, less<AsciiString>, allocator<pair<const AsciiString, float> > >::iterator, bool>
_Rb_tree<AsciiString, pair<const AsciiString, float>, _Select1st<pair<const AsciiString, float> >, less<AsciiString>, allocator<pair<const AsciiString, float> > >::insert_unique(const pair<const AsciiString, float> &);
}

#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

class MilesAudioManager::GlobalVolumeData
{
public:
	void rva0005A3FA(void *key, float value);

private:
	char m_pad[0x1B8];
	_STL::map<AsciiString, float> m_map1B8;
};

void MilesAudioManager::GlobalVolumeData::rva0005A3FA(void *key, float value)
{
	m_map1B8.insert(_STL::pair<const AsciiString, float>(*(const AsciiString *)key, value));
}
