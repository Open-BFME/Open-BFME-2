// cl: /Ob0
//
// Rva003AD160 copy ctor, retail 0x004CBF6D, 45B. Port of the Open-BFME-1
// Rva003AD160Copy donor (b1 0x003AD160) with the BFME2 member repair read
// off the three retail calls: member 1 (at +0x00) still copies through the
// donor-attested Rva0036CA00Str copy ctor (pinned at 0x000A8C7C same batch),
// but members 2 and 3 are WeaponTemplateSetHead (76B memcpy copy ctor,
// already matched at 0x00045455, no pin needed). Member 2 ends exactly where
// member 3 starts (+0x04 + 0x4C = +0x50), so no padding is needed.

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class WeaponTemplateSetHead
{
	char _m[0x4C];

public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
};

class Rva003AD160
{
	Rva0036CA00Str m_00;
	WeaponTemplateSetHead m_04;
	WeaponTemplateSetHead m_50;

public:
	Rva003AD160(const Rva003AD160 &other);
};

Rva003AD160::Rva003AD160(const Rva003AD160 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_50(other.m_50)
{
}
