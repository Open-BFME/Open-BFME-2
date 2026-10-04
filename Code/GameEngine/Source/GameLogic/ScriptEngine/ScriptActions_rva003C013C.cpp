// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva003C013C@ScriptActions@@IAEXABVAsciiString@@0@Z @0x003C013C 111B: trigger-area shroud reveal.
// Evidence: calls rowed StringBase copy 0x000365F0 via by-value AsciiString temp plus rowed getQualifiedTriggerAreaByName 0x0035768D plus pinned PolygonTrigger rect 0x002E3954 plus rowed player-mask 0x00357475 plus rowed shroud siblings 0x00739AF0 0x00739CA0; globals g_Va009FE16C TheShroudManager; ret 8 two AsciiStrings.
#include "ascii_string.h"

struct FloatRect0073CE30
{
	float m_left;
	float m_top;
	float m_right;
	float m_bottom;
};

class PolygonTrigger
{
public:
	void rva002E3954(FloatRect0073CE30 *rect);
};

class ScriptEngine
{
public:
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern ScriptEngine *g_Va009FE16C;

class Rva00739AF0
{
public:
	void rva00739AF0(FloatRect0073CE30 *rect, int a, unsigned int b);
};

class Rva00739CA0
{
public:
	void rva00739CA0(FloatRect0073CE30 *rect, int a, unsigned int b);
};
class PartitionManager;
extern PartitionManager *TheShroudManager;

class ScriptActions
{
protected:
	void rva003C013C(const AsciiString &areaName, const AsciiString &playerName);
};

void ScriptActions::rva003C013C(const AsciiString &areaName, const AsciiString &playerName)
{
	PolygonTrigger *trig = g_Va009FE16C->getQualifiedTriggerAreaByName(areaName);
	if (!trig)
		return;
	FloatRect0073CE30 rect;
	trig->rva002E3954(&rect);
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
	PolygonTrigger *trig38 = (PolygonTrigger *)((char *)trig + 0x38);
	((Rva00739AF0 *)TheShroudManager)->rva00739AF0(&rect, (int)trig38, (unsigned int)mask);
	((Rva00739CA0 *)TheShroudManager)->rva00739CA0(&rect, (int)trig38, (unsigned int)mask);
}
