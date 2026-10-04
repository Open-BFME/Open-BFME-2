// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

AsciiString AsciiStringToQuotedPrintable(AsciiString original);

struct PreferenceNode
{
	char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();
	PreferenceNode *end() const
	{
		return m_end;
	}

private:
	PreferenceNode *m_end;
};

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class QuickMatchPreferences : public UserPreferences
{
public:
	Bool isMapSelected(const AsciiString &mapName);
};

// ?isMapSelected@QuickMatchPreferences@@QAE_NABVAsciiString@@@Z
Bool QuickMatchPreferences::isMapSelected(const AsciiString &mapName)
{
	Int ret;
	PreferenceNode *it = find(AsciiStringToQuotedPrintable(mapName));
	if (it == end())
	{
		return true;
	}

	ret = atoi(it->m_value.str());

	return (ret != 0);
}
