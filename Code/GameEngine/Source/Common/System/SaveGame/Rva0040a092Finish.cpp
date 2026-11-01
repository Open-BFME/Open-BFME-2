// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?parseCommandButton@CommandSet@@SAXPAVINI@@PAXPAPBVCommandButton@@H@Z @0x0040A092 173B
// Evidence: chain lane; calls rowed findCommandButton 0x0031BE3C via g_bfmeWorldRV,
// INI getNextToken 0x2DF97 getFilename 0x2C005 getLineNum 0x2BBED, INIException
// 0x2F681 throw via pinned _CxxThrowException; stores found button into out[index];
// prev CommandSet.cpp same flags/layout.  ZH donor CommandSet::parseCommandButton
// (ControlBar.cpp) is the same token/find/store shape.  The last byte is the
// getFilename temp: writing `ini->getFilename().str()` and `ini->getLineNum()`
// inline in the throw (rather than through named locals) makes the compiler keep
// the return-value pointer in eax and reserve the 0x10-byte frame retail has.
#include "ascii_string.h"

class INI
{
public:
    const char *getNextToken(const char *delim);
    AsciiString getFilename() const;
    int getLineNum() const;
};

class CommandButton
{
};

class ControlBar
{
public:
    const CommandButton *findCommandButton(const AsciiString &name);
};

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;
extern const char g_00C39070[] = "Unknown command '%s' found in command set. File: %s Line: %d\n";

#include "../../../../Include/Common/INI/FieldParse.h"

class CommandSet
{
public:
	static void parseCommandButton(INI *ini, void *unused, const CommandButton **out, int index);
};
// WorldBuilder CommandSet::parseCommandButton, WB VA 0x00C28A00 (strings lead, score 1.0).
void CommandSet::parseCommandButton(INI *ini, void *unused, const CommandButton **out, int index)
{
    const char *token = ini->getNextToken(0);
    const CommandButton *found;
    {
        AsciiString tmp(token);
        found = ((ControlBar *)(void *)((BfmeWorldRV *)TheControlBar))->findCommandButton(tmp);
    }
    if (found == 0) {
        throw INIException(3, g_00C39070, token, ini->getFilename().str(), ini->getLineNum());
    }
    out[index] = found;
}
