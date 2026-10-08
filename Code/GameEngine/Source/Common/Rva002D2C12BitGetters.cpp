// cl: /MD
class Rva005248D0
{
public:
	unsigned char rva002D2C12() const;
	unsigned char rva002D2C18() const;
private:
	char m_pad[0x24];
	union {
		unsigned char m_flags;
		struct {
			unsigned char m_b0 : 1;
			unsigned char m_b1 : 1;
			unsigned char m_b2 : 1;
			unsigned char m_rest : 5;
		};
	};
};

unsigned char Rva005248D0::rva002D2C12() const
{
	return m_b0;
}

unsigned char Rva005248D0::rva002D2C18() const
{
	return m_b2;
}

// Lead: current BFME1 9cbfb551 WeaponSetGetAbleToAttackSpecificObject.cpp
// isForcedAttack predicate. Native 2C71E1..2C71E9 is a complete caller-clean
// leaf after RET at 2C71DE and returns full EAX argument&1. Preserve a neutral
// raw-word interface because the original enum/predicate identity is unknown.
unsigned int Rva002C71E1LowBit(unsigned int flags)
{
    return flags & 1U;
}
