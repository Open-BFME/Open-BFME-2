// cl: /O1 /DNDEBUG /MD /EHsc
// BFME1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f:
// game/GameEngine/Source/GameLogic/Object/Object_rva001CBC20DefectionComplete.cpp.
// Target native 0x0029A12B..0x0029A205 (218 bytes, RET) and matching unnamed
// WorldBuilder 0x00CBFF50 establish the same defection-completion operation.
// The member retains its existing address-derived Object pin name: the
// original method spelling is not established by target evidence.
// Target deltas: status bit tests 62/38/70; contain +0x250, AI +0x258;
// containment virtual slot +0x10C; direct rowed restoreOriginalTeam,
// Object::setStatus(enum,bool), and canonical rowed AI operations.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0, OBJECT_STATUS_LAST = 100
};

enum NameKeyType
{
	INVALID_NAME_KEY = 0, NAME_KEY_MIN = (-2147483647 - 1), NAME_KEY_MAX = 2147483647
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
public:
	unsigned char m_pad_000[0x2c];
	unsigned char m_field2c;
};

class ContainModuleInterface
{
public:
	// Declaration-only dispatch view.  No object or vtable is emitted here;
	// Target slot 67 (+0x10C) dispatches containment release.
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
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void releaseContainment() = 0;
};

class AIUpdateInterface
{
public:
	void rva0026331C();
	void rva002633B6();
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	void restoreOriginalTeam();
	void rva00293105();
	void updateUpgradeModules();
	void rva0029A12B();

	Module *getContain() const { return (Module *)m_contain; }
	void *getAI() const { return m_ai; }

	// Rowed Object::findModule (0x0028B6D6) is a protected member, so the
	// mangled call name carries that access.
protected:
	Module *findModule(NameKeyType key) const;

	unsigned char m_pad000[0x250];
	void *m_contain;
	void *m_pad254;
	AIUpdateInterface *m_ai;
};

// ?rva0029A12B@Object@@QAEXXZ
void Object::rva0029A12B()
{
	if (!testStatus((ObjectStatusTypes)0x3e))
		return;

	Module *contain = getContain();
	setStatus((ObjectStatusTypes)0x3e, false);
	restoreOriginalTeam();

	static NameKeyType key_TemporarilyDefectUpdate =
		TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");

	Module *update = findModule(key_TemporarilyDefectUpdate);
	update->m_field2c = 1;

	if (contain != 0)
		((ContainModuleInterface *)contain)->releaseContainment();

	if (!testStatus((ObjectStatusTypes)0x26))
	{
		void *ai = getAI();
		if (ai != 0)
		{
			if (testStatus((ObjectStatusTypes)0x46))
				rva00293105();

			((AIUpdateInterface *)ai)->rva0026331C();
			((AIUpdateInterface *)ai)->rva002633B6();
		}
	}

	setStatus((ObjectStatusTypes)0x52, true);
	updateUpgradeModules();
}
