// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// ?setControlBarSchemeByPlayerTemplate@ControlBarSchemeManager@@QAEXPBVPlayerTemplate@@_N@Z @0x0031FD0D 316B unlock: ControlBarSchemeManager side selection by PlayerTemplate side
// Evidence: donor BFME1/ZH ControlBarSchemeManager::setControlBarSchemeByPlayerTemplate (Small/Observer/Default literals, compare vs compareNoCase, Display width/height over res, findControlBarScheme Default fallback, init tail); callers at 0x31ADF9 0x31C5E7; unblocks 0x31C5C8; layout m_currentScheme+0 m_multiplyer+4 list+0xC from ControlBarScheme init TU; callees rowed StringBase copy/concat/compare/compareNoCase/set/releaseBuffer init find.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

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

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }
private:
	char m_pad[0x18];
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

class ControlBarSchemeManager
{
public:
	void setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt, bool useSmall);
	ControlBarScheme *findControlBarScheme(AsciiString name);
private:
	ControlBarScheme *m_currentScheme;
	Coord2D m_multiplyer;
	typedef std::list<ControlBarScheme *> ControlBarSchemeList;
	ControlBarSchemeList m_schemeList;
};

void ControlBarSchemeManager::setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt, bool useSmall)
{
	if (!pt)
		return;
	AsciiString side = pt->getSide();
	if (useSmall)
		side.concat("Small");
	if (m_currentScheme && m_currentScheme->m_side.compare(side) == 0)
	{
		m_currentScheme->init();
		return;
	}
	if (side.isEmpty())
		side.set("Observer");
	ControlBarScheme *tempScheme = 0;
	for (ControlBarSchemeList::iterator it = m_schemeList.begin(); it != m_schemeList.end(); ++it)
	{
		ControlBarScheme *scheme = *it;
		if (!scheme)
			continue;
		if (scheme->m_side.compareNoCase(side) == 0)
		{
			if (!tempScheme || tempScheme->m_ScreenCreationRes.x < scheme->m_ScreenCreationRes.x)
				tempScheme = scheme;
		}
	}
	if (tempScheme)
	{
		m_multiplyer.x = TheDisplay->getWidth() / (float)tempScheme->m_ScreenCreationRes.x;
		m_multiplyer.y = TheDisplay->getHeight() / (float)tempScheme->m_ScreenCreationRes.y;
		m_currentScheme = tempScheme;
	}
	else
	{
		m_currentScheme = findControlBarScheme("Default");
	}
	if (m_currentScheme)
		m_currentScheme->init();
}
