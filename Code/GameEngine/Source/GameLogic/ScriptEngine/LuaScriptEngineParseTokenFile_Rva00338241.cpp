// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /O1 -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
// ?rva00338241@LuaScriptEngine@@QAEXPBD_N@Z, retail 0x00338241, 214 bytes.
// BFME2 ParseTokenFile over LuaScriptEngine: openFile 3-arg plus size plus
// new[] plus read plus close plus Rva00542806 init plus finish loop plus
// ParseToken plus delete[]. Ported from Open-BFME-1
// LuaScriptEngineParseTokenFile.cpp (rva002EC840ParseTokenFile): BFME2 adds
// third openFile arg 0 plus Rva00542806/Rva0054288B for BfmeLexEAN ctor/dtor
// plus m_keepOpen at +0xD8. Evidence: sole callers 0x003387D4/0x00338997;
// callees rowed openFile 0x00600C34 plus List init 0x00542806 plus ParseToken
// 0x003381C4 plus thunk 0x0054288B plus new[]/delete[]; layout +0xD8 matches.

typedef int Int;
typedef bool Bool;

extern void *operator new[](unsigned int size);
extern void operator delete[](void *memory);

class File
{
public:
	virtual void fileVirtual00() = 0;
	virtual void fileVirtual01() = 0;
	virtual void close() = 0;
	virtual Int read(void *buffer, Int bytes) = 0;
	virtual void fileVirtual03() = 0;
	virtual void fileVirtual04() = 0;
	virtual void fileVirtual05() = 0;
	virtual void fileVirtual06() = 0;
	virtual void fileVirtual07() = 0;
	virtual void fileVirtual08() = 0;
	virtual void fileVirtual09() = 0;
	virtual Int size() = 0;
	virtual void fileVirtual12() = 0;
};

class FileSystem
{
public:
	File *openFile(const char *filename, int a, int b);
};
extern FileSystem *TheFileSystem;

class Rva00542806
{
public:
	Rva00542806 *rva00542806(char *a1, int a2, int a3);
private:
	char *m_ptr;
	char m_pad4[8];
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
	char m_buf[0x184];
};

class Rva0054288B
{
public:
	void rva0054288B();
};

struct ParserWrap : Rva00542806
{
	ParserWrap(char *a1, int a2, int a3) { rva00542806(a1, a2, a3); }
	~ParserWrap() { ((Rva0054288B *)this)->rva0054288B(); }
};

class XmlNameSlotList
{
public:
	Int finish();
};

class BfmeLexEAN;
class __declspec(novtable) LuaScriptEngine
{
public:
	void rva00338241(const char *filename, Bool keepOpen);
	void rva002EC770ParseToken(BfmeLexEAN *parser);
private:
	char m_pad[0xD8];
	unsigned char m_keepOpen;
};

void LuaScriptEngine::rva00338241(const char *filename, Bool keepOpen)
{
	File *file = TheFileSystem->openFile(filename, 0x41, 0);
	if (file != 0)
	{
		Int size = file->size();
		char *source = (char *)operator new[](size + 10);
		file->read(source, size);
		source[size] = 0;
		file->close();
		char buffer[0x1000];
		m_keepOpen = keepOpen;
		ParserWrap parser(source, (int)buffer, 0xFFF);
		for (;;)
		{
			Int status = ((XmlNameSlotList *)&parser)->finish();
			if (status == 0)
				break;
			if (--status != 0)
				return;
			rva002EC770ParseToken((BfmeLexEAN *)&parser);
		}
		m_keepOpen = 0;
		operator delete[](source);
	}
}
