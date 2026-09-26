// cl: /O1 /DNDEBUG /MD
//
// ??0Rva002AA14DBonuses@@QAE@XZ, retail 0x002AA14D, 23 bytes. Builds the two
// 0x1C kind-of masks at +0x14/+0x30 through the rowed Rva0024C7B3Member ctor
// (0x24C7B3). The layout is the BattlePlan bonuses record: armor scalar,
// three plan counters, sight scalar, then valid/invalid masks (0x4C total,
// matching the 0x4C operator-new at the BattlePlanUpdate ctor 0x497ED0,
// which fills every other field itself). The address-derived name is honest:
// the bonuses identity is strong inference (donor BattlePlanUpdate.cpp plus
// the sibling PlayerBattlePlanBonuses record), not a recovered type name.

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

class Rva002AA14DBonuses
{
public:
	Rva002AA14DBonuses();

	float m_armorScalar; // +0
	int m_bombardment; // +4
	int m_searchAndDestroy; // +8
	int m_holdTheLine; // +0xC
	float m_sightRangeScalar; // +0x10
	Rva0024C7B3Member m_validKindOf; // +0x14
	Rva0024C7B3Member m_invalidKindOf; // +0x30
};

// ??0Rva002AA14DBonuses@@QAE@XZ @0x2AA14D
Rva002AA14DBonuses::Rva002AA14DBonuses()
{
}
