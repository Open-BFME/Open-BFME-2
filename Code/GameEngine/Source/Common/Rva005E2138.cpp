// cl: /MD
//
// ?rva005E2138@Rva005E2138@@QAEPAXXZ retail 0x005E2138 12B
// Evidence: unlock lane; callee rva005F05E6 0x005F05E6; unblocks 0x005E2144 0x005E22A0 0x005E278E 0x005E270E 0x005E28FE; prev Disp0DwordImmSetters next Rva00513E03Length.
class Rva005F05E6
{
public:
	void *rva005F05E6(int i);
};
class Rva005E2138
{
public:
	void *rva005E2138();
	void rva005E2144(bool flag);
private:
	char m_pad00[0x10];
	Rva005F05E6 *m_ptr10;
	int m_int14;
};
class Rva005E2144Mgr
{
public:
	virtual void p0();
	virtual void p1();
	virtual void vslot2(int mode);
};
void *Rva005E2138::rva005E2138()
{
	return m_ptr10->rva005F05E6(m_int14);
}
void Rva005E2138::rva005E2144(bool flag)
{
	Rva005E2144Mgr *obj = (Rva005E2144Mgr *)rva005E2138();
	obj->vslot2(flag ? 2 : 1);
}
