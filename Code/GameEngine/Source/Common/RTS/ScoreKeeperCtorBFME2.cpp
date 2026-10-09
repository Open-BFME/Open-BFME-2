// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// stlport
// ZH ScoreKeeper.cpp constructor/reset semantic guide and native39CAE1.
// Layout established by existing BFME2 reset and destructor: six maps plus
// twenty per-player maps; three vectors and the small string/metadata record.
#include <map>
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT 1
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS 1
#include "Common/Snapshot.h"
#undef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#undef BFME_SNAPSHOT_NAME_SLOT
#include "unicode_string.h"

// Keep the native24-byte map header allocation distinct from the older
// unsigned-pair base binding at30087C. Original allocator spelling unknown.
template<class T> class Rva0039CAE1Allocator : public _STL::allocator<T> {
public:
 template<class U> struct rebind {typedef Rva0039CAE1Allocator<U> other;};
 Rva0039CAE1Allocator() throw() {}
 Rva0039CAE1Allocator(const Rva0039CAE1Allocator&) throw() {}
 template<class U> Rva0039CAE1Allocator(const Rva0039CAE1Allocator<U>&) throw() {}
};
typedef _STL::map<unsigned,void*,_STL::less<unsigned>,Rva0039CAE1Allocator<_STL::pair<const unsigned,void*> > > ScoreCountMap;
class Rva0039B893 : public Snapshot {
public:
 Rva0039B893();virtual __forceinline ~Rva0039B893(){}
 int field04;float field08;short field0C,field0E,field10;
protected:virtual void loadPostProcess();virtual void crc(Xfer*);virtual void xfer(Xfer*);
};
struct Rva0039CAE1Metadata {
 UnicodeString text;unsigned a,b;
 Rva0039CAE1Metadata():a(0),b(3){}
};
class ScoreKeeper : public Snapshot {
public:
 ScoreKeeper();virtual ~ScoreKeeper();
 virtual void LoadPostProcess();virtual const char*GetSnapshotName()const;virtual void DoXfer(Xfer*);
 void reset(int);
private:
 char opaque004[0x1C4];
 ScoreCountMap map1C8,map1D4;
 int field1E0;
 ScoreCountMap map1E4,objectsBuilt,objectsDestroyed[20],objectsLost,objectsCaptured;
 _STL::vector<int> trackedKills;
 Rva0039CAE1Metadata metadata;
 _STL::vector<Rva0039B893>frameStats;
 _STL::vector<int>field328;
};
ScoreKeeper::ScoreKeeper() {reset(0);}
