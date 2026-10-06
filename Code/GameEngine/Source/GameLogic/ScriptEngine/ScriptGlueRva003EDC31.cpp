// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva003EDC31@Rva0020DXXXElem@@QAEXXZ @0x003EDC31 101B: refresh cached rect from TerrainLogic slot 0x30 then walk pointer array with pinned 0x569AA8.
// Evidence: caller Rva0020D7F9Family.cpp; TheTerrainLogic rowed; pinned rva00569AA8; sibling ScriptGlueRva003EDC16 walk; movss needs arch SSE.
class Rva00569AA8
{
public:
	void rva00569AA8();
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct TwoCoord
{
	Coord3D a;
	Coord3D b;
};

class TerrainLogic
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
	virtual void slot12(void *out);
};

extern TerrainLogic *TheTerrainLogic;

class Rva0020DXXXElem
{
public:
	void rva003EDC31();
private:
	char m_pad00[0x1C];
	void **m_begin;
	void **m_end;
	char m_pad24[0xC4];
	float m_E8;
	float m_EC;
	float m_F0;
	float m_F4;
};

void Rva0020DXXXElem::rva003EDC31()
{
	TwoCoord buf;
	TheTerrainLogic->slot12(&buf);
	m_F0 = buf.b.x;
	m_F4 = buf.b.y;
	m_E8 = buf.a.x;
	m_EC = buf.a.y;
	for (void **it = m_begin; it != m_end; ++it)
		((Rva00569AA8 *)*it)->rva00569AA8();
}
