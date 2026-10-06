// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Chain wrappers for ?rva002D352C@Rva002D352C@@QAEXHH@Z retail 0x002D352C.
// Each is a 17B thiscall on the outer object at +0x10 delegating to the inner
// max-store with a fixed index: 0x002D381D index 0, 0x002D382E index 1,
// 0x002D383F index 2. Evidence: each does push [esp+4] mov ecx [ecx+0x10]
// push imm call 0x002D352C ret 4; callers are jmp thunks 0x003BD43C
// 0x003BD451 0x003BD466 via global 0x00DFF028. Owner unproven so honest
// outer classes per address. Flags /O1 frameless; /Oy- would add a frame.
class Rva002D352C
{
public:
	void rva002D352C(int index, int seconds);
};
class Rva002D381D
{
public:
	void rva002D381D(int seconds);
private:
	char m_pad[0x10];
	Rva002D352C *m_inner;
};
class Rva002D382E
{
public:
	void rva002D382E(int seconds);
private:
	char m_pad[0x10];
	Rva002D352C *m_inner;
};
class Rva002D383F
{
public:
	void rva002D383F(int seconds);
private:
	char m_pad[0x10];
	Rva002D352C *m_inner;
};
void Rva002D381D::rva002D381D(int seconds)
{
	m_inner->rva002D352C(0, seconds);
}
void Rva002D382E::rva002D382E(int seconds)
{
	m_inner->rva002D352C(1, seconds);
}
void Rva002D383F::rva002D383F(int seconds)
{
	m_inner->rva002D352C(2, seconds);
}
