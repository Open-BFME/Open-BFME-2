// Split from GapBodiesSeat10O1.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Small unrowed .text bodies from the 0x0051xxxx..0x005Fxxxx (/O1) region.
// Retail bytes establish every shape; the owning classes are not recovered,
// so each keeps an address-derived name and a view of only the fields it
// touches. Bodies reached through a vftable slot (an absolute reference in
// .rdata, no direct caller) are declared virtual; the others have no
// recovered caller. Callees are the rowed bodies the retail jmp targets.

// ?rva00531041@Rva00531041@@QAEXXZ @0x00531041 9B: clear +0x10 then +0x0C.


// ?rva0054C836@Rva0054C836@@QBE_NXZ @0x0054C836 9B: pointer at +0x14 non-null.


// ?rva005FC6EE@Rva005FC6EE@@QBE_NXZ @0x005FC6EE 9B: bit 0 of the byte at +0x34
// of the object held at +0x18 (same shape as the rowed 0x005F273B).


// ?rva005CCBA8@Rva005CCBA8@@QAEXXZ @0x005CCBA8 8B: clear the byte at +0x20 of
// the object held at +0x08.


// Vector members whose rowed grow/resize bodies the slots tail-jump to.
template <class T>
struct Rva00584A7DVector
{
	void grow(unsigned int count);
};
struct Rva00584A7DEntry;
struct Rva00587057Entry;
struct BfmePod60;
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> >
	class vector
	{
	public:
		void resize(unsigned int count);
		T *erase(T *first, T *last);
		void clear();
		void _M_fill_insert(T *position, unsigned int count, const T &value);
	private:
		T *_M_start;
		T *_M_finish;
		T *_M_end_of_storage;
	};
	template <class T, class A = allocator<T> >
	class deque
	{
	public:
		~deque();
		void pop_front();
		void push_back(const T &value);
	};
	template <class A, class B> struct pair;
	template <class P> struct _Select1st;
	template <class T> struct less;
	template <class K, class V, class KoV, class C, class A>
	class _Rb_tree
	{
	public:
		~_Rb_tree();
		void clear();
		unsigned int erase(const K &key);
	};
	template <class T> struct _Identity;
	template <class T, class A> class list;
}

// ?rva00584A75@Rva00584A75@@UAEXI@Z @0x00584A75 8B (vftable slot at VA
// 0x00C6FC84): grow the +0x08 vector through rowed 0x00584A3D.


// ?rva0058704F@Rva0058704F@@UAEXI@Z @0x0058704F 8B (vftable slot at VA
// 0x00C6FD94): grow the +0x08 vector through rowed 0x0058702C.


// ?rva00588A95@Rva00588A95@@UAEXI@Z @0x00588A95 8B (vftable slot at VA
// 0x00C6FF3C): resize the +0x08 vector through rowed 0x00588A72.


// ?rva005CFACB@Rva005CFACB@@UAEXXZ @0x005CFACB 8B (vftable slot at VA
// 0x00C75558): forward to the rowed 0x005EA91A on the +0x0C member.


// ?rva00574AB3@Rva00574AB3@@UAE_NXZ @0x00574AB3 8B (vftable slot at VA
// 0x00C3C6D0): direct (qualified) call of the rowed Rva005743C0 slot body
// 0x005743C0 on the object held at +0x04.


// Out-of-line destructors whose only non-trivial member sits at +0, so each
// is a bare tail jump to that member's rowed destructor. Each is reached
// only from EH unwind funclets (0x0079xxxx..0x007Axxxx), i.e. it destroys a
// local of its type; the owning types are unrecovered.
class AsciiString;
struct TreeHintRef0051030C;
struct BfmeOpaque2148;
struct SBServer;

typedef _STL::pair<const AsciiString, TreeHintRef0051030C> Rva00510D07Pair;
typedef _STL::pair<const int, SBServer> Rva005E4920Pair;

// ??1Rva00510D07@@QAE@XZ @0x00510D07 5B: tree member, rowed dtor 0x0051097F.


// ??1Rva00550634@@QAE@XZ @0x00550634 5B: BfmeMsg member, rowed dtor 0x00655780.


// ??1Rva00551983@@QAE@XZ @0x00551983 5B: deque member, rowed dtor 0x00551868.


// ??1Rva005E4920@@QAE@XZ @0x005E4920 5B: tree member, rowed dtor 0x005E4670.


// ??1Rva0060D0AE@@QAE@XZ @0x0060D0AE 5B: member, rowed dtor 0x0060D031.


