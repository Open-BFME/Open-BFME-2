// cl: /DNDEBUG /MD
//
// ?onExit@SpecialDisguiseUpdate@@MAEX_N0@Z, retail 0x004B0414, 56 bytes.
// Slot 13 of the vftable 0x00C56398 whose slot-2 name getter returns
// "SpecialDisguiseUpdate" (rowed pool key 0x004B018E), where the
// SpecialAbilityUpdate vftable holds the rowed onExit 0x004502CE: runs it,
// then sets the float at Drawable+0xB0 of the owner's drawable (rowed
// Thing::getDrawable) back to 1.0f. Member name not recovered.

class Drawable
{
public:
	unsigned char m_pad00[0xB0];
	float m_B0;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

class ModuleData;
class SpecialDisguiseUpdate;

class SpecialAbilityUpdate
{
	friend class SpecialDisguiseUpdate;
public:
	virtual ~SpecialAbilityUpdate();
private:
	void onExit(bool a, bool b);
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class SpecialDisguiseUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void onExit(bool a, bool b);
};

// ?onExit@SpecialDisguiseUpdate@@MAEX_N0@Z @0x004B0414
void SpecialDisguiseUpdate::onExit(bool a, bool b)
{
	SpecialAbilityUpdate::onExit(a, b);
	if (m_object->getDrawable())
		m_object->getDrawable()->m_B0 = 1.0f;
}
