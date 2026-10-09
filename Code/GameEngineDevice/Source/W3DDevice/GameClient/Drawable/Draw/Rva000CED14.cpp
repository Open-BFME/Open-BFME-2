// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva000CED14@W3DTreeDrawModuleData@@UAE?AVAsciiString@@H@Z @0x000CED14 27B: vslot 14 of W3DTreeDrawModuleData W3DPropDrawModuleData W3DFloorDrawModuleData returns m_modelName at +08 by value via hidden plus int dummy ret 8; layout from W3DTreeDrawModuleDataCtorG7; donor ZH W3DTreeDraw.h; sibling Version getAsciiBuildLocation 27B precedent
#include "ascii_string.h"
class W3DTreeDrawModuleDataBase {
public:
	virtual ~W3DTreeDrawModuleDataBase() {}
};
class W3DTreeDrawModuleData : public W3DTreeDrawModuleDataBase {
public:
	unsigned int m_unused04;
	AsciiString m_modelName;
	virtual AsciiString rva000CED14(int dummy);
};
AsciiString W3DTreeDrawModuleData::rva000CED14(int dummy)
{
	return m_modelName;
}
