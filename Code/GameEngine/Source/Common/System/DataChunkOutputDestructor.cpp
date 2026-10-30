// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Donor: Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe,
// game/GameEngine/Source/Common/System/DataChunkOutputDestructor.cpp;
// Zero Hour DataChunk.cpp supplies the output teardown and 256-byte copy loop.
// Target 00307680..00307779 and WB BD8650 prove stream +0, FILE +4,
// table +8, wide path getter 2360FC and the added _wunlink after closing.
// UnicodeString and its StringBase view use the shared BFME2 headers.
#include <stddef.h>
extern "C" __declspec(dllimport) struct _iobuf *__cdecl _wfopen(const wchar_t *, const wchar_t *);
extern "C" __declspec(dllimport) int __cdecl fclose(struct _iobuf *);
extern "C" __declspec(dllimport) int __cdecl fseek(struct _iobuf *, long, int);
extern "C" __declspec(dllimport) size_t __cdecl fread(void *, size_t, size_t, struct _iobuf *);
extern "C" __declspec(dllimport) int __cdecl _wunlink(const wchar_t *);
#define SEEK_SET 0
#include "unicode_string.h"

class GlobalData
{
public:
    UnicodeString rva002360FC() const;
};
extern GlobalData *TheWritableGlobalData;

class OutputStream
{
public:
    virtual int write(const void *data, int count) = 0;
};
class Mapping;
class ChunkInputStream;
class OutputStream;
class AsciiString;

class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents() : m_list(0), m_nextID(1), m_listLength(0), m_headerOpened(false) {}
    ~DataChunkTableOfContents();
    void read(ChunkInputStream &s);
    void write(OutputStream &stream);
    unsigned int allocateID(const AsciiString &name);
    AsciiString getName(unsigned int id);

    Mapping *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;

private:
    Mapping *findMapping(const AsciiString &name);
};class OutputChunk;
struct _iobuf;
class OutputStream;
class OutputChunk;
class AsciiString;
class UnicodeString;
class Dict;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class DataChunkOutput
{
public:
    void writeInt(int intValue);
    void writeReal(float realValue);
    void writeByte(unsigned char byteValue);
    DataChunkOutput(OutputStream *pOut);
    ~DataChunkOutput();
    void writeAsciiString(const AsciiString &textValue) throw();
    void writeUnicodeString(UnicodeString textValue);
    void writeNameKey(NameKeyType key);
    void writeDict(const Dict &d);

private:
    OutputStream *m_pOut;
    _iobuf *file;
    DataChunkTableOfContents m_contents;
    OutputChunk *m_chunkStack;
};
// Target 00306FA5..00307033 (RET4): Zero Hour's DataChunkOutput ctor with
// BFME 2's wide user-data path (getter 2360FC) and _wfopen of the same
// _tmpChunk.dat the destructor reads back.
DataChunkOutput::DataChunkOutput(OutputStream *pOut) :
    m_pOut(pOut)
{
    UnicodeString tmpFileName = TheWritableGlobalData->rva002360FC();
    tmpFileName.concat(L"_tmpChunk.dat");
    file = ::_wfopen(tmpFileName.str(), L"wb");
    m_chunkStack = 0;
}

DataChunkOutput::~DataChunkOutput()
{
    m_contents.write(*m_pOut);
    ::fclose(file);
    UnicodeString tmpFileName = TheWritableGlobalData->rva002360FC();
    tmpFileName.concat(L"_tmpChunk.dat");
    file = ::_wfopen(tmpFileName.str(), L"rb");
    ::fseek(file, 0, SEEK_SET);
    char buffer[256];
    int len = 256;
    while (len == 256)
    {
        len = ::fread(buffer, 1, 256, file);
        m_pOut->write(buffer, len);
    }
    ::fclose(file);
    ::_wunlink(tmpFileName.str());
}
