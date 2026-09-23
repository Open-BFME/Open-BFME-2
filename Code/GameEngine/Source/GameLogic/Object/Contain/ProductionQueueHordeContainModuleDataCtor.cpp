// cl: /O1 /DNDEBUG /MD
// stlport
//
// ??0ProductionQueueHordeContainModuleData@@QAE@XZ, retail 0x00481776,
// 36 bytes. ModuleData ctor over the rowed HordeGarrisonContainModuleData
// base (0x47A251, 88B): the implicit _STL::vector<int> member at +0xD4
// builds through the folded Vector_base at 0x211E58 (int spelling reuses
// the existing pin), and the compiler installs the derived vtable 0x00C490F8
// between the vector setup and call (TransitionDamageFX precedent: only
// compiler stores split setup/call; the base carries a non-dtor virtual so
// no EH prolog draws). Class size 0xE0 proven by the
// ProductionQueueHordeContain data factory (news 0xE0, sole caller at
// 0x24C1B3). Row supersedes the ctor pin.

#include <vector>

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class HordeGarrisonContainModuleData
{
public:
	HordeGarrisonContainModuleData();
	virtual void unused();
	static void buildFieldParse(MultiIniFieldParse &parse);

protected:
	// +0x00 vptr; remainder opaque to 0x58 (rowed base size).
	unsigned char m_opaque[0x54];
};

class ProductionQueueHordeContainModuleData : public HordeGarrisonContainModuleData
{
public:
	ProductionQueueHordeContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x58 pad to the vector member.
	unsigned char m_pad58[0x7C];
	// +0xD4 vector (implicit default init; ends at the rowed 0xE0 size).
	_STL::vector<int> m_vectorD4;
};

// ??0ProductionQueueHordeContainModuleData@@QAE@XZ @0x00481776
ProductionQueueHordeContainModuleData::ProductionQueueHordeContainModuleData()
	: HordeGarrisonContainModuleData()
{
}

// ?buildFieldParse@ProductionQueueHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0048175B
void ProductionQueueHordeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	HordeGarrisonContainModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C490D4), 0);
}
