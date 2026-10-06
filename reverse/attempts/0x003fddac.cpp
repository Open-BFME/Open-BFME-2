// ?rva003FDDAC@Rva003FDDAC@@QAEXXZ
// partial score=0.85 date=2026-10-06
// cl: /O1 /MD /EHsc
// ?rva003FDDAC@Rva003FDDAC@@QAEXXZ @ 0x003FDDAC 110B: guarded audio event owner submit via temp Rva002DA5D3 then tail rva005391A9. Evidence: same +0x38 null-check shape as neighbour Rva003FDD29 plus rowed 0x002DA5D3 plus TheAudio slot 0x64 plus rowed dtor 0x002D9A43 plus rowed 0x005391A9 tail.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct OpaqueRefElement4;

struct Rva002DA5D3
{
	Rva002DA5D3(const OpaqueRefElement4 &ref, int id) throw();
};

class __declspec(novtable) BfmeStringTailRecord144
{
public:
	virtual ~BfmeStringTailRecord144();
private:
	char m_pad[0x88 - 4];
};

class AudioManager
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
	virtual void v25(BfmeStringTailRecord144 *tmp);
};

extern AudioManager *TheAudio;

class Rva005391A9
{
public:
	void rva005391A9();
};

inline void *operator new(unsigned int, void *p)
{
	return p;
}

class Rva003FDDAC
{
public:
	void rva003FDDAC();
private:
	char m_pad00[0x14];
	void *m_p14;
	char m_pad18[0x38 - 0x18];
	void *m_p38;
};

void Rva003FDDAC::rva003FDDAC()
{
	if (*(int *)((char *)m_p14 + 0x10) != 0)
	{
		if (m_p38 != 0)
		{
			BfmeStringTailRecord144 tmp;
			new (&tmp) Rva002DA5D3(*(const OpaqueRefElement4 *)((const char *)m_p14 + 0x10), *(int *)((char *)m_p38 + 0x20));
			TheAudio->v25(&tmp);
		}
	}
	((Rva005391A9 *)this)->rva005391A9();
}
