// cl: /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
//
// ?addArchiveFile@Win32BIGFileSystem@@UAE_NPBD_N@Z, retail 0x006046b0, 314 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// ?rva006045A2@Win32BIGFileSystem@@QAE_NPBD0PAUBigArchiveMemberInfo@@_N@Z
// stlport
// Native6045A2..6046B0 RET16: the nested index copies a twelve-byte member
// descriptor. Keep its node's placement copy out of line, as native29E11A
// calls the 30-byte Construct at41360E. This also preserves the real map
// temporary lifetimes without layout padding or artificial wrapper objects.
// Evidence: reverse/attempt_support/big-archive-recovery-20261020.md.
// Retail imports strncmp, while _mbscpy and the allocation operators use
// direct calls. Select each CRT header's linkage before its first inclusion.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <mbstring.h>
#include <new>
#define _STLP_BFME_TREE_NODE_BASE_O2
#include <map>
// ?init@Win32BIGFileSystem@@UAEX_N@Z @0x00603944 188B: vslot 1 of vtable 0x0087A94C (class of ??0Win32BIGFileSystem@@QAE@XZ). Loads lang big files. Evidence: vtable slot 1; strings "%s*.big" "lang\" "lang\%sAudio.big" "EnglishAudio.big" "*.big" "apt\"; global TheArchiveFileSystem; buffers g_00DD509C g_Rva0107301CEmptyString.


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


// WorldBuilder16507D0 names the method and source path. Native C7A94C
// vtable slot5 selects6046B0; complete RET8 body314 bytes. ZH's BIG parser
// is a semantic lead only: this target uses File read slot3, a single
// directory read, two accepted identifiers and a twelve-byte descriptor.



// Native 6045A2,270B,RET16; caller6046B0 and shared header at this+4.
// Nested map semantics and record words are target-derived; names of mapped
// records and fields are descriptive views, not original-name claims.
namespace _STL { template <> void _Construct<BigMemberMap::value_type, BigMemberMap::value_type>(BigMemberMap::value_type *, const BigMemberMap::value_type &); }
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
  members.insert(BigMemberMap::value_type(name, *info));
 } else {
  if (!overwrite)
   return false;
  entry->second = *info;
 }
 return true;
}


bool Win32BIGFileSystem::addArchiveFile(const char *filename, bool overwrite) {
    bool success = false;
    File *file=TheArchiveFileSystem->openFile(filename,0x41,0);
    if (!file) return false;
    BigArchiveHeader header;
    if (file->read(&header, 16) == 16 &&
        (strncmp(BigArchiveSignatures[0], header.identifier, 4) == 0 ||
         strncmp(BigArchiveSignatures[1], header.identifier, 4) == 0)) {
        BigArchiveMemberInfo info;
        info.file = file;
        unsigned int directorySize = Rva009CC290Swap(header.directorySize);
        unsigned int count = Rva009CC290Swap(header.entryCount);
        char *directory = new char[directorySize];
        if (file->read(directory, directorySize - 16) == directorySize - 16) {
            char *entry = directory;
            while (count--) {
                char path[260];
                _mbscpy(reinterpret_cast<unsigned char *>(path), reinterpret_cast<unsigned char *>(entry + 8));
                char *name = Rva00605365(path);
                const char *parent = path == name ? "" : path;
                info.offset = Rva009CC290Swap(*reinterpret_cast<unsigned int *>(entry));
                info.size = Rva009CC290Swap(*reinterpret_cast<unsigned int *>(entry + 4));
                success |= rva006045A2(parent, name, &info, overwrite);
                entry = static_cast<char *>(reinterpret_cast<Rva00603925 *>(entry)->rva00603925());
            }
        }
        delete[] directory;
    }
    return success;
}
