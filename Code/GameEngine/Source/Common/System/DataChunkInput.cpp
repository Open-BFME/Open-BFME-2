// cl: /O1 /DNDEBUG /MD /EHsc
// readable body of ??1DataChunkInput@@QAE@XZ: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?readArrayOfBytes@DataChunkInput@@QAEXPADH@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?readAsciiString@DataChunkInput@@QAE?AVAsciiString@@XZ: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?readNameKey@DataChunkInput@@QAE?AW4NameKeyType@@XZ: Code/GameEngine/Source/Common/System/DataChunk.cpp

// DataChunkInput's teardown and its three readers:
//
//   ~DataChunkInput  0x00102910   the chunk stack, the parser list and the
//                                 table's mapping list, each freed through the
//                                 node's virtual deleting destructor
//   readArrayOfBytes 0x00102870   raw bytes
//   readAsciiString  0x00103450   a counted string
//   readNameKey      0x00103390   an id looked up in the table, then interned
//
// The destructor is the layout evidence the readers rely on: the chunk stack
// is at +0x1c, the parser list at +0x18 and the table of contents starts at
// +0x04. Both facts used to be asserted four times over -- one file spelled
// the table as char[0x10], another as four fields, a third as four differently
// typed fields -- and the InputChunk fields the readers decrement were named
// in one file and padded over in two.
//
// The yield is BFME's, not Zero Hour's: every read gives the OS a slice and
// pumps the engine's window messages first, through slot 16 of the GameEngine
// vtable.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

class GameEngine;
extern GameEngine *TheGameEngine;

// BFME retail GameEngine vtable: serviceWindowsOS is slot 16 (+0x40).
class BFME_GameEngineServiceWindowsOS
{
public:
	virtual void _bfme_ge_slot00() = 0;
	virtual void _bfme_ge_slot01() = 0;
	virtual void _bfme_ge_slot02() = 0;
	virtual void _bfme_ge_slot03() = 0;
	virtual void _bfme_ge_slot04() = 0;
	virtual void _bfme_ge_slot05() = 0;
	virtual void _bfme_ge_slot06() = 0;
	virtual void _bfme_ge_slot07() = 0;
	virtual void _bfme_ge_slot08() = 0;
	virtual void _bfme_ge_slot09() = 0;
	virtual void _bfme_ge_slot10() = 0;
	virtual void _bfme_ge_slot11() = 0;
	virtual void _bfme_ge_slot12() = 0;
	virtual void _bfme_ge_slot13() = 0;
	virtual void _bfme_ge_slot14() = 0;
	virtual void _bfme_ge_slot15() = 0;
	virtual void serviceWindowsOS() = 0;
};

// BFME yields to the OS before every read.
static void bfmeDataChunkYieldToOS(void)
{
	::Sleep(0);
	if (TheGameEngine)
		reinterpret_cast<BFME_GameEngineServiceWindowsOS *>(TheGameEngine)->serviceWindowsOS();
}

// The retail bodies use the shared StringBase<char> implementations at
// 0x00887B60 and 0x00887BE0, while the returned type keeps the AsciiString
// ABI name at the DataChunkInput boundary.
template <typename T>
class StringBase
{
public:
	StringBase(void) : m_data(0) {}
	StringBase(const T *text);
	T *getBufferForRead(Int len);
	// ?set@?$StringBase@D@@QAEXABV1@@Z aliases the retail
	// ?set@UnicodeString@@QAEXABV1@@Z pin (see symbols.csv) -- both types
	// share this StringBase<char> implementation.
	void set(const StringBase &other);

protected:
	void *m_data;
private:
	StringBase(const StringBase &other);
	friend class AsciiString;
	friend class BFME_GameEngineServiceWindowsOS;
	friend class ChunkInputStream;
	friend class DataChunkInfo;
	friend class DataChunkInput;
	friend class DataChunkTableOfContents;
	friend class InputChunk;
	friend class Mapping;
	friend class NameKeyGenerator;
	friend class UserParser;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	// Retail's AsciiString adds no members to StringBase<char>: a copy of one
	// encodes the base copy ctor at 0x00887B60 directly, so the delegation has
	// to be visible here.
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	// Retail's openDataChunk builds AsciiString("") by calling the
	// StringBase<char> C-string ctor 0x00037BA0 directly; AsciiString's own
	// out-of-line const char * ctor (0x0000654A) only forwards to it.
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString();

	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}

	const char *str() const
	{
		static const char empty = 0;
		return m_data ? static_cast<const char *>(m_data) + 8 : &empty;
	}

	// parse()'s scope/label matches inline this compare (repe cmpsb) rather
	// than calling out -- there is no separate call target for it in the
	// retail body.
	int compare(const AsciiString &that) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapReaderWriterInfo.h
