// ?addArchiveFile@Win32BIGFileSystem@@QAE_NPBD_N@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /Oy- /G7 /MD /EHsc- /DNDEBUG /D_CRTIMP=
// WB16507D0 names Win32BIGFileSystem::addArchiveFile; native6046B0..6047EA
// RET8 is314B. The ZH Win32BIGFileSystem.cpp at BF1 donor9cbfb55 establishes
// BIGF parsing, network-order directory records and retained open files, but
// its older openArchiveFile interface does not supply this target algorithm.
// This complete trial emits314B with only the independent offset-store and
// next-size PUSH exchanged at+F5. Its called index6045A2 remains unowned.
// g_bigArchiveMagicF/4 are proposed descriptive external names for the native
// pointer slots DD5150/DD5154; these names are NOT pinned or data claims.
#include <mbstring.h>
extern "C" __declspec(dllimport) int __cdecl strncmp(const char*,const char*,unsigned);
void *__cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *);
class ArchiveFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;
class ArchiveReadView {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual int read(void *, int);
};
class ArchiveSystemReadView {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual ArchiveReadView *open(const char *, int, int);
};
extern const char *g_bigArchiveMagicF;
extern const char *g_bigArchiveMagic4;
unsigned int Rva009CC290Swap(unsigned int);
char *Rva00605365(char *);
class Rva00603925 { public: void *rva00603925(); };
struct BigHeaderView { char magic[4]; unsigned int fileSize, count, directorySize; };
struct ArchiveEntryView { ArchiveReadView *file; unsigned int offset, size; };
class Win32BIGFileSystem {
public:
    bool addArchiveFile(const char *, bool);
    bool rva006045A2(const char *, const char *, const ArchiveEntryView *, bool);
};
bool Win32BIGFileSystem::addArchiveFile(const char *filename, bool overwrite) {
    bool success = false;
    ArchiveReadView *file = reinterpret_cast<ArchiveSystemReadView *>(TheArchiveFileSystem)->open(filename, 0x41, 0);
    if (!file) return false;
    BigHeaderView header;
    if (file->read(&header, 16) == 16 &&
        (strncmp(g_bigArchiveMagicF, header.magic, 4) == 0 ||
         strncmp(g_bigArchiveMagic4, header.magic, 4) == 0)) {
        ArchiveEntryView info;
        info.file = file;
        unsigned int directorySize = Rva009CC290Swap(header.directorySize);
        unsigned int count = Rva009CC290Swap(header.count);
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
