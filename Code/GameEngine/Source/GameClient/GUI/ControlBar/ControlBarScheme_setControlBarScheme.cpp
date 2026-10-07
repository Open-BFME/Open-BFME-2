// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// ?setControlBarScheme@ControlBarSchemeManager@@QAEXVAsciiString@@@Z @0x0031FC6A 162B
// Evidence: BFME1 donor ControlBarScheme.cpp ControlBarSchemeManager::setControlBarScheme(AsciiString) (find + Display w/h over res + store + init, no assert in retail); caller at 0x0031BA80 passes ControlBar+0x44; callee findControlBarScheme typed AsciiString lookup at 0x0031FC08 + init row 0x0031ED2C + TheDisplay; layout m_currentScheme+0 m_multiplyer+4 list+0xC from setControlBarSchemeByPlayerTemplate TU; shape-lever AsciiString inline forwarder fixes mov-ecx-esp transposition.
#include <list>
#include "ascii_string.h"

struct ICoord2D
{
	int x;
	int y;
};

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class ControlBarScheme
{
public:
	void init();
	AsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	AsciiString m_side;
};

class Display
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
};

extern Display *TheDisplay;

#include "ControlBarSchemeManagerView.h"

void ControlBarSchemeManager::setControlBarScheme(AsciiString schemeName)
{
	ControlBarScheme *tempScheme = findControlBarScheme(schemeName);
	if (tempScheme)
	{
		unsigned int w = TheDisplay->getWidth() / (unsigned int)tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.x = (float)w;
		unsigned int h = TheDisplay->getHeight() / (unsigned int)tempScheme->m_ScreenCreationRes.y;
		m_multiplyer.y = (float)h;
		m_currentScheme = tempScheme;
	}
	else
	{
		m_currentScheme = 0;
	}
	if (m_currentScheme)
		m_currentScheme->init();
}
