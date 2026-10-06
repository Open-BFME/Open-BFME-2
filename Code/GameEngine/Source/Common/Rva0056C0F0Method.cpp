// cl: /Oy- /MD
// ?rva0056C0F0@Rva0056C0F0@@QAEXIPAUVec3@@@Z @0x0056C0F0 125B. Div-mod cell index to world x/y via scale plus TerrainLogic slot 0x18 height for z. Evidence: caller 0x004052DA passes index plus 12B out; two div dword ptr [ecx] plus unsigned fild correction; TheTerrainLogic plus g_Va007C26F0.
class TerrainLogic
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual float getHeight(float x, float y, int z);
};
extern TerrainLogic *TheTerrainLogic;
struct Vec3 { float x; float y; float z; };
class Rva0056C0F0
{
public:
	void rva0056C0F0(unsigned int idx, Vec3 *out);
	unsigned int m_width;
	char m_pad[8];
	float m_scale;
};
void Rva0056C0F0::rva0056C0F0(unsigned int idx, Vec3 *out)
{
	unsigned int col = idx % m_width;
	out->x = ((float)col * m_scale) + (m_scale * 0.5f);
	idx /= m_width;
	out->y = ((float)idx * m_scale) + (m_scale * 0.5f);
	out->z = TheTerrainLogic->getHeight(out->x, out->y, 0) + 0.5f;
}
