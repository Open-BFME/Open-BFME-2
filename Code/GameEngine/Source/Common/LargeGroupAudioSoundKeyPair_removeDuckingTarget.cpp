class ModuleData;
// stlport
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc
//
// ?removeDuckingTarget@LargeGroupAudioSoundKeyPair@@QAEXPAVBitRange@@PAX@Z @0x0056913D 158B.
// Twin of 0x005691DB (see Rva005691DBScan.cpp for the recipe): same slot
// notify via pinned 0x005C834A and same && short-circuit statement-temp
// element scan, plus a rowed 0x00568F04 find-erase of this from the host
// vector before the scan and a +0xC clear beside the +0x10 clear on match.
// Honest address-derived names.

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

class Rva00568F04
{
public:
	void rva00568F04(void *item);
	char m_pad00[0x58];
private:
	void **m_begin; // +0x58 +0x58
	void **m_end; // +0x5C +0x5C
};

class BitRange
{
public:
	AsciiString rva00568BE2() throw();
};

struct Rva0056913DKeyRef
{
	char m_pad[0x18];
	AsciiString m_key; // +0x18
};

struct DuckingTarget
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

void LargeGroupAudioSoundKeyPair::removeDuckingTarget(BitRange *host, void *tag)
{
	Rva005C834A **slot = reinterpret_cast<Rva005C834A **>(m_grids);
	int left = 4;
	do {
		if (*slot != 0)
			((HostClass005C815B *)*slot)->method_005C834A((int)host, (int)tag);
		++slot;
	} while (--left != 0);
	((Rva00568F04 *)host)->rva00568F04(this);
	for (DuckingTarget *duckingTarget = reinterpret_cast<DuckingTarget *>(m_subjects.begin()); duckingTarget != reinterpret_cast<DuckingTarget *>(m_subjects.end()); ++duckingTarget) {
		Rva0056913DKeyRef *keyRef = (Rva0056913DKeyRef *)*(void **)((char *)host + 0x3C);
		bool hit;
		if (asBase(duckingTarget->m_a).compare(asBase(keyRef->m_key)) == 0 && asBase(duckingTarget->m_b).compare(asBase(host->rva00568BE2())) == 0)
			hit = true;
		else
			hit = false;
		if (hit) {
			duckingTarget->m_flags = 0;
			duckingTarget->m_active = 0;
			return;
		}
	}
}
