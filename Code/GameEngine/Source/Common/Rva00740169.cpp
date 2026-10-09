// cl: /DNDEBUG /MD /GX
// ?rva00740169@Rva00740242@@QAEXHMMM@Z, retail 0x00740169, 58 bytes.
// Vslot 4 of Rva00740242 vtable 0x008F1600: if arg0!=0 return else call m_0C slot 6 with three floats.
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
class Rva0074011F
{
public:
	void rva0074011F();
	void *m_p0;
	void *m_p1;
};
class Rva00740242 : public Rva007401F6
{
public:
	virtual ~Rva00740242();
	virtual void rva00740169(int a, float b, float c, float d);
private:
	M0CClass *m_0C;
	void *m_10;
	int m_14;
	void *m_18;
	int m_1C;
	Rva0074011F m_20;
};
struct Float3
{
	float x;
	float y;
	float z;
};
void Rva00740242::rva00740169(int a, float b, float c, float d)
{
	if (a != 0)
		return;
	Float3 tmp;
	tmp.x = b;
	tmp.y = c;
	tmp.z = d;
	m_0C->Method(&tmp);
}
