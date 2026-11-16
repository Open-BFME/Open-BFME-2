// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// Range-27 over-button removal.
// ?Rva00524477@Holder00524477@@QAEXHH@Z @0x00524477 101B
#include "ascii_string.h"
#include <utility>

namespace _STL
{
template <> pair<int, AsciiString> make_pair<int, AsciiString>(const int &, const AsciiString &);
}

int find(int a, int b, int c) throw();

// The existing find row still spells its three pointer arguments as integers.
static inline int find(int first, int last, const _STL::pair<int, AsciiString> &key) throw()
{
	return find(first, last, reinterpret_cast<int>(&key));
}

struct C00524477
{
	int m_0;
};

// Row spelling: 0x00523EC8 is vector<CameraMarker>::erase(iterator) over m_C.
struct CameraMarker;
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	T *erase(T *position);
};
}
typedef _STL::vector<CameraMarker, _STL::allocator<CameraMarker> > CameraMarkerVector;

// Row spelling: 0x002245FF is AptPlayer::RemoveOverButtonHandler.
#include "../../../Libraries/Source/Apt/AptPlayerClass.h"

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Holder00524477
{
	char m_pad[0xC];
	C00524477 m_C;
	int m_end;
	void Rva00524477(int level, int a2);
};

void Holder00524477::Rva00524477(int level, int a2)
{
	if ((*(AptPlayer **)&g_bfmeAptWindowManager) == 0)
		return;
	int rr = find(m_C.m_0, m_end,
		_STL::make_pair(level, *reinterpret_cast<const AsciiString *>(a2)));
	if (rr == m_end)
		return;
	(*(AptPlayer **)&g_bfmeAptWindowManager)->RemoveOverButtonHandler(level, *(const AsciiString *)a2);
	((CameraMarkerVector *)&m_C)->erase((CameraMarker *)rr);
}
