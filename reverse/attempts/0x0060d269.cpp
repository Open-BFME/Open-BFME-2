// ?rva0060D269@Rva0060D269@@QAEAAIABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z
// partial score=0.9467 date=2026-10-09
// ?rva0060D2E9@XferSave@@QAEXPBD@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G6 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_CSTD_FUNCTION_IMPORTS
// stlport
// ZH XferSave block/string transfers and BFME1 xfer_save.cpp supply the
// semantic lead. Native60D2E9..60D434 and60D435..60D4C9 establish the
// stream4 flag8 position-vectorC and compressed-name table18. These
// BFME2 helpers retain address names; the writer's original names unknown.
namespace _STL { void __cdecl free(void *); }
#include <string>
#include <vector>
#include <hash_map>
class ModuleData;
namespace _STL { template<> void vector<const ModuleData *>::push_back(const ModuleData *const&); }
class XferException {
public: XferException(int,const char*,...); XferException(const XferException&); ~XferException();
 void *text; int tag;
};
class BfmeByteStream {
public: virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual int write(const void*,int); virtual int skip(int,int);
};
struct Rva0060CAEANode { void *next; _STL::string key; unsigned int value; };
struct Rva0060CAEAIterator { Rva0060CAEANode *cur; const void *table;
 Rva0060CAEAIterator(Rva0060CAEANode*c,const void*t):cur(c),table(t){} };
class Rva0060CAEA { public: Rva0060CAEAIterator rva0060CB61(const _STL::string&); Rva0060CAEANode *rva0060CAEA(const _STL::string&)const throw(); };
class Rva0060D269 { public: unsigned int &rva0060D269(const _STL::string&); };
class XferSave {
public:
 virtual ~XferSave();
 void rva0060D2E9(const char*);
 int rva0060D435(const char*);
private:
 BfmeByteStream *volatile stream;
 bool flag; char pad9[3];
 void *positions[3];
 char names[20]; char secondNames[16];
 unsigned int previousNames;
};
typedef _STL::pair<const _STL::string,unsigned int> XferNamePair;
typedef _STL::hashtable<XferNamePair,_STL::string,_STL::hash<_STL::string>,
 _STL::_Select1st<XferNamePair>,_STL::equal_to<_STL::string>,_STL::allocator<XferNamePair> > XferNameTable;
namespace _STL { template<> XferNamePair &XferNameTable::_M_insert(const XferNamePair&); }
unsigned int &Rva0060D269::rva0060D269(const _STL::string &key) {
 Rva0060CAEANode *node;
 { Rva0060CAEAIterator it=((Rva0060CAEA*)this)->rva0060CB61(key); node=it.cur; }
 return !node ? ((XferNameTable*)this)->_M_insert(XferNamePair(key,0)).second : node->value;
}
