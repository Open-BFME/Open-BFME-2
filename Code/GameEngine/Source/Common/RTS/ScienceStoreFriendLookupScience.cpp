// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
// ?friend_lookupScience@ScienceStore@@QBE?AW4ScienceType@@PBD@Z @0x1FF65D
// (81B): ScienceStore::friend_lookupScience, ZH Science.cpp verbatim (public
// const): NAMEKEY the name, isValidScience (row) or INIException(3, ...) via
// the shared filler plus _CxxThrowException. DEBUG_CRASH vanishes in NDEBUG.
// Throw-info anchor is TU-local sacrificial (DIR32 auto-patches, content
// unchecked -- INI_scanReal idiom).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class AsciiString;
class UnicodeString;
class ScienceInfo;
class Player;
class Rva0043D3A8;

class NameKeyGenerator
{
public:
    const AsciiString &keyToName(NameKeyType key);
    NameKeyType nameToKey(const AsciiString &str);
    NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ScienceStore
{
    const ScienceInfo *findScienceInfo(ScienceType st) const;
    bool rva000E7C20SciencePrereqMemo(const Player *player, ScienceType st,
        void *memo) const;
public:
    bool isScienceGrantable(ScienceType st) const;
    bool playerHasPrereqsForScience(const Rva0043D3A8 *holder, ScienceType science) const;
    int getSciencePurchaseCost(ScienceType science) const;
    bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const;
    bool isValidScience(ScienceType st) const;
    ScienceType friend_lookupScience(const char *scienceName) const;
    AsciiString getInternalNameForScience(ScienceType science) const;
    bool playerHasRootPrereqsForScience(const Player *player, ScienceType st) const;
    bool getNameAndDescription(ScienceType st, UnicodeString &name,
        UnicodeString &description) const;
    ScienceType getScienceFromInternalName(const AsciiString &name) const;
};
struct INIException
{
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

struct FriendLookupThrowInfoAnchor { int a; int b; int c; int d; };
static const FriendLookupThrowInfoAnchor friendLookupThrowInfoAnchor = { 0, 0, 0, 0 };

// ?friend_lookupScience@ScienceStore@@QBE?AW4ScienceType@@PBD@Z
ScienceType ScienceStore::friend_lookupScience(const char *scienceName) const
{
	NameKeyType nkt = TheNameKeyGenerator->nameToKey(scienceName);
	ScienceType st = (ScienceType)nkt;
	if (!isValidScience(st))
	{
		INIException e(3, "Science name %s not known! (Did you define it in Science.ini?)", scienceName);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&friendLookupThrowInfoAnchor); __assume(0);
	}
	return st;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?lookupScience@ScienceStore@@QBE?AW4ScienceType@@PBD@Z=?friend_lookupScience@ScienceStore@@QBE?AW4ScienceType@@PBD@Z")
