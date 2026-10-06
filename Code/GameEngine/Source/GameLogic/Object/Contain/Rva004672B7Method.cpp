// cl: /MD
// ?rva004672B7@TransportContain@@UAEXHH@Z @0x004672B7 99B: slot 9 Contain method with early-out plus flag-gated subobject virtuals.
// Evidence: slots 9 of six Contain vtables 0x00844278 0x00845C38 0x00845EB8 0x00846D28 0x008470F8 0x008474A0, ret 8 two args, flag byte at +0x1c8 bit 0x20 via +0x08, subobject at +0x20 slots 0x80 0x8c 0xa8 0xd8 0xe0.

class Sub20_4672B7
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32(int);
	virtual void v33();
	virtual void v34();
	virtual void v35(int);
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42(int);
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual bool v54();
	virtual void v55();
	virtual int v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
};

struct Obj08_4672B7
{
	unsigned char m_pad[0x1c8];
	unsigned char m_flag;
};

class TransportContain
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void rva004672B7(int a1, int a2);
private:
	int m_04;
	Obj08_4672B7 *m_08;
	unsigned char m_pad0C[0x20 - 0x0C];
	Sub20_4672B7 m_20;
};

void TransportContain::rva004672B7(int a1, int a2)
{
	if (a1 == a2)
		return;
	if (m_08->m_flag & 0x20)
	{
		m_20.v42(0);
		return;
	}
	m_20.v32(2);
	if (m_20.v54())
	{
		if (m_20.v56() != a2)
			m_20.v35(2);
	}
}
