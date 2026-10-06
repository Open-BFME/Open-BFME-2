// ?selectFriends@SelectionTranslator@@QAE_NPAVDrawable@@PAVGameMessage@@_N@Z
// partial score=0.98 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /Os /DNDEBUG /MD /EHsc
// stlport
// ?selectFriends@SelectionTranslator@@QAE_NPAVDrawable@@PAVGameMessage@@_N@Z @0x0042FE7F 321B: CanSelect gate plus max-limit warning plus selectCountMap inc plus append plus selectDrawable. Evidence: pin, LINK BONUS 29B from selectFriendsWrapper, donor SelectionTranslator_selectFriends, rowed CanSelectDrawable 0x0042FA63, retail slots 0x11c/0x118/0x40/0x108 plus fetch 0x3c plus UnicodeString plus ImageSubscriptMap 0x002077D6 plus append 0x0030F979.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

enum ObjectID
{
	OBJECTID_NONE = 0
};

class Drawable;
class GameMessage;
class ThingTemplate;

class Object
{
public:
	unsigned char m_pad00[0x74];
	ObjectID m_id;
};

class Drawable
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0xFC - 0x08];
	Object *m_object;
};

class GameMessage
{
public:
	void appendObjectIDArgument(ObjectID id);
};

class GameTextInterface
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
	virtual void slot14();
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class InGameUI
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
	virtual void slot14();
	virtual void slot15();
	virtual void message(UnicodeString format, ...);
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void selectDrawable(Drawable *draw);
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual Int getSelectCount();
	virtual Int getMaxSelectCount();
};

extern InGameUI *TheInGameUI;

class Image;
class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
};

Bool CanSelectDrawable(const Drawable *draw, Bool dragSelecting);

class SelectionTranslator
{
public:
	Bool selectFriends(Drawable *draw, GameMessage *createTeamMsg, Bool dragSelecting);

private:
	unsigned char m_pad00[0x20];
	Bool m_displayedMaxWarning;
	unsigned char m_pad21[0x28 - 0x21];
	ImageSubscriptMap m_selectCountMap;
};

Bool SelectionTranslator::selectFriends(Drawable *draw, GameMessage *createTeamMsg, Bool dragSelecting)
{
	if (CanSelectDrawable(draw, dragSelecting))
	{
		if (TheInGameUI->getMaxSelectCount() > 0)
		{
			Int maxLimit = TheInGameUI->getMaxSelectCount();
			Int curCount = TheInGameUI->getSelectCount();
			if (curCount >= maxLimit)
			{
				if (!m_displayedMaxWarning)
				{
					m_displayedMaxWarning = true;
					UnicodeString msg;
					msg.format(TheGameText->fetch("GUI:MaxSelectionSize").str(), TheInGameUI->getMaxSelectCount());
					TheInGameUI->message(msg);
				}
				return false;
			}
		}
		++(int &)m_selectCountMap[(unsigned int)draw->m_template];
		if (draw->m_object && createTeamMsg)
			createTeamMsg->appendObjectIDArgument(draw->m_object->m_id);
		TheInGameUI->selectDrawable(draw);
		return true;
	}
	return false;
}
