// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// WB 0x0100D3E0 unnamed ScriptActions member, retail 0x003C596A (150B): find
// the model-condition flag a script names (the 591 ModelConditionNames at
// 0x00DBAA98) and set it on the named unit for a time given in seconds,
// converted to logic frames (Object 0x002949AE, WorldBuilder's
// BitFlags<591>::SetBit caller in Object.cpp). Built without /arch:SSE: the
// seconds-to-frames product goes through x87 and _ftol2 in retail.

#include "ascii_string.h"

extern const char *const ModelConditionNames[];
extern const int g_009BA4E4;	// logic frames per second

enum ModelConditionFlagType { MODEL_CONDITION_FIRST = 0 };
inline int LogicFramesPerSecond() { return g_009BA4E4; }

class Object
{
public:
	void setSpecialModelConditionState(ModelConditionFlagType flag, unsigned int frames);
	void rva002949AE(int flag, int frames, float value);
};

template<class OBJ> class DLINK_ITERATOR
{
public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJ *cur() const { return m_cur; }
private:
    OBJ *m_cur;
    char m_pad[20];
};
class Team
{
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
	Object *getUnitNamed(const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void rva003C596A(const AsciiString &unitName, const AsciiString &flagName,
		float seconds, float value);
};

void ScriptActions::rva003C596A(const AsciiString &unitName, const AsciiString &flagName,
	float seconds, float value)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj)
		return;
	int flag = -1;
	int frames = 0;
	bool found = false;
	for (int i = 0; i < 591; ++i) {
		AsciiString name(ModelConditionNames[i]);
		if (flagName.compare(name) == 0) {
			flag = i;
			found = true;
			frames = (int)(LogicFramesPerSecond() * seconds);
			break;
		}
	}
	if (found)
		obj->rva002949AE(flag, frames, value);
}

// BFME 1 f98983a7d doTeamSetModelConditionForDuration supplies the
// name-search and member walk. Target3C5A00..3C5AB8 proves 591 names,
// x87 frame conversion, 24-byte iterator and direct rowed Object setter.
// Dispatcher RET10 establishes this free action ABI; original name unproven.
void __stdcall Rva003C5A00Do(const AsciiString &teamName, const AsciiString &flagName,
    float seconds, float value)
{
    Team *team = TheScriptEngine->getTeamNamed(teamName, false);
    if (!team)
        return;
    int flag = 0;
    int frames;
    for (; flag < 591; ++flag)
    {
        AsciiString name(ModelConditionNames[flag]);
        if (flagName.compare(name) == 0)
        {
            frames = (int)(LogicFramesPerSecond() * seconds);
            goto matched;
        }
    }
    return;
matched:
    for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
    {
        Object *object = iter.cur();
        if (!object)
            continue;
        object->setSpecialModelConditionState((ModelConditionFlagType)flag, frames);
    }
}
