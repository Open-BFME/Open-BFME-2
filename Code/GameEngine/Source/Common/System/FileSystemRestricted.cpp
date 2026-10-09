// cl: /O1 /EHsc /MD
// Restricted-file-list entry insertion, retail 0x00601522..0x00601572.
// WB 0x01644940 corroborates group fallback, duplicate suppression, permanent
// string storage and insertion. Original helper name is unknown.
// The native nested tree is 12 bytes; keys at node+0x10 are C strings.
// Existing _M_find, string-pool and insertion owners are retained as ABI views;
// the comparator/mapped template names do not assert application element types.
// BFME1 9cbfb55 FileSystem.cpp was checked; restricted lists are target-specific.
namespace _STL {
template<class T> struct _Identity {};
template<class T> struct less {};
template<class T> class allocator {};
template<class K,class V,class KeyOfValue,class Compare,class Alloc> class _Rb_tree {
public:
 void *header; int count; char comparator; char pad[3];
};
}
struct Rva00600A40Element;
typedef _STL::_Rb_tree<Rva00600A40Element,Rva00600A40Element,_STL::_Identity<Rva00600A40Element>,_STL::less<Rva00600A40Element>,_STL::allocator<Rva00600A40Element> > NativeNestedTree;
namespace _STL {
template<class A,class B> struct pair {};
template<class T> struct _Select1st {};
}
struct Rva00603A00Mapped { unsigned word; };
struct Rva006038D4Less {};
struct Rva0060126D;
namespace _STL { template<class T> struct _Rb_tree_node; }
namespace _STL {
template<> class _Rb_tree<const char*,pair<const char *const,Rva00603A00Mapped>,_Select1st<pair<const char *const,Rva00603A00Mapped> >,Rva006038D4Less,allocator<pair<const char *const,Rva00603A00Mapped> > > {
 friend struct ::Rva0060126D;
private:
 template<class K> _Rb_tree_node<pair<const char *const,Rva00603A00Mapped> > *_M_find(const K&) const;
};
}
typedef _STL::_Rb_tree<const char*,_STL::pair<const char *const,Rva00603A00Mapped>,_STL::_Select1st<_STL::pair<const char *const,Rva00603A00Mapped> >,Rva006038D4Less,_STL::allocator<_STL::pair<const char *const,Rva00603A00Mapped> > > FindTree;
struct Rva006013B7Pair { void *first; bool second; Rva006013B7Pair(void *p,bool b) : first(p),second(b) {} };
struct Rva006054AF { void *rva006054AF(const char *); };
extern unsigned int g_Va00E06E60;
struct Rva0060126D {
 void *header;
 NativeNestedTree &rva0060147B(const char *name);
 void rva00601522(NativeNestedTree *group,const char *name);
};

struct Rva00600991 { void rva00600BC6(void *out,void *arg); };
void Rva0060126D::rva00601522(NativeNestedTree *group,const char *name)
{
 if (!group) {
  group=&rva0060147B("");
  if (!group) return;
 }
 void *node=reinterpret_cast<const FindTree *>(group)->_M_find<const char *>(name);
 if (node != group->header) return;
 name=(const char *)reinterpret_cast<Rva006054AF *>(&g_Va00E06E60)->rva006054AF(name);
 struct { void *node; bool inserted; } result;
 reinterpret_cast<Rva00600991 *>(group)->rva00600BC6(&result,(void *)&name);
}

// ZH File.h at donor9cbfb55 and the existing BFME2 File.cpp establish
// nextLine slot6 and convertToRAMFile slot14; native calls are +18/+38.
class AsciiString;
class File {
public:
 virtual ~File();
 virtual bool open(const char *,int);
 virtual void close();
 virtual int read(void *,int);
 virtual int write(const void *,int);
 virtual int seek(int,int);
 virtual void nextLine(char *,int);
 virtual bool scanInt(int &);
 virtual bool scanReal(float &);
 virtual bool scanString(AsciiString &);
 virtual bool print(const char *,...);
 virtual int size();
 virtual int position();
 virtual char *readEntireAndClose();
 virtual File *convertToRAMFile();
 bool eof();
};
class FileSystem {
public:
 File *openFile(const char *,int,int);
 static void initialiseRestrictedFilelist(const char *);
};
extern FileSystem *TheFileSystem;
class FilePathGate { public: unsigned char treeHeader[12]; bool inclusion; };
extern FilePathGate *TheFilePathGate;
class Rva0060146B { public: Rva0060146B(); unsigned char bytes[16]; };
void *__cdecl operator new(unsigned int);
void __cdecl Rva006005D5RTrim(char *);
extern "C" int __cdecl strcmp(const char *,const char *);

// WB16449A0 and native601572..6016AC prove a static cdecl taking one path.
// First line sets inclusion mode; +group lines change the nested tree; other
// lines are trimmed and inserted. Target allocation16 and flag+C are witnessed.
void FileSystem::initialiseRestrictedFilelist(const char *filename)
{
 File *file=TheFileSystem->openFile(filename,0,0);
 if (!file) return;
 TheFilePathGate=reinterpret_cast<FilePathGate *>(new Rva0060146B);
 file=file->convertToRAMFile();
 char line[260];
 NativeNestedTree *group=0;
 if (!file->eof()) {
  file->nextLine(line,260);
  Rva006005D5RTrim(line);
  if (strcmp(line,"#EXCLUSION")==0) TheFilePathGate->inclusion=false;
  else if (strcmp(line,"#INCLUSION")==0) TheFilePathGate->inclusion=true;
 }
 while (!file->eof()) {
  file->nextLine(line,260);
  Rva006005D5RTrim(line);
  if (line[0]=='+') group=&reinterpret_cast<Rva0060126D *>(TheFilePathGate)->rva0060147B(line+1);
  else reinterpret_cast<Rva0060126D *>(TheFilePathGate)->rva00601522(group,line);
 }
}
