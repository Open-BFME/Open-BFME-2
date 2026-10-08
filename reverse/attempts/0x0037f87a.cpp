// ?rva0037F87A@Rva0037F4EA@@QAEXPAX@Z
// partial score=0.92 date=2026-10-08
// cl: /O1 /MD /arch:SSE
// ?rva0037F4EA@Rva0037F4EA@@QAEPAV1@H@Z retail 0x0037F4EA 48B
// Evidence: callers 0x0037F90F 0x0037F985 pass dword from +0x12c; zeroes six floats plus bool; second instance at +0x20
class Rva0037F4EA
{
public:
	Rva0037F4EA *rva0037F4EA(int v);
	void rva0037F87A(void *context);
private:
	friend class Rva0037F8AC;
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
	Rva0037F4EA m_00;
	Rva0037F4EA m_20;
	float m_40;
	bool m_44;
};

Rva0037F4EA *Rva0037F4EA::rva0037F4EA(int v)
{
	m_00 = v;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	m_1c = false;
	return this;
}

// ?rva0037F8AC@Rva0037F8AC@@QAEXPAX@Z
// Native Ghidra extent 0x0037F8AC..0x0037F90F; RET 4. Each record's
// validity byte guards its update. Valid records supply the two planar
// coordinates at +0x10/+0x14 for the cached squared distance.
void Rva0037F8AC::rva0037F8AC(void *context)
{
	if (!m_00.m_1c)
		m_00.rva0037F87A(context);
	if (!m_20.m_1c)
		m_20.rva0037F87A(context);
	if (m_00.m_1c && m_20.m_1c)
	{
		float dx = m_00.m_10 - m_20.m_10;
		float dy = m_00.m_14 - m_20.m_14;
		m_40 = dx * dx + dy * dy;
		m_44 = true;
	}
}

// ?rva0037F90F@Rva0037F8AC@@QAEPAV1@PAXPAURva0037F90FInput@@1@Z
// Native Ghidra extent 0x0037F90F..0x0037F950; RET 12. Two rowed
// initializers use +0x12c, followed by a same-receiver call to 0x0037F8AC.
Rva0037F8AC *Rva0037F8AC::rva0037F90F(void *context,
	Rva0037F90FInput *first, Rva0037F90FInput *second)
{
	m_00.rva0037F4EA(first->field_12c);
	m_20.rva0037F4EA(second->field_12c);
	m_40 = 0.0f;
	m_44 = false;
	rva0037F8AC(context);
	return this;
}

// ?rva0037F950@Rva0037F8AC@@QAEPAV1@PAXPBVRva0037F51A@@1@Z
// Native Ghidra extent 0x0037F950..0x0037F985; RET 12. Copies the two
// records through the verified provider, then clears and refreshes the
// cached distance exactly as the adjacent identifier initializer does.
Rva0037F8AC *Rva0037F8AC::rva0037F950(void *context,
	const Rva0037F51A *first, const Rva0037F51A *second)
{
	reinterpret_cast<Rva0037F51A *>(&m_00)->rva0037F51A(*first);
	reinterpret_cast<Rva0037F51A *>(&m_20)->rva0037F51A(*second);
	m_40 = 0.0f;
	m_44 = false;
	rva0037F8AC(context);
	return this;
}

struct Rva0037F7B6Coord { float x,y,z; };
class Rva0037F7B6Record;
class Rva0020E89C;
class Rva0020EAF6View { public: Rva0020E89C *rva0020EAF6(int); };
struct Rva0059E647World { char opaque[0xb0]; Rva0020EAF6View *lookup; };
extern Rva0059E647World *g_rva0059E647World;
bool __stdcall Rva0037F7B6Get(Rva0037F7B6Record*, Rva0037F7B6Coord*, Rva0037F7B6Coord*);
// Native 50B RET4, same existing record-owner pin and data prefix.
void Rva0037F4EA::rva0037F87A(void *context) {
    Rva0020E89C *record=g_rva0059E647World->lookup->rva0020EAF6(m_00);
    if(record) m_1c=Rva0037F7B6Get(reinterpret_cast<Rva0037F7B6Record*>(record),
        reinterpret_cast<Rva0037F7B6Coord*>(&m_04),reinterpret_cast<Rva0037F7B6Coord*>(&m_10));
}
