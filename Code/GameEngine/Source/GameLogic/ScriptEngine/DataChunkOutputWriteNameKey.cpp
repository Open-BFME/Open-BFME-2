// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// DataChunkOutput::writeNameKey, retail 0x00307D29 (true 92 bytes; the 10B
// reloc row covers only the SEH-prologue head: mov eax,cookie + call
// __EH_prolog, so that row size is a misbound).
// ZH DataChunk.cpp writeNameKey ported with one BFME2 delta proven by the
// retail bodies: keyToName returns a reference to the generator's interned
// string (retail 0x00148C95 returns the bucket/global AsciiString pointer in
// eax with ret 4: no hidden pointer, no copy on the return path), so the
// declaration here returns const AsciiString &. kname copy-constructs from
// it through AsciiString's inline forwarder, which routes directly to the
// StringBase<char> copy body at 0x365F0 (the push eax + lea ecx + call shape
// at all 61 keyToName call sites, cf. BFME1 ascii_string.h for the same
// delegation evidence). Teardown inlines to the folded releaseBuffer at
// 0x36410.

struct BfmeStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

class AsciiString;
#include "ascii_string.h"


enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

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
};
class UnicodeString;
class Dict
{
public:
	enum DataType { DICT_NONE = -1, DICT_BOOL, DICT_INT, DICT_REAL, DICT_ASCIISTRING, DICT_UNICODESTRING };
private:
	struct DictPairData { unsigned short m_refCount; unsigned short m_numPairsAllocated; unsigned short m_numPairsUsed; };
public:
	Dict(int numPairsToPreAllocate);
	Dict(const Dict &other) : m_data(other.m_data)
	{
	    if (m_data)
	        ++m_data->m_refCount;
	}
	~Dict() { releaseData(); }
	void setBool(int key, bool value);
	void setInt(int key, int value);
	void setReal(int key, float value);
	void setAsciiString(int key, const AsciiString &value);
	void setUnicodeString(int key, const UnicodeString &value);
private:
	void releaseData();
public:
	int getPairCount() const { return m_data ? m_data->m_numPairsUsed : 0; }
	NameKeyType getNthKey(int n) const;
	DataType getNthType(int n) const;
	bool getNthBool(int n) const;
	int getNthInt(int n) const;
	float getNthReal(int n) const;
	AsciiString getNthAsciiString(int n) const;
	UnicodeString getNthUnicodeString(int n) const;
private:
	DictPairData *m_data; // +0x00
};

struct _iobuf;
class OutputStream;
class OutputChunk;
class AsciiString;
class UnicodeString;
class Dict;

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
// ?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z
void DataChunkOutput::writeNameKey(NameKeyType key)
{
	AsciiString kname = TheNameKeyGenerator->keyToName(key);
	int keyAndType = m_contents.allocateID(kname);
	keyAndType <<= 8;
	Dict::DataType t = Dict::DICT_ASCIISTRING;
	keyAndType |= (t & 0xff);
	writeInt(keyAndType);
}
