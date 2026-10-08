// cl: /Ob2 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ??1Rva0041E875@@QAE@XZ @0x0041E875 113B.
// Dtor of the 0x28-byte GUI class also owning 0x0041E7F2/0x0041E732: three
// AsciiStrings at +0/+4/+8, first vector buffer at +0xC, flag at +0x18,
// second vector (void*) at +0x1C drained by 0x0041E7F2 then freed.
// Retail calls E7F2, frees [0x1C], frees [0xC], releases +8/+4/+0 with EH
// states 4>3>2>1>0>-1. Evidence: callees rowed E7F2, _free 0x00030830,
// releaseBuffer 0x00036410; caller dtor chain via 0x0041E8F6/0x0041EC73.
// Reuse the existing native 17-byte unsigned max specialization.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include "ascii_string.h"
#include <vector>

class Rva0041E7F2
{
public:
	void rva0041E7F2();
};

class ModuleData;

// Reuse the existing 49-byte native push-back provider at 0x004DFCB0
// (stlport_moduledatavector_push.cpp), which calls the 140-byte growth
// provider at 0x002DFCF6 (ModuleFactory.cpp). The application element
// identity remains unresolved outside the established caller contexts.
namespace _STL {
template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(
    const ModuleData *const &);
}

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva0041E875
{
public:
	~Rva0041E875();
	void rva0041E8E6(const ModuleData *arg);
private:
	AsciiString m_s0;
	AsciiString m_s1;
	AsciiString m_s2;
	_STL::vector<BfmeE16> m_vec1;
	bool m_flag;
	char m_padFlag[3];
	_STL::vector<const ModuleData *> m_vec2;
};

Rva0041E875::~Rva0041E875()
{
	((Rva0041E7F2 *)this)->rva0041E7F2();
}

void Rva0041E875::rva0041E8E6(const ModuleData *arg)
{
	m_vec2.push_back(arg);
}
