#pragma once
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include <list>

class ControlBarScheme;
class Player;
class PlayerTemplate;

// Shared accessed manager prefix from native lookup 0x31FC08 and the
// verified setters 0x31FC6A/0x31FD0D: current scheme0, multiplier4,
// STLport listC. These pointer-only users do not construct the manager or
// assert its complete allocation extent. Scheme fields remain in their
// existing layouts; the lookup needs only the native name subobject at +0.
class ControlBarSchemeManager
{
public:
	ControlBarScheme *findControlBarScheme(AsciiString name);
	ControlBarScheme *newControlBarScheme(AsciiString name);
	void setControlBarScheme(AsciiString name);
	void setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt, bool useSmall);
	void setControlBarSchemeByPlayer(Player *player);
private:
	ControlBarScheme *m_currentScheme;
	Coord2D m_multiplyer;
	typedef _STL::list<ControlBarScheme *> ControlBarSchemeList;
	ControlBarSchemeList m_schemeList;
};
