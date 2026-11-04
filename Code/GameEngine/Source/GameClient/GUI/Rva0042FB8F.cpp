// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport

// ?rva0042FB8F@Rva0042FB8F@@QAE_NPAVDrawable@@PAVGameMessage@@@Z @0x0042FB8F 285B: selection-limit gate showing GUI:MaxSelectionSize via InGameUI message then appending ObjectID. Evidence: retail calls TheInGameUI slots 0x11c/0x118/0x40 plus TheGameText fetch 0x3c plus UnicodeString format/release/copy plus GameMessage appendObjectIDArgument 0x0030F979; BFME1 donor SelectionTranslator::killThemKillThemAll same shape (draw null plus object null plus max/select plus displayed-warning byte plus append).
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

class Object
{
public:
	unsigned char m_pad00[0x74];
	ObjectID m_id;
};

#include "../../../Include/GameClient/Drawable.h"

#include "../../../Include/Common/MessageStream.h"

#include "../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

#include "../../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

class Rva0042FB8F
{
public:
	bool rva0042FB8F(Drawable *draw, GameMessage *msg);

private:
	unsigned char m_pad00[0x20];
	bool m_displayedMaxWarning;
};

bool Rva0042FB8F::rva0042FB8F(Drawable *draw, GameMessage *killThemAllMsg)
{
	if (draw)
	{
		if (draw->m_object)
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
						TheInGameUI->rva0029E846(msg);
					}
					return false;
				}
			}
			if (killThemAllMsg)
			{
				killThemAllMsg->appendObjectIDArgument(draw->m_object->m_id);
			}
			return true;
		}
	}
	return false;
}
