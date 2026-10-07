// cl: /DNDEBUG /MD
// ?rva004BDA67@Rva004BDA67@@QAEXXZ @0x004BDA67 66B: the rubble-state reset
// that ActiveBody::setCorrectDamageState (0x004BE8BD) runs on itself. The
// damage-state calc 0x004BDA29 lives in ActiveBody.cpp, its only caller's unit:
// that caller keeps ecx across the call, which MSVC does only for a callee it
// has already compiled in the same unit.

class Rva003BD306Target
{
public:
	void rva0039B548();
};

struct Rva004BDA67M04
{
	char m_pad[0x50];
	unsigned char m_flag50;
};

struct Rva004BDA67ObjInner
{
	char m_pad[0x61C];
	int m_val61C;
};

class Object
{
public:
	void rva0028DA28();
private:
	void rva0028DAB9();
public:
	char m_pad00[4];
	void *m_obj04;
	char m_pad08[0x264 - 8];
	Rva003BD306Target *m_target264;
	friend class Rva004BDA67;
};

class Rva00298E6A
{
public:
	void rva00298E6A();
};

class Rva004BDA67
{
public:
	void rva004BDA67();
private:
	char m_pad00[4];
	void *m_04;
	Object *m_08;
};

void Rva004BDA67::rva004BDA67()
{
	Object *obj = m_08;
	Rva003BD306Target *t = obj->m_target264;
	if (t != 0)
		t->rva0039B548();
	Rva004BDA67M04 *m04 = (Rva004BDA67M04 *)m_04;
	if (m04->m_flag50 != 0)
		obj->rva0028DA28();
	Rva004BDA67ObjInner *inner = *(Rva004BDA67ObjInner **)((char *)obj + 4);
	if (inner->m_val61C > 0)
		obj->rva0028DAB9();
	((Rva00298E6A *)obj)->rva00298E6A();
}
