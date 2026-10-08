// cl: /O1 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// ?rva0023D3AF@Object@@QAEXPAX@Z @0x0023D3AF 184B.
// Per-frame transform snapshot. GameLogic::update calls it on every object
// whose m_188 differs from the frame it passes (0x002459E1), and
// Object::rva0029660C calls it twice after a teleport (0x00296622 and
// 0x00296631) so both snapshots hold the new position.
//
// Target evidence (game.dat): thiscall ret 4; reads the Thing transform at
// Object +0x08 (translation dwords +0x14/+0x24/+0x34, as calcNaturalRallyPoint
// reads it) and a second Matrix3D at +0x158 (translation +0x164/+0x174/+0x184);
// writes the 12-byte position at +0x18C from the saved matrix when byte +0x1A4
// is set and from the current one otherwise, then copies the transform row by
// row into +0x158 (WWMath Matrix3D::operator=), stores the argument at +0x188
// and the flags +0x1A4=1 +0x1A5=1 +0x1A6=0. The call sites pass
// TheGameLogic +0x40 (ZH's frame counter offset is structural inference).
// Kept in its own unit: compiled beside rva0029660C, cl sees that it keeps
// ECX and drops that caller's reload of this.

#include "matrix3d.h"

class Object
{
public:
	void rva0023D3AF(void *frame);

private:
	unsigned char m_pad00[0x08];
	Matrix3D m_transform; // +0x08, Thing's transform
	unsigned char m_pad38[0x158 - 0x38];
	Matrix3D m_158; // +0x158, the transform as of frame m_188
	unsigned int m_188; // +0x188
	Vector3 m_18C; // +0x18C, the position one snapshot earlier
	unsigned char m_pad198[0x1A4 - 0x198];
	bool m_1A4; // +0x1A4, m_158 holds a snapshot
	bool m_1A5; // +0x1A5
	bool m_1A6; // +0x1A6
};

void Object::rva0023D3AF(void *frame)
{
	if (m_1A4)
		m_158.Get_Translation(&m_18C);
	else
		m_transform.Get_Translation(&m_18C);
	m_1A5 = true;
	m_158 = m_transform;
	m_1A4 = true;
	m_188 = (unsigned int)frame;
	m_1A6 = false;
}
