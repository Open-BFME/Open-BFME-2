// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// CommandButton::isReady(const Object *), retail 0x0035B069 (135 bytes),
// pinned. Zero Hour's body (GameClient/GUI/ControlBar/ControlBar.cpp) with
// BFME 2's additions read from the target: a null source is never ready, and
// command type 0x17 (+0x14) is ready when the source has the button's
// upgrade (+0x24, if any) and its +0x458 frame has been reached. Otherwise
// ZH's checks: the special power module for +0x44 (the rowed lookup
// 0x0028BB9E, reached through its address-named view) at 100% (vslot 2,
// fld1/fucomip), or an upgrade the source is affected by (pinned 0x002940B9,
// address-named view) and does not yet have (rowed 0x00290D2B).
//
// Built /O1 /G7 against STLport like the Apt screens (AptDisconnectScreen.cpp):
// the label lists are vector<AsciiString>, and only that build keeps the
// label getters' isEmpty call out of line and reloads the list bounds in
// every block as retail does.
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class UpgradeTemplate;
class SpecialPowerTemplate;

#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
	Bool hasUpgrade(const UpgradeTemplate *upgrade) const; // Object::hasUpgrade
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	Bool bfmeReadyFrameReached() const { Bool ready = m_readyFrame <= TheGameLogic->getFrame(); return ready; }
private:
	char m_pad[0x458];
	unsigned m_readyFrame; // +0x458
};

// Object::getSpecialPowerModule through the view its row carries (kept file-local so this unit emits
// no copy of the shared inline names).
static inline SpecialPowerModuleInterface *getSpecialPowerModule(const Object *obj, const SpecialPowerTemplate *sp)
{
	return (SpecialPowerModuleInterface *)obj->getSpecialPowerModule(sp);
}

class Image;

// The button's image list (+0xEC) as the bounds-checked twin 0x0035B1C3
// (Rva0035B1C3Finish.cpp) reads it: a signed count of the char span.
struct CommandButtonImageList
{
	const Image **m_begin;
	const Image **m_end;
	const Image **m_capacity;
	int size() const { return (int)((char *)m_end - (char *)m_begin) >> 2; }
	const Image *at(int index) const { return m_begin[index]; }
};

#include "../../../../Include/GameClient/CommandButton.h"

// The canonical header exposes the +0x58/+0x64/+0xEC ranges as raw storage;
// each use views the range in place, as retail reloads its bounds per block.
template <class T> static inline const T &rangeView(const void *storage)
{
	return *reinterpret_cast<const T *>(storage);
}

Bool CommandButton::isReady(const Object *sourceObj) const
{
	if( !sourceObj )
		return false;

	if( m_command == 0x17 )
	{
		if( m_upgradeTemplate && !sourceObj->hasUpgrade( m_upgradeTemplate ) )
			return false;
		return sourceObj->bfmeReadyFrameReached();
	}

	SpecialPowerModuleInterface *mod = getSpecialPowerModule( sourceObj, m_specialPower );
	if( mod && mod->getPercentReady() == 1.0f )
		return true;

	if (m_upgradeTemplate && sourceObj->affectedByUpgrade(m_upgradeTemplate) && !sourceObj->hasUpgrade(m_upgradeTemplate))
		return true;

	return false;
}

// Retail 0x0035B140, 36 bytes: BFME 1's CommandButton::isContextCommand
// (0x0049AE80, GUI/ControlBar/ControlBar.cpp), ZH's CONTEXTMODE_COMMAND
// option test (bit 9 of +0x1C) behind command-type special cases; BFME 2's
// are 0x18, 0x20, 0x26 and 0x17. InGameUI::setGUICommand (0x0029A889) calls
// it between its need-target test and the radius cursor, as in ZH.
Bool CommandButton::isContextCommand() const
{
	if( m_command == 0x18 || m_command == 0x20 || m_command == 0x26 || m_command == 0x17 )
		return true;
	return ((m_options >> 9) & 1) != 0;
}

// Retail 0x0035B19E, 37 bytes: the image the button's +0xFC index selects
// from its list, or null when the index is negative or past the end. The
// spell store (parseSpellIndex_Thunk.cpp, 0x0043C9FD) binds it per button.
const Image *CommandButton::rva0035B19E() const
{
	int index = fieldFC;
	if (index < 0)
		return 0;
	if ((unsigned int)index < (unsigned int)rangeView<CommandButtonImageList>(&m_imagesBegin).size())
		return rangeView<CommandButtonImageList>(&m_imagesBegin).at(index);
	return 0;
}

// Retail 0x0035B1E9, 73 bytes: the button's label, +0x7C when set, else the
// entry of the +0x58 list the +0xFC index selects, clamped to the last one,
// or the empty string for an empty list. The spell store's frame update
// (parseSpellIndex_Thunk.cpp, 0x0043CD3C) fetches its help text with it.
const AsciiString &CommandButton::rva0035B1E9() const
{
	if (!field7C.isEmpty())
		return field7C;
	if (!rangeView<_STL::vector<AsciiString> >(&m_textLabelBegin).empty())
	{
		if ((unsigned int)fieldFC >= rangeView<_STL::vector<AsciiString> >(&m_textLabelBegin).size())
			return rangeView<_STL::vector<AsciiString> >(&m_textLabelBegin).back();
		return rangeView<_STL::vector<AsciiString> >(&m_textLabelBegin)[fieldFC];
	}
	return AsciiString::TheEmptyString;
}

// Retail 0x0035B26F, 47 bytes: the same selection from the +0x64 list with
// no override; the spell store's description text.
const AsciiString &CommandButton::rva0035B26F() const
{
	if (!rangeView<_STL::vector<AsciiString> >(&m_descriptionBegin).empty())
	{
		if ((unsigned int)fieldFC >= rangeView<_STL::vector<AsciiString> >(&m_descriptionBegin).size())
			return rangeView<_STL::vector<AsciiString> >(&m_descriptionBegin).back();
		return rangeView<_STL::vector<AsciiString> >(&m_descriptionBegin)[fieldFC];
	}
	return AsciiString::TheEmptyString;
}
