// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/moduledata /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00420F3F..0x00421084 (325 bytes), secondary Snapshot transfer.
// WB 0x01292D20 names DelayedExperienceLevelGrantSystem::DoXfer and asserts
// entry.experienceLevel != NULL. Retail's 0x00420E67 destructor proves the
// primary 12-byte system base, Snapshot at +0x0C, list at +0x10 and load flag
// at +0x14. MSVC's secondary-base override uses Snapshot-relative this.
// GameEngine::init registers 0x00DFECC4 as TheExperienceLevelSystem.
// The owned 0x0028951F lookup resolves its level NameKey; level +0x10 is an
// AsciiString copied through StringBase<char>'s 0x000365F0 constructor.
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f's named level lookup
// corroborates the NameKey / level relationship; retail bytes establish ABI.
#include "ascii_string.h"
#include <list>
// Compare nodes directly instead of emitting a competing iterator-base copy.
namespace _STL {
template<class T, class L, class R>
static inline bool operator!=(const _List_iterator<T,L> &a, const _List_iterator<T,R> &b)
{ return a._M_node != b._M_node; }
}
#include "Common/Snapshot.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class Overridable;
#include "../../../Include/GameLogic/Module/Rva0028951F.h"
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;  // defined in DelayedExperienceLevelGrantUpdate.cpp
enum ObjectID { INVALID_ID = 0 };
class Xfer;
void XferObjectID(Xfer *, ObjectID *);
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version { public: Version(unsigned char a,unsigned char b):minimum(a),current(b){} unsigned char minimum,current; };
// Reuse the ledger-owned 12-byte list footprint (push_back at 0x00420DF3).
struct BfmePod12 { ObjectID object; const Overridable *level; bool grant; };
template<> void _STL::list<BfmePod12>::push_back(const BfmePod12 &);
template<> void _STL::_List_base<int,_STL::allocator<int> >::clear();
struct GrantLevelNameView { unsigned char unknown[0x10]; AsciiString name; };
class GameEngineDeletingBase { public: virtual ~GameEngineDeletingBase(); private: char unknown04[8]; };
class DelayedExperienceLevelGrantSystem : public GameEngineDeletingBase, public Snapshot {
public:
    virtual void xfer(Xfer *);
private:
    _STL::list<BfmePod12> entries;
    bool loading;
};
void DelayedExperienceLevelGrantSystem::xfer(Xfer *xfer) {
    Xfer::Version version(1,1);
    xfer->operator==(version);
    if (xfer->IsLoading()) {
        // Retail uses the already-owned folded int list clear at 0x0023DAA5.
        reinterpret_cast<_STL::_List_base<int,_STL::allocator<int> > *>(&entries)->clear();
        loading = true;
        int count;
        xfer->operator==(count);
        while (count > 0) {
            BfmePod12 entry;
            XferObjectID(xfer,&entry.object);
            xfer->operator==(entry.grant);
            AsciiString name;
            xfer->operator==(name);
            entry.level = reinterpret_cast<Rva0028951F *>(TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(name));
            if (entry.level) entries.push_back(entry);
            --count;
        }
    } else {
        int count = entries.size();
        xfer->operator==(count);
        _STL::list<BfmePod12>::iterator end=entries.end();
        for (_STL::list<BfmePod12>::iterator it=entries.begin();it._M_node!=end._M_node;) {
            XferObjectID(xfer,&it->object);
            xfer->operator==(it->grant);
            AsciiString name(reinterpret_cast<const GrantLevelNameView *>(it->level)->name);
            xfer->operator==(name);
            ++it;
        }
    }
}
