// ?rva006045A2@Win32BIGFileSystem@@QAE_NPBD0PAUBigArchiveMemberInfo@@_N@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <map>
// ?init@Win32BIGFileSystem@@UAEX_N@Z @0x00603944 188B: vslot 1 of vtable 0x0087A94C (class of ??0Win32BIGFileSystem@@QAE@XZ). Loads lang big files. Evidence: vtable slot 1; strings "%s*.big" "lang\" "lang\%sAudio.big" "EnglishAudio.big" "*.big" "apt\"; global TheArchiveFileSystem; buffers g_00DD509C g_Rva0107301CEmptyString.
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *fmt, ...);

class File
{
public:
 virtual ~File();
 virtual void slot01();
 virtual void slot02();
 virtual int read(void *buffer, int size);
};

// Native 6046B0 builds this twelve-byte descriptor; helper6045A2 copies
// its three words into the archive filename map. Names describe this view.
struct BigArchiveMemberInfo
{
 File *file;
 unsigned int offset;
 unsigned int size;
};

struct Rva006038D4Less
{
 bool operator()(const char *a, const char *b) const;
};
typedef _STL::map<const char *, BigArchiveMemberInfo, Rva006038D4Less> BigMemberMap;
typedef _STL::map<const char *, BigMemberMap, Rva006038D4Less> BigFolderMap;
class Rva006054AF
{
public:
 void *rva006054AF(const char *text);
};
extern unsigned int g_Va00E06E60;

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual File *openFile(const char *filename, int access, int unknown);
	virtual void A4();
	virtual bool doesFileExist(const char *filename) const;
};

extern ArchiveFileSystem *TheArchiveFileSystem;
extern char g_00DD509C[];

class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();
	virtual void init(bool flag);
	virtual void V2();
	virtual void V3();
	virtual void V4();
	virtual bool addArchiveFile(const char *filename, bool overwrite);
	virtual void V6();
	virtual void V7();
	virtual void S8(const char *a, const char *b, int c);
 bool rva006045A2(const char *folder, const char *name, BigArchiveMemberInfo *info, bool overwrite);
private:
 BigFolderMap m_folders;
};

void Win32BIGFileSystem::init(bool flag)
{
	char buf[0x104];

	if (TheArchiveFileSystem == 0)
		return;
	if (!flag)
		return;

	int (__cdecl *sprintfImp)(char *, const char *, ...);
	sprintfImp = sprintf;

	sprintfImp(buf, "%s*.big", g_00DD509C);
	S8("lang\\", buf, 1);

	sprintfImp(buf, "lang\\%sAudio.big", g_00DD509C);
	if (!TheArchiveFileSystem->doesFileExist(buf)) {
		S8("lang\\", "EnglishAudio.big", 0);
	}

	const char *pat = "*.big";
	S8("", pat, 0);
	S8("apt\\", pat, 0);
}

// Native DD5150/DD5154 point to full BIGF/BIG4 strings at BD22F0/BD22E8.
// Mutable pointer storage keeps the same two global loads as the retail body.
const char *BigArchiveSignatures[2] = { "BIGF", "BIG4" };

struct BigArchiveHeader
{
 char identifier[4];
 unsigned int archiveSize;
 unsigned int entryCount;
 unsigned int directorySize;
};

class Rva00603925
{
public:
 unsigned int offset;
 unsigned int size;
 char name[1]; // variable trailing NUL-terminated name, not a fixed allocation
 void *rva00603925();
};
unsigned int __cdecl Rva009CC290Swap(unsigned int);
char *Rva00605365(char *);

extern "C" unsigned char *__cdecl _mbscpy(unsigned char *, const unsigned char *);
void *__cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *) throw();

// WorldBuilder16507D0 names the method and source path. Native C7A94C
// vtable slot5 selects6046B0; complete RET8 body314 bytes. ZH's BIG parser
// is a semantic lead only: this target uses File read slot3, a single
// directory read, two accepted identifiers and a twelve-byte descriptor.
bool Win32BIGFileSystem::addArchiveFile(const char *filename, bool overwrite)
{
 bool actuallyAdded = false;
 File *file = TheArchiveFileSystem->openFile(filename, 0x41, 0);
 if (!file)
  return false;
 BigArchiveHeader header;
 if (file->read(&header, sizeof(header)) == sizeof(header)) {
  if (_STL::strncmp(BigArchiveSignatures[0], header.identifier, 4) == 0 ||
      _STL::strncmp(BigArchiveSignatures[1], header.identifier, 4) == 0) {
   BigArchiveMemberInfo info;
   info.file = file;
   unsigned int directorySize = Rva009CC290Swap(header.directorySize);
   unsigned int count = Rva009CC290Swap(header.entryCount);
   unsigned char *directory = new unsigned char[directorySize];
   if (file->read(directory, directorySize - sizeof(header)) == directorySize - sizeof(header)) {
    Rva00603925 *entry = (Rva00603925 *)directory;
    for (unsigned int index = 0; index != count; ++index) {
      char path[260];
      _mbscpy((unsigned char *)path, (const unsigned char *)entry->name);
      char *name = Rva00605365(path);
      const char *folder = path == name ? "" : path;
      info.offset = Rva009CC290Swap(entry->offset);
      info.size = Rva009CC290Swap(entry->size);
      actuallyAdded |= rva006045A2(folder, name, &info, overwrite);
      entry = (Rva00603925 *)entry->rva00603925();
    }
   }
   delete [] directory;
  }
 }
 return actuallyAdded;
}


// Native 6045A2,270B,RET16; caller6046B0 and shared header at this+4.
// Nested map semantics and record words are target-derived; names of mapped
// records and fields are descriptive views, not original-name claims.
bool Win32BIGFileSystem::rva006045A2(const char *folder, const char *name,
                                  BigArchiveMemberInfo *info, bool overwrite)
{
 if (folder == name)
  folder = "";
 BigFolderMap::iterator parent = m_folders.find(folder);
 Rva006054AF *pool = (Rva006054AF *)&g_Va00E06E60;
 if (parent == m_folders.end()) {
  folder = (const char *)pool->rva006054AF(folder);
  parent = m_folders.insert(_STL::make_pair(folder, BigMemberMap())).first;
 }
 BigMemberMap &members = parent->second;
 BigMemberMap::iterator entry = members.find(name);
 if (entry == members.end()) {
  name = (const char *)pool->rva006054AF(name);
  members.insert(_STL::make_pair(name, *info));
 } else {
  if (!overwrite)
   return false;
  entry->second = *info;
 }
 return true;
}

