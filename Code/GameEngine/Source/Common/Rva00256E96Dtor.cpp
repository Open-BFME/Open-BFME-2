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
#include "../../Include/Common/BfmeModuleData.h"
class SubsystemInterface {public:virtual ~SubsystemInterface();private:int p4,p8;};
#include "Common/Snapshot.h"
class Rva00255CA8 {public:void rva00255CA8();~Rva00255CA8();private:char p[12];};
class Rva00256E96:public SubsystemInterface,public Snapshot {
public:virtual ~Rva00256E96();private:Rva00255CA8 m_map;_STL::vector<const ModuleData*>m_list;};
Rva00256E96::~Rva00256E96(){m_map.rva00255CA8();for(_STL::vector<const ModuleData*>::iterator i=m_list.begin();i!=m_list.end();++i){const ModuleData*data=*i;::delete data;}m_list.clear();}
