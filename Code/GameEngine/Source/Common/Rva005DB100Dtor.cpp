// cl: /DNDEBUG /MD /EHsc
// ??1Rva005DB100@@UAE@XZ @0x005DB100 69B
// retail 0x005DB100 69 bytes unlock dtor vtable 0x008766A4 plus ReleaseTreeHintRef at +0x38+0xAC
// via rowed Release 0x0007DEEF and rowed base dtor 0x0039AD56 caller deleting dtor 0x005DB1EB
// neighbours prev 0x005DB023 Chain and next 0x005DB82B Disp0 setters

struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva005DB100Mid { char m_pad[172]; TargetRef00217D4C m_hint; };

class Rva0039AD56
{
public:
	virtual ~Rva0039AD56();
};

class Rva005DB100 : public Rva0039AD56
{
public:
	virtual ~Rva005DB100();
private:
	char m_pad04[52];
	Rva005DB100Mid *m_38;
};

Rva005DB100::~Rva005DB100()
{
	if (m_38)
		ReleaseTreeHintRef00217D4C(&m_38->m_hint);
}