// ?rva00525E00@Rva00525E00@@QAEXPAVXfer@@@Z @0x00525E00 7B (called from
// 0x002D64C7): forward the Xfer to the rowed 0x00525ABF on the object held
// at +0.
class Xfer;
class Rva00525ABF
{
public:
	void rva00525ABF(Xfer *xfer);
};
class Rva00525E00
{
public:
	void rva00525E00(Xfer *xfer);
private:
	Rva00525ABF *m_00;
};
void Rva00525E00::rva00525E00(Xfer *xfer)
{
	m_00->rva00525ABF(xfer);
}

// ?rva0050EE1C@Rva0050EE1C@@QBEHXZ @0x0050EE1C 7B: the rowed
// AsciiStringPlusString::length 0x002198C8 of this object plus one.


// ?rva00522AFC@Rva00522AFC@@QAEAAV1@ABV1@@Z @0x00522AFC 18B: assignment of an
// object whose only member is an AsciiString->AsciiString tree, through the
// rowed tree operator= 0x0052274D, returning this.
typedef _STL::pair<const AsciiString, AsciiString> Rva00522AFCPair;
namespace _STL
{
	template <>
	class _Rb_tree<AsciiString, Rva00522AFCPair, _Select1st<Rva00522AFCPair>, less<AsciiString>, allocator<Rva00522AFCPair> >
	{
	public:
		_Rb_tree &operator=(const _Rb_tree &other);
	};
}


// ?Rva0051C3AB@@YAXAAUBfmeE12@@0@Z @0x0051C3AB 5B: swap two 12-byte records
// through the rowed _STL::swap<BfmeE12> 0x004219CD (a tail jump).
struct BfmeE12;
namespace _STL
{
	template <class T> void swap(T &a, T &b);
}
void Rva0051C3AB(BfmeE12 &a, BfmeE12 &b);


// ?rva005206FE@Rva005206FE@@QAEXPAURva005205DAElement@@IABU2@@Z @0x005206FE
// 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert
// 0x005205DA (a tail jump with the arguments forwarded).
struct Rva005205DAElement;
namespace _STL
{
	template <>
	class vector<Rva005205DAElement, allocator<Rva005205DAElement> >
	{
	public:
		void _M_fill_insert(Rva005205DAElement *position, unsigned int count, const Rva005205DAElement &value);
	};
}


// ?rva00531C54@Rva00531C54@@QAEXXZ @0x00531C54 6B: clear the 16-bit field at +2.

int Rva00531EF6(unsigned short value);


// ?rva0053B8F1@Rva0053B8F1@@QBE_NXZ @0x0053B8F1 7B: the flag byte at +0x106.


// ?rva0056864A@Rva0056864A@@QBEEXZ @0x0056864A 7B: high nibble of the byte at +0x47.


// ?rva005778D1@Rva005778D1@@QBEHXZ @0x005778D1 9B and
// ?rva005778DA@Rva005778D1@@QAEPAXXZ @0x005778DA 9B: through the object held
// at +0x40 to its first-word pointee, read its +4 word / take its +8 address.



// ?rva00564B12@Rva00564B12@@QAEAAVRva005045DBTree@@ABV2@@Z @0x00564B12 8B:
// assign the +0x0C tree through the rowed Rva005045DBTree::assign 0x005045DB.


// ?rva005CCB54@Rva005CCB54@@QBEEXZ @0x005CCB54 7B: the byte at +0x23 of the
// object held at +0x08.


// ?rva005CDD20@Rva005CDD20@@QAEXXZ @0x005CDD20 5B: clear the +0x24 word.


// ?rva005E2D46@Rva005E2D46@@QBEHXZ @0x005E2D46 5B: the +0x08 word plus one.


// ?rva005FF1F8@Rva005FF1F8@@QBEHXZ @0x005FF1F8 15B: element count of the
// 8-byte-element vector at +0x30 of the object held at +0x04 (same shape as
// the rowed Rva005F8427::rva005F8408).


// ?rva005E88E4@Rva005E88E4@@QAEXXZ @0x005E88E4 10B: the rowed 0x005F884D on
// the +0x04 member of the object held at +0.


// ?rva005E358A@Rva005E358A@@QAEXXZ @0x005E358A 5B and
// ?rva005EB8D1@Rva005EB8D1@@QAEXXZ @0x005EB8D1 5B: tail jumps to the rowed
// 0x005F1B51 / 0x0022999F on the member at +0.



// By-value iterator/pair wrappers over a rowed lookup on the member at +0:
// the hidden return slot is passed straight through (or filled from eax)
// and returned.

