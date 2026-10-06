// ?getObjectExitInterface@Object@@QBEPAVExitInterface@@XZ
// partial score=0.95 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
//
// ?getObjectExitInterface@Object@@QBEPAVExitInterface@@XZ, retail 0x0028B445, 55 bytes.
// Object::getObjectExitInterface scans the BehaviorModule array at +0x244 via the +0x0C
// sub-object (slot 20 / +0x50 getUpdateExitInterface) then falls back to the contain
// module at +0x250 (slot 29 / +0x74 getContainExitInterface) with a tail-jump.
// Evidence: caller 0x0049D57F (ProductionUpdate::removeFromProductionQueue via m_object+8)
// plus 11 other callers; BFME1 donor Object.cpp:3047 same shape with +0x1F0/+0x1FC and
// slots +0x4C/+0x60; BFME2 layout +0x244/+0x250 proven by ObjectFindModule/Object_isAbleToAttack.

class ExitInterface;

class BehaviorExitInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ExitInterface *getUpdateExitInterface() = 0;
};

class BehaviorModule;

class ContainModule
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual ExitInterface *getContainExitInterface() = 0;
};

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;
	char m_pad244[0x250 - 0x244 - 4];
	ContainModule *m_contain250;

public:
	ExitInterface *getObjectExitInterface() const;
};

ExitInterface *Object::getObjectExitInterface() const
{
	ExitInterface *exitInterface = 0;
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		char *adjusted = reinterpret_cast<char *>(*m) + 0xc;
		if ((exitInterface = reinterpret_cast<BehaviorExitInterface *>(adjusted)->getUpdateExitInterface()) != 0)
			break;
	}
	if (exitInterface == 0)
	{
		ContainModule *contain = m_contain250;
		if (contain != 0)
			return contain->getContainExitInterface();
	}
	return exitInterface;
}
