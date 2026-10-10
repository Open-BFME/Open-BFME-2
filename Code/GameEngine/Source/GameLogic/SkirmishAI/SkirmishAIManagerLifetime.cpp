// cl: /O1 /G7 /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Native2A921B..2A92E4 and constructor2A9725 establish SubsystemInterface12,
// SnapshotC, owned2296B data10, map908, vector914, bucket table920, vector934,
// and owning twelve-byte list pointer940. Actual member types remain unresolved;
// provider views retain observed offsets, ownership, and cleanup. EHs/EHc-
// preserves native states5/3 before releasing the two vector buffers.
// Replaces the old Rva002A921B opaque shell. Lifetime and reset now use the
// Rva002A8F24 receiver already established by Register/newMap/xfer. The
// inherited primary E weak-alias pin retains its existing native28B address
// and forwards the emitted G wrapper; both deleting rows are byte-verified.
#include <vector>
#include <map>
#include <hash_map>
#include <new>
typedef int Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva002A8D49 {public:Rva002A8D49();~Rva002A8D49();unsigned char data[0x8f8];};
class Rva002A8B8C {public:~Rva002A8B8C();};
struct ManagerCollectorStorage {unsigned words[3];__forceinline ~ManagerCollectorStorage(){reinterpret_cast<Rva002A8B8C*>(this)->~Rva002A8B8C();}};
struct Rva002A9706Element {char bytes[1];bool operator<(const Rva002A9706Element&)const;bool operator==(const Rva002A9706Element&)const;};
namespace _STL {template<> struct hash<Rva002A9706Element>{unsigned operator()(const Rva002A9706Element&) const;};}
class Rva002A8FE0 {public:~Rva002A8FE0();void rva002A8FE0();unsigned words[5];};
class Rva004E9337 {public:void rva004E9337();};
class ObjectCreationList {public:ObjectCreationList();__forceinline ~ObjectCreationList(){reinterpret_cast<Rva004E9337*>(this)->rva004E9337();}unsigned words[3];};
class ModuleData;
enum ObjectID {OBJECTID_INVALID=0};
class Rva002A8F24:public SubsystemInterface,public Snapshot {
public:Rva002A8F24();virtual ~Rva002A8F24();virtual void init(){}virtual void reset();virtual void update();virtual void loadPostProcess(){}virtual const char*GetSnapshotName()const{return "SkirmishAIManager";}virtual void xfer(Xfer*);
 Rva002A8D49 data10;
 ManagerCollectorStorage collectors908;
 _STL::vector<const ModuleData*>teams914;
 Rva002A8FE0 builders920;
 _STL::vector<ObjectID>heroIDs934;
 ObjectCreationList*owned940;
};
Rva002A8F24::~Rva002A8F24(){reset();builders920.rva002A8FE0();if(owned940){delete owned940;owned940=0;}}
