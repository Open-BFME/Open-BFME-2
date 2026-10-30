class ModuleData;
// stlport
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc
//
// ?removePointersToGridCellsInDuckingTarget@LargeGroupAudioSoundKeyPair@@QAEXPAVBitRange@@PAX@Z @0x005691DB 145B.
// Clear-on-match scan: notify the 4 slots at +0x2C via pinned 0x005C834A,
// then walk elements [m_begin,m_end) at +0x14/+0x18 stride 0x14; the first
// element whose StringBase at +0 compares 0 against the +0x3C key's +0x18
// StringBase AND whose +4 compares 0 against a BitRange::rva00568BE2 temp
// (0x00568BE2, temp torn down via releaseBuffer 0x00036410) gets its +0x10
// byte cleared and the scan returns. Twin of 0x0056913D, which also erases
// via rowed 0x00568F04 and clears +0xC. Honest address-derived names;
// element halves reuse the Rva005686F5Elem adjacency (+0/+4 strings).
// The && short-circuit is load-bearing: the rva00568BE2 hidden temp is a
// statement-scoped temporary constructed only when the first compare is 0,
// so its flag-guarded teardown sits at the if/else join reached by both
// paths; a named inner-scope temp lets MSVC prove post-domination and drop
// the flag (124B). Nested call keeps `push eax` for the compare argument.
//
// Codegen: the strings are the shared AsciiString, whose destructor calls
// releaseBuffer directly, and rva00568BE2 returns one (the row's own spelling,
// Rva003ED498Count.cpp). Retail has no EH frame (no __EH_prolog, no fs chain),
// only the plain [ebp-4] alive-flag, so compare and releaseBuffer are declared
// non-throwing below; the shared header declares them potentially-throwing,
// which emits a frame.

#include "ascii_string.h"

// Retail has no EH frame here (no __EH_prolog, only the [ebp-4] alive flag of
// the rva00568BE2 temporary): it compiled compare and the temporary's
// releaseBuffer teardown as non-throwing.
template <> int StringBase<char>::compare(const StringBase<char> &str) const throw();
template <> void StringBase<char>::releaseBuffer() throw();

// The element strings compare through StringBase<char>::compare, as retail calls it.
static inline const StringBase<char> &asBase(const AsciiString &asciiString)
{
	return *(const StringBase<char> *)&asciiString;
}

// The ledger row at 0x005C834A is HostClass005C815B::method_005C834A.
class HostClass005C815B
{
public:
	void method_005C836F(int key, float value);
	void method_005C839B(int,int);
	void method_005C834A(int a, int b) throw();
	void method_005C815B();
};

class Rva005C834A
{
public:
};

class BitRange
{
public:
	AsciiString rva00568BE2() throw();
};

struct Rva005691DBKeyRef
{
	char m_pad[0x18];
	AsciiString m_key; // +0x18
};

struct Rva005691DBElem
{
	AsciiString m_a;	// +0x0
	AsciiString m_b;	// +0x4
	char m_pad08[4];	// +0x8
	unsigned m_flags;	// +0xC
	unsigned char m_active; // +0x10
	char m_pad11[3];
};

#include <set>
#include <vector>
#include "ascii_string.h"
class LargeGroupAudioSoundKeyPair;
class LargeGroupAudioAudioMap;
class LargeGroupAudioSubject;
class Rva005C8176;
struct Rva005C8876Grid;
struct BfmeStringRecord00568CE0;
class BitRange;
class Xfer;
struct VersionPair;
struct FloatPair;
struct Rva0056A378Source;
class OpaqueRefCounted { public: void Release_Ref(); };

class Rva003ED94FDtor { public: ~Rva003ED94FDtor(); void *header; int flags; };

class ObjectCreationList {public: ObjectCreationList(); char opaque[12];};

struct Rva0056A061KeyMap : ObjectCreationList { ~Rva0056A061KeyMap(){reinterpret_cast<Rva003ED94FDtor *>(this)->Rva003ED94FDtor::~Rva003ED94FDtor();} };

struct Rva0056A061Ref { Rva0056A061Ref():value(0){} OpaqueRefCounted *value; ~Rva0056A061Ref(){if(value)value->Release_Ref();} };

struct Rva00568FE4Key { float x; float y; unsigned short w; unsigned short pad; };

struct Rva00568FE4Less {
	bool operator()(const Rva00568FE4Key &a, const Rva00568FE4Key &b) const {
		if (a.x < b.x) return false;
		if (a.x > b.x) return true;
		if (a.y < b.y) return false;
		if (a.y > b.y) return true;
		return a.w < b.w;
	}
};

typedef _STL::multiset<Rva00568FE4Key, Rva00568FE4Less, _STL::allocator<Rva00568FE4Key> > Rva00568FE4Multi;
class LargeGroupAudioSoundKeyPair
{
public:
 int getGrid(int index);
 void removeDuckingTarget(BitRange *host, void *tag);
 void removePointersToGridCellsInDuckingTarget(BitRange *host, void *tag);
 bool rva00568920() const;	// 0x00568920
 void rva00568939(int key);	// 0x00568939
 LargeGroupAudioSoundKeyPair(LargeGroupAudioAudioMap *owner, const char *name);
 ~LargeGroupAudioSoundKeyPair();
 void rva0056A378(Rva0056A378Source arg);
 void rva00569BBC(Xfer *, VersionPair *);
 void allocateGrids();
 void update(bool*);
 void setupAllDuckingTargets();
 void xferGridCellVector(Xfer *, void *, VersionPair *);
 void rva0056979A(const FloatPair &pos, unsigned short weight);
 void rva005697F7(LargeGroupAudioSubject *subject);
 void unregisterSubject(LargeGroupAudioSubject *subject);
 void updateSubject(LargeGroupAudioSubject *subject);
private:
 Rva0056A061KeyMap m_keys;
 Rva0056A061Ref m_owner;
 AsciiString m_name;
 _STL::vector<BfmeStringRecord00568CE0> m_subjects;
 Rva00568FE4Multi m_pendingAdds;
 Rva005C8176 *m_grids[4];
 Rva005C8876Grid *m_grid;
 _STL::vector<const ModuleData *> m_v40;
 _STL::vector<const ModuleData *> m_v4C;
 _STL::vector<const ModuleData *> m_v58;
 int m_totalWeight;
};

void LargeGroupAudioSoundKeyPair::removePointersToGridCellsInDuckingTarget(BitRange *host, void *tag)
{
	Rva005C834A **slot = reinterpret_cast<Rva005C834A **>(m_grids);
	int left = 4;
	do {
		if (*slot != 0)
			((HostClass005C815B *)*slot)->method_005C834A((int)host, (int)tag);
		++slot;
	} while (--left != 0);
	for (Rva005691DBElem *e = reinterpret_cast<Rva005691DBElem *>(m_subjects.begin()); e != reinterpret_cast<Rva005691DBElem *>(m_subjects.end()); ++e) {
		Rva005691DBKeyRef *keyRef = (Rva005691DBKeyRef *)*(void **)((char *)host + 0x3C);
		bool hit;
		if (asBase(e->m_a).compare(asBase(keyRef->m_key)) == 0 && asBase(e->m_b).compare(asBase(host->rva00568BE2())) == 0)
			hit = true;
		else
			hit = false;
		if (hit) {
			e->m_active = 0;
			return;
		}
	}
}
