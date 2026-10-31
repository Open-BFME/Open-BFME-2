// cl: /O1 /DNDEBUG /MD /arch:SSE
// Reconstruction of the 106B float handoff at 0x00319AA0: mirror the
// arg pair into +0x44/+0x48, run the banked 0x3197B7 gate, and when
// +0x88 is present build a 3-float record (the pair reinterpreted plus
// zero) for the rowed maker plus a slot-5 virtual on the helper. All
// names but rowed/banked callees are address-derived.
class Rva003195C9Owner;

class Rva003195C9Owner
{
public:
	void rva00319AA0(const int *pair);
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

// The maker 0x002BF5B0, rowed as Rva002BF4F3::rva002BF5B0 (its bool
// result is unused here).
class Vector3;
class Rva002BF4F3
{
public:
	bool rva002BF5B0(const Vector3 *pair, Vector3 *rec);
};

// The gate 0x003197B7, rowed as Rva00319AA0::rva003197B7.
class Rva00319AA0
{
public:
	void rva003197B7();
};

// Bind to the existing data-ledger owner; keep the retail access view local.
class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;

class Rva00319AA0Helper
{
public:
	virtual void h00() = 0; virtual void h01() = 0;
	virtual void h02() = 0; virtual void h03() = 0;
	virtual void h04() = 0;
	virtual void slot05(void *rec) = 0;
};

void Rva003195C9Owner::rva00319AA0(const int *pair)
{
	int *pm = &m_44;
	*pm = pair[0];
	pm[1] = pair[1];
	((Rva00319AA0 *)this)->rva003197B7();
	if (m_88 != 0)
	{
		Rva00319AA0Float3 rec;
		rec.m_00 = *(float *)&m_44;
		rec.m_04 = *(float *)&m_48;
		rec.m_08 = 0.0f;
		((Rva002BF4F3 *)((Rva002D3627Host *)TheLivingWorld))->rva002BF5B0((const Vector3 *)pm, (Vector3 *)&rec);
		((Rva00319AA0Helper *)m_88)->slot05(&rec);
	}
}
