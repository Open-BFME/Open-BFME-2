#ifndef BFME2_PLACE_EVENT_TRANSLATOR_VIEW_H
#define BFME2_PLACE_EVENT_TRANSLATOR_VIEW_H

// Existing BFME 2 placement receiver: constructor 0x0043216D and
// translateGameMessage 0x0043218A agree on offsets +4 through +0x15.
// This keeps the existing modeled virtual interface; it does not add slots.
class GameMessage;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

enum GameMessageDisposition
{
	KEEP_MESSAGE = 0,
	DESTROY_MESSAGE = 1
};

class PlaceEventTranslator
{
public:
	PlaceEventTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	ICoord2D m_downPos;
	unsigned int m_downFrame;
	unsigned int m_upFrame;
	bool m_isDown;
	bool m_isDragging;
};

#endif