// ?rva005538BA@Rva005538BA@@QAE?AURva005538BAIterator@@PBX@Z @0x005538BA 20B:
// wrap the node pointer from the rowed 0x005533BC lookup.


// ?rva00601457@Rva00601457@@QAE?AURva006013B7Pair@@ABURva00600F9CElement@@@Z
// @0x00601457 20B: forward to the rowed 0x006013B7.
struct Rva00600F9CElement;


// ?rva0060CC71@Rva0060CC71@@QAE?AURva0060CAEAIterator@@ABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z
// @0x0060CC71 20B: forward to the rowed 0x0060CB61.
namespace _STL
{
	template <class C> class char_traits;
	template <class C, class T, class A> class basic_string;
}
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > Rva0060CC71String;


// STLport vector::clear() is erase(begin(), end()): these instantiations
// push the +4 finish and +0 start words and call the rowed erase(first,
// last) of the same vector. ?clear@?$vector@URva0054107FRecord@@...@QAEXXZ
// @0x00541BC9 11B (erase 0x0054152D), ?clear@?$vector@VRva0054103E@@...
// @0x00541BD4 11B (erase 0x00541553) and ?clear@?$vector@URva00565865Element@@...
// @0x00565A7E 11B (erase 0x00565865).
template <class T, class A>
void _STL::vector<T, A>::clear()
{
	erase(_M_start, _M_finish);
}
struct Rva0054107FRecord;
class Rva0054103E;
struct Rva00565865Element;
template void _STL::vector<Rva0054107FRecord>::clear();
template void _STL::vector<Rva0054103E>::clear();
template void _STL::vector<Rva00565865Element>::clear();

// ?rva00600396@Rva00600396@@QAEHXZ @0x00600396 15B: the rowed 0x003F468D on
// the object held at +0x14 with the +0x18 and +0x1C words.


// Queue-style wrappers over a deque held at +0: each is a bare tail jump to
// the rowed deque<T>::pop_front / push_back of the same instantiation. The
// owning adaptor types are unrecovered, so each keeps an address name.
class PingRequest;
class BuddyRequest;
struct BfmeOpaqueOwnedRecord1432;
struct BfmeOpaqueOwnedRecord1408;

// ?rva0054FF12@Rva0054FF12@@QAEXXZ @0x0054FF12 5B: deque<PingRequest>::pop_front.


// ?rva00550C81@Rva00550C81@@QAEXXZ @0x00550C81 5B: deque<BuddyRequest>::pop_front.


// ?rva00550C86@Rva00550C86@@QAEXXZ @0x00550C86 5B: deque<BfmeOpaque2148>::pop_front.


// ?rva00551B1E@Rva00551B1E@@QAEXABVBuddyRequest@@@Z @0x00551B1E 5B: deque<BuddyRequest>::push_back.


// ?rva00551B23@Rva00551B23@@QAEXABUBfmeOpaque2148@@@Z @0x00551B23 5B: deque<BfmeOpaque2148>::push_back.


// ?rva00557B46@Rva00557B46@@QAEXXZ @0x00557B46 5B: deque<BfmeOpaqueOwnedRecord1432>::pop_front.


// ?rva00557BA2@Rva00557BA2@@QAEXXZ @0x00557BA2 5B: deque<BfmeOpaqueOwnedRecord1408>::pop_front.


// ?rva00559131@Rva00559131@@QAEXABUBfmeOpaqueOwnedRecord1432@@@Z @0x00559131 5B: deque<BfmeOpaqueOwnedRecord1432>::push_back.


// ?rva00559136@Rva00559136@@QAEXABUBfmeOpaqueOwnedRecord1408@@@Z @0x00559136 5B: deque<BfmeOpaqueOwnedRecord1408>::push_back.


// cdecl destroy helpers: ecx = the argument, then a tail jump to the rowed
// destructor (or reset member) of the pointee.
class Rva004E1A04
{
public:
	~Rva004E1A04();
};
#include "../../Include/Common/Rva004E366E.h"
class Rva005344C0
{
public:
	~Rva005344C0();
};
class Rva00568C4E
{
public:
	~Rva00568C4E();
};
#include "../../Include/Common/BfmePoolRef10.h"
void Rva0052BFCF(Rva004E1A04 *p);

void Rva0052BFD8(Rva004E366E *p);

void Rva00534626(Rva005344C0 *p);

void Rva005690DE(Rva00568C4E *p);

void Rva005690E7(BfmePoolRef10 *p);


// Bare tail jumps to a rowed member of the object at +0.

// ?rva0055381C@Rva0055381C@@QAEXXZ @0x0055381C 5B: Rva0038201D::rva003828B6 on the member at +0.


