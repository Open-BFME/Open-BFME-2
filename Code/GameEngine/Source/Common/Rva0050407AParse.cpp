// cl: /O1 /Ob1 /arch:SSE /DNDEBUG /MD /EHsc
// ?Rva0050407AParseColorControlPointBlock@@YAXPAVINI@@PAX1PBX@Z @0x0050407A (151B):
// ColorControlPoint INI block parser. Retail checks INI and instance, throws
// INIException(3, "ColorControlPoint::ParseINIBlock::Invalid data passed in.")
// otherwise. Follows ControlPoint::ParseINIBlock at 0x00064680 (record via
// ctor at 0x0050406E, initFromINI with table at 0x00863CE8, rescale of +0x18
// via 0x00503E4F) plus a color fixup: copy the leading 12B color through
// Rva002BE7DB, triplicate its first float to all three, copy back, then hand
// the record with the instance to the userData callback. Evidence: single
// chain caller context (prev 0x0050406E), string literal, FieldParse table,
// Scale pin, Rva002BE7DB row, callback shape.
typedef int Int;
typedef float Real;

struct FieldParse;

class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);
private:
	Int m_code;
	const char *m_msg;
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
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	unsigned int m_18;
};

class Rva0050406E
{
public:
	Rva0050406E();
	Rva00064390 m_base;
};

extern const FieldParse g_00C63CE8[];

static unsigned int rva003BB860Scale(unsigned int value)
{
	return (unsigned int)((float)value * 0.03f);
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
		record.m_base.m_18 = rva003BB860Scale(record.m_base.m_18);
		Rva002BE7DBValue tmp;
		Rva002BE7DBValue &rv = ((Rva002BE7DB *)&record)->rva002BE7DB(tmp);
		float v = rv.x;
		tmp.x = v;
		tmp.y = v;
		tmp.z = v;
		*(Block12 *)&record = *(const Block12 *)&tmp;
		Rva0050407ACallback callback = (Rva0050407ACallback)userData;
		if (callback)
			callback(instance, &record);
	} else {
		throw INIException(3, "ColorControlPoint::ParseINIBlock::Invalid data passed in.");
	}
}
