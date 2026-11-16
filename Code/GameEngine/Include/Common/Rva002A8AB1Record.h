// Rva002A8AB1Record: canonical declarations for the members units call through private views of it,
// and the fields rowed retail bodies read; offsets no rowed body proves stay opaque padding.
#ifndef CANONICAL_RVA002A8AB1RECORD_H
#define CANONICAL_RVA002A8AB1RECORD_H

class AsciiString;
class Object;
class TeamPrototype;
class Rva002C5FBA;

struct Rva002A8AB1Record
{
	void rva002C6A3D(Object *object);
	void rva002C6A4E(Object *obj);
	void *rva002C6ACB();
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
	void rva004EC07D(TeamPrototype *proto);
	void *rva004EC088(int kind, void *list, const void *name);
	void rva004EC30E(Object *object);

	unsigned char m_pad000[0xCC];
	unsigned int m_cc;		// +0xCC, read by AIDifficulty::allowEconomyUpgrade 0x0058AEBC
	unsigned int m_d0;		// +0xD0, read by AIDifficulty::allowEconomyUpgrade 0x0058AEBC
	unsigned char m_pad0D4[0x164 - 0xD4];
	Rva002C5FBA *m_164;		// +0x164, Team::getLocation 0x0039D7DB calls Rva002C5FBA::rva002C5FBA on it
	unsigned char m_168;	// +0x168, byte tested by rva002C6A3D and rva002C6A4E
	unsigned char m_pad169[3];
	int m_16C;				// +0x16C, dword read by AIDozerManager::buildDozer 0x00599564 and others
	float m_170;			// +0x170, fld by ArmyMemberDefinition::getInterpolatedPercentageOfArmy 0x0041F2A8
};

#endif // CANONICAL_RVA002A8AB1RECORD_H