// ?rva00553821@Rva00553821@@QAEXXZ @0x00553821 5B: Rva0038204A::rva003828DF on the member at +0.


// ?rva00553826@Rva00553826@@QAEXXZ @0x00553826 5B: Rva00382077::rva00382908 on the member at +0.


// ?rva0055382B@Rva0055382B@@QAEXXZ @0x0055382B 5B: Rva005532D6::rva005532D6 on the member at +0.



// ?rva0056FCC7@Rva0056FCC7@@QBE_NABVGen_0054EC50@@@Z @0x0056FCC7 5B: Gen_0054EC50::bfmeDiffers on the member at +0.


// ?rva0056FCCC@Rva0056FCCC@@QBE_NABVGen_0054EC80@@@Z @0x0056FCCC 5B: Gen_0054EC80::bfmeDiffers on the member at +0.


// ?rva0056FCD1@Rva0056FCD1@@QBE_NABVRva0056FA50@@@Z @0x0056FCD1 5B: Rva0056FA50::rva0056FA50 on the member at +0.


// ?rva0056FCD6@Rva0056FCD6@@QBE_NABVRva0056FA72@@@Z @0x0056FCD6 5B: Rva0056FA72::rva0056FA72 on the member at +0.


// ?rva005709CC@Rva005709CC@@QAE_NXZ @0x005709CC 5B: the rowed
// AptOnlineLogin::rva005706D4 0x005706D4 on the member at +0.


// ?rva005693CF@Rva005693CF@@QAEXXZ @0x005693CF 5B: clear the key tree at +0
// through the rowed _Rb_tree::clear 0x0056926C.
struct Rva00568FE4Key;
struct Rva00568FE4Less;


// ??1Rva00534765@@QAE@XZ @0x00534765 5B: member-only dtor, rowed 0x0053470B.


// ?rva00531EB8@Rva00531EB8@@QAEXXZ @0x00531EB8 4B: advance the +0 pointer by one word.


// ?rva00586FBB@Rva00586FBB@@QAEXPAVRva00585B16@@IABV2@@Z @0x00586FBB 5B and
// ?rva005880B8@Rva005880B8@@QAEXPAURva00587375@@IABU2@@Z @0x005880B8 5B:
// fill-insert into the vector at +0 through the rowed _M_fill_insert.
class Rva00585B16;
struct Rva00587375;



// ?rva005F600D@Rva005F600D@@QAEXH@Z @0x005F600D 7B and
// ?rva005F6014@Rva005F600D@@QAEXH@Z @0x005F6014 7B: clear / set the +0x35
// flag byte; the word argument is unused.



// ?rva005F8F80@Rva005F8F80@@QAEXH@Z @0x005F8F80 12B and
// ?rva005F8F8B@Rva005F8F80@@QAEXH@Z @0x005F8F8B 11B: clear the owned handle at
// +0x2C / +0x3C through the rowed Rva000AD6F4::clear 0x000AD6F4; the word
// argument is unused.



// ?rva005B1903@Rva005B1903@@QAEXPAUBfmePod8@@IABU2@@Z @0x005B1903 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x000B02B6.
// 0x000B02B6 is the BfmeE8 instantiation (its copies are
// __uninitialized_copy 0x004C3121 and _M_insert_overflow 0x00057C80), so the
// vector and the incoming record use that spelling; BfmePod8 in this
// signature is the same 8-byte record under the older placeholder name.
struct BfmePod8;
struct BfmeE8;

// ?rva005B1908@Rva005B1908@@QAEXPAUBfmePod20@@IABU2@@Z @0x005B1908 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x005B1748.
struct BfmePod20;

// ?rva005EE00F@Rva005EE00F@@QAEXPAUBfmeStringRecord005ED5F3@@IABU2@@Z @0x005EE00F 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x005EDEF3.
struct BfmeStringRecord005ED5F3;


// ?rva005EFD8A@Rva005EFD8A@@QAEXPAURva005EFD53Element@@IABU2@@Z @0x005EFD8A 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x005EFC30.
struct Rva005EFD53Element;


// Tail jumps to a rowed member of the tree / array at +0.
struct Rva0027EA49;
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > Rva005C6BF0Tree;
typedef _STL::_Rb_tree<int, Rva005E4920Pair, _STL::_Select1st<Rva005E4920Pair>, _STL::less<int>, _STL::allocator<Rva005E4920Pair> > Rva005E466BTree;

