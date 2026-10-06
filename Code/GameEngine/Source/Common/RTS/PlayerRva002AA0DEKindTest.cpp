// cl: /O1 /DNDEBUG /MD
//
// ?rva002AA0DE@Player@@QAE_NPBVThing@@@Z @0x002AA0DE 69B: Player member that
// answers whether a thing matches the kind-of filter held by the object at
// +0xB8: true when the filter and the thing exist, the thing is any of the
// filter's required kinds (+0x14) and none of its forbidden kinds (+0x30),
// both through the rowed Thing::isAnyKindOf 0x0030ADC7. Identity is
// address-derived.

template <int NUMBITS>
class BitFlags
{
private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
};

struct Rva002AA0DEKindFilter
{
	char m_pad00[0x14];
	BitFlags<69> m_mustBe;
	char m_pad20[0x30 - 0x20];
	BitFlags<69> m_mustNotBe;
};

class Player
{
public:
	bool rva002AA0DE(const Thing *thing);
private:
	char m_pad00[0xB8];
	Rva002AA0DEKindFilter *m_B8;
};

bool Player::rva002AA0DE(const Thing *thing)
{
	if (m_B8 && thing && thing->isAnyKindOf(m_B8->m_mustBe) && !thing->isAnyKindOf(m_B8->m_mustNotBe))
		return true;
	return false;
}
