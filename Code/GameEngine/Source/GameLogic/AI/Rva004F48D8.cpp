// cl: /O1 /G7 /MD
// ?rva004F48D8@Rva004F07E6@@QAEXXZ at 0x004F48D8 (79B).
// Vtable slot 18 of 0x00862DC8 (class Rva004F07E6 dtor 0x004F07E6).
// Evidence: calls pin bfmeTailDTK 0x004F46A9 and vslot 0x68; global g_Va00DBA4E4; imul by 5 precedent AIRoamingDefenseTactic.

extern int g_Va00DBA4E4;

class BfmeThingDTK
{
public:
	void bfmeTailDTK();
};

struct Rva004F48D8Sub
{
	char m_pad[0x338];
	unsigned char m_338;
};

class Rva004F07E6
{
public:
	void rva004F48D8();
private:
	char m_pad0[4];
	char m_pad4[8];
	Rva004F48D8Sub *m_sub;
	unsigned char m_10;
	char m_pad11[3];
	int m_14;
	char m_pad18[12];
	int m_24;
};

class VCall26
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
};

void Rva004F07E6::rva004F48D8()
{
	if (m_sub->m_338 == 0)
		return;
	if (m_10 == 0)
	{
		--m_14;
		if (m_14 <= 0)
		{
			m_10 = 1;
			m_24 = 0;
		}
	}
	--m_24;
	if (m_24 >= 1)
		return;
	((BfmeThingDTK *)this)->bfmeTailDTK();
	if (m_10 != 0)
		((VCall26 *)this)->v26();
	m_24 = g_Va00DBA4E4 * 5;
}
