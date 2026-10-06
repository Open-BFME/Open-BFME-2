// cl: /DNDEBUG /MD /EHsc
//
// ?rva0028C264@Object@@QAE_NPAHH@Z @0x0028C264 121B
// Object dual-path frame-gated id fetch. Evidence: thiscall via callers
// 0x0046BBD9 0x0046BC0C 0x00349EDF 0x00349F56 (ecx=Object, out dword zeroed,
// delay 4); same globals as neighbour rva0028C1CC (LogicFramesPerSecond
// 0x00DBA4E4, TheGameLogic frame 0x00DFE78C+0x40); provider at +0x250 slot
// 0x7c matching ObjectRva0028C197, body at +0x254 slots 0x40/0x3c matching
// ObjectRva0028B85B; ret 8 bool via al; name stays address-derived (Object
// owner proven by callers and offsets, identity unproven).

extern int g_Va00DBA4E4;

class Rva0028C264Inner
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual bool slot36(int *out, int frames);
};

class Rva0028C264Provider
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Rva0028C264Inner *slot31();
};

struct Rva0028C264Result
{
	char m_pad[8];
	int m_value; // +8
};

class Rva0028C264Body
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual Rva0028C264Result *slot15();
	virtual int slot16();
};

class Object
{
public:
	bool rva0028C264(int *out, int n);

private:
	char m_pad[0x250];
	Rva0028C264Provider *m_provider250; // +0x250
	Rva0028C264Body *m_body254; // +0x254
};

class GameLogic
{
	public:
	char m_pad[0x40];
	unsigned m_frame; // +0x40
};

extern class GameLogic *TheGameLogic;

#define LogicFramesPerSecond g_Va00DBA4E4

bool Object::rva0028C264(int *out, int n)
{
	int frames = LogicFramesPerSecond * n;
	Rva0028C264Provider *provider = m_provider250;
	Rva0028C264Inner *inner;
	if (provider != 0)
		inner = provider->slot31();
	else
		inner = 0;
	if (inner != 0)
		return inner->slot36(out, frames);
	Rva0028C264Body *body = m_body254;
	if (body != 0)
	{
		int t = body->slot16();
		if (t != -1)
		{
			if ((unsigned)(t + frames) >= TheGameLogic->m_frame)
			{
				Rva0028C264Result *r = body->slot15();
				if (r != 0)
					*out = r->m_value;
				return true;
			}
		}
	}
	return false;
}
