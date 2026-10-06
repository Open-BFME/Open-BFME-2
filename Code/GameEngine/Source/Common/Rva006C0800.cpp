// cl: /MD
// ?rva006C0800@Rva006C0800@@QAEXW4PointModeEnum@PointGroupClass@@@Z @ 0x006C0800 8B
// Honest address name: tail jmp loading member at +0x10 then jumping to rowed
// PointGroupClass::Set_Point_Mode. Same PointModeEnum signature forwards.
// Evidence: mov ecx [ecx+0x10] plus jmp shape, callee row in pointgr.cpp,
// callers at 0x002A7B89 and 0x002A84E6, neighbours 0x006C07D0 and 0x006C0820.
class PointGroupClass
{
public:
	enum PointModeEnum
	{
		TRIS,
		QUADS,
		SCREENSPACE
	};
	void Set_Point_Mode(PointModeEnum mode);
};
class Rva006C0800
{
public:
	void rva006C0800(PointGroupClass::PointModeEnum mode);
private:
	char m_pad[0x10];
	PointGroupClass *m_ptr;
};
void Rva006C0800::rva006C0800(PointGroupClass::PointModeEnum mode)
{
	m_ptr->Set_Point_Mode(mode);
}
