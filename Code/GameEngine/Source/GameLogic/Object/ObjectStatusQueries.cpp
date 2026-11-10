// cl: /DNDEBUG /MD
//
// Three Object queries just ahead of Object::rva0023D3AF (0x0023D3AF):
// - Object::isDisabled, retail 0x0023D394 (11B): Zero Hour's inline
//   "return m_disabledMask.any();", the mask at +0x1C8 (BitFlags<11>::any,
//   rowed at 0x0023C58B, whose callers all pass Object+0x1C8), tail-jumped;
// - 0x0023D39F / 0x0023D3A7 (8B each): testStatus (rowed 0x0004E536) of BFME 2
//   status bits 0x4A and 4. Which named ZH-style query each one is is not
//   established, so they keep address-derived names.

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0023D3A7 = 4,
	OBJECT_STATUS_RVA0023D39F = 0x4A
};

#include "../../../Include/Common/BitFlagsTemplate.h"

class Object
{
public:
	bool isDisabled() const;
	bool testStatus(ObjectStatusTypes bit) const;
	bool rva0023D39F() const;
	bool rva0023D3A7() const;

private:
	unsigned char m_pad000[0x1C8];
	BitFlags<11> m_disabledMask; // +0x1C8
};

// Object::isDisabled is rowed at its identical inline copy in
// ControlBarRappellerCount.cpp; retaining a strong copy here conflicts with it.

bool Object::rva0023D39F() const
{
	return testStatus(OBJECT_STATUS_RVA0023D39F);
}

bool Object::rva0023D3A7() const
{
	return testStatus(OBJECT_STATUS_RVA0023D3A7);
}
