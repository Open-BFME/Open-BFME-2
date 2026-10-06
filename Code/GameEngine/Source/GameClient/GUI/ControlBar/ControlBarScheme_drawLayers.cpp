// cl: /O1 /DNDEBUG /MD /EHsc
// ControlBarSchemeManager::drawForeground @0x0031FA9A (43B) and
// ::drawBackground @0x0031FAC5 (43B): Zero Hour ControlBarScheme.cpp's
// bodies. Each hands the current scheme (+0x00) the manager's multiplier
// (+0x04, by value) and the caller's offset. drawBackground's identity is its
// caller W3DCommandBarBackgroundDraw 0x0009FA82 (ZH: man->drawBackground(
// offset)); drawForeground is its twin one body earlier, calling the twin of
// the scheme draw drawBackground calls. The scheme draws are rowed under
// address names (0x0031F89E and 0x0031F96F); their ZH names are pinned.
//
// class-gate: allow Coord2D retail copies the by-value multiplier into an esp temp and parks its address in the dead offset slot (mov [ebp+0xc],esp under an ebp frame) - the shape of an argument with a user copy ctor and dtor; the canonical plain Coord2D copies with two pushes
class Coord2D
{
public:
	Coord2D() {}
	Coord2D(const Coord2D &o) : x(o.x), y(o.y) {}
	~Coord2D() {}
	float x;
	float y;
};

typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

class ControlBarScheme
{
public:
	void drawForeground(Coord2D multi, ICoord2D offset);
	void drawBackground(Coord2D multi, ICoord2D offset);
};

class ControlBarSchemeManager
{
public:
	void drawForeground(ICoord2D offset);
	void drawBackground(ICoord2D offset);

private:
	ControlBarScheme *m_currentScheme;   // +0x00
	Coord2D m_multiplyer;                // +0x04
};

void ControlBarSchemeManager::drawForeground(ICoord2D offset)
{
	if (m_currentScheme)
		m_currentScheme->drawForeground(m_multiplyer, offset);
}

void ControlBarSchemeManager::drawBackground(ICoord2D offset)
{
	if (m_currentScheme)
		m_currentScheme->drawBackground(m_multiplyer, offset);
}
