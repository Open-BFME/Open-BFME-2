// cl: /DNDEBUG /MD /EHs
//
// ?Rva003FD7CEParse@@YAXPAVINI@@@Z, retail 0x003FD7CE, 95 bytes.
// Chain: calls 0x0021294A which just landed. Parses one INI token via rowed
// getNextToken 0x0002DF97, builds a StringBase<char> via rowed ctor
// 0x00037BA0, creates a Rva003FD789 via rowed 0x0021294A on the global at
// 0x009FE1C8, tears down the temp via rowed releaseBuffer 0x00036410, then
// inits the new object from the FieldParse table at 0x00837CD8 via rowed
// initFromINI 0x0002DE78. Prev 0x003FD789 is the Rva003FD789 dtor.
class INI;
struct FieldParse;
template <typename T> class StringBase;
class Rva0021294A;
class Rva003FD789;

template <typename T>
class StringBase
{
	friend void Rva003FD7CEParse(INI *ini);
public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
private:
	StringBase(const char *text);
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *obj, const FieldParse *table);
};

class Rva0021294A
{
public:
	Rva003FD789 *rva0021294A(const StringBase<char> &str);
};

class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
extern const FieldParse g_00837CD8;

void __cdecl Rva003FD7CEParse(INI *ini)
{
	const char *token = ini->getNextToken(0);
	if (token == 0)
		return;
	Rva003FD789 *item;
	{
		StringBase<char> name(token);
		item = ((Rva0021294A *)TheLivingWorldManager)->rva0021294A(name);
	}
	ini->initFromINI(item, &g_00837CD8);
}

// TheLivingWorldManager (the data ledger's name): matched references place it at VA 0xdfe1c8.
LivingWorldManager *TheLivingWorldManager = 0;
