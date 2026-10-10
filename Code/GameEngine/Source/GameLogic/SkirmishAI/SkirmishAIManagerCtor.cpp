// Native 0x002A9725..0x002A97DB constructor; sizeof receiver 0x944.
// WB manager call graph and native vtables establish the receiver identity.
// Pointer vector spelling is the inherited opaque ABI view: native update
// proves AIGameTeam pointers, without establishing ModuleData as their type.
// Direct STLport map/hash members avoid temporary placement-construction
// cleanup states. All fields and calls are verified against this retail row.
// cl: /O1 /G7 /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <map>
#include <hash_map>
#include <new>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
typedef int Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva002A8D49 {public:Rva002A8D49();~Rva002A8D49();unsigned char data[0x8f8];};
struct Rva002A9706Element {char bytes[1];bool operator<(const Rva002A9706Element&)const;bool operator==(const Rva002A9706Element&)const;};
namespace _STL {template<> struct hash<Rva002A9706Element>{unsigned operator()(const Rva002A9706Element&) const;};}
class Rva004E9337 {public:void rva004E9337();};
class ObjectCreationList {public:ObjectCreationList();__forceinline ~ObjectCreationList(){reinterpret_cast<Rva004E9337*>(this)->rva004E9337();}unsigned words[3];};
class ModuleData;
enum ObjectID {OBJECTID_INVALID=0};
class Rva002A8F24:public SubsystemInterface,public Snapshot {
public:Rva002A8F24();virtual ~Rva002A8F24();virtual void init();virtual void reset();virtual void update();virtual void loadPostProcess(){}virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 Rva002A8D49 data10;
 _STL::map<int,void*> collectors908;
 _STL::vector<const ModuleData*>teams914;
 _STL::hash_map<int,Rva002A9706Element> builders920;
 _STL::vector<ObjectID>heroIDs934;
 ObjectCreationList*owned940;
};
Rva002A8F24::Rva002A8F24():owned940(0){owned940=new ObjectCreationList;}
