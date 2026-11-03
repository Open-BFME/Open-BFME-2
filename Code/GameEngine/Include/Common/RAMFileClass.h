// Canonical BFME2 RAMFile. Target facts (addresses are RVAs): constructor 0x006054E7 calls File::File (0x006024FD), zeroes three 4-byte fields at +0x14/+0x18/+0x1C and stores table 0x0087AA00 (VA 0x00C7AA00) at +0. Destructor 0x00605504 restores that same table, array-deletes +0x14, calls File::close (0x0060259A), then File::~File (0x006025CE), which restores File's table 0x0087A808. The differing base table belongs to File. LocalFile::convertToRAMFile pushes 0x20 at 0x00605FEC, allocates at 0x00605FF0, calls RAMFile's constructor at 0x00606003 and dispatches open(File*) through +0x44 at 0x00606017: sizeof(RAMFile)=0x20 and File occupies +0..+0x13. StreamingArchiveFile's constructor 0x00605A28 calls RAMFile and starts its members at +0x20 with its own table 0x0087AA50.
// Table 0x0087AA00 has 20 slots before StreamingArchiveFile's table at 0x0087AA50: 0 deleting destructor 0x006056A1 (calls 0x00605504); 1 open(const char*,int) 0x006056BD; 2 close 0x00605547; 3 read 0x00605564; 4 write 0x00574473; 5 seek 0x006055AA; 6 nextLine 0x006055E7; 7 scanInt 0x0060580C; 8 scanReal 0x006058CD; 9 scanString 0x006056FA; 10 File::print 0x00602451; 11 File::size 0x00602412; 12 File::position 0x00602447; 13 readEntireAndClose 0x00605682; 14 convertToRAMFile 0x0047A6A9 (mov eax,ecx; ret); 15 File::lock 0x006024CA; 16 File::unlock 0x006024EE; 17 open(File*) 0x006059B5; 18 openFromArchive 0x0060577A; 19 copyDataToFile 0x0060565E. RAMFile is concrete and polymorphic; its constructor and virtual destructor are declared out of line.
// read at 0x00605567/0x00605573/0x00605576 loads +0x14 as a buffer, +0x18 as its cursor and +0x1C as its extent; 0x006055A0 advances +0x18. seek at 0x006055BE/0x006055C7 selects +0x1C for END and +0x18 for CURRENT and stores +0x18 at 0x006055E1. copyDataToFile at 0x0060566D/0x00605672 passes +0x1C/+0x14 to File::write. Zero Hour Common/RAMFile.h supplies the corroborated field names m_data, m_pos, m_size and method signatures; its System/RAMFile.cpp names the slot-14 return-this operation convertToRAMFile. The inherited slots retain File's registered declarations.

#pragma once

#ifndef __BFME2_RAMFILECLASS_H_
#define __BFME2_RAMFILECLASS_H_

#include "File.h"

class RAMFile : public File
{
public:
    RAMFile();
    virtual ~RAMFile();
    virtual bool open(const char *filename, int access = 0);
    virtual void close();
    virtual int read(void *buffer, int bytes);
    virtual int write(const void *buffer, int bytes);
    virtual int seek(int pos, seekMode mode = CURRENT);
    virtual void nextLine(char *buffer = 0, int bytes = 0);
    virtual bool scanInt(int &value);
    virtual bool scanReal(float &value);
    virtual bool scanString(AsciiString &value);
    virtual char *readEntireAndClose();
    virtual File *convertToRAMFile() { return this; }
    virtual bool open(File *file);
    virtual bool openFromArchive(File *archiveFile, const AsciiString &filename, int offset, int size);
    virtual bool copyDataToFile(File *file);

protected:
    char *m_data;
    int m_pos;
    int m_size;
};

#endif
