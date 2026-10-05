// ?rva00346925@Rva00346925@@QAEXPAVObject@@0PAVAIUpdateInterface@@@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /arch:SSE
// ?rva00346925@Rva00346925@@QAEXPAVObject@@0PAVAIUpdateInterface@@@Z, RVA 0x00346925, 208 bytes.
// Evidence: unlock lane caller 0x0034FE6E shares +0x18/+0x20 layout with prev Rva003468F5; rowed Normalize 0x00005A70 + Object rva0028AD32 0x0028AD32 + pin requestPath 0x0026893F; virtual slot 0x38 with push 0; float 50.0f for MAX_LINE_TILING_FACTOR 0x007D5E50; +0x38 pos and +0x18/+0x20/+0x48 from retail.
struct Coord3D
{
	float x;
	float y;
	float z;
	float Normalize();
};

class Object
{
public:
	char m_pad0[0x38];
	float m_x38;
	float m_y3c;
	float m_z40;
	void rva0028AD32();
};

class AIUpdateInterface
{
public:
	void requestPath(Coord3D *p, bool b);
};

class Machine18
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
	virtual void v14(int v);
};

class Rva00346925
{
public:
	void rva00346925(Object *a, Object *b, AIUpdateInterface *c);
private:
	char m_pad0[0x18];
	Machine18 *m_p18;
	char m_pad1c[0x20 - 0x1c];
	Coord3D m_point20;
	char m_pad2c[0x48 - 0x2c];
	bool m_b48;
};

// ?rva00346925@Rva00346925@@QAEXPAVObject@@0PAVAIUpdateInterface@@@Z present-unmatched
void Rva00346925::rva00346925(Object *a, Object *b, AIUpdateInterface *c)
{
	if (b == 0)
		return;
	Coord3D tmp = {b->m_x38 - a->m_x38, b->m_y3c - a->m_y3c, b->m_z40 - a->m_z40};
	tmp.Normalize();
	float k = 50.0f;
	tmp.x = tmp.x * k + b->m_x38;
	tmp.y = tmp.y * k + b->m_y3c;
	tmp.z = tmp.z * k + b->m_z40;
	m_p18->v14(0);
	a->rva0028AD32();
	m_point20 = tmp;
	m_b48 = false;
	c->requestPath(&tmp, true);
}
