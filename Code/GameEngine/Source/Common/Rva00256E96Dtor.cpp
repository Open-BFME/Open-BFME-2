// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// Retail 0x00256E96 (163 B) and existing deleting wrapper 0x002571DD.
// Target: primary table BF3FEC; secondary Snapshot at +0x0C; tree +0x10;
// pointer vector +0x1C. Calls 255CA8 clear and 256429 destructor prove the
// existing neutral tree view. Each pointee uses slot-zero deletion with flag
// zero followed by global delete; vector erase/free follows.
// Semantic lead: ZH ModuleFactory::~ModuleFactory at BFME1 revision 575ba2b04
// clears its template map then deletes its module-data list. ModuleData pointer
// spelling is carried from that donor; offsets/slots/ABI are native evidence.
// Keep the existing opaque owner name until the class ledger is reconciled.
#include <vector>
#include <functional>
#include <utility>
#include "../../Include/Common/BfmeModuleData.h"
class SubsystemInterface {public:SubsystemInterface();virtual ~SubsystemInterface();private:int p4,p8;};
#include "Common/Snapshot.h"
// Constructor-only ABI adapter for the existing empty12B tree provider.
// Its LadderPref payload spelling is not a target ModuleFactory data claim.
class LadderPref;
namespace _STL {template<class K,class V,class C,class A>class map{public:map();private:char p[12];};}
typedef _STL::map<long,LadderPref,_STL::less<long>,_STL::allocator<_STL::pair<const long,LadderPref> > > EmptyTreeAdapter;
class Rva00255CA8:public EmptyTreeAdapter {public:Rva00255CA8(){}void rva00255CA8();~Rva00255CA8();};
class Rva00256E96:public SubsystemInterface,public Snapshot {
public:Rva00256E96();virtual ~Rva00256E96();private:Rva00255CA8 m_map;_STL::vector<const ModuleData*>m_list;};
Rva00256E96::~Rva00256E96(){m_map.rva00255CA8();for(_STL::vector<const ModuleData*>::iterator i=m_list.begin();i!=m_list.end();++i){const ModuleData*data=*i;::delete data;}m_list.clear();}

// NEW117B native256E19..256E8E RET0: clean ZH ModuleFactory.cpp at
// donor575ba2b04 lines305..310 clears its template store and data list.
// Keep existing Rva00256E96 owner name; no new original-name claim.
// Constructor-only adapter uses the owned empty12B tree at242F01.
// Target keys and payload remain opaque; LadderPref is an ABI adapter only.
// Native256E19..256E8E uses the same sequence, both12B containers and bases.
Rva00256E96::Rva00256E96(){m_map.rva00255CA8();m_list.clear();}
