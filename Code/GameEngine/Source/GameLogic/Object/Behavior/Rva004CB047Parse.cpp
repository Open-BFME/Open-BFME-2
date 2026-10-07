// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /arch:SSE /G7
// stlport
// ?Rva004CB047Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x004CB047, 172 bytes.
// Stored as the SoundState FieldParse callback at 0x00C5F154. The callback
// reads a BfmeObject544 through INI and appends it to the target's +8 vector.

struct FieldParse;

class INI;

class Rva000B937E
{
	public:
	void rva000B937E(INI *ini, void *userData);

private:
	unsigned char m_storage[0x220];
};

struct BfmeObject544 : Rva000B937E
{
	BfmeObject544();
	~BfmeObject544();
};

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *parse, unsigned int extraOffset);

private:
	unsigned char m_storage[0x84];
};

class INI
{
public:
	void initFromINIMulti(void *object, const MultiIniFieldParse &parse);
};

namespace _STL
{
template <class T>
class allocator;

template <class T, class Allocator>
class vector
{
public:
	void push_back(const T &value);
};
}

struct Rva004CB047Target
{
	unsigned char m_prefix[8];
	_STL::vector<BfmeObject544, _STL::allocator<BfmeObject544> > m_soundStates;
};

extern const FieldParse g_00C5F114[];
int Rva0033A495Get(void);

void Rva004CB047Parse(INI *ini, void *instance, void *store, const void *userData)
{
	if (instance == 0)
		return;

	BfmeObject544 soundState;
	soundState.rva000B937E(ini, 0);

	MultiIniFieldParse parse;
	parse.add(g_00C5F114, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva0033A495Get()), 0x4C);
	ini->initFromINIMulti(&soundState, parse);
	((Rva004CB047Target *)instance)->m_soundStates.push_back(soundState);
}
