// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0TerrainType@@QAE@XZ @0x00317F6F 129B: ctor storing vtable 0x0080C66C, clearing two AsciiString members, defaulting two vector<ScienceType> members, pushing SCIENCE_NONE into the first, zeroing flag bytes plus0C plus1C and dword plus20. Evidence: rowed Vector_base plus releaseBuffer plus push_back callees plus vtable store; class identity: ZH TerrainTypeCollection::newTerrain constructs it at 0x00318194 (pinned ??0TerrainType).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
// _STLP_NO_EXCEPTIONS: push_back's out-of-line overflow path is retail's one copy
// (ThingTemplate.cpp's 179-byte row at 0x00148D00), which has no unwind guard; with
// the guard this TU emitted a 236-byte copy that loses to it at link time.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

// Nothing here calls the base destructor out of line (~vector inlines it); its
// unreferenced copy differed from the first one in link order. Declared imported
// and force-inlined, it is not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{
	if (_M_start != 0)
		_M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}
}

#include "ascii_string.h"
class TerrainType
{
	friend class TerrainTypeCollection;
public:
	TerrainType();
	virtual ~TerrainType();
	TerrainType &operator=(const TerrainType &that);
	void friend_setName(AsciiString name);
private:
	AsciiString m_str04;
	AsciiString m_str08;
	unsigned char m_f0c;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_v1;
	unsigned char m_f1c;
	TerrainType *m_next;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_v2;
};
TerrainType::TerrainType()
{
  m_str04.clear();
  m_str08.clear();
  ScienceType st = SCIENCE_NONE;
  m_f0c = 0;
  m_v1.push_back(st);
  m_next = 0;
  m_f1c = 0;
}
