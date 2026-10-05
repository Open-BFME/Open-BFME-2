// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva004BDA29@Rva004BDA29@@QBEHXZ @0x004BDA29 62B. Damage-state calc from
// health ratio without division: returns 3 when health == 0.0f (RUBBLE),
// 2 when health <= reallyThresh*maxHealth, 1 when health <= damagedThresh*
// maxHealth, else 0 (PRISTINE). Evidence: caller 0x004BE8BD/1189B (vtable
// slot 21 of Highlander/Immortal/Structure/Respawn/DelayedDeath/Oathbreaker
// bodies) calls this address with same this then compares result to
// [ebx+0x30] (m_curDamageState) and stores it; reads are [ecx+0x18] health,
// [ecx+0x20] maxHealth, [ecx+0x24] damagedThresh, [ecx+0x28] reallyThresh
// plus global 0.0f at 0x007BAEAC; ZH ActiveBody.cpp calcDamageState donor
// uses same 0/1/2/3 BodyDamageType order with division.
class Rva004BDA29 {
    virtual void vtableSlot0();
    char m_pad04[0x14];
    float m_health;
    char m_pad1C[4];
    float m_maxHealth;
    float m_damagedThresh;
    float m_reallyDamagedThresh;
public:
    int rva004BDA29() const;
};
int Rva004BDA29::rva004BDA29() const
{
    if (m_health == 0.0f)
        return 3;
    else if (m_reallyDamagedThresh * m_maxHealth >= m_health)
        return 2;
    else if (m_damagedThresh * m_maxHealth >= m_health)
        return 1;
    else
        return 0;
}

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
