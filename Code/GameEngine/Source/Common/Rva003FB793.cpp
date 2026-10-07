// cl: /O1 /G7 /arch:SSE /MD
//
// ?rva003FB793@Rva003F936EHost@@QAEXPAUVec3@@@Z @0x003FB793 52B.
// If the +8 member is set, run its slot-20 virtual, then copy its +0x24,
// +0x34, +0x44 floats to the out vec. The slot-20 call is indirect, and the
// slot-7 call below is indirect too, so no pins are needed.
// ?rva003F936E@@YGXPAXPAM@Z @0x003F936E 63B.
// Null-checked: fill a stack Vec3 via rva003FB793, overwrite x/y from the
// float pair, forward its address to virtual slot 7. Free __stdcall (own
// this unused by retail; callers set ecx conventionally). The 12B Vec3 write
// fills the whole sub-esp reserve; the float copies land on top of it.
struct Vec3
{
	float x, y, z;
};

class Rva003FB793Inner
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
	virtual void vfunc20();
};

struct Rva003FB793Elem
{
	char m_pad00[0x24];
	float m_24;
	char m_pad28[0x0C];
	float m_34;
	char m_pad38[0x0C];
	float m_44;
};

class Rva003F936EHost
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void vfunc7(Vec3 *v);
	void rva003FB793(Vec3 *out);
private:
	char m_pad04[4];
	Rva003FB793Inner *m_p08;
};

void __stdcall rva003F936E(Rva003F936EHost *o, float *f);

// ?rva003FB793@Rva003F936EHost@@QAEXPAUVec3@@@Z present-unmatched
void Rva003F936EHost::rva003FB793(Vec3 *out)
{
	Rva003FB793Inner *p = m_p08;
	if (p == 0)
		return;
	p->vfunc20();
	Rva003FB793Elem *e = (Rva003FB793Elem *)p;
	out->x = e->m_24;
	out->y = e->m_34;
	out->z = e->m_44;
}

void __stdcall rva003F936E(Rva003F936EHost *o, float *f)
{
	if (o == 0)
		return;
	Vec3 tmp;
	o->rva003FB793(&tmp);
	tmp.x = f[0];
	tmp.y = f[1];
	o->vfunc7(&tmp);
}
