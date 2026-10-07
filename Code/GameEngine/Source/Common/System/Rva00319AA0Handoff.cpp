// cl: /O1 /DNDEBUG /MD /arch:SSE
// Reconstruction of the 106B float handoff at 0x00319AA0: mirror the
// arg pair into +0x44/+0x48, run the banked 0x3197B7 gate, and when
// +0x88 is present build a 3-float record (the pair reinterpreted plus
// zero) for the pinned maker plus a slot-5 virtual on the helper. All
// names but rowed/banked callees are address-derived.
class Rva003195C9Owner;

class Rva003195C9Owner
{
public:
	void rva00319AA0(const int *arg);
	void rva003197B7();
private:
	unsigned char m_pad[0x44];
	int m_44;
	int m_48;
	unsigned char m_pad4c[0x88 - 0x4c];
	void *m_88;
};

struct Rva00319AA0Float3
{
	float m_00;
	float m_04;
	float m_08;
};

class Rva002BF5B0Maker
{
public:
	void rva002BF5B0(void *pair, void *rec);
};

extern Rva002BF5B0Maker *TheRva00319AA0Maker;

class Rva00319AA0Helper
{
public:
	virtual void h00() = 0; virtual void h01() = 0;
	virtual void h02() = 0; virtual void h03() = 0;
	virtual void h04() = 0;
	virtual void slot05(void *rec) = 0;
};

void Rva003195C9Owner::rva00319AA0(const int *arg)
{
	int *pm = &m_44;
	*pm = arg[0];
	pm[1] = arg[1];
	rva003197B7();
	if (m_88 != 0)
	{
		Rva00319AA0Float3 rec;
		rec.m_00 = *(float *)&m_44;
		rec.m_04 = *(float *)&m_48;
		rec.m_08 = 0.0f;
		((Rva002BF5B0Maker *)TheRva00319AA0Maker)->rva002BF5B0(pm, &rec);
		((Rva00319AA0Helper *)m_88)->slot05(&rec);
	}
}
