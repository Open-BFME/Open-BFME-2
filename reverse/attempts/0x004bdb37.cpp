// ?rva004BDB37@Rva004BDB37@@QAEXXZ
// partial score=0.96 date=2026-10-04
// cl: /O1
// ?rva004BDB37@Rva004BDB37@@QAEXXZ @0x004BDB37 78B evidence: vslot 41 of DetachableRiderBody plus rowed getDrawable plus pin bfmeCallFCB plus rowed Drawable-rva plus tail slot 0x28
class Drawable
{
public:
	void rva00274176(bool b);
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class BfmeSubFCB
{
public:
	void bfmeCallFCB(void *p, int i);
};

class EdiObj
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
	virtual void v21(int i);
};

class Rva004BDB37
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
	void rva004BDB37();

private:
	char m_pad00[0x1C];
	void *m_20;
	int m_24;
};

void Rva004BDB37::rva004BDB37()
{
	if (!(*(Thing **)((char *)this - 8))->getDrawable())
		return;
	EdiObj *edi = (EdiObj *)((char *)this - 0x10);
	bool f = false;
	for (int n = 3; n != 0; --n) {
		edi->v21(1);
		((BfmeSubFCB *)(*(Thing **)((char *)this - 8)))->bfmeCallFCB(m_20, m_24);
		Drawable *d = (*(Thing **)((char *)this - 8))->getDrawable();
		d->rva00274176(f);
	}
	v10();
}
