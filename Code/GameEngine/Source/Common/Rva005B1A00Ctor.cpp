// cl: /Ob1
//
// GUICommandTranslator's constructor, retail 0x0043132D (53 bytes): GameClient::init
// (0x0023A580) news it (0x3C bytes) and attaches it to TheMessageStream at priority
// 40. It installs GUICommandTranslator's own table 0x00C3C968 (slot 0
// translateGameMessage 0x004314B1, slot 1 the translators' folded deleting
// destructor 0x004296EE) and clears every field. Zero Hour's GUICommandTranslator.cpp
// defines the constructor and an empty destructor; retail ICF-folded that
// destructor with the other translators' at 0x00429191. The field labels follow
// GUICommandTranslatorTranslateGameMessage.cpp's view.

#include "../../Include/GameClient/FormationTranslator.h"

struct ICoord2DFields
{
	int x;
	int y;
};

class GUICommandTranslator : public GameMessageTranslator
{
public:
	GUICommandTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual ~GUICommandTranslator();

private:
	int m_04;
	int m_08;
	ICoord2DFields m_leftMouseUpPosition;	// +0x0C
	bool m_14;
	int m_leftMouseDownTime;				// +0x18
	int m_leftMouseUpTime;					// +0x1C
	int m_20;
	int m_24;
	ICoord2DFields m_rightMouseUpPosition;	// +0x28
	bool m_rightMouseDragged;				// +0x30
	int m_rightMouseDownTime;				// +0x34
	int m_rightMouseUpTime;					// +0x38
};

GUICommandTranslator::GUICommandTranslator()
{
	m_04 = 0;
	m_08 = 0;
	m_leftMouseUpPosition.x = 0;
	m_leftMouseUpPosition.y = 0;
	m_14 = false;
	m_leftMouseDownTime = 0;
	m_leftMouseUpTime = 0;
	m_20 = 0;
	m_24 = 0;
	m_rightMouseUpPosition.x = 0;
	m_rightMouseUpPosition.y = 0;
	m_rightMouseDragged = false;
	m_rightMouseDownTime = 0;
	m_rightMouseUpTime = 0;
}

GUICommandTranslator::~GUICommandTranslator()
{
}
