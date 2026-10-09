// cl: /O1 /G6 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_CSTD_FUNCTION_IMPORTS
// stlport
#define _STLP_NO_EXCEPTIONS 1
// BFME1 XferBlockWriter_rva009D86E0.cpp donor9cbfb551 supplies the
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
 Rva0060CAEAIterator(Rva0060CAEANode *c,const void *t):cur(c),table(t) {}
};
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

int XferSave::rva0060D435(const char *name) {
 if(!stream) return 0;
 int marker=0x424c4f4b;
 if(stream->write(&marker,4)!=4) throw XferException(1,0);
 if(flag) rva0060D2E9(name);
 int position=stream->skip(0,1);
 if(position==-1) throw XferException(1,0);
 name=(const char*)position;
 ((_STL::vector<const ModuleData*>*)positions)->push_back(*(const ModuleData *const*)&name);
 int placeholder=0;
 if(stream->write(&placeholder,4)!=4) throw XferException(1,0);
 return 0;
}

