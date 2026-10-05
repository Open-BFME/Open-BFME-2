// ?rva0052AF95@Rva0052AF95@@QAEXXZ
// partial score=0.93 date=2026-10-05
// cl: /O2 /EHsc /MD
// ?rva0052AF95@Rva0052AF95@@QAEXXZ, RVA 0x0052AF95 size 110.
// Chain lane: calls 0x002DA651 just landed; all callees rowed. Evidence:
// same-page neighbours VslotSmallBodiesAM / Rva0052B024Loop share /O1;
// ctor 0x002DA651 builds 0x88-byte audio prefix, TheAudio slot 0x64 consumes
// it, dtor 0x002D9A43 tears down, then rowed 0x005391A9 on same this.
struct OpaqueRefElement4
{
	void *referent;
};
struct Holder14
{
	char m_pad00[0x10];
	int m_flag10;
};
struct Holder38
{
	char m_pad00[0x18];
	int m_id;
};
struct Rva002DA651
{
	Rva002DA651(const OpaqueRefElement4 &, int);
	virtual ~Rva002DA651();
	char m_pad[0x84];
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
	virtual void audioEvent(Rva002DA651 *ev);
};
extern AudioManager *TheAudio;
class Rva005391A9
{
public:
	void rva005391A9();
};
class Rva0052AF95
{
public:
	void rva0052AF95();
private:
	char m_pad00[0x14];
	Holder14 *m_p14;
	char m_pad18[0x20];
	Holder38 *m_p38;
};
// ?rva0052AF95@Rva0052AF95@@QAEXXZ present-unmatched
void Rva0052AF95::rva0052AF95()
{
	if (m_p14->m_flag10 != 0 && m_p38 != 0)
	{
		OpaqueRefElement4 &ref = *(OpaqueRefElement4 *)((char *)m_p14 + 0x10);
		Rva002DA651 tmp(ref, m_p38->m_id);
		TheAudio->audioEvent(&tmp);
	}
	((Rva005391A9 *)this)->rva005391A9();
}