// ?rva005C6BF0@Rva005C6BF0@@QAEXXZ @0x005C6BF0 5B: rowed tree clear 0x005C6B83.
// ??1Rva005C6C76@@QAE@XZ @0x005C6C76 5B: member-only dtor, rowed tree dtor 0x005C6BF5.



// ?rva005E466B@Rva005E466B@@QAEXXZ @0x005E466B 5B: rowed int->SBServer tree clear 0x005E43A8.


// ?rva00628C69@Rva00628C69@@QAEXXZ @0x00628C69 5B: rowed RemoveAll 0x00628C25.


// Fill wrappers over the rowed cdecl Rva005EA1B1Fill 0x005EA1B1:
// ?Rva005EA966@@YAPAMPAMHABH@Z @0x005EA966 5B forwards the same three
// arguments (a tail jump); ?Rva005EA5CE@@YAPAMPAMHABHABURva005EA5CETag@@@Z
// @0x005EA5CE 21B takes an extra empty tag argument, so it re-pushes the
// three and calls (the shape of STLport's __uninitialized_fill_n dispatch).
float *Rva005EA1B1Fill(float *dest, int count, const int &value);
struct Rva005EA5CETag
{
};
float *Rva005EA966(float *dest, int count, const int &value);

float *Rva005EA5CE(float *dest, int count, const int &value, const Rva005EA5CETag &);


// ?rva005C6D48@Rva005C6D48@@QAEIABURva0027EA49@@@Z @0x005C6D48 5B and
// ?rva005CABBB@Rva005CABBB@@QAEIABVAsciiString@@@Z @0x005CABBB 5B: erase a key
// from the map<AsciiString, list<AsciiString> > tree at +0 through its rowed
// _Rb_tree::erase(const key &) 0x005CA950.
typedef _STL::list<AsciiString, _STL::allocator<AsciiString> > Rva005CABBBList;
typedef _STL::pair<const AsciiString, Rva005CABBBList> Rva005CABBBPair;
typedef _STL::_Rb_tree<AsciiString, Rva005CABBBPair, _STL::_Select1st<Rva005CABBBPair>, _STL::less<AsciiString>, _STL::allocator<Rva005CABBBPair> > Rva005CABBBTree;

class Rva005CABBB
{
public:
	unsigned int rva005CABBB(const AsciiString &key);
private:
	Rva005CABBBTree m_tree;
};
unsigned int Rva005CABBB::rva005CABBB(const AsciiString &key)
{
	return m_tree.erase(key);
}

// ?rva00549420@Rva00549420@@QBEHABV1@@Z @0x00549420 5B and
// ?rva00584D50@Rva00584D50@@QBEHABV1@@Z @0x00584D50 5B: deque iterator
// difference through the rowed _Deque_iterator_base::_M_subtract.
struct BfmeE8;
namespace _STL
{
	template <class T>
	struct _Deque_iterator_base
	{
		int _M_subtract(const _Deque_iterator_base &other) const;
		T *_M_cur;
		T *_M_first;
		T *_M_last;
		T **_M_node;
	};
}



// ?rva005D7357@Rva005D7357@@QBEIXZ @0x005D7357 5B: bucket count of the
// int->int hash_map at +0 through its rowed bucket_count.
namespace _STL
{
	template <class T> struct hash;
	template <class T> struct equal_to;
	template <class K, class V, class H, class E, class A>
	class hash_map
	{
	public:
		unsigned int bucket_count() const;
	};
}


// ?rva0052B488@Rva0052B488@@QAEHPBD@Z @0x0052B488 5B: rowed
// XferSave::rva0060D435 0x0060D435 on the saver at +0 (a tail jump).


// ?Rva005676FB@@YAPAXPAVGameWindow@@@Z @0x005676FB 5B: cdecl forward to the
// rowed GadgetButtonGetData 0x00327D56.
class GameWindow;
void *GadgetButtonGetData(GameWindow *window);
void *Rva005676FB(GameWindow *window);


// ?Rva005BE344@@YAPAHPAHHPBH@Z @0x005BE344 5B: cdecl forward to the rowed
// rva499ed0 0x005BE225 with the same arguments.
int *rva499ed0(int *dest, int count, const int *value);
int *Rva005BE344(int *dest, int count, const int *value);


// ?rva00603912@Rva00603912@@QBEIXZ @0x00603912 9B and
// ?rva0060391B@Rva00603912@@QBEIXZ @0x0060391B 10B: byte-swap the +0 / +4 word
// through the rowed cdecl Rva009CC290Swap 0x006038EF.
unsigned int Rva009CC290Swap(unsigned int value);


bool Rva006D3850(int codePoint);

