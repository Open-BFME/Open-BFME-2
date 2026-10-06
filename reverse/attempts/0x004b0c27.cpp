// ?rva004B0C27@Rva004B0C27@@QAEHXZ
// partial score=0.95 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva004B0C27@Rva004B0C27@@QAEHXZ @0x004B0C27 173B.
// Latch the byte at +0x21 from the skirmish record and the cache. Then
// the actor slots 10, 6, 8, and 7 run off the parent at this-0x10.

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *key);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva004B0942
{
public:
	void *rva004B0942();
	void rva004B0AAA();
};

class Actor
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual bool s6();
	virtual bool s7();
	virtual bool s8();
	virtual void s9();
	virtual bool s10();
};

class Rva004B0C27
{
public:
	int rva004B0C27();

private:
	char m_pad[0x18];
	int m_a;
	int m_b;
	unsigned char m_flag20;
	unsigned char m_flag21;
};

int Rva004B0C27::rva004B0C27()
{
	if (m_flag21 == 0) {
		Object *obj = *(Object **)((char *)this - 8);
		Player *player = obj->getControllingPlayer();
		Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(player);
		int wide;
		if (rec != 0 && ((Rva004B0942 *)((char *)this - 0x10))->rva004B0942() != 0)
			wide = 1;
		else
			wide = 0;
		m_flag21 = (unsigned char)wide;
		if (m_flag21 == 0)
			goto fail;
	}
	if (m_flag20 == 0)
		((Rva004B0942 *)((char *)this - 0x10))->rva004B0AAA();
	Rva004B0942 *parent = (Rva004B0942 *)((char *)this - 0x10);
	Actor *actor = (Actor *)parent->rva004B0942();
	if (actor->s10()) {
		actor = (Actor *)parent->rva004B0942();
		if (actor->s6()) {
			if (m_a == 0 && m_b > 0) {
				actor = (Actor *)parent->rva004B0942();
				actor->s8();
			}
		} else if (m_a > 0) {
			actor = (Actor *)parent->rva004B0942();
			actor->s7();
		}
	}
	int result = 1;
	goto done;
fail:
	result = 0x3fffffff;
done:
	return result;
}
