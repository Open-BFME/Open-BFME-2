// cl: /O1 /Ob2 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Donor LanguageFilter initialization with the target file and string ABI.
// Target adds RAM-file conversion and delete-on-close; its map starts at +0xC.
// The filesystem forwards a third 32-bit argument, passed as zero here.
#include <map>

typedef int Int;
typedef bool Bool;
template<class T> class StringBase {
    struct Header { int refCount; unsigned short length; unsigned short capacity; T data[1]; };
    Header *m_data;
    friend class UnicodeString;
    StringBase(const StringBase &other);
    __forceinline ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
    StringBase(const T *text);
public:
    int compareNoCase(const StringBase &other) const throw();
};

class UnicodeString : private StringBase<unsigned short> {
public:
    __forceinline UnicodeString(const unsigned short *text)
        : StringBase<unsigned short>(text) {}
    __forceinline UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>((const StringBase<unsigned short>&)other) {}
    __forceinline ~UnicodeString() {}
    int compareNoCase(const UnicodeString &other) const throw() {
        return ((const StringBase<unsigned short>&)*this).compareNoCase(
            (const StringBase<unsigned short>&)other);
    }
};

struct UnicodeStringLessThan {
    Bool operator()(UnicodeString a, UnicodeString b) const {
        return a.compareNoCase(b) < 0;
    }
};
typedef _STL::pair<const UnicodeString, bool> LanguageFilterValue;
typedef _STL::map<UnicodeString, bool, UnicodeStringLessThan,
    _STL::allocator<LanguageFilterValue> > LanguageFilterMap;

class File {
public:
    enum { READ = 1, BINARY = 0x40 };
    virtual void slot0();
    virtual void slot1();
    virtual void close();
    virtual Int read(void *buffer, Int bytes);
    virtual Int write(const void *buffer, Int bytes);
    virtual Int seek(Int bytes, Int mode);
    virtual void nextLine(char *buf, Int bufSize);
    virtual bool scanInt(Int &value);
    virtual bool scanReal(float &value);
    virtual bool scanString(void *value);
    virtual bool print(const char *format, ...);
    virtual Int size();
    virtual Int position();
    virtual char *readEntireAndClose();
    virtual File *convertToRAMFile();
    void deleteOnClose() { m_deleteOnClose = true; }
private:
    void *m_nameStr;
    Int m_access;
    bool m_open;
    bool m_deleteOnClose;
};
class FileSystem {
public:
    File *openFile(const char *filename, Int access, Int extra);
};
extern FileSystem *TheFileSystem;

static const char BadWordFileName[] = "langdata.dat";

class LanguageFilter {
public:
    virtual void init();
protected:
    bool readWord(File *file, unsigned short *buf);
    void unHaxor(UnicodeString &word);
    void *opaquePrefix[2];
    LanguageFilterMap m_wordList;
};

void LanguageFilter::init()
{
    m_wordList.clear();
    File *file1 = TheFileSystem->openFile(BadWordFileName,
        File::READ | File::BINARY, 0);
    if (file1 == 0)
        return;
    file1 = file1->convertToRAMFile();
    if (file1 == 0)
        return;
    file1->deleteOnClose();
    unsigned short word[128];
    while (readWord(file1, word)) {
        Int wordLen = wcslen(word);
        if (wordLen == 0)
            continue;
        for (Int i = 0; i < wordLen; ++i) {
            word[i] = word[i] ^ 0x5555;
        }
        UnicodeString uniword(word);
        unHaxor(uniword);
        m_wordList[uniword] = true;
    }
    file1->close();
    file1 = 0;
}
