// Canonical BFME2 FileSystem. Target facts (addresses are RVAs unless marked VA): GameEngine tables 0x007E7188 and 0x007C2530 slot 27 contain factory 0x00225F44; 0x0022E3AB calls that slot and 0x0022E3B1 stores its result in TheFileSystem (VA 0x00E06A48). The factory allocates 4 bytes and calls constructor 0x00600611, which stores VA 0x00C7A660 at +0. Destructor 0x0060061A restores the same table and destroys the two global file services, with no base teardown or data fields. Table RVA 0x0087A660 has one slot, deleting destructor 0x006006BD; its following word starts "shaders.big". Shutdown 0x0023067E..0x00230698 destroys TheFileSystem through slot 0. These lifetime bodies are ledgered as Rva0060061A; they prove sizeof 4 and a virtual destructor, without SubsystemInterface inheritance.
// Target facts: openFile (0x00600C34), doesFileExist (0x00600D7D), getFileInfo (0x00600E3A) and getFileListInDirectory (0x00600FC9) do not dereference incoming this; their indirect calls use global services (VA 0x00E06E54 and 0x00E06E5C) and the path gate (VA 0x00E06A4C). 0x00077BF8 forwards AsciiString text to getFileInfo; 0x0037BD2B forwards UnicodeString text to rva006006A9 (0x006006A9). rva00600676 (0x00600676) and rva006006A9 dispatch wide paths through the archive global. rva002DBA07 (0x002DBA07) and rva0002BA86 (0x0002BA86) forward with third argument zero; rva000783A1 (0x000783A1) forwards two packed integers. initialiseRestrictedFilelist (0x00601572) is static cdecl. The listing row uses _STL::set with BfmeStringNoCaseLess. Calls at 0x003007CB and 0x004D2BA1 pass third argument zero to openFile, supporting its default bufferSize.
// Donor facts: Zero Hour Common/FileSystem.h corroborates the openFile, doesFileExist, getFileInfo and getFileListInDirectory names. Its SubsystemInterface base and cache member do not fit the retail four-byte object. Constructors, the virtual destructor and all rowed methods are declared out of line.

#pragma once

#ifndef __BFME2_FILESYSTEM_H_
#define __BFME2_FILESYSTEM_H_

class AsciiString;
class File;
class UnicodeString;
struct BfmeStringNoCaseLess;
struct FileInfo;

namespace _STL
{
    template <class T> class allocator;
    template <class Key, class Compare, class Allocator> class set;
}

class FileSystem
{
public:
    FileSystem();
    virtual ~FileSystem();

    File *openFile(const char *filename, int access, int bufferSize = 0);
    bool doesFileExist(const char *filename) const;
    bool getFileInfo(const char *filename, FileInfo *fileInfo) const;
    bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const;
    void getFileListInDirectory(const AsciiString &directory, const AsciiString &searchName,
        _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > &filenameList,
        bool searchSubdirectories) const;
    static void initialiseRestrictedFilelist(const char *filename);

    File *rva00600676(const unsigned short *filename, int access, int bufferSize);
    bool rva006006A9(const unsigned short *filename);
    bool rva0037BD2B(const UnicodeString &filename);
    File *rva002DBA07(const unsigned short *filename, int access);
    File *rva0002BA86(const char *filename, int access);
    File *rva000783A1(const char *filename, int access, int first, int second);
};

extern FileSystem *TheFileSystem;

#endif
