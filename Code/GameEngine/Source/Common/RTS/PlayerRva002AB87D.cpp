// cl: /DNDEBUG /MD /EHsc
// ?rva002AB87D@Player@@QBE_NPBVUpgradeTemplate@@@Z @0x002AB87D (23B): Player::rva002AB87D null-guarded UpgradeTemplate bit test.
// Evidence: this is Player* from Object::getControllingPlayer at 0x00335656 in FUN_007355B2 with arg UpgradeTemplate* from UpgradeCenter::findUpgrade; reads int at +0x38 as bit index for rowed ?testBit@Rva002AA8BF@@QBE_NH@Z @0x002AA8BF over flags at +0x13C; Player passes through as Rva base at offset 0; 23 callers including 0x0033565D and 0x0040652A.
class UpgradeTemplate
{
public:
	char m_pad[0x38];
	int m_bitIndex;
};

class Rva002AA8BF
{
public:
	bool testBit(int bit) const;
};

class Player : public Rva002AA8BF
{
public:
	bool rva002AB87D(const UpgradeTemplate *tmpl) const;
};

// ?rva002AB87D@Player@@QBE_NPBVUpgradeTemplate@@@Z
bool Player::rva002AB87D(const UpgradeTemplate *tmpl) const
{
	if (!tmpl)
		return false;
	return testBit(tmpl->m_bitIndex);
}
