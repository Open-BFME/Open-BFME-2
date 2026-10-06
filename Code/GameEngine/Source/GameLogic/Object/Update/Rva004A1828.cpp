// cl: /DNDEBUG /MD
// ?Rva004A1828Get@@YAHPAURva004A1828Owner@@@Z @0x004A1828 36B
// First-match scan over Owner+0x244 pointer list via virtual slot 0x68.
// Evidence: retail loop with call [eax+0x68] test/jne return else advance,
// null entry returns 0; callers 0x002789E6 0x002989E8 0x002AA661 0x0045FE6D
// with 0x0045FE4A pushing one Object star and testing result.

struct Rva004A1828Item
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
	virtual int check();
};

struct Rva004A1828Entry
{
	unsigned char m_pad[0x0C];
	Rva004A1828Item m_item; // +0x0C
};

struct Rva004A1828Owner
{
	unsigned char m_pad[0x244];
	Rva004A1828Entry **m_list; // +0x244
};

int Rva004A1828Get(struct Rva004A1828Owner *owner)
{
	Rva004A1828Entry **list = owner->m_list;
	for (;;)
	{
		Rva004A1828Entry *entry = *list;
		if (!entry)
			return 0;
		int result = entry->m_item.check();
		if (result)
			return result;
		++list;
	}
}
