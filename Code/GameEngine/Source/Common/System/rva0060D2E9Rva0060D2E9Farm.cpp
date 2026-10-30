// ?rva0060D2E9@XferSave@@QAEXPBD@Z
// ?rva0060D2E9@XferSave@@QAEXPBD@Z
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
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@D@_STL@@QBEPADIPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * allocator<char>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * _STL::_STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
class ModuleData;
namespace _STL { template<> void vector<const ModuleData *>::push_back(const ModuleData *const&); }
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();
	void *text; // +0x00
	int tag; // +0x04
};
class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int write(const void *buffer, int size);
	virtual int skip(int count, int flag);
};
struct Rva0060CAEANode { void *next; _STL::string key; unsigned int value; };
struct Rva0060CAEAIterator { Rva0060CAEANode *cur; const void *table;
 Rva0060CAEAIterator(Rva0060CAEANode *c,const void *t):cur(c),table(t) {}
};
struct Rva0060CAEABuckets
{
	void **_M_start;
	void **_M_finish;
	void **_M_end;

	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}
	void *operator[](unsigned int n) const
	{
		return _M_start[n];
	}
};

class Rva0060CAEA
{
public:
	Rva0060CAEANode *rva0060CAEA(const _STL::string &key) const throw();
	Rva0060CAEAIterator rva0060CB61(const _STL::string &key);
private:
	int m_00; // +0x00
	Rva0060CAEABuckets m_buckets; // +0x04
};
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

struct Wmarker_4 { unsigned char pad[3]; unsigned char v; };
void XferSave::rva0060D2E9(const char *name) {
 if(name==0 || *name==0) {
  unsigned char marker=0;
  if(stream->write(&marker,1)!=1) throw XferException(1,0);
 } else {
  struct {
   Rva0060CAEANode *found;
   unsigned int length;
  } lookup;
  {
   const _STL::string key(name);
   *(Rva0060CAEANode *volatile *)&lookup.found=((Rva0060CAEA*)names)->rva0060CAEA(key);
  }
  if(lookup.found) {
   Wmarker_4 marker; marker.v = 0xff;
   if(stream->write(&marker.v,1)!=1) throw XferException(1,0);
   if(stream->write(&lookup.found->value,4)!=4) throw XferException(1,0);
  } else {
   lookup.length=strlen(name);
   if(lookup.length>0xfe) lookup.length=0xfe;
   if(stream->write(&lookup.length,1)!=1) throw XferException(1,0);
   if(stream->write(name,lookup.length)!=(int)lookup.length) throw XferException(1,0);
   const _STL::string key(name);
   const unsigned int auxCount=previousNames;
   const unsigned int nameCount=*(unsigned int*)(names+16);
   ((Rva0060D269*)names)->rva0060D269(key)=nameCount+auxCount;
  }
 }
}


