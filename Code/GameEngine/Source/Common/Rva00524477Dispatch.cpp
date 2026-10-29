// cl: /Ireference/shims/bfme2_ascii /MD
// Range-27 string-out-param dispatch.
// ?Rva00524477@Holder00524477@@QAEXHH@Z @0x00524477 101B
// Thiscall (a1, a2): bails when the 0x00DFE4CC singleton is null, else
// fills an 8-byte {int, AsciiString} out-block through pinned 0x0023FC23
// (AsciiString member rides uninitialized; destroyed explicitly through
// the shim inline dtor = rowed releaseBuffer 0x00036410), forwards the
// result triple through the int-returning spelling of rowed 0x005243FA
// (pinned; the body forwards 0x0052408B's eax), and on a changed m_10
// runs the singleton's rowed 0x002245FF plus m_C's rowed 0x00523EC8.
// Link: declare ~AsciiString only (the shim's documented per-unit switch) so this TU calls the out-of-line
// retail destructor instead of emitting a non-retail ??_GAsciiString copy; the // cl: line is untouched.
#ifndef BFME_ASCII_DTOR_DECL
#define BFME_ASCII_DTOR_DECL
#endif
#include "ascii_string.h"

struct Out00524477
{
	int m_0;
	AsciiString m_4;
};

// Native three-word cdecl hidden-return ABI matches the recovered STLport
// make_pair provider. Its generated linker alias retains this legacy view;
// typed-return trials add EH data or trigger MSVC7.1 ICE in this flat-frame unit.
int Rva0023FC23(Out00524477 *out, int *a1, int a2);
int Rva005243FA(int a, int b, int c);

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
class AptPlayer
{
public:
	void RemoveOverButtonHandler(int a1, const AsciiString &name);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Holder00524477
{
	char m_pad[0xC];
	C00524477 m_C;
	int m_10;
	void Rva00524477(int level, int a2);
};

void Holder00524477::Rva00524477(int level, int a2)
{
	if ((*(AptPlayer **)&g_bfmeAptWindowManager) == 0)
		return;
	char buf[8];
	Out00524477 *out = (Out00524477 *)buf;
	int searchKey = Rva0023FC23(out, &level, a2);
	int rangeEnd = m_10;
	int rangeBegin = m_C.m_0;
	int rr = Rva005243FA(rangeBegin, rangeEnd, searchKey);
	((AsciiString *)(buf + 4))->~AsciiString();
	if (rr == m_10)
		return;
	(*(AptPlayer **)&g_bfmeAptWindowManager)->RemoveOverButtonHandler(level, *(const AsciiString *)a2);
	((CameraMarkerVector *)&m_C)->erase((CameraMarker *)rr);
}
