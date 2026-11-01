// Canonical BFME2 File. Target facts (addresses below are RVAs):
// 0x006024FD stores table 0x0087A808 at +0, zeroes +4/+8/+0x10 (4 bytes) and +0x0C/+0x0D (1 byte), and calls StringBase<char>::set at 0x000055F5 on +4. 0x006025CE restores the same table, clears +0x0D, calls close, closes the +0x10 handle and clears the +4 string through 0x00036410. RAMFile::open(File*) at 0x006059B5 reads the pointer at +4 (0x006059C1), returns pointer+8 or empty text and reads access at +8 (0x006059C6): getName/getAccess expand inline; the name word is opaque pointer storage here. LanguageFilter::init at 0x00388787 stores 1 at the converted File's +0x0D, proving inline deleteOnClose. Those accessor names come from Zero Hour Common/File.h. 0x00602255 calls File's constructor and places MemoryReadFile's first member at +0x14: the File subobject occupies 0x14 bytes. No separate base constructor or base teardown appears; Zero Hour's MemoryPoolObject inheritance is not transferred.
// Table 0x0087A808 has 17 slots before the next table at 0x0087A84C: 0 deleting destructor 0x00602619; 1 open 0x00602543; 2 close 0x0060259A; 3-9 purecall 0x0003B810; 10 print 0x00602451; 11 size 0x00602412; 12 position 0x00602447; 13-14 purecall; 15 lock 0x006024CA; 16 unlock 0x006024EE. eof is the nonvirtual row 0x006024AC. The destructor and constructor remain declared out of line. Zero Hour Common/File.h supplies the names and signatures of the pure slots, seekMode and access flags; BFME2's rowed subclass overrides corroborate those slots. open tests access masks 0x102 and 0x60 and stores +8/+0x0C; close tests +0x0C/+0x0D and deletes through slot 0 followed by global delete 0x0002FD60. lock/unlock use the +0x10 mutex handle. size calls seek at slot 5 with CURRENT=1, END=2 and START=0. print tests TEXT=0x20 and calls write at slot 4. These bytes prove a polymorphic abstract class with an out-of-line virtual destructor.

#pragma once

#ifndef __BFME2_FILE_H_
#define __BFME2_FILE_H_

class AsciiString;

class File
{
public:
    enum access
    {
        NONE = 0, READ = 1, WRITE = 2, APPEND = 4, CREATE = 8,
        TRUNCATE = 0x10, TEXT = 0x20, BINARY = 0x40,
        READWRITE = READ | WRITE, ONLYNEW = 0x80, STREAMING = 0x100
    };
    enum seekMode { START, CURRENT, END };

    File();
    virtual ~File();
    virtual bool open(const char *filename, int access = 0);
    virtual void close();
    virtual int read(void *buffer, int bytes) = 0;
    virtual int write(const void *buffer, int bytes) = 0;
    virtual int seek(int bytes, seekMode mode = CURRENT) = 0;
    virtual void nextLine(char *buffer = 0, int bytes = 0) = 0;
    virtual bool scanInt(int &value) = 0;
    virtual bool scanReal(float &value) = 0;
    virtual bool scanString(AsciiString &value) = 0;
    virtual bool print(const char *format, ...);
    virtual int size();
    virtual int position();
    virtual char *readEntireAndClose() = 0;
    virtual File *convertToRAMFile() = 0;
    virtual void lock();
    virtual void unlock();

    bool eof();
    __forceinline const char *getName() const
    {
        const char *data = (const char *)m_nameStorage;
        return data ? data + 8 : "";
    }
    __forceinline int getAccess() const { return m_access; }
    void deleteOnClose() { m_deleteOnClose = true; }

protected:
    void *m_nameStorage;
    int m_access;
    bool m_open;
    bool m_deleteOnClose;
    void *m_mutex;
};

#endif
