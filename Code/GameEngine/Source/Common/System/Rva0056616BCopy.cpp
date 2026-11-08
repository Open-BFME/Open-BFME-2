// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ??0Rva0056616B@@QAE@ABV0@@Z @0x0052D555 333B
// Copy ctor for Rva0056616B (vtable 0x008689D0) copying 16 members in order via rowed StringBase 0x365F0 vector copy ctors and custom copies then byte at +0xB4.
// Evidence: unlock lane; callees all rowed per packet (StringBase EnableRegionRecord Pod40 Pod88 Rva0052BDE6 Rva0052BE33 AsciiString Pod32 Rva004E32F2 Rva0052CD81 Rva0052C867 Rva0052C8AB E16 Rva005668E9 Rva0052BEF0); prev vector copy family next deleting dtor share layout.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "ascii_string.h"

class EnableRegionRecord;
struct BfmePod40;
struct BfmePod88;
class Rva0052BDE6;
class Rva0052BE33;
struct BfmePod32;
class Rva003A6F70;
class Rva004E32F2;
class Rva0052CD81;
class Rva0052C867;
class Rva0052C8AB;
class Rva004E1A04;
struct Rva005668E9Element;
class Rva0052BEF0;

// The native cleanup at 0x0079727B calls the existing 63B owner at
// 0x0052CCC4. Its verified three-pointer vector destruction supplies the
// storage cleanup; this does not establish the original element type.
template <class T> struct RvaCopyVectorStorage {
 T *m_start; T *m_finish; T *m_end;
 ~RvaCopyVectorStorage() { if (m_start) free(m_start); }
};
struct Rva0052BF9BElem;
void __cdecl Rva0022C8E3DestroyRange(Rva0052BF9BElem *, Rva0052BF9BElem *);

namespace _STL {
template <typename T> class allocator {};
template <typename T, typename A> class vector : public RvaCopyVectorStorage<T> {
public:
	vector(const vector &other);
	~vector();
};
}

namespace _STL {
template <> __declspec(noinline) vector<Rva0052BE33, allocator<Rva0052BE33> >::~vector()
{
 Rva0022C8E3DestroyRange(reinterpret_cast<Rva0052BF9BElem *>(m_start),
                       reinterpret_cast<Rva0052BF9BElem *>(m_finish));
}
}

struct Rva0052BF33Elem;
void __cdecl Rva005A6EDADestroyRange(Rva0052BF33Elem *, Rva0052BF33Elem *);

namespace _STL {
template <> __declspec(noinline) vector<EnableRegionRecord, allocator<EnableRegionRecord> >::~vector()
{
 Rva005A6EDADestroyRange(reinterpret_cast<Rva0052BF33Elem *>(m_start),
                       reinterpret_cast<Rva0052BF33Elem *>(m_finish));
}
}

struct Rva0052BF4DElem;
void __cdecl Rva0052C266DestroyRange(Rva0052BF4DElem *, Rva0052BF4DElem *);

namespace _STL {
template <> __declspec(noinline) vector<BfmePod40, allocator<BfmePod40> >::~vector()
{
 Rva0052C266DestroyRange(reinterpret_cast<Rva0052BF4DElem *>(m_start),
                       reinterpret_cast<Rva0052BF4DElem *>(m_finish));
}
}

struct Rva004E1AD5Item;
void __cdecl Rva004E1FCCGet(Rva004E1AD5Item *, Rva004E1AD5Item *);

namespace _STL {
template <> __declspec(noinline) vector<BfmePod88, allocator<BfmePod88> >::~vector()
{
 Rva004E1FCCGet(reinterpret_cast<Rva004E1AD5Item *>(m_start),
                       reinterpret_cast<Rva004E1AD5Item *>(m_finish));
}
}

struct Rva0052BFB5Elem;
void __cdecl Rva0052C37ADestroyRange(Rva0052BFB5Elem *, Rva0052BFB5Elem *);

namespace _STL {
template <> __declspec(noinline) vector<Rva0052BDE6, allocator<Rva0052BDE6> >::~vector()
{
 Rva0052C37ADestroyRange(reinterpret_cast<Rva0052BFB5Elem *>(m_start),
                       reinterpret_cast<Rva0052BFB5Elem *>(m_finish));
}
}

