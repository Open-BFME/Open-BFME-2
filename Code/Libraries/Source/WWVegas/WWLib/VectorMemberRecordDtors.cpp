// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
//
// Record destructors whose members are STLport vectors. All callees are
// matched rows or pins; owner types beyond the pin names are unrecovered.
//
// ??1BfmeStringRecord00111ACF@@QAE@XZ @0x003F60C8 60B: POD vector buffer at
//   +0x10 freed inline, then vector<Rva003F610FElement> at +0x04 (0x003F5E85).
// ??1Rva003F610FElement@@QAE@XZ @0x003F535B 60B (0x30-byte element): vector
//   <BfmeAssignRecord104> at +0x10 (0x003B904B), then POD buffer at +0x04.
// ??1RvaVecAnimSet@@QAE@XZ @0x001F0D04 63B: vector<AnimSet> body inline,
//   _Destroy<AnimSet*> (0x001F0801) then free of the buffer.
// ??1TensileFormationUpdateMember@@QAE@XZ @0x004BA35A 63B: same shape over
//   the rowed Rva004BA341DestroyRange (0x2C-stride Rva004BA1C8 records).
#include <vector>

#include <stdlib.h>

template <class T> class OpaqueVector
{
public:
	~OpaqueVector();

private:
	T *m_begin;
	T *m_finish;
	T *m_end;
};

struct Rva003F610FElement;
struct BfmeAssignRecord104;

namespace _STL
{
template <> class vector<Rva003F610FElement, allocator<Rva003F610FElement> >
{
public:
	~vector();

private:
	Rva003F610FElement *m_begin;
	Rva003F610FElement *m_finish;
	Rva003F610FElement *m_end;
};

template <> class vector<BfmeAssignRecord104, allocator<BfmeAssignRecord104> >
{
public:
	~vector();

private:
	BfmeAssignRecord104 *m_begin;
	BfmeAssignRecord104 *m_finish;
	BfmeAssignRecord104 *m_end;
};
}

struct BfmeStringRecord00111ACF
{
	~BfmeStringRecord00111ACF();
	int m_00;
	_STL::vector<Rva003F610FElement> m_04;
	_STL::vector<int> m_10;
};
inline BfmeStringRecord00111ACF::~BfmeStringRecord00111ACF() {}

struct Rva003F610FElement
{
	~Rva003F610FElement();
	int m_00;
	_STL::vector<int> m_04;
	_STL::vector<BfmeAssignRecord104> m_10;
	int m_1C[5];
};
Rva003F610FElement::~Rva003F610FElement() {}

struct GenericObjectCreationNugget
{
	struct AnimSet;
};

// Declared-only specialization: the call resolves to the pinned retail
// _Destroy<AnimSet*> body.
namespace _STL
{
template <> void _Destroy<GenericObjectCreationNugget::AnimSet *>(
	GenericObjectCreationNugget::AnimSet *first, GenericObjectCreationNugget::AnimSet *last);
}

// vector_base-shaped owner: the buffer free runs in the base dtor, which
// gives retail's EH state around it.
template <class T> struct RvaVectorBuffer
{
	~RvaVectorBuffer()
	{
		if (m_begin)
			free(m_begin);
	}
	T *m_begin;
	T *m_finish;
	T *m_end;
};

struct RvaVecAnimSet : RvaVectorBuffer<GenericObjectCreationNugget::AnimSet>
{
	~RvaVecAnimSet();
};
RvaVecAnimSet::~RvaVecAnimSet()
{
	_STL::_Destroy(m_begin, m_finish);
}

class Rva004BA1C8;
void Rva004BA341DestroyRange(Rva004BA1C8 *first, Rva004BA1C8 *last);

struct TensileFormationUpdateMember : RvaVectorBuffer<Rva004BA1C8>
{
	~TensileFormationUpdateMember();
};
TensileFormationUpdateMember::~TensileFormationUpdateMember()
{
	Rva004BA341DestroyRange(m_begin, m_finish);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeBfmeStringRecord00111ACFInlineAnchor@@YAXPAVBfmeStringRecord00111ACF@@@Z absent-from-retail
void _bfmeBfmeStringRecord00111ACFInlineAnchor(BfmeStringRecord00111ACF *p)
{
    p->BfmeStringRecord00111ACF::~BfmeStringRecord00111ACF();
}
#pragma inline_depth()
