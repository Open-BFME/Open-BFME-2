// cl: /DNDEBUG /MD /EHsc
// ?rva00573A00@Rva00573A00@@QAEXPBUCoord3D@@@Z @0x00573A00 53B
// Method: copies 12B Coord3D arg to +0x30, then z = TerrainLogic height(x y 0).
// Global 0x00DFEC50 is TheTerrainLogic; virtual slot +0x18 returns float.
// Evidence: lea eax [ebx+30] mov edi eax 3x movsd, fld [ebx+34], mov ecx
// [0xdfec50] mov edx [ecx] push 0 push ecx push ecx fstp [esp+4] fld [eax]
// fstp [esp] call [edx+18] fstp [ebx+38] ret 4. Callers at 0x0041EE7C etc.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class TerrainLogic
{
	public:
	virtual void _0();
	virtual void _1();
	virtual void _2();
	virtual void _3();
	virtual void _4();
	virtual void _5();
	virtual float getHeight(float x, float y, int z);
};
extern class TerrainLogic *TheTerrainLogic;
struct Rva00573A00
{
	void rva00573A00(const Coord3D *p);
	char m_pad00[0x30];
	Coord3D m_pos;
};
void Rva00573A00::rva00573A00(const Coord3D *p)
{
	m_pos = *p;
	m_pos.z = TheTerrainLogic->getHeight(m_pos.x, m_pos.y, 0);
}
