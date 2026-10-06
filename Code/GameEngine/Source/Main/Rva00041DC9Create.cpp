// cl: /DNDEBUG /MD /EHsc
// ?rva00041DC9@Win32GameEngine@@UAEPAXXZ @0x00041DC9 50B
// Virtual slot 33 factory returning new Rva0004CA4C (0x3C) via new plus ctor
// 0x0004CA3A. Evidence: chain lane calls just-landed ctor; vtable 0x007C2530
// slot 33; unblocks none (leaf chain end); EH_prolog.
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva002D22CA : public GameEngineDeletingBase
{
public:
	Rva002D22CA();
	virtual ~Rva002D22CA();
private:
	void *m_tables0C[12];
};

class Rva0004CA4C : public Rva002D22CA
{
public:
	Rva0004CA4C();
	virtual ~Rva0004CA4C();
};

class Win32GameEngine
{
public:
	virtual void dummy00() = 0;
	virtual void dummy01() = 0;
	virtual void dummy02() = 0;
	virtual void dummy03() = 0;
	virtual void dummy04() = 0;
	virtual void dummy05() = 0;
	virtual void dummy06() = 0;
	virtual void dummy07() = 0;
	virtual void dummy08() = 0;
	virtual void dummy09() = 0;
	virtual void dummy10() = 0;
	virtual void dummy11() = 0;
	virtual void dummy12() = 0;
	virtual void dummy13() = 0;
	virtual void dummy14() = 0;
	virtual void dummy15() = 0;
	virtual void dummy16() = 0;
	virtual void dummy17() = 0;
	virtual void dummy18() = 0;
	virtual void dummy19() = 0;
	virtual void dummy20() = 0;
	virtual void dummy21() = 0;
	virtual void dummy22() = 0;
	virtual void dummy23() = 0;
	virtual void dummy24() = 0;
	virtual void dummy25() = 0;
	virtual void dummy26() = 0;
	virtual void dummy27() = 0;
	virtual void dummy28() = 0;
	virtual void dummy29() = 0;
	virtual void dummy30() = 0;
	virtual void dummy31() = 0;
	virtual void dummy32() = 0;
	virtual void *rva00041DC9();
};

void *Win32GameEngine::rva00041DC9()
{
	return new Rva0004CA4C();
}
