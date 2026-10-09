// ?rva006045A2@Win32BIGFileSystem@@QAE_NPBD0PBUFileInfo@@_N@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Complete near match for native 6045A2..6046B0 (RET16), WB1650630.
// WB16507D0 names the caller Win32BIGFileSystem::addArchiveFile. Its call
// passes parent and leaf strings plus a three-word file/offset/size record.
// Native tree node+10 is the CString key and node+14 is the mapped value.
// Existing Rva helper names remain ABI views; unsigned key spellings on the
// copy/factory providers do not establish integer archive keys. StorageMap
// supplies 12B storage and the existing CString tree cleanup at603AA8; lookups
// use the independently matched strcmp comparator6038D4 instead of less<PBD>.
// No new providers or aliases are asserted by this bank. Constructor413727
// still needs whole-body fold admission for this emitted template spelling.
// This trial is265B: extra8B locals, ESI/EDI swap, result-pointer loads versus
// retail's shared pair home, constructor-result push versus LEA, and cleanup
// offsets differ. The full expression retains all three map temporaries.
#include <map>
struct Rva00603A00Mapped { unsigned m_bits; };
struct Rva006038D4Less { bool operator()(const char*,const char*) const; };
typedef _STL::pair<const char* const,Rva00603A00Mapped> CStringPair;
class Win32BIGFileSystem;
namespace _STL {
template<> class _Rb_tree<const char*,CStringPair,_Select1st<CStringPair>,Rva006038D4Less,allocator<CStringPair> > {
 friend class ::Win32BIGFileSystem;
 template<class K> _Rb_tree_node<CStringPair> *_M_find(const K&) const;
};
}
typedef _STL::_Rb_tree<const char*,CStringPair,_STL::_Select1st<CStringPair>,Rva006038D4Less,_STL::allocator<CStringPair> > FindTree;
class Win32BIGFileSystem;
struct FindView : FindTree {
 friend class Win32BIGFileSystem;
};
typedef _STL::map<const char*,Rva00603A00Mapped> StorageMap;
typedef _STL::pair<const unsigned,void*> IntegerPair;
typedef _STL::_Rb_tree<unsigned,IntegerPair,_STL::_Select1st<IntegerPair>,_STL::less<unsigned>,_STL::allocator<IntegerPair> > IntegerTree;
class Rva00603FD2 { public: unsigned key; StorageMap tree; };
Rva00603FD2 Rva00604251(const unsigned&,const IntegerTree&);
class Rva0060426C { public: unsigned key; StorageMap tree; Rva0060426C(const Rva0060426C&); };
struct Rva006044A0Node;
struct Rva006044A0Pair { Rva006044A0Node *first; bool second; Rva006044A0Pair(Rva006044A0Node *p,bool b):first(p),second(b){} };
struct Rva006044A0 { Rva006044A0Pair rva006044A0(const Rva0060426C&); };
struct Rva00603E50Node;
struct FileInfo { void *file; unsigned offset,size; };
struct Rva00603E50Value { const char *key; FileInfo info; };
struct Rva00603E50Pair { Rva00603E50Node *first; bool second; Rva00603E50Pair(Rva00603E50Node *p,bool b):first(p),second(b){} };
struct Rva00603E50 { Rva00603E50Pair rva00603E50(const Rva00603E50Value&); };
struct Rva006054AF { void *rva006054AF(const char*); };
extern unsigned g_Va00E06E60;
class Win32BIGFileSystem {
 public:
 unsigned prefix;
 void *header; unsigned count,compare;
 bool rva006045A2(const char*,const char*,const FileInfo*,bool);
};
bool Win32BIGFileSystem::rva006045A2(const char *parent,const char *leaf,const FileInfo *info,bool overwrite)
{
 if(leaf==parent)parent="";
 FindView *outer=reinterpret_cast<FindView*>(&header);
 void *node=outer->_M_find<const char*>(parent);
 Rva006054AF *pool=reinterpret_cast<Rva006054AF*>(&g_Va00E06E60);
 if(node!=header) {}
 else {
  parent=(const char*)pool->rva006054AF(parent);
  node=reinterpret_cast<Rva006044A0*>(outer)->rva006044A0(
   Rva0060426C(reinterpret_cast<const Rva0060426C&>(Rva00604251(
    reinterpret_cast<const unsigned&>(parent),
    reinterpret_cast<const IntegerTree&>(StorageMap()))))).first;
 }
 parent=static_cast<char*>(node)+20;
 node=reinterpret_cast<FindView*>(const_cast<char*>(parent))->_M_find<const char*>(leaf);
 if(node==*reinterpret_cast<void*const*>(parent)) {
  Rva00603E50Value value;
  value.key=(const char*)pool->rva006054AF(leaf);
  value.info=*info;
  reinterpret_cast<Rva00603E50*>(const_cast<char*>(parent))->rva00603E50(value);
 }else{
  if(!overwrite)return false;
  *reinterpret_cast<FileInfo*>(static_cast<char*>(node)+20)=*info;
 }
 return true;
}
