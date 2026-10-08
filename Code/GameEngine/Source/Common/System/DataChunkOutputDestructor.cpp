// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Donor: Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe,
// game/GameEngine/Source/Common/System/DataChunkOutputDestructor.cpp;
// Zero Hour DataChunk.cpp supplies the output teardown and 256-byte copy loop.
// Target 00307680..00307779 and WB BD8650 prove stream +0, FILE +4,
// table +8, wide path getter 2360FC and the added _wunlink after closing.
// UnicodeString and its StringBase view use the shared BFME2 headers.
#include <stdio.h>
#include <io.h>
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
class DataChunkTableOfContents
{
public:
    ~DataChunkTableOfContents();
    void write(OutputStream &stream);
private:
    void *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;
};
class OutputChunk;
class DataChunkOutput
{
public:
    ~DataChunkOutput();
private:
    OutputStream *m_pOut;
    FILE *m_tmp_file;
    DataChunkTableOfContents m_contents;
    OutputChunk *m_chunkStack;
};

DataChunkOutput::~DataChunkOutput()
{
    m_contents.write(*m_pOut);
    ::fclose(m_tmp_file);
    UnicodeString tmpFileName = TheWritableGlobalData->rva002360FC();
    tmpFileName.concat(L"_tmpChunk.dat");
    m_tmp_file = ::_wfopen(tmpFileName.str(), L"rb");
    ::fseek(m_tmp_file, 0, SEEK_SET);
    char buffer[256];
    int len = 256;
    while (len == 256)
    {
        len = ::fread(buffer, 1, 256, m_tmp_file);
        m_pOut->write(buffer, len);
    }
    ::fclose(m_tmp_file);
    ::_wunlink(tmpFileName.str());
}
