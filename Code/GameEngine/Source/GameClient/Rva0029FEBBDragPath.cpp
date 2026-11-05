// ?rva0029FEBB@Rva0029FEBB@@QAEXUICoord2D@@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /ICode/Libraries/Include /ICode/GameEngine/Source/Common /Ireference/shims/bfmealloc
// stlport
// ?rva0029FEBB@Rva0029FEBB@@QAEXUICoord2D@@@Z retail 0x0029FEBB 324B (RET 8)
// d3 seat7 rebuild from WB twin 0xDB6240: by-value ICoord2D argument copied to a local pos (that alone fixes
// the 0x1c frame and the EDI/EBX/ESI register map earlier banks missed), list<ICoord2D> at +0x910, IRegion-like
// lo/hi ints at +0x914..+0x920, TheMouse drag tolerance (+0x12e8) / 3, length/normalize rowed, scale inlined.
// The rowed Coord3D::length (0x00003571) and ::normalize (0x000035B6) are defined below, visible and out
// of line (bodies as AIAttackApproachComputePath.cpp; the length copy is retail's): with them cl loads the
// drag tolerance before the vec.x store as retail does. The list's push_back is ICF-folded with the rowed
// list<BfmeSpecialPowerTimer8>::push_back (0x004DE74D, same 8-byte element), which this unit calls.
#include <list>
// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper
// (retail keeps one _List_iterator_base::operator!=; BfmeAptScreenLanLobbyOnInitGadget.cpp pattern).
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "Lib/Coord3D.h"
#include "Lib/ICoord2D.h"
#include "BfmeSpecialPowerTimer8.h"

// The canonical Mouse keeps the drag tolerance (+0x12E8) in opaque storage.
#include "../../Include/GameClient/Mouse.h"

class Rva0029FEBB
{
public:
	void rva0029FEBB(ICoord2D in);
private:
	char m_pad[0x910];
	_STL::list<ICoord2D> m_points; // +0x910
	int m_loX; // +0x914
	int m_loY; // +0x918
	int m_hiX; // +0x91c
	int m_hiY; // +0x920
};

#include <math.h>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
__declspec(noinline) inline float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

__declspec(noinline) inline void Coord3D::normalize()
{
	float len = length();
	if (len != 0.0f) {
		float scale = 1.0f / len;
		x *= scale;
		y *= scale;
		z *= scale;
	}
}

void Rva0029FEBB::rva0029FEBB(ICoord2D in)
{
	ICoord2D pos = in;
	if (m_points.size() == 0)
	{
		m_loX = pos.x;
		m_hiX = pos.x;
		m_loY = pos.y;
		m_hiY = pos.y;
	}
	else
	{
		const ICoord2D &last = m_points.back();
		ICoord2D delta;
		delta.x = pos.x - last.x;
		delta.y = pos.y - last.y;
		Coord3D vec;
		vec.x = (float)delta.x;
		unsigned int tol = *(const unsigned int *)TheMouse->field12E8;
		vec.y = (float)delta.y;
		int thresh = tol / 3;
		vec.z = 0.0f;
		if (vec.length() < thresh)
			return;
		if (vec.length() > thresh * 10.0f)
		{
			vec.normalize();
			float s = thresh * 9.9f;
			pos.x = (int)(s * vec.x) + last.x;
			pos.y = (int)(s * vec.y) + last.y;
		}
		if (pos.x < m_loX)
			m_loX = pos.x;
		else if (pos.x > m_hiX)
			m_hiX = pos.x;
		if (pos.y < m_loY)
			m_loY = pos.y;
		else if (pos.y > m_hiY)
			m_hiY = pos.y;
	}
	reinterpret_cast<_STL::list<BfmeSpecialPowerTimer8> &>(m_points).push_back(reinterpret_cast<const BfmeSpecialPowerTimer8 &>(pos));
}
