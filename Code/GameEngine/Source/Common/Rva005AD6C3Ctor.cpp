// cl: /DNDEBUG /MD /EHsc
// ??0Rva005AD6C3@@QAE@PBURva005DCC4BSource@@@Z @ 0x005AD6C3 39B
// Derived of rowed Rva005DCC4B: base converts source+0x74, then +0x08=0 and
// +0x0C=TheGameLogic frame+0x40. Evidence: call at 0x005AD6CA to rowed
// ??0Rva005DCC4B@@QAE@PBURva005DCC4BSource@@@Z, vtable 0x0087258C at [this],
// TheGameLogic 0x00DFE78C deref +0x40, caller 0x00506AC4 new 0x10 pushes Object
// into vector<ModuleData*>.

typedef int Int;

struct Rva005DCC4BSource
{
	char m_bytes00[0x74];
	Int m_field74;
};

class Rva005DCC4B
{
public:
	Rva005DCC4B(const Rva005DCC4BSource *source);
	virtual ~Rva005DCC4B();

	Int m_field04;
};

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Rva005AD6C3 : public Rva005DCC4B
{
public:
	Rva005AD6C3(const Rva005DCC4BSource *source);
	virtual ~Rva005AD6C3();

	Int m_field08;
	Int m_field0C;
};

Rva005AD6C3::Rva005AD6C3(const Rva005DCC4BSource *source)
	: Rva005DCC4B(source)
{
	m_field08 = 0;
	m_field0C = (Int)TheGameLogic->m_frame;
}
