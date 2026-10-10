// cl: /O1 /ICode/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /MD
// ?rva005DAB30@Rva005DAAB6@@QAEHPAVPlayer@@@Z
// ?rva005DAB30@Rva005DAAB6@@QAEHPAVPlayer@@@Z @0x005DAB30 165B: build availability of the production entry named by m_0C (ThingFactory::findTemplate 0x002D06CA) for the player; vslot 16 of vftable 0x008765A8; layout shared with the slot-15 sibling in Rva005DAAB6Slot15.cpp.

extern class ThingFactory *TheThingFactory;
extern class GameLogic *TheGameLogic;
extern class Rva00A027B8 *g_00A027B8;
// g_00A027B8: matched references place it at VA 0xe027b8 (zero-filled .bss).
class Rva00A027B8 * g_00A027B8;


#include "ascii_string.h"

class Object;


#include "GameLogicObjectLookupView.h"

class Rva00A027B8
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual int slot14(Object *a1, void *a2, void *a3, float a4, bool a5);
};

class Rva0055B0CC
{
	friend class Rva005DAAB6;
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void Slot6(void *arg1, bool arg2);
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Rva0055AED6(void *xfer, void *arg2);
private:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

class Rva005DAAB6 : public Rva0055B0CC
{
public:
	virtual bool rva005DABD5(bool arg);
 int rva005DAB30(class Player *player);
private:
	bool m_2C;
	struct Coord3D
	{
		float x;
		float y;
		float z;
	};
	Coord3D m_30;
	float m_3C;
 class CommandButton *m_command;
};

enum BuildableStatus { BSTATUS_YES, BSTATUS_IGNORE_PREREQUISITES, BSTATUS_NO, BSTATUS_ONLY_BY_AI };
class ThingTemplate { public: BuildableStatus getBuildable() const; };
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); };
class CommandButton { public: const ThingTemplate *rva0035B570() const; };
class Rva005DAB30Production {
public: virtual void v0(); virtual void v1(); virtual void v2(); virtual bool busy();
};
class Player {
public:
 bool allowedToBuild(const ThingTemplate *) const;
 bool canBuild(const ThingTemplate *) const;
 unsigned char rva002AA00C(ThingTemplate *, int);
 char unknown[0x5C]; int type;
};
class Object {
public: Player *getControllingPlayer() const; void *rva0028BCF4() const;
};
int Rva005DAAB6::rva005DAB30(Player *player)
{
 const ThingTemplate *objectTemplate = TheThingFactory->findTemplate(m_0C);
 Object *object = TheGameLogic->findObjectByID(m_08);
 if (objectTemplate && object && player->allowedToBuild(objectTemplate)) {
  BuildableStatus status = m_command->rva0035B570()->getBuildable();
  if (status == BSTATUS_NO || (status == BSTATUS_ONLY_BY_AI && object->getControllingPlayer()->type != 1)) return 9;
  Rva005DAB30Production *production = (Rva005DAB30Production *)object->rva0028BCF4();
  if (production && !production->busy() && player->canBuild(objectTemplate))
   return player->rva002AA00C((ThingTemplate *)objectTemplate, 0) ? 0 : 2;
 }
 return 9;
}
