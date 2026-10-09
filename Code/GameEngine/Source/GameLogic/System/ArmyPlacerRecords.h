#ifndef ARMY_PLACER_RECORDS_H
#define ARMY_PLACER_RECORDS_H

class Rva0037F4EA
{
public:
	Rva0037F4EA *rva0037F4EA(int v);
	void rva0037F87A(void *context);
	void rva0037F6EA(void *context, int player);
private:
	friend class Rva0037F8AC;
	friend class ArmyPlacer;
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	bool m_1c;
};

// Target-only view: the initializer at 0x0037F90F reads the identifier
// from +0x12c of each input. Its original type and name are unknown.
struct Rva0037F90FInput
{
	unsigned char opaque_00[0x12c];
	int field_12c;
};

// The existing 0x0037F51A provider copies this same 0x20-byte record
// layout. Keep its existing spelling so the copy initializer binds that
// verified body; the relationship between the address-derived views is
// structural evidence, not a recovered original class name.
class Rva0037F51A
{
public:
	Rva0037F51A &rva0037F51A(const Rva0037F51A &source);
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

class Rva0037F8AC
{
public:
	void rva0037F8AC(void *context);
	Rva0037F8AC *rva0037F90F(void *context, Rva0037F90FInput *first,
		Rva0037F90FInput *second);
	Rva0037F8AC *rva0037F950(void *context, const Rva0037F51A *first,
		const Rva0037F51A *second);
private:
	friend class ArmyPlacer;
	Rva0037F4EA m_00;
	Rva0037F4EA m_20;
	float m_40;
	bool m_44;
};

#endif
