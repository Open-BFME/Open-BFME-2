// ?rva0020F34E@Rva0020F34E@@QAEXIPAVRva002E2285@@@Z
// partial score=0.85 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0020F34E@Rva0020F34E@@QAEXIPAVRva002E2285@@@Z @0x0020F34E 154B.
// Thiscall walk over the rule vector at +0x5C..+0x60: each rule that the unrowed
// predicate 0x0020F143 accepts (given the argument and a float 1.0) contributes a
// scaled copy of its six-int block at +4 through the matched copy ctor, scale
// 0x0020E27B and add-to-target 0x002E2285; the copy is destroyed with the
// virtual-dtor state. Evidence: target only; names are address-derived.
#include <vector>

class Rva0020E449
{
public:
	Rva0020E449(const Rva0020E449 &other);
	virtual ~Rva0020E449() {}
	void rva0020E27B(float s);

private:
	int m_v[6];
};

class Rva002E2285
{
public:
	void rva002E2285(int *target, const Rva0020E449 &value);
};

class Rva0020F34ERule
{
public:
	bool rva0020F143(Rva002E2285 *a, float &b);

public:
	char m_pad00[4];
	Rva0020E449 m_poly;
};

class Rva0020F34E
{
public:
	void rva0020F34E(unsigned int unused, Rva002E2285 *obj);

private:
	char m_pad00[0x5C];
	Rva0020F34ERule **m_begin;
	Rva0020F34ERule **m_end;
};

void Rva0020F34E::rva0020F34E(unsigned int unused, Rva002E2285 *obj)
{
	for (unsigned int i = 0; i < (unsigned int)(m_end - m_begin); ++i)
	{
		Rva0020F34ERule *rule = m_begin[i];
		float one = 1.0f;
		if (rule->rva0020F143(obj, one))
		{
			Rva0020E449 scaled(rule->m_poly);
			scaled.rva0020E27B(one);
			obj->rva002E2285((int *)rule, scaled);
		}
	}
}
