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

class SpecialPowerModuleInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual Real getPercentReady() const = 0; // vslot 2
};

class BfmeArg985
{
public:
	char bfmeHas985C(int upgrade); // Object::affectedByUpgrade
};

class GameLogic
{
public:
	unsigned getFrame() const { return m_frame; }
private:
	char m_pad[0x40];
	unsigned m_frame;
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const; // Object::hasUpgrade
	Bool bfmeReadyFrameReached() const { Bool ready = m_readyFrame <= TheGameLogic->getFrame(); return ready; }
private:
	char m_pad[0x458];
	unsigned m_readyFrame; // +0x458
};

// Object::getSpecialPowerModule and Object::affectedByUpgrade through the
// address-named views their rows carry (kept file-local so this unit emits
// no copy of the shared inline names).
static inline SpecialPowerModuleInterface *getSpecialPowerModule(const Object *obj, const SpecialPowerTemplate *sp)
{
	return (SpecialPowerModuleInterface *)obj->getSpecialPowerModule(sp);
}
static inline Bool affectedByUpgrade(const Object *obj, const UpgradeTemplate *upgrade)
{
	return ((BfmeArg985 *)obj)->bfmeHas985C((int)upgrade) != 0;
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

class CommandButton
{
public:
	Bool isReady(const Object *sourceObj) const;
	const Image *rva0035B19E() const;
	const AsciiString &rva0035B1E9() const;
	const AsciiString &rva0035B26F() const;
private:
	char m_pad00[0x14];
	int m_commandType;                         // +0x14
	char m_pad18[0x24 - 0x18];
	const UpgradeTemplate *m_upgradeTemplate;  // +0x24
	char m_pad28[0x44 - 0x28];
	const SpecialPowerTemplate *m_specialPower; // +0x44
	char m_pad48[0x58 - 0x48];
	_STL::vector<AsciiString> m_labels;        // +0x58
	_STL::vector<AsciiString> m_descriptions;  // +0x64
	char m_pad70[0x7C - 0x70];
	AsciiString m_label;                       // +0x7C, wins over m_labels when set
	char m_pad80[0xEC - 0x80];
	CommandButtonImageList m_images;           // +0xEC
	char m_padF8[0xFC - 0xF8];
	int m_listIndex;                           // +0xFC, selects from m_images and the label lists
};

Bool CommandButton::isReady(const Object *sourceObj) const
{
	if( !sourceObj )
		return false;

	if( m_commandType == 0x17 )
	{
		if( m_upgradeTemplate && !sourceObj->rva00290D2B( m_upgradeTemplate ) )
			return false;
		return sourceObj->bfmeReadyFrameReached();
	}

	SpecialPowerModuleInterface *mod = getSpecialPowerModule( sourceObj, m_specialPower );
	if( mod && mod->getPercentReady() == 1.0f )
		return true;

	if (m_upgradeTemplate && affectedByUpgrade(sourceObj, m_upgradeTemplate) && !sourceObj->rva00290D2B(m_upgradeTemplate))
		return true;

	return false;
}

// Retail 0x0035B19E, 37 bytes: the image the button's +0xFC index selects
// from its list, or null when the index is negative or past the end. The
// spell store (parseSpellIndex_Thunk.cpp, 0x0043C9FD) binds it per button.
const Image *CommandButton::rva0035B19E() const
{
	int index = m_listIndex;
	if (index < 0)
		return 0;
	if ((unsigned int)index < (unsigned int)m_images.size())
		return m_images.at(index);
	return 0;
}

// Retail 0x0035B1E9, 73 bytes: the button's label, +0x7C when set, else the
// entry of the +0x58 list the +0xFC index selects, clamped to the last one,
// or the empty string for an empty list. The spell store's frame update
// (parseSpellIndex_Thunk.cpp, 0x0043CD3C) fetches its help text with it.
const AsciiString &CommandButton::rva0035B1E9() const
{
	if (!m_label.isEmpty())
		return m_label;
	if (!m_labels.empty())
	{
		if ((unsigned int)m_listIndex >= m_labels.size())
			return m_labels.back();
		return m_labels[m_listIndex];
	}
	return AsciiString::TheEmptyString;
}

// Retail 0x0035B26F, 47 bytes: the same selection from the +0x64 list with
// no override; the spell store's description text.
const AsciiString &CommandButton::rva0035B26F() const
{
	if (!m_descriptions.empty())
	{
		if ((unsigned int)m_listIndex >= m_descriptions.size())
			return m_descriptions.back();
		return m_descriptions[m_listIndex];
	}
	return AsciiString::TheEmptyString;
}
