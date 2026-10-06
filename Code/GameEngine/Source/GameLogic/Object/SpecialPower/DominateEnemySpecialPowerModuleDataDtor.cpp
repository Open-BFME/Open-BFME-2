// cl: /MD /GX /DNDEBUG /Oy-
// Rva0044ECCE is an address-derived base stand-in; its target class name is unproven.
//
// ??1DominateEnemySpecialPowerModuleData@@UAE@XZ, retail 0x004CCABA, 56 bytes.
// DominateEnemySpecialPower ModuleData dtor (ctor rowed at 0x004CCA24 in
// DominateEnemySpecialPowerModuleDataCtor.cpp, vtable 0x0085F6F8 with slot 0
// ??_G at 0x004CCA9E). Destroys the filter member at +0xD8 through the pinned
// 0x360D26 body, then the Rva0044ECCE base through the pinned 0x44ECCE
// body. Layout follows the ctor TU (0xC8 base plus float at +0xC8 plus ints at
// +0xCC/+0xD0 plus bool at +0xD4 plus filter at +0xD8, total 0xDC matching the
// factory news). novtable suppresses the derived vtable store retail lacks
// (Topple precedent); the base call restores the base table.

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();

private:
	unsigned char m_pad[0xC8 - 4];
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class __declspec(novtable) DominateEnemySpecialPowerModuleData : public Rva0044ECCE
{
public:
	virtual ~DominateEnemySpecialPowerModuleData();

private:
	float m_dominateRadius; // +0xC8
	int m_triggerFX; // +0xCC
	int m_dominatedFX; // +0xD0
	bool m_permanentlyConvert; // +0xD4
	unsigned char m_padD5[3];
	Rva00360D26Member m_filter; // +0xD8
};

DominateEnemySpecialPowerModuleData::~DominateEnemySpecialPowerModuleData()
{
}
