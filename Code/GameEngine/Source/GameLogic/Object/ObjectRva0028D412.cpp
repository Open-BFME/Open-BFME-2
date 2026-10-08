// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0028D412@Object@@QAEXPBVMatrix3D@@@Z, retail 0x0028D412..0x0028D481
// (111 bytes, RET 4). An Object transform setter: the rowed
// Thing::setTransformMatrix 0x0030A2B7 is applied, both per-frame snapshots
// are refreshed for the current frame (rowed 0x0023D3AF twice, with
// TheGameLogic's +0x40 frame, as Object::rva0029660C does after a teleport),
// the partition data at +0x84 is dirtied (0x002747F9, pinned), the transform
// applied again, the shroud refreshed (rowed updateShroudNow 0x0028C11A), and
// the +0x250 module's slot-31 object, if any, gets the matrix through its
// slot 109. Zero Hour has no Object-level setter of this shape and
// WorldBuilder's twin (0x00CCBE90) is unnamed, so the name stays
// address-derived.

#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class Matrix3D;

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *mtx);
};

class Rva002747F9
{
public:
	void rva002747F9(int dirty);
};

#define VSLOTS10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class Rva0028D412Target
{
public:
	VSLOTS10(s0) VSLOTS10(s1) VSLOTS10(s2) VSLOTS10(s3) VSLOTS10(s4)
	VSLOTS10(s5) VSLOTS10(s6) VSLOTS10(s7) VSLOTS10(s8) VSLOTS10(s9)
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103(); virtual void s104();
	virtual void s105(); virtual void s106(); virtual void s107(); virtual void s108();
	virtual void setTransform(const Matrix3D *mtx);		// slot 109
};

class Rva0028D412Module
{
public:
	VSLOTS10(s0) VSLOTS10(s1) VSLOTS10(s2)
	virtual void s30();
	virtual Rva0028D412Target *slot31();
};

#undef VSLOTS10

class Object : public Thing
{
public:
	void rva0023D3AF(void *frame);
	void updateShroudNow();
	void rva0028D412(const Matrix3D *mtx);

private:
	unsigned char m_pad00[0x84];
	Rva002747F9 *m_partitionData84;			// +0x84
	unsigned char m_pad88[0x250 - 0x88];
	Rva0028D412Module *m_module250;			// +0x250
};

void Object::rva0028D412(const Matrix3D *mtx)
{
	Thing::setTransformMatrix(mtx);
	rva0023D3AF((void *)TheGameLogic->getFrame());
	rva0023D3AF((void *)TheGameLogic->getFrame());
	if (m_partitionData84)
		m_partitionData84->rva002747F9(1);
	Thing::setTransformMatrix(mtx);
	updateShroudNow();
	Rva0028D412Module *module = m_module250;
	if (module)
	{
		Rva0028D412Target *target = module->slot31();
		if (target)
			target->setTransform(mtx);
	}
}
