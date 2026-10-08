// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX- /Oi-
// stlport
//
// ?getUpgradeActivationMasks@UpgradeMuxData@@QBEXAAUUpgradeMaskType@@0@Z,
// retail 0x004CB189, 369 bytes. Dedicated TU.
//
// Zero Hour reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/Thing/Module.cpp,
// UpgradeMuxData::getUpgradeActivationMasks) adapted for BFME2 retail drift,
// following the BFME1 conversion of the same body
// (reference/open-bfme-1/Code/GameEngine/Source/Common/Thing/UpgradeMuxData_getUpgradeActivationMasks.cpp).
//
// BFME2 deltas measured from retail bytes:
// - Masks are 128 bytes each leading the object (+0x00/+0x80, memset 0x80 x2,
//   rep movsd 0x20 x2 out), not 24-byte masks at +0x00/+0x18; modeled as a
//   1024-bit TU-local UpgradeMaskType (size-evidenced, not header-proven).
// - Activation/conflict name vectors follow at +0x100/+0x10C (ZH +0x30/+0x3C).
// - UpgradeTemplate carries the mask bit index as a plain int at +0x38
//   (ZH mask member at +0x20); the BitFlags::set index math (word = i >> 5,
//   bit = 1 << (i & 31)) falls out of _Unchecked_set, xor/inc included.
// - The DEBUG_CRASH text feeds the INIException filler directly (filler pin
//   0x002F681 + _CxxThrowException pin 0x00629094, INI_scanReal.cpp idiom:
//   explicit filler call plus explicit noreturn throw, no `throw` keyword,
//   so no SEH prologue). Throw-info anchor is a sacrificial static (DIR32).
// - Vector clears route to the outlined vector<AsciiString>::erase at
//   0x002CCFC (82 image-wide callers pushing finish/start pairs; range
//   destroy plus finish update inside), pinned on first resolution.

#include <bitset>
#include <string.h>
#include <vector>
#include "ascii_string.h"

// TU-local 1024-bit mask view (size-measured: 0x80 memsets, 0x20 rep movsd).
// Lowering mirrors ZH Common/BitFlags.h over std::bitset (clear via memset,
// set via the unchecked word-or) but spelled directly: this toolchain will
// not inline the stlport reset/_Unchecked_set bodies here (they arrive as
// calls), while retail has them fully inline.
struct UpgradeMaskType
{
	void clear()
	{
		memset(&m_words[0], 0, sizeof(m_words));
	}

	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (unsigned long)1 << (bit & 31);
	}

	unsigned long m_words[32];
};

class UpgradeTemplate
{
public:
	unsigned int getUpgradeMask() const { return m_upgradeMaskIndex; }

private:
	unsigned char m_pad[0x38];
	unsigned int m_upgradeMaskIndex; // +0x38 (retail-measured)
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;	// Upgrade.cpp's global (0x009FEB60)

struct INIException
{
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

__declspec(noreturn) void __stdcall _CxxThrowException(void *pExc, void *pInfo);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, copied from retail's INIException throwinfo at
// 0xCFE2FC). Its content is never compared.
struct UpgradeMuxThrowInfoAnchor { int a; int b; int c; int d; };
static const UpgradeMuxThrowInfoAnchor upgradeMuxThrowInfoAnchor = { 0, 0, 0, 0 };

class UpgradeMuxData
{
public:
	void getUpgradeActivationMasks(UpgradeMaskType &activation,
		UpgradeMaskType &conflicting) const;

private:
	mutable UpgradeMaskType m_activationMask; // +0x00 (128 bytes)
	mutable UpgradeMaskType m_conflictingMask; // +0x80 (128 bytes)
	mutable _STL::vector<AsciiString> m_activationUpgradeNames; // +0x100
	mutable _STL::vector<AsciiString> m_conflictingUpgradeNames; // +0x10C
};

// ?getUpgradeActivationMasks@UpgradeMuxData@@QBEXAAUUpgradeMaskType@@0@Z
void UpgradeMuxData::getUpgradeActivationMasks(
	UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	if (!m_activationUpgradeNames.empty() || !m_conflictingUpgradeNames.empty())
	{
		m_activationMask.clear();
		m_conflictingMask.clear();

		_STL::vector<AsciiString>::const_iterator it;
		for (it = m_activationUpgradeNames.begin();
			it != m_activationUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate *theTemplate =
				TheUpgradeCenter->findUpgrade(*it);
			if (!theTemplate && !it->isEmpty() && !it->isNone())
			{
				INIException e(3,
					"An upgrade module references %s, which is not an Upgrade",
					it->str());
				_CxxThrowException(&e, (void *)&upgradeMuxThrowInfoAnchor);
			}

			m_activationMask.set(theTemplate->getUpgradeMask());
		}

		for (it = m_conflictingUpgradeNames.begin();
			it != m_conflictingUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate *theTemplate =
				TheUpgradeCenter->findUpgrade(*it);
			if (!theTemplate && !it->isEmpty() && !it->isNone())
			{
				INIException e(3,
					"An upgrade module references %s, which is not an Upgrade",
					it->str());
				_CxxThrowException(&e, (void *)&upgradeMuxThrowInfoAnchor);
			}

			m_conflictingMask.set(theTemplate->getUpgradeMask());
		}

		m_activationUpgradeNames.clear();
		m_conflictingUpgradeNames.clear();
	}

	activation = m_activationMask;
	conflicting = m_conflictingMask;
}

// The (void *, void *) declaration above is a C++ overload, so calls spell
// ?_CxxThrowException@@YGXPAX0@Z; retail calls the MSVC 7.1 throw helper
// __CxxThrowException@8 (its import thunk at 0x00629094). Same ABI: bind the spelling.
#pragma comment(linker, "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8")
