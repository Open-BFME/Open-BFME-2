// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Six Rva0020DXXX methods (59/56/52/52/52/53B @0x0020D7F9/34/F1/25/59/EC).
// Homogeneous range-triple family on TheGameLogic (global 0x00DFE78C,
// +0x40 frame, GameLogicAwakenUpdate spelling): a pointer range at +0x10
// (custom container with dtor rowed 0x003ED94F), byte flags at +0x38/+0x3A
// and a frame tag at +0x3C. Target facts from game.dat:
// - 0x20D7F9/34 loop the range calling element workers 0x003EDC31/16 (no
//   null check), clear flags, then sync +0x3C from TheGameLogic frame (or 0
//   when null; 0x20D7F9 clears +0x38 too).
// - 0x20D8F1/25/59 return early when +0x38 set or the frame matches +0x3C,
//   else loop the range calling element workers 0x003EDE44/69/D8 with the
//   int param (ret 4, frameless).
// - 0x20D9EC is the implicit dtor (member dtor 0x003ED94F on +0x10 then
//   base dtor 0x001E3624; no vtable store, so implicit like the Rva001FDB55
//   precedent, forced out by the absent-from-retail anchor below).
// Element workers 0x003EDC31/16/44/69/D8 are unrowed/unpinned: declared
// here and pinned from the emitted spellings. The strict element type, the
// +0x39 byte, the +0x18..0x37 gap and the base size are unproven.
class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

struct Rva0020DXXXElem
{
	void rva003EDC31();
	void rva003EDC16();
	void rva003EDE44(int x);
	void rva003EDF69(int x);
	void rva003EDFD8(int x);
};

struct Rva003ED94FDtor
{
	~Rva003ED94FDtor();
	void **m_begin;
	void **m_end;
};

class Rva001E3624
{
public:
	virtual ~Rva001E3624();
private:
	char m_pad[0x0C];
};

class Rva0020DXXX : public Rva001E3624
{
public:
	void rva0020D7F9();
	void rva0020D834();
	void rva0020D8F1(int x);
	void rva0020D925(int x);
	void rva0020D959(int x);
private:
	Rva003ED94FDtor m_vec10;
	char m_pad18[0x20];
	char m_38;
	char m_39;
	char m_3A;
	char m_3B;
	int m_3C;
};

void Rva0020DXXX::rva0020D7F9()
{
	void **fin = m_vec10.m_end;
	for (void **i = m_vec10.m_begin; i != fin; ++i)
		((Rva0020DXXXElem *)*i)->rva003EDC31();
	m_38 = 0;
	m_3A = 0;
	GameLogic *g = TheGameLogic;
	if (g != 0)
		m_3C = g->m_frame;
	else
		m_3C = 0;
}

void Rva0020DXXX::rva0020D834()
{
	void **fin = m_vec10.m_end;
	for (void **i = m_vec10.m_begin; i != fin; ++i)
		((Rva0020DXXXElem *)*i)->rva003EDC16();
	m_3A = 0;
	GameLogic *g = TheGameLogic;
	if (g != 0)
		m_3C = g->m_frame;
	else
		m_3C = 0;
}

void Rva0020DXXX::rva0020D8F1(int x)
{
	if (m_38 != 0)
		return;
	if (TheGameLogic->m_frame == (unsigned int)m_3C)
		return;
	void **fin = m_vec10.m_end;
	for (void **i = m_vec10.m_begin; i != fin; ++i)
		((Rva0020DXXXElem *)*i)->rva003EDE44(x);
}

void Rva0020DXXX::rva0020D925(int x)
{
	if (m_38 != 0)
		return;
	if (TheGameLogic->m_frame == (unsigned int)m_3C)
		return;
	void **fin = m_vec10.m_end;
	for (void **i = m_vec10.m_begin; i != fin; ++i)
		((Rva0020DXXXElem *)*i)->rva003EDF69(x);
}

void Rva0020DXXX::rva0020D959(int x)
{
	if (m_38 != 0)
		return;
	if (TheGameLogic->m_frame == (unsigned int)m_3C)
		return;
	void **fin = m_vec10.m_end;
	for (void **i = m_vec10.m_begin; i != fin; ++i)
		((Rva0020DXXXElem *)*i)->rva003EDFD8(x);
}

// Anchor forces the implicit dtor out of line under its own name; the anchor
// itself is not retail code.
// ?_bfmeRva0020DXXXDtorAnchor@@YAXXZ absent-from-retail
void _bfmeRva0020DXXXDtorAnchor()
{
	static_cast<Rva0020DXXX *>(0)->Rva0020DXXX::~Rva0020DXXX();
}
