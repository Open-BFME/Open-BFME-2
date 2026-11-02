// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Game-mode-keyed preferences (vtable 0x00C3EF60, retail 0x0044D50D-
// 0x0044D774): a UserPreferences whose typed accessors store every key as
// "<mode>:<key>", with mode 0 = "Rts", 1 = "Strat" (War of the Ring) and
// anything else unprefixed. The prefixed key is formatted into a scratch
// AsciiString member (+0x18) and handed to the base accessor; write is a
// plain forward. The class name is descriptive -- no retail spelling is
// known. LANPreferences (vtable 0x00C3EF04) derives from it. The
// UserPreferences model is the one in Common/UserPreferences.cpp.

#include <stdio.h>
#include <map>
#include <stdlib.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"



#include "unicode_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;
// Declaration-only: the rowed map<AsciiString,AsciiString>::operator[] is bound,
// this TU emits no per-flag copy of it or of the tree internals it pulls in.
namespace _STL {
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &);
}

#include "../../Include/Common/UserPreferences.h"

class GameModePreferences : public UserPreferences
{
public:
	GameModePreferences(Int mode);
	virtual ~GameModePreferences();

	virtual Bool write(void);
	virtual Bool getBool(const AsciiString &key, Bool defaultValue) const;
	virtual Real getReal(const AsciiString &key, Real defaultValue) const;
	virtual Int getInt(const AsciiString &key, Int defaultValue) const;
	virtual void setBool(const AsciiString &key, Bool val);
	virtual void setReal(const AsciiString &key, Real val);
	virtual void setInt(const AsciiString &key, Int val);

	Int getStrategicScenario(void);
	void setStrategicScenario(Int scenario);
	Int rva0054F5A4(void);
	void rva0054F7C0(Int val);
	void rva0044DDFB(int *vals);
	Int rva0044D836(void);
	Int rva0044D88C(void);
	AsciiString rva0044DBA5(void);
	void rva0044DC54(Int val);
	void rva0044DCB9(Int val);
	void rva0044DD1E(Int val);
	void rva0044DD83(AsciiString val);
	void rva0044DE5A(const AsciiString &val);
	void rva0044DEC1(const AsciiString &val);

private:
	const AsciiString &makeKey(const char *key) const;

	Int m_mode;
	mutable AsciiString m_key;
};
AsciiString AsciiStringToQuotedPrintable(AsciiString original);
// ?rva0044DE5A@GameModePreferences@@QAEXABVAsciiString@@@Z, retail 0x0044DE5A
// (103 bytes, directly before the Password setter; caller 0x005A29EA): the
// same quoted-printable store under the "GameName" key.
void GameModePreferences::rva0044DE5A(const AsciiString &val)
{
	(*this)[makeKey("GameName")].setCopyInline(AsciiStringToQuotedPrintable(val));
}
void GameModePreferences::rva0044DEC1(const AsciiString &val)
{
	(*this)[makeKey("Password")].setCopyInline(AsciiStringToQuotedPrintable(val));
}
