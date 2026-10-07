// cl: /DNDEBUG /MD
//
// Target 0x0023D68E walks the GameLogic +0xAC Object list and applies a
// Drawable update when the boolean argument is set or the template flag at
// +0x117 bit 0 is clear. Its operation name remains unresolved. The helper
// called with the current Object in ECX at 0x0023D6C2 is address-derived.
//
// Target 0x0023D6FA returns true for a null Object or when its template flag
// at +0x10A bit 1 is clear. Otherwise it builds a player mask from the
// controlling Player's +0x54 value, calls the rowed GameLogic method at
// 0x0023C924, then returns false. The target function's operation name and
// the field names remain unresolved.

class Drawable;

class ObjectTemplate
{
public:
	char m_pad[0x10A];
	unsigned char m_flagsAt10A;
	char m_pad10B[0xC];
	unsigned char m_flagsAt117;
};

class Player
{
public:
	char m_pad[0x54];
	int m_indexAt54;
};

class Object
{
public:
	char m_pad00[4];
	ObjectTemplate *m_template;
	char m_pad08[0x84];
	Object *m_next;

	Drawable *getDrawable(void) const;
	Player *getControllingPlayer(void) const;
	bool isLocallyControlled(void) const;
};

class Rva0028D680
{
public:
	void rva0028D680(void);
};

class GameLogic
{
public:
	void rva0023D68E(bool value);
	void selectObject(Object *object, bool mode, unsigned int playerMask, bool locallyControlled);

private:
	char m_pad00[0xAC];
	Object *m_objectHead;
};

class Drawable
{
public:
	void rva00270FAC(bool value);
};

extern GameLogic *TheGameLogic;

void GameLogic::rva0023D68E(bool value)
{
	Object *object = m_objectHead;
	while (object != 0) {
		if (value || (object->m_template->m_flagsAt117 & 1) == 0) {
			Drawable *drawable = object->getDrawable();
			if (drawable != 0) {
				drawable->rva00270FAC(value);
				((Rva0028D680 *)object)->rva0028D680();
			}
		}
		object = object->m_next;
	}
}

int rva0023D6FA(Object *object)
{
	if (object != 0 && (object->m_template->m_flagsAt10A & 2) != 0) {
		Player *player = object->getControllingPlayer();
		unsigned int playerMask = 1 << player->m_indexAt54;
		TheGameLogic->selectObject(object, true, playerMask, object->isLocallyControlled());
		return 0;
	}
	return 1;
}
