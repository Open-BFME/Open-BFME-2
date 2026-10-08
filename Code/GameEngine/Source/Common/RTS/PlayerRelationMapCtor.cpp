// cl: /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??0PlayerRelationMap@@QAE@XZ @0x002AF6F7 50B.
// Target evidence: Team::Team (0x003A39A7) news a 0x18-byte block and runs
// this body on it, storing the result at Team+0x11C next to the rowed
// TeamRelationMap ctor 0x003A3959 (+0x118); the body arms EH state 0 for an
// unwindable base, stores vtable 0x00BFDD90 and constructs the rowed
// hash_map<int, Rva002AF625Element> at +4 (0x002AF625). Donor: ZH Player.h
// PlayerRelationMap (Snapshot-derived relation map; BFME2 keys a hash_map).
// The class name is carried from the donor; the element type stays address-named.
#include <hash_map>
#include "Common/Snapshot.h"

struct Rva002AF625Element {Rva002AF625Element();Rva002AF625Element(const Rva002AF625Element&);Rva002AF625Element&operator=(const Rva002AF625Element&);~Rva002AF625Element(){}char bytes[8]; bool operator==(const Rva002AF625Element&)const;};

class PlayerRelationMap : public Snapshot
{
public:
	PlayerRelationMap();
	virtual ~PlayerRelationMap();
protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
private:
	_STL::hash_map<int, Rva002AF625Element> m_map;
};

PlayerRelationMap::PlayerRelationMap()
{
}
