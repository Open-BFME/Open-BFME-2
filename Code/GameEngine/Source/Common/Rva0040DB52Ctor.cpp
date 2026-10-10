// cl: /O1 /Ob2 /G7 /arch:SSE /GX- /Oy- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0Rva0040DB52@@QAE@XZ, retail 0x0040E039, 98 bytes.
// Default constructor of the Snapshot-derived holder (vtable 0x008394CC): clears the flag at
// +0x0C, sets the color word at +0x10 to 0xFF000000, builds the two empty vectors at +0x14 and
// +0x20 through the rowed empty _Vector_base 0x00211E58 (kept out of line, as in the retail
// code), zeroes the two floats at +4 and +8, and clears both vectors through the rowed
// ParticleSystemID-vector erase 0x00532803 and pointer erase 0x0031BD55 (the erase bodies are
// shared across element types). Evidence: target bytes, the rowed callees and the existing
// Rva0040DB52 destructor/xfer units; field names are neutral views.
#include <vector>
#include "Common/Snapshot.h"

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

enum ParticleSystemID
{
	PARTICLE_SYSTEM_INVALID = 0
};

namespace _STL {
template <> __declspec(noinline) _Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16> &a)
	: _M_start(0), _M_finish(0), _M_end_of_storage(a, (BfmeE16 *)0)
{
}
}

class Rva0040DB52 : public Snapshot
{
public:
	Rva0040DB52();
	virtual ~Rva0040DB52();
protected:
	virtual void xfer(Xfer *xfer);
private:
	float m_04;
	float m_08;
	bool m_0C;
	unsigned int m_10;
	_STL::vector<BfmeE16> m_vec14;
	_STL::vector<BfmeE16> m_vec20;
};

Rva0040DB52::Rva0040DB52()
	: m_0C(false), m_10(0xFF000000), m_vec14(_STL::allocator<BfmeE16>()), m_vec20(_STL::allocator<BfmeE16>())
{
	m_04 = 0.0f;
	m_08 = 0.0f;
	_STL::vector<ParticleSystemID> *ids = (_STL::vector<ParticleSystemID> *)&m_vec14;
	_STL::vector<void *> *rest = (_STL::vector<void *> *)&m_vec20;
	ids->erase(ids->begin(), ids->end());
	rest->erase(rest->begin(), rest->end());
}
