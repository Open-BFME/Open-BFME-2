// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/moduledata /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Update slot of the delayed experience-level grant queue (xfer lives in DelayedExperienceLevelGrantXfer.cpp).
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
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Xfer;
void XferObjectID(Xfer *, ObjectID *);
struct GrantVersion { GrantVersion(unsigned char a,unsigned char b):minimum(a),current(b){} unsigned char minimum,current; };
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
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
// Reuse the ledger-owned 12-byte list footprint (push_back at 0x00420DF3).
struct BfmePod12 { ObjectID object; const Overridable *level; bool grant; };
template<> void _STL::list<BfmePod12>::push_back(const BfmePod12 &);
template<> void _STL::_List_base<int,_STL::allocator<int> >::clear();
#include "../../../Include/Common/GameEngineDeletingBase.h"
enum ObjectStatusTypes { OBJECT_STATUS_58 = 0x58 };
#include "../Object/object.h"
class DelayedExperienceLevelGrantSystem : public GameEngineDeletingBase, public Snapshot {
public:
    virtual void xfer(Xfer *);
    virtual void update();
    void rva00420C8E(struct ExperienceLevelView *level, Object *obj, bool grant);
private:
    _STL::list<BfmePod12> entries;
    bool loading;
};
// Retail 0x00420EB3..0x00420F0E (91 bytes), slot 10 (update) of the primary
// table 0x00C3BDC4 beside reset 0x00420B55: each queued entry whose object
// still exists, and is not effectively dead unless it carries status 0x58,
// gets its level applied by 0x00420C8E (unrowed, pinned from this call);
// then the queue is emptied through the same folded list clear xfer uses.
// The GameLogic receiver as an equal-arm conditional (late-folded ?:) reproduces retail's
// register order for the findObjectByID call (W7-R1 lever).
void DelayedExperienceLevelGrantSystem::update() {
    for (_STL::list<BfmePod12>::iterator it=entries.begin(); it!=entries.end(); ++it) {
        Object *obj = (TheGameLogic ? TheGameLogic : TheGameLogic)->findObjectByID(it->object);
        if (obj && !(obj->isEffectivelyDead() && !obj->testStatus(OBJECT_STATUS_58)))
            rva00420C8E((ExperienceLevelView *)it->level, obj, it->grant);
    }
    reinterpret_cast<_STL::_List_base<int,_STL::allocator<int> > *>(&entries)->clear();
}
