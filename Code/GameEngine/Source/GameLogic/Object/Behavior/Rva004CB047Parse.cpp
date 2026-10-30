// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /arch:SSE /G7
// stlport
// ?Rva004CB047Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x004CB047, 172 bytes.
// Stored as the SoundState FieldParse callback at 0x00C5F154. The callback
// reads a BfmeObject544 through INI and appends it to the target's +8 vector.

#include <vector>

struct FieldParse;

class INI;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

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
	static void Rva004CAB3D_ParseVoicePriority(INI *ini, void *instance, void *store, const void *userData);
	void initFromINIMulti(void *object, const MultiIniFieldParse &parse);
};

// bfme link decl-only begin
// The append is the rowed push_back 0x004CB00D (StlportObject544Vector.cpp).
namespace _STL { template <> void vector<BfmeObject544, allocator<BfmeObject544> >::push_back(const BfmeObject544 &); }
// bfme link decl-only end

struct Rva004CB047Target
{
	unsigned char m_prefix[8];
	_STL::vector<BfmeObject544, _STL::allocator<BfmeObject544> > m_soundStates;
};

void Rva0033DC9CParse(INI *ini, void *instance, void *store, const void *userData);

// The sound state's own fields (.rdata 0x00C5F114, 3 entries read from
// retail; the SoundState table 0x00C5F150 that stores this callback follows
// it). Defined here, its only user.
extern const FieldParse g_soundStateFieldParse[] =
{
	{ "UnitSpecificSounds", Rva0033DC9CParse, 0, 0x20C },
	{ "VoicePriority", INI::Rva004CAB3D_ParseVoicePriority, 0, 0x218 },
	{ 0, 0, 0, 0 }
};
int Rva0033A495Get(void);

void Rva004CB047Parse(INI *ini, void *instance, void *store, const void *userData)
{
	if (instance == 0)
		return;

	BfmeObject544 soundState;
	soundState.rva000B937E(ini, 0);

	MultiIniFieldParse parse;
	parse.add(g_soundStateFieldParse, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva0033A495Get()), 0x4C);
	ini->initFromINIMulti(&soundState, parse);
	((Rva004CB047Target *)instance)->m_soundStates.push_back(soundState);
}
