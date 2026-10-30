// cl: /DNDEBUG /MD /GX
// ?SetLight@W3DAptComponentView3D@@UAEXHMMM@Z, retail 0x00740169, 58 bytes.
// Vslot 4 of W3DAptComponentView3D vtable 0x008F1600: if arg0!=0 return else call m_0C slot 6 with three floats.
// Evidence: vtable slot 4; model donor Rva00740242Dtor.cpp; callee slot 0x18; caller none.
class M0CClass
{
public:
	virtual void Delete_This() = 0;
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void Method(void *p);
};
class Rva007401F6
{
public:
	virtual ~Rva007401F6();
private:
	char m_pad04[8];
};
class RefCountClass;
class Rva0074011F
{
public:
	~Rva0074011F();
	void rva0074011F();
	RefCountClass *m_p0; // +0x00
	RefCountClass *m_p1; // +0x04
};
class W3DAptComponentView3D : public Rva007401F6
{
public:
	virtual ~W3DAptComponentView3D();
	virtual void SetLight(int a, float b, float c, float d);
private:
	RefCountClass *m_0C;
	RefCountClass *m_10;
	int m_14;
	RefCountClass *m_18;
	int m_1C;
	Rva0074011F m_20;
};
struct Float3
{
	float x;
	float y;
	float z;
};
void W3DAptComponentView3D::SetLight(int a, float b, float c, float d)
{
	if (a != 0)
		return;
	Float3 tmp;
	tmp.x = b;
	tmp.y = c;
	tmp.z = d;
	reinterpret_cast<M0CClass *>(m_0C)->Method(&tmp);
}