// parse()'s inlined closeDataChunk() proves the next two slots: tell() at
// +0x04, absoluteSeek() at +0x08. atEndOfFile() proves eof() at +0x0C.
class ChunkInputStream
{
public:
	virtual Int read(void *pData, Int numBytes);
	virtual Int tell(void);
	virtual void absoluteSeek(Int pos);
	virtual Bool eof(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class InputChunk
{
public:
	virtual void *deleteInstance(int flags);	// vptr this+0x00 (MemoryPoolObject pattern)

	InputChunk *next;					// this+0x04
	UnsignedInt id;						// this+0x08
	UnsignedShort version;					// this+0x0C
	UnsignedShort padding;
	Int chunkStart;						// this+0x10
	Int dataSize;						// this+0x14
	Int dataLeft;						// this+0x18
};

class DataChunkInput;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
struct DataChunkInfo
{
	~DataChunkInfo();
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType version;
	Int dataSize;
};

typedef Bool (*DataChunkParserPtr)(DataChunkInput &file, DataChunkInfo *info, void *userData);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
// DataChunkInput::registerParser (0x00103840) proves the extra intrusive
// previous-link at +0x08 ahead of the parser field at +0x0C, which parse()'s
// direct field call (call dword ptr [ecx+0x0C]) also requires.
class UserParser
{
	public:
	virtual void *deleteInstance(int flags);
	virtual ~UserParser();
	UserParser *next;					// this+0x04
	UserParser **previous;					// this+0x08
	DataChunkParserPtr parser;				// this+0x0C
	AsciiString label;					// this+0x10
	AsciiString parentLabel;				// this+0x14
	void *userData;						// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
struct Mapping
{
	virtual ~Mapping();
	Mapping *next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
	AsciiString getName(UnsignedInt id);
	Bool isOpenedForRead(void) { return m_headerOpened; }

	~DataChunkTableOfContents();

	Mapping *m_list;					// this+0x00
	Int m_listLength;
	UnsignedInt m_nextID;
	Bool m_headerOpened;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkInput
{
protected:
	ChunkInputStream *m_file;				// this+0x00
	DataChunkTableOfContents m_contents;			// this+0x04
	Int m_fileposOfFirstChunk;				// this+0x14
	UserParser *m_parserList;				// this+0x18
	InputChunk *m_chunkStack;				// this+0x1C

	__declspec(noinline) void decrementDataLeft(Int size)
	{
		InputChunk *c;

		c = m_chunkStack;
		while (c) {
			c->dataLeft -= size;
			c = c->next;
		}
	}

	Int readInt(void)
	{
		Int i;
		m_file->read(&i, sizeof(Int));
		decrementDataLeft(sizeof(Int));
		return i;
	}

	// parse() has no separate call target for closeDataChunk -- MSVC inlines
	// this whole body (the deleteInstance call at the end is the only
	// call still visible), so it is modelled here rather than as its own row.
	// Retail 0x00306F53 (82B) is the standalone out-of-line copy, called by
	// 0x00307BF6; evidence is the tell/absoluteSeek/decrement/unlink/
	// deleteInstance(0)/operator-delete sequence.
	void closeDataChunk(void)
	{
		if (m_chunkStack == 0) {
			return;
		}

		if (m_chunkStack->dataLeft > 0) {
			m_file->absoluteSeek(m_file->tell() + m_chunkStack->dataLeft);
			decrementDataLeft(m_chunkStack->dataLeft);
		}

		InputChunk *c = m_chunkStack;
		m_chunkStack = m_chunkStack->next;
		::operator delete(c != 0 ? c->deleteInstance(0) : 0);
	}

public:
	~DataChunkInput();
	void readArrayOfBytes(char *ptr, Int len);
	AsciiString readAsciiString(void);
	NameKeyType readNameKey(void);
	UserParser *registerParser(const AsciiString &label,
		const AsciiString &parentLabel,
		DataChunkParserPtr parser,
		void *userData);

	AsciiString openDataChunk(DataChunkVersionType *ver);
	// parse()'s call site has no separate call target for this either -- it
	// is the same 12-byte body as the standalone matched row at 0x00102740,
	// inlined here because the caller is visibly small too.
	UnsignedInt getChunkDataSize(void)
	{
		if (m_chunkStack == 0) {
			return 0;
		}
		return m_chunkStack->dataSize;
	}
	// Retail 0x00306E2E (18B): atEndOfChunk via dataLeft<=0 (null=>true).
	// ZH donor DataChunk.cpp atEndOfChunk verbatim. Caller 0x000AD07F.
	Bool atEndOfChunk(void);
	Bool atEndOfFile(void) { return m_file->eof(); }

	Bool parse(void *userData);
	void clearChunkStack();
	void reset();
};

Bool DataChunkInput::atEndOfChunk(void)
{
	if (m_chunkStack) {
		if (m_chunkStack->dataLeft <= 0)
			return true;
		return false;
	}
	return true;
}

void operator delete(void *ptr);

// Retail 0x00306DCC (20B): reset the stream to just-opened state: drain the
// chunk stack, then seek the file back to the first-chunk position. ZH
// DataChunk.cpp donor verbatim (clearChunkStack(); m_file->absoluteSeek(
// m_fileposOfFirstChunk)); absoluteSeek at ChunkInputStream slot 2 (+0x08)
// is proven by parse()'s inlined closeDataChunk. Rowed clearChunkStack at
// 0x00306DA4 resolves the call. Served via the chain lane.
void DataChunkInput::reset()
{
	clearChunkStack();
	m_file->absoluteSeek(m_fileposOfFirstChunk);
}

// ??1DataChunkInput@@QAE@XZ
// Retail 0x00306F01 (82B): clearChunkStack() for the InputChunk stack, the
// deleteInstance(0)/operator-delete loop over m_parserList at +0x18, then
// the implicit m_contents dtor (rowed 0x00306D5C) under the /EHsc frame.
// ZH donor proves the three phases; BFME2 routes both lists through the
// virtual deleteInstance at slot 0 (MessageStreamListCtors.cpp precedent).
DataChunkInput::~DataChunkInput()
{
	clearChunkStack();

	UserParser *parser = m_parserList;
	while (parser != 0) {
		UserParser *next = parser->next;
		::operator delete(parser->deleteInstance(0));
		parser = next;
	}
}

// ?readArrayOfBytes@DataChunkInput@@QAEXPADH@Z
// DataChunkInput::readArrayOfBytes: defined in DataChunkInputReadScalars.cpp (its row's unit).

// ?readAsciiString@DataChunkInput@@QAE?AVAsciiString@@XZ
// ?readAsciiString@DataChunkInput@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString DataChunkInput::readAsciiString(void)
{
	UnsignedShort len;

	bfmeDataChunkYieldToOS();
	m_file->read(&len, sizeof(UnsignedShort));
	decrementDataLeft(sizeof(UnsignedShort));

	AsciiString theString;
	if (len > 0) {
		char *str = theString.getBufferForRead(len);
		m_file->read(str, len);
		decrementDataLeft(len);

		str[len] = '\0';
	}

	return theString;
}

// readNameKey lives in DataChunkReadNameKey.cpp (declared-only callees keep
// the out-of-line readInt call; this TU's inline readInt would fold it).
// See 0x003077E0.

// ?parse@DataChunkInput@@QAE_NPAX@Z
// ?parse@DataChunkInput@@QAE_NPAX@Z present-unmatched
Bool DataChunkInput::parse(void *userData)
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType ver;
	UserParser *parser;
	Bool scopeOK;
	DataChunkInfo info;

	// If the header wasn't a chunk table of contents, we can't parse.
	if (!m_contents.isOpenedForRead()) {
		return false;
	}

	// if we are inside a data chunk right now, get its name
	if (m_chunkStack)
		parentLabel = m_contents.getName(m_chunkStack->id);

	while (atEndOfFile() == false)
	{
		if (m_chunkStack) { // If we are parsing chunks in a chunk, check current length.
			if (m_chunkStack->dataLeft < 4) {
				break;
			}
		}
		// open the chunk
		label = openDataChunk(&ver);
		if (atEndOfFile()) { // FILE * returns eof after you read past end of file, so check.
			break;
		}

		// find a registered parser for this chunk
		for (parser = m_parserList; parser; parser = parser->next)
		{
			// chunk labels must match
			if (parser->label.compare(label) == 0)
			{
				// make sure parent name (scope) also matches
				scopeOK = true;

				if (parentLabel.compare(parser->parentLabel) != 0)
					scopeOK = false;

				if (scopeOK)
				{
					// fill out the chunk info and call the user parser
					info.label = label;
					info.parentLabel = parentLabel;
					info.version = ver;
					info.dataSize = getChunkDataSize();

					// BFME: a parser registered with its own userData
					// (registerParser's 4th argument) takes priority over
					// parse()'s own userData argument.
					if (parser->parser(*this, &info, parser->userData ? parser->userData : userData) == false)
						return false;
					break;
				}
			}
		}

		// close chunk (and skip to end if need be)
		closeDataChunk();
	}

	return true;
}

UserParser *DataChunkInput::registerParser(const AsciiString &label,
	const AsciiString &parentLabel,
	DataChunkParserPtr parser,
	void *userData)
{
	UserParser *p;
	DataChunkInput *self = this;

	p = new UserParser;
	p->label.set(label);
	p->parentLabel.set(parentLabel);
	p->parser = parser;

	void *ud = userData;
	UserParser **head = &self->m_parserList;
	p->userData = ud;

	UserParser *next = *head;
	UserParser **pn = &p->next;
	*pn = next;
	if (next != 0)
		next->previous = pn;
	p->previous = head;
	*head = p;
	return p;
}

AsciiString DataChunkInput::openDataChunk(DataChunkVersionType *ver)
{
	InputChunk *c = new InputChunk;
	c->id = 0;
	c->version = 0;
	c->dataSize = 0;
	m_file->read((char *)&c->id, sizeof(UnsignedInt));
	decrementDataLeft(sizeof(UnsignedInt));
	m_file->read((char *)&c->version, sizeof(DataChunkVersionType));
	decrementDataLeft(sizeof(DataChunkVersionType));
	m_file->read((char *)&c->dataSize, sizeof(Int));
	decrementDataLeft(sizeof(Int));
	c->dataLeft = c->dataSize;
	c->chunkStart = m_file->tell();
	*ver = c->version;
	c->next = m_chunkStack;
	m_chunkStack = c;
	if (atEndOfFile())
		return AsciiString("");
	return m_contents.getName(c->id);
}

UserParser::~UserParser()
{
}

DataChunkInfo::~DataChunkInfo()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?consume@DataChunkInput@@QAEXH@Z=?decrementDataLeft@DataChunkInput@@IAEXH@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?deleteInstance@UserParser@@UAEPAXH@Z=??_GUserParser@@UAEPAXI@Z")
