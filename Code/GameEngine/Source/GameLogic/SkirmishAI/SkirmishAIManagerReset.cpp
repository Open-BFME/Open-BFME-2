// cl: /Ireference/open-bfme-1/inputs/vendor /O1 /G7 /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Native2A9072..2A9140 and WB E8DAB0 prove reset cleanup order.
// Pointer elements are owned concrete destructor views; their original types
// remain unresolved. Five final scalar words are reset state; one neutral
// identifier below is a new loader-zero provider with proven four-byte extents.
// The reference algorithm header retains the native const-reference empty tag;
// allocator headers continue to come from bfmealloc. Visible noinline copy
// wrapper and erase retain native dead argument home; all206/38/29/42 bytes
// and relocations were independently checked. No donor global names inferred.
// Native2A921B..2A92E4 and constructor2A9725 establish SubsystemInterface12,
// SnapshotC, owned2296B data10, map908, vector914, bucket table920, vector934,
// and owning twelve-byte list pointer940. Actual member types remain unresolved;
// provider views retain observed offsets, ownership, and cleanup. EHs/EHc-
// preserves native states5/3 before releasing the two vector buffers.
// The established Rva002A8F24 receiver owns the layout. The inherited
// Rva002A921B reset entry remains as a complete byte-and-relocation twin
// for existing consumers; its compatibility receiver inherits these fields.
#include "stlport/stl/_algobase.h"
#include <vector>
#include <map>
#include <hash_map>
#include <new>
typedef int Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva002A8D49 {public:Rva002A8D49();~Rva002A8D49();unsigned char data[0x8f8];};
class Rva002A8B8C {public:~Rva002A8B8C();void rva002A8BEE() throw();};
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

class Rva004E9657 {public:~Rva004E9657() throw();};
class Rva004E013B {public:~Rva004E013B() throw();};
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
// Consume the already owned40B pointer erase without emitting a different
// algorithm-header COMDAT copy; native caller206 remains exact.
namespace _STL {template<> vector<void*>::iterator vector<void*>::erase(iterator);
template<> inline __declspec(noinline) ParticleSystemID* __copy_ptrs<ParticleSystemID*,ParticleSystemID*>(ParticleSystemID*first,ParticleSystemID*last,ParticleSystemID*result,const __false_type&){ random_access_iterator_tag tag;return __copy(first,last,result,tag,static_cast<int*>(0));}
template<> inline __declspec(noinline) vector<ParticleSystemID>::iterator vector<ParticleSystemID>::erase(iterator first,iterator last){_TrivialAss tag;iterator i=__copy_ptrs(last,this->_M_finish,first,tag);_Destroy(i,this->_M_finish);this->_M_finish=i;return first;}}
class RvaVector {public:void**erase(void**,void**) throw();};
class Rva00601941 {public:void rva00601941() throw();};
extern unsigned g_00DFEFC8;
unsigned BfmeSkirmishAIResetState1;
extern int Rva00A03D80;
extern unsigned g_00DFEFC0,g_AITargetThreatFinderSerial;
void Rva002A8F24::reset(){
 _STL::vector<void*>& teams=*reinterpret_cast<_STL::vector<void*>*>(&teams914);
 for(_STL::vector<void*>::iterator i=teams.begin();static_cast<const void*>(i)!=static_cast<const void*>(teams914.end());){
  delete reinterpret_cast<const Rva004E9657*>(*i);
  i=teams.erase(i);
 }
 reinterpret_cast<RvaVector*>(&teams914)->erase(teams.begin(),teams.end());
 typedef _STL::map<int,Rva004E013B*> Collectors;
 Collectors& map=*reinterpret_cast<Collectors*>(&collectors908);
 for(Collectors::iterator i=map.begin();i!=map.end();++i)delete i->second;
 reinterpret_cast<Rva002A8B8C*>(&collectors908)->rva002A8BEE();
 reinterpret_cast<_STL::vector<ParticleSystemID>*>(&heroIDs934)->clear();
 reinterpret_cast<Rva00601941*>(owned940)->rva00601941();
 _STL::vector<void*>& cached=*reinterpret_cast<_STL::vector<void*>*>(reinterpret_cast<char*>(this)+0x864);
 reinterpret_cast<RvaVector*>(&cached)->erase(cached.begin(),cached.end());
 g_00DFEFC8=0;BfmeSkirmishAIResetState1=0;g_00DFEFC0=0;g_AITargetThreatFinderSerial=0;Rva00A03D80=0;
}

// Compatibility receiver inherits the established layout without another
// private field view. Both emitted reset entries are complete relocation twins.
class Rva002A921B:public Rva002A8F24 {public:virtual void reset();};
void Rva002A921B::reset(){
 _STL::vector<void*>& teams=*reinterpret_cast<_STL::vector<void*>*>(&teams914);
 for(_STL::vector<void*>::iterator i=teams.begin();static_cast<const void*>(i)!=static_cast<const void*>(teams914.end());){
  delete reinterpret_cast<const Rva004E9657*>(*i);
  i=teams.erase(i);
 }
 reinterpret_cast<RvaVector*>(&teams914)->erase(teams.begin(),teams.end());
 typedef _STL::map<int,Rva004E013B*> Collectors;
 Collectors& map=*reinterpret_cast<Collectors*>(&collectors908);
 for(Collectors::iterator i=map.begin();i!=map.end();++i)delete i->second;
 reinterpret_cast<Rva002A8B8C*>(&collectors908)->rva002A8BEE();
 reinterpret_cast<_STL::vector<ParticleSystemID>*>(&heroIDs934)->clear();
 reinterpret_cast<Rva00601941*>(owned940)->rva00601941();
 _STL::vector<void*>& cached=*reinterpret_cast<_STL::vector<void*>*>(reinterpret_cast<char*>(this)+0x864);
 reinterpret_cast<RvaVector*>(&cached)->erase(cached.begin(),cached.end());
 g_00DFEFC8=0;BfmeSkirmishAIResetState1=0;g_00DFEFC0=0;g_AITargetThreatFinderSerial=0;Rva00A03D80=0;
}
