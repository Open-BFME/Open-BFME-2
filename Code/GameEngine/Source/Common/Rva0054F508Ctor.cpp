// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva0054F508@@QAE@H@Z retail 0x0054F52F 117B.
// Custom profile preferences ctor over GameModePreferences: formats
// "%s\CustomPref%d.ini" with "Online Files" and GameSpy profile id, then loads.
// Evidence: vtable 0x0086AA60 stored at [this]; base ctor 0x0044D54B;
// format 0x00038150; load 0x003B1A09; releaseBuffer 0x00036410;
// GameSpy slot 0x7C getLocalProfileID via global 0x00A02320; callers
// 0x0038558A 0x003855AB 0x00387109 0x0038FB76 0x005A5C3C; deleting dtor
// 0x0054F513 in Rva0044D56ADerived.cpp.
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

private:
	const AsciiString &makeKey(const char *key) const;

	Int m_mode;
	mutable AsciiString m_key;
};

#include "../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva0054F508 : public GameModePreferences
{
public:
	Rva0054F508(Int mode);
	virtual ~Rva0054F508();
};

Rva0054F508::Rva0054F508(Int mode) : GameModePreferences(mode)
{
	AsciiString userPrefFilename;
	userPrefFilename.format("%s\\CustomPref%d.ini", "Online Files", TheGameSpyInfo->getLocalProfileID());
	load(userPrefFilename);
}
