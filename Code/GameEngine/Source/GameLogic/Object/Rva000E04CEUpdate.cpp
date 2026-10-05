// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva000E04CE@Rva000E04CE@@QAEXPAVSegmentedLineClass@@@Z RVA 0x000E04CE size 104.
// Retail updates a SegmentedLine from a Coord3D vector: if 2+ points set tile
// factor from g_00BC2918 then Set_Points then a virtual on the line then erase
// all but the last point. Evidence: calls to rowed Set_Texture_Tile_Factor
// 0x0015E3D0 and Set_Points 0x0015F100 and vector<Coord3D>::erase
// 0x00081A24 with idiv-12 size calc, virtual at +0x30, ret 4 one pointer arg.
#include <vector>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Vector3
{
public:
	float x;
	float y;
	float z;
};

class SegmentedLineClass
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12(void *p);
	void Set_Texture_Tile_Factor(float f);
	void Set_Points(unsigned int n, Vector3 *p);
};

extern float g_00BC2918;

class Rva000E04CE
{
public:
	void rva000E04CE(SegmentedLineClass *line);
private:
	int m_pad0[7];
	void *m_1c;
	char m_pad20[0x22c];
	_STL::vector<Coord3D> m_vec;
};

void Rva000E04CE::rva000E04CE(SegmentedLineClass *line)
{
	if (m_vec.size() <= 1) {
		return;
	}
	line->Set_Texture_Tile_Factor(g_00BC2918);
	line->Set_Points(m_vec.size(), (Vector3 *)&m_vec[0]);
	line->v12(m_1c);
	m_vec.erase(m_vec.begin(), m_vec.end() - 1);
}
