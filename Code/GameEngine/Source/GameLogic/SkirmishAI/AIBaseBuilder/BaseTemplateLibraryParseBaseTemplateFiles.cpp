// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// ?parseBaseTemplateFiles@BaseTemplateLibrary@@QAEXXZ retail 0x0041F095..0x0041F25E
// (457 bytes with the trailing int3 after the noreturn throw; Ghidra counts 456).
//
// Identity: WorldBuilder 0x013305B0 is BaseTemplateLibrary::parseBaseTemplateFiles
// (AIBaseTemplate.cpp, assert 221).
//
// What the body does:
// - For each entry of the hash map at +0x0C it takes the record's file name
//   (record +4) and stops at the first empty one.
// - It opens "Bases\<name>\<name>.bse" through the cached file stream
//   (rowed ctor 0x00240000, open 0x00308050, close 0x003079ED, dtor
//   0x0023F4F0).
// - It parses the "CastleTemplates" chunks with the rowed
//   parseBaseTemplateDataChunk 0x0041ED84, bound through the rowed parser
//   ctor 0x0041E6BE. Its inline base dtor unregisters through 0x00306D7B.
// - A failed parse throws ERROR_BAD_INI (0xDEAD0005).
// The stream and parser views follow the rowed SidesListDataChunks.cpp.
//
// Matching notes:
// - The stream ctor is nothrow, so no EH state is spent between the file
//   name copy and the stream.
// - The open failure continues the loop, so the label temporary and the file
//   name share retail's frame slots.
#include <hash_map>
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

enum ErrorCode
{
	ERROR_BAD_INI = 0xDEAD0005
};

class ChunkInputStream
{
};

class Rva00240000 : public ChunkInputStream
{
public:
	Rva00240000() throw();				// 0x00240000
	~Rva00240000();						// 0x0023F4F0
	bool rva00308050(AsciiString path);	// 0x00308050, open
private:
	char m_data[0x20];
};

class Rva003079ED
{
public:
	void rva003079ED();					// 0x003079ED, close
};

struct DataChunkInfo;

class DataChunkInput
{
public:
	explicit DataChunkInput(ChunkInputStream *stream);	// 0x00307316
	~DataChunkInput();					// 0x00306F01
	bool parse(void *userData);			// 0x00307AC0
private:
	char m_data[0x28];
};

class Q1Forwardee0000871A
{
public:
	void handle(int token);				// 0x00306D7B
};

class DataChunkParser
{
public:
	DataChunkParser(DataChunkInput *input, const AsciiString *name, const AsciiString *label);
	virtual ~DataChunkParser() { m_registry->handle(m_token); }
private:
	Q1Forwardee0000871A *m_registry;	// +0x04
	int m_token;						// +0x08
};

class Rva0041E6BE : public DataChunkParser
{
public:
	Rva0041E6BE(int a, int b, DataChunkInput *input, const AsciiString *name, const AsciiString *label);
private:
	int m_a;
	int m_b;
};

struct BaseTemplateFileRecord
{
	Int m_00;
	AsciiString m_fileName;				// +0x04
};

// The SubsystemInterface slots up to postProcessLoad (slot 3); the subsystem's
// vtable is 0x0083AF78 (??_7Rva0022BD9ASubsystem, ctor 0x0041EFFF).
class BaseTemplateLibrary
{
public:
	virtual ~BaseTemplateLibrary();
	virtual void init();
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	void parseBaseTemplateFiles();
	bool parseBaseTemplateDataChunk(DataChunkInput &file, DataChunkInfo *info);
private:
	char m_pad04[0x0C - 0x04];
	_STL::hash_map<Int, BaseTemplateFileRecord *> m_files;	// +0x0C
};

void BaseTemplateLibrary::parseBaseTemplateFiles()
{
	for (_STL::hash_map<Int, BaseTemplateFileRecord *>::iterator it = m_files.begin(); it != m_files.end(); ++it)
	{
		AsciiString name = (*it).second->m_fileName;
		if (name.isEmpty())
			return;
		AsciiString path("Bases\\");
		path.concat(name);
		path.concat("\\");
		path.concat(name);
		path.concat(".bse");
		AsciiString fileName = path;
		Rva00240000 stream;
		if (!stream.rva00308050(fileName))
			continue;
		DataChunkInput file(&stream);
		bool (BaseTemplateLibrary::*parser)(DataChunkInput &, DataChunkInfo *) = &BaseTemplateLibrary::parseBaseTemplateDataChunk;
		Rva0041E6BE dispatcher((int)this, *(int *)&parser, &file, &AsciiString("CastleTemplates"), &AsciiString::TheEmptyString);
		if (!file.parse(0))
			throw ERROR_BAD_INI;
		((Rva003079ED *)&stream)->rva003079ED();
	}
}

// ?postProcessLoad@BaseTemplateLibrary@@UAEXXZ @0x0041F27A 5B, right after
// parseBaseTemplateFiles: slot 3 of the subsystem vtable 0x0083AF78, a tail
// jump into parseBaseTemplateFiles above.
void BaseTemplateLibrary::postProcessLoad()
{
	parseBaseTemplateFiles();
}
