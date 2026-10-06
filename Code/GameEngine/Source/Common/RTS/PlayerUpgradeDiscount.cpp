// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs-c-
// Player::getProductionCostChangeBasedOnUpgradeDiscount, retail 0x002ADC82
// (69 bytes):
// ?getProductionCostChangeBasedOnUpgradeDiscount@Player@@QBEMVAsciiString@@@Z
// Identity (target): WorldBuilder's debug Player.cpp body of this name
// walks the same 0x24-byte record range and calls 0x002ACF02 on each with
// the upgrade name, then releases the by-value name, as retail does.
// Body (target): the sum over the Player +0x3B0/+0x3B4 record range of
// each record's discount for the named upgrade. The record type and the
// method's constness are not established.
#include "ascii_string.h"

class Rva002ACF02Record
{
public:
	float rva002ACF02(const AsciiString &upgradeName) const;

private:
	unsigned char m_bytes[0x24];
};

class Player
{
public:
	float getProductionCostChangeBasedOnUpgradeDiscount(AsciiString upgradeName) const;

private:
	unsigned char m_pad000[0x3B0];
	Rva002ACF02Record *m_discountsBegin; // +0x3B0
	Rva002ACF02Record *m_discountsEnd; // +0x3B4
};

float Player::getProductionCostChangeBasedOnUpgradeDiscount(AsciiString upgradeName) const
{
	float total = 0.0f;
	for (const Rva002ACF02Record *it = m_discountsBegin; it != m_discountsEnd; ++it)
		total += it->rva002ACF02(upgradeName);
	return total;
}
