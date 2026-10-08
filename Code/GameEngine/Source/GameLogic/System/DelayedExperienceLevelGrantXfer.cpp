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
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Overridable;
class Rva0028951F { public: const Overridable *rva0028951F(int); };
class ExperienceLevelSystem;
ExperienceLevelSystem *TheExperienceLevelSystem = 0;
enum ObjectID { INVALID_ID = 0 };
class Xfer;
void XferObjectID(Xfer *, ObjectID *);
struct GrantVersion { GrantVersion(unsigned char a,unsigned char b):minimum(a),current(b){} unsigned char minimum,current; };
class Xfer { public: virtual ~Xfer();
virtual bool IsLoading() const;
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual Xfer &xferVersion(GrantVersion *);
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual Xfer &xferAsciiString(AsciiString *);
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual Xfer &xferInt(int *);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};
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
    GrantVersion version(1,1);
    xfer->xferVersion(&version);
    if (xfer->IsLoading()) {
        // Retail uses the already-owned folded int list clear at 0x0023DAA5.
        reinterpret_cast<_STL::_List_base<int,_STL::allocator<int> > *>(&entries)->clear();
        loading = true;
        int count;
        xfer->xferInt(&count);
        while (count > 0) {
            BfmePod12 entry;
            XferObjectID(xfer,&entry.object);
            xfer->xferBool(&entry.grant);
            AsciiString name;
            xfer->xferAsciiString(&name);
            entry.level = reinterpret_cast<Rva0028951F *>(TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(name));
            if (entry.level) entries.push_back(entry);
            --count;
        }
    } else {
        int count = entries.size();
        xfer->xferInt(&count);
        _STL::list<BfmePod12>::iterator end=entries.end();
        for (_STL::list<BfmePod12>::iterator it=entries.begin();it._M_node!=end._M_node;) {
            XferObjectID(xfer,&it->object);
            xfer->xferBool(&it->grant);
            AsciiString name(reinterpret_cast<const GrantLevelNameView *>(it->level)->name);
            xfer->xferAsciiString(&name);
            ++it;
        }
    }
}