struct Rva0052BF67Elem;
void __cdecl Rva0052C3BFDestroyRange(Rva0052BF67Elem *, Rva0052BF67Elem *);

namespace _STL {
template <> __declspec(noinline) vector<BfmePod32, allocator<BfmePod32> >::~vector()
{
 Rva0052C3BFDestroyRange(reinterpret_cast<Rva0052BF67Elem *>(m_start),
                       reinterpret_cast<Rva0052BF67Elem *>(m_finish));
}
// The same 63-byte body under its real element (0x0052C823's vector<Rva003A6F70>).
template <> __declspec(noinline) vector<Rva003A6F70, allocator<Rva003A6F70> >::~vector()
{
 Rva0052C3BFDestroyRange(reinterpret_cast<Rva0052BF67Elem *>(m_start),
                       reinterpret_cast<Rva0052BF67Elem *>(m_finish));
}
}

class LivingWorldRegionConnection;
void __cdecl Rva003F0CA1_DestroyRange(LivingWorldRegionConnection *, LivingWorldRegionConnection *);

namespace _STL {
template <> __declspec(noinline) vector<Rva004E32F2, allocator<Rva004E32F2> >::~vector()
{
 Rva003F0CA1_DestroyRange(reinterpret_cast<LivingWorldRegionConnection *>(m_start),
                       reinterpret_cast<LivingWorldRegionConnection *>(m_finish));
}
}

class Rva004E1A04;
void __cdecl Rva0052CEDDClear(Rva004E1A04 *, Rva004E1A04 *);

namespace _STL {
template <> __declspec(noinline) vector<Rva004E1A04, allocator<Rva004E1A04> >::~vector()
{
 Rva0052CEDDClear(reinterpret_cast<Rva004E1A04 *>(m_start),
                       reinterpret_cast<Rva004E1A04 *>(m_finish));
}
}

class Rva004E366E;
void __cdecl Rva0052CEF6Clear(Rva004E366E *, Rva004E366E *);

namespace _STL {
template <> __declspec(noinline) vector<Rva005668E9Element, allocator<Rva005668E9Element> >::~vector()
{
 Rva0052CEF6Clear(reinterpret_cast<Rva004E366E *>(m_start),
                       reinterpret_cast<Rva004E366E *>(m_finish));
}
}

// The parent's other three member cleanups (native unwind funclets
// 0x007972B2 at +0x6C, 0x007972BD at +0x78, 0x007972C8 at +0x84) jump to the
// same 63B three-pointer owners: +0x6C to 0x0052CCC4 (range 0x0022C8E3, as for
// m_38 above), +0x78 and +0x84 to 0x0052CDE1 (range _Destroy 0x00319784).
// Their members are the vector-shaped records whose copy constructors are
// rowed at 0x0052CD81, 0x0052C867 and 0x0052C8AB; these destructors give
// those records' cleanup names the existing owner bodies.
class Rva0052CD81 : public RvaCopyVectorStorage<Rva0052BF9BElem>
{
public:
	Rva0052CD81(const Rva0052CD81 &other);
	~Rva0052CD81();
};
__declspec(noinline) Rva0052CD81::~Rva0052CD81()
{
 Rva0022C8E3DestroyRange(m_start, m_finish);
}

struct Elem003AF9E0;
namespace _STL {
template <class _ForwardIterator> void _Destroy(_ForwardIterator, _ForwardIterator);
template <> void _Destroy<Elem003AF9E0 *>(Elem003AF9E0 *, Elem003AF9E0 *);
}

class Rva0052C867 : public RvaCopyVectorStorage<Elem003AF9E0>
{
public:
	Rva0052C867(const Rva0052C867 &other);
	~Rva0052C867();
};
__declspec(noinline) Rva0052C867::~Rva0052C867()
{
 _STL::_Destroy(m_start, m_finish);
}

class Rva0052C8AB : public RvaCopyVectorStorage<Elem003AF9E0>
{
public:
	Rva0052C8AB(const Rva0052C8AB &other);
	~Rva0052C8AB();
};
__declspec(noinline) Rva0052C8AB::~Rva0052C8AB()
{
 _STL::_Destroy(m_start, m_finish);
}

// The copy parent and its EH rows live in Rva0056616BCopyDeferred.cpp.
