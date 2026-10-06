// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0039D533@Rva0039D533@@QAEXPAURva0039D533Src@@@Z 0x0039D533 102 virtual copy via slots 0x7c 0x6c 0x04
// 102B __thiscall taking source with virtuals at +0x7c +0x6c filling dest ints at +0x00 +0x04 +0x08 +0x0c +0x10 +0x14 last conditional on slot +0x04.
// Caller 0x0039D6AC; prev/next are byte getters and Rva0039D5A9Sum.
struct Rva0039D533Src
{
	virtual void v00();
	virtual bool v01();
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
	virtual void v27(int *out);
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31(int *out);
};

struct Rva0039D533
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	void rva0039D533(Rva0039D533Src *src);
};

void Rva0039D533::rva0039D533(Rva0039D533Src *src)
{
	src->v31(&m_00);
	src->v31(&m_04);
	src->v31(&m_08);
	src->v27(&m_0c);
	src->v27(&m_10);
	int tmp = m_14;
	src->v31(&tmp);
	if (src->v01())
		m_14 = tmp;
}
