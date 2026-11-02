// Target facts (code addresses are RVAs):
// DataChunkInput has no virtual functions or base classes. Constructor 0x00307316 stores the stream argument at +0 (0x00307327), constructs the contents at +4 (0x00307329..0x0030733D), clears +0x18/+0x1C/+0x20/+0x24 (0x00307345..0x0030734E), and stores the stream's tell result at +0x14 (0x00307360). Neither it nor destructor 0x00306F01 installs a vftable; indirect calls use the stream or list nodes, never this.
// Destructor 0x00306F01 calls clearChunkStack at 0x00306F16, walks parser nodes from +0x18 at 0x00306F1B, and destroys the contents at +4 at 0x00306F3E..0x00306F41. There is no constructor/destructor table disagreement and no parent header to include.
// Contents constructor 0x00306D48 stores a null list at +0, zero count at +4, next ID 1 at +8, and false at +0xC. Constructor 0x00307316 embeds these stores at DataChunkInput +4; together with the four trailing pointers and first-chunk position, the layout is 0x28 bytes. Retail caller 0x0032F91A constructs it at EBP-0x80 immediately below the live stream at EBP-0x58.
// clearChunkStack 0x00306DA4 and decrementDataLeft 0x00306E40 use the stack at +0x1C. getChunkVersion 0x00306E06 reads its word +0x0C, getChunkDataSize 0x00306E16 its dword +0x14, and getChunkDataSizeLeft 0x00306E22 its dword +0x18. registerParser 0x00307779 links the parser list at +0x18 and returns the new UserParser in EAX at 0x003077DA.
// Out-of-line DataChunkInput rows: atEndOfFile 0x00306C08, clearChunkStack 0x00306DA4, reset 0x00306DCC, getChunkVersion 0x00306E06, getChunkDataSize 0x00306E16, getChunkDataSizeLeft 0x00306E22, atEndOfChunk 0x00306E2E, decrementDataLeft 0x00306E40, readReal 0x00306E56, readInt 0x00306E78, readByte 0x00306E9A, readArrayOfBytes 0x00306EBC, destructor 0x00306F01, closeDataChunk 0x00306F53, constructor 0x00307316, openDataChunk 0x0030740F, getChunkLabel 0x003074D7, readAsciiString 0x0030750A, readUnicodeString 0x003075A3, registerParser 0x00307779, readNameKey 0x003077E0, readDict 0x00307833, parse 0x00307AC0. Ledger manglings prove their signatures, including the protected closeDataChunk and decrementDataLeft.
// Contents rows: constructor 0x00306D48 (also inlined at 0x00307331..0x0030733D), destructor 0x00306D5C, getName 0x003070F1, write 0x0030715D, read 0x003071E9, findMapping 0x00307A2C, getID 0x00307A53, allocateID 0x00307A6A. parse reads contents byte +0xC at 0x00307AE3; allocateID increments contents dword +4 at 0x00307AB3 and next ID +8 at 0x00307AA3.
// Donor names: Zero Hour GeneralsMD Common/DataChunk.h supplies the field names, DataChunkVersionType, DataChunkParserPtr, and isOpenedForRead. BFME2's registerParser returns UserParser*, as its ledger row proves. No donor header is included.
#ifndef BFME2_COMMON_DATACHUNK_H
#define BFME2_COMMON_DATACHUNK_H

class AsciiString;
class UnicodeString;
class Dict;
class ChunkInputStream;
class OutputStream;
class Mapping;
class InputChunk;
class UserParser;
class DataChunkInput;
class DataChunkTableOfContents;
struct DataChunkInfo;
enum NameKeyType;

typedef unsigned short DataChunkVersionType;
typedef bool (*DataChunkParserPtr)(DataChunkInput &file, DataChunkInfo *info, void *userData);

class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents() : m_list(0), m_listLength(0), m_nextID(1), m_headerOpened(false) {}
    ~DataChunkTableOfContents();
    unsigned int getID(const AsciiString &name);
    AsciiString getName(unsigned int id);
    unsigned int allocateID(const AsciiString &name);
    bool isOpenedForRead() { return m_headerOpened; }
    void write(OutputStream &stream);
    void read(ChunkInputStream &stream);

    Mapping *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;

private:
    Mapping *findMapping(const AsciiString &name);
};

class DataChunkInput
{
public:
    DataChunkInput(ChunkInputStream *stream);
    ~DataChunkInput();
    UserParser *registerParser(const AsciiString &label, const AsciiString &parentLabel,
        DataChunkParserPtr parser, void *userData = 0);
    bool parse(void *userData = 0);
    AsciiString openDataChunk(DataChunkVersionType *version);
    bool atEndOfFile();
    bool atEndOfChunk();
    void clearChunkStack();
    void reset();
    AsciiString getChunkLabel();
    DataChunkVersionType getChunkVersion();
    unsigned int getChunkDataSize();
    unsigned int getChunkDataSizeLeft();
    float readReal();
    int readInt();
    unsigned char readByte();
    AsciiString readAsciiString();
    UnicodeString readUnicodeString();
    Dict readDict();
    void readArrayOfBytes(char *buffer, int length);
    NameKeyType readNameKey();

protected:
    void closeDataChunk();
    void decrementDataLeft(int size);
    ChunkInputStream *m_file;
    DataChunkTableOfContents m_contents;
    int m_fileposOfFirstChunk;
    UserParser *m_parserList;
    InputChunk *m_chunkStack;

public:
    void *m_currentObject;
    void *m_userData;
};

#endif
