// cl: /Ob1 /DNDEBUG /MD /EHsc
// ?Rva0050407AParseColorControlPointBlock@@YAXPAVINI@@PAX1PBX@Z @0x0050407A (151B):
// ColorControlPoint INI block parser. Retail checks INI and instance, throws
// INIException(3, "ColorControlPoint::ParseINIBlock::Invalid data passed in.")
// otherwise. Follows ControlPoint::ParseINIBlock at 0x00064680 (record via
// ctor at 0x0050406E, initFromINI with table at 0x00863CE8, rescale of +0x18
// via 0x00503E4F) plus a color fixup: copy the leading 12B color through
// Rva002BE7DB, triplicate its first float to all three, copy back, then hand
// the record with the instance to the userData callback. Evidence: single
// chain caller context (prev 0x0050406E), string literal, FieldParse table,
// Rowed frame rescale, Rva002BE7DB row, callback shape.
typedef int Int;
typedef float Real;

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };

class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);
	~INIException();
private:
	// Retail's copy constructor and destructor own the message at +0;
	// its throw information names the destructor at RVA 0x0002BD30.
	char *m_msg;
	Int m_code;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

struct Rva002BE7DBValue
{
	float x;
	float y;
	float z;
};

class Rva002BE7DB
{
public:
	float m_x;
	float m_y;
	float m_z;
	Rva002BE7DBValue &rva002BE7DB(Rva002BE7DBValue &out) const;
};

class Rva00064390
{
public:
	Rva00064390();
	int m_intensity;
	int m_04;
	int m_08;
	int m_0C;
	float m_easeIn;
	float m_easeOut;
	unsigned int m_time;
};

class Rva0050406E
{
public:
	Rva0050406E();
	Rva00064390 m_base;
};

extern "C" {
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?dup_002F0F7@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00863CE8: 4 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C63CE8[5] = {
	{ "Intensity", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
	{ "Time", (FieldParseProc)&__identifier("?dup_002F0F7@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ "EaseIn", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "EaseOut", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ 0, 0, 0, 0 }
};

// Same file-static helper as the ControlPoint parser: retail uses the
// writable frame-rate global, rather than a fixed 30 Hz scale.
extern int BfmeClientFramesPerSecond;
static unsigned int msecToFramesRva00503E4F(unsigned int value)
{
	return (unsigned int)((Real)BfmeClientFramesPerSecond * (Real)value * 0.001f);
}

typedef void (*Rva0050407ACallback)(void *instance, Rva0050406E *record);

struct Block12
{
	int v0;
	int v1;
	int v2;
};

void Rva0050407AParseColorControlPointBlock(INI *ini, void *instance, void *, const void *userData)
{
	if (ini && instance) {
		Rva0050406E record;
		ini->initFromINI(&record, g_00C63CE8);
		record.m_base.m_time = msecToFramesRva00503E4F(record.m_base.m_time);
		Rva002BE7DBValue color;
		Rva002BE7DBValue &rv = ((Rva002BE7DB *)&record)->rva002BE7DB(color);
		float intensity = rv.x;
		color.x = intensity;
		color.y = intensity;
		color.z = intensity;
		*(Block12 *)&record = *(const Block12 *)&color;
		Rva0050407ACallback callback = (Rva0050407ACallback)userData;
		if (callback)
			callback(instance, &record);
	} else {
		throw INIException(3, "ColorControlPoint::ParseINIBlock::Invalid data passed in.");
	}
}
