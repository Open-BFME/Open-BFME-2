class ModuleData;
// stlport
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc
//
// ?rva00569373@Rva00569373@@QAEXPAX@Z @0x00569373 32B.
// Drain loop over the +0x58/+0x5C pointer vector: while begin != end, call
// the rowed 0x005691DB-twin 0x0056913D on *begin with (this, tag). Each call
// erases its own element from this vector via rowed 0x00568F04, so the
// re-fetched begin advances without an explicit cursor. Honest
// address-derived names; host doubles as the BitRange of 0x0056913D.
class BitRange;

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

class Rva00569373
{
public:
	void rva00569373(void *);
	char m_pad00[0x58];
private:
	LargeGroupAudioSoundKeyPair **volatile m_begin; // +0x58 +0x58
	LargeGroupAudioSoundKeyPair **m_end; // +0x5C +0x5C
};

void Rva00569373::rva00569373(void *tag)
{
	while (m_begin != m_end)
		(*m_begin)->removeDuckingTarget((BitRange *)this, tag);
}
