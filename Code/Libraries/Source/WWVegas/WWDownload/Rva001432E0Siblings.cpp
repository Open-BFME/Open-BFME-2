// cl: /DNDEBUG /MD
// Sibling of rowed ??0Cftp@@QAE@XZ at 0x006CA5E0 (18B), matched on mnemonic
// shape only -- the identity differs. Retail 0x001432E0 (13B) calls virtual
// slot 0x50 on this and then returns the byte flag at +0x74.
class Rva001432E0Base
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
};

class Rva001432E0 : public Rva001432E0Base
{
public:
	virtual void slot50();
	bool rva001432E0();

private:
	char m_pad[0x70];
	bool m_flag;
};

bool Rva001432E0::rva001432E0()
{
	slot50();
	return m_flag;
}
