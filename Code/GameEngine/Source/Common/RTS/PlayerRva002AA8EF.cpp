// cl: /DNDEBUG /MD /EHsc
// ?rva002AA8EF@Player@@QBE_NPBVUpgradeTemplate@@@Z @0x002AA8EF (48B):
// null-guarded UpgradeTemplate bit test over the Player bit words at +0xBC,
// the in-production twin of rowed rva002AB87D (+0x13C, out-of-line testBit).
// Evidence: the caller 0x0049D9A2 takes the player from
// Object::getControllingPlayer, calls this only for an upgrade whose type
// (+4) is 0, returns when it answers false, then scans the production queue
// for a type-2 entry holding that upgrade -- Zero Hour's
// ProductionUpdate::cancelUpgrade guard around Player::hasUpgradeInProduction
// (donor shape; Player.cpp still carries that ZH body present-unmatched, so
// this keeps the address name). Bit index is UpgradeTemplate +0x38 as in
// rva002AB87D.
class UpgradeTemplate
{
public:
	char m_pad[0x38];
	int m_bitIndex;
};

class Player
{
public:
	bool rva002AA8EF(const UpgradeTemplate *tmpl) const;

private:
	char m_pad[0xBC];
	unsigned int m_inProgressBits[1];
};

bool Player::rva002AA8EF(const UpgradeTemplate *tmpl) const
{
	if (!tmpl)
		return false;
	int bit = tmpl->m_bitIndex;
	return (m_inProgressBits[(unsigned int)bit >> 5] & (1 << (bit & 31))) != 0;
}
