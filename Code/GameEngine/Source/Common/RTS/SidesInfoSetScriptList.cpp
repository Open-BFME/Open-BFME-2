// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// SidesInfo::setScriptList, retail 0x003297F3 (8 bytes): `add ecx,8` then a
// tail jump into the ScriptList member-wise swap at 0x003B58DF. ZH's
// SidesInfo::setScriptList(ScriptList *) stored a pointer; BFME2 keeps the
// ScriptList by value at +0x08 and swaps the caller's list in.
// ScriptEngine::reset calls it with an empty temporary for every side.

class ScriptList
{
public:
	void swap(ScriptList *other);

private:
	char m_body[0x4C];
};

struct SidesInfo
{
	void setScriptList(ScriptList *list);

	char m_pad[8];
	ScriptList m_scriptList; // +0x08
};

inline void SidesInfo::setScriptList(ScriptList *list)
{
	m_scriptList.swap(list);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (SidesInfo::*_bfmeInlineAnchor_SidesInfoSetScriptList_0)(ScriptList *list) = &SidesInfo::setScriptList;
