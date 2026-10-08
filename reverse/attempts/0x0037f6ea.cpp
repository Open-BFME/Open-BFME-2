// ?rva0037F6EA@Rva0037F51A@@QAEXHH@Z
// partial score=0.93 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD
// ?rva0037F6EA@Rva0037F51A@@QAEXHH@Z @0x0037F6EA 53B
// Leaf __thiscall updating m_1C via living-world lookup and ArmyPlacer Get.
// Evidence: callers 0x0037F9AE, callees TheLivingWorldLogic rva0020EAF6
// Rva0037F62DGet, layout m_00 m_04 as Coord3D m_10 as Coord3D m_1C bool
// from Rva0037F551.cpp, prev ArmyPlacer Get row.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};
class LivingWorldLogic
{
public:
	char m_pad[0xB0];
	Rva0020EAF6View *m_viewB0;
};
extern LivingWorldLogic *TheLivingWorldLogic;
bool __stdcall Rva0037F62DGet(int player, Coord3D *start, Coord3D *rally);
class Rva0037F51A
{
public:
	void rva0037F6EA(int a, int b);
private:
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	bool m_1c;
};
void Rva0037F51A::rva0037F6EA(int a, int b)
{
	Rva0020E89C *p = TheLivingWorldLogic->m_viewB0->rva0020EAF6(m_00);
	if (!p)
		return;
	bool ok = Rva0037F62DGet(b, (Coord3D *)&m_04, (Coord3D *)&m_10);
	m_1c = ok;
}
