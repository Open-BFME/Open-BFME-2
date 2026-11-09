// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// NON-RETAIL shim for the allocator family (P78), a labelled step and not a recovered form. This unit's kept STL copies
// allocate from the game's table, so they must free there too, and /D_CRTIMP= would also rebind the imports its rows
// need. While the STL headers parse, free names a local inline to that table; those copies call it directly where
// retail's call _free. Retired when the real allocator headers give this unit retail's _free binding, or when these
// copies are no longer kept from this unit (P75). If anything odd happens under the STL headers, look here first.
#include <malloc.h>
#include <stdlib.h>
extern "C" void (__cdecl *__gameMemFreePtr)(void *, int);
inline void bfmeGameFree(void *block) { __gameMemFreePtr(block, 3); }
#define free bfmeGameFree
// stlport
// Clean BFME1 semantic guide: 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// EmotionTrackerUpdateModuleDataParseAddEmotion.cpp (RVA 00290520).
// Target: WB 0122FC70 names IniParseAddEmotion; native 004B2087..004B21B9
// has the same grammar/copy/override flow, a 190-byte template, flag at 18D,
// and the module-data pointer vector at 34. Record methods retain their
// existing provider names rather than asserting the original class spelling.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
#include <vector>
#include <string.h>
#include "ascii_string.h"

#include "../../../../Include/Common/INI/INI.h"
#include "../../../../Include/Common/INI/FieldParse.h"
// Existing lookup ABI spelling; the retained temporary is an AsciiString.
class BfmeEmotionName;
class EmotionNugget;
#include "../../../../Include/GameLogic/EmotionSystem.h"
#undef free
extern EmotionSystem *TheEmotionSystem;

// The verified ctor/copy own this record; only its name and override flag
// are accessed here. The middle includes nontrivial strings and flag blocks.
class Rva004DC920 {
public:
    Rva004DC920();
    void rva004DC788(const Rva004DC920 &);
    AsciiString name;
    unsigned char middle[0x18d-4];
    bool isOverride;
    unsigned char tail[2];
};
class Rva004DCAD2 { public: void rva004DCAD2(INI *); };
class EmotionTrackerUpdateModuleData {
public:
    static void IniParseAddEmotion(INI *, void *, void *, const void *);
    unsigned char prefix[0x34];
    _STL::vector<Rva004DC920 *> entries;
};

void EmotionTrackerUpdateModuleData::IniParseAddEmotion(INI *ini, void *, void *store, const void *)
{
    EmotionTrackerUpdateModuleData *data = (EmotionTrackerUpdateModuleData *)store;
    const char *token = ini->getNextToken();
    bool hasOverride = false;
    if (token != 0) {
        if (_strcmpi(token, "override") == 0) {
            hasOverride = true;
            token = ini->getNextToken();
        }
    }
    if (token == 0)
        throw INIException(3, "Emotion name or 'OVERRIDE <Emotion name>' expected.");
    Rva004DC920 *source = (Rva004DC920 *)TheEmotionSystem->findNugget(reinterpret_cast<const BfmeEmotionName &>(AsciiString(token)));
    if (source == 0)
        throw INIException(3, "Emotion not found");
    Rva004DC920 *copy = new Rva004DC920;
    copy->rva004DC788(*source);
    copy->name.setCopyInline(AsciiString(token));
    if (hasOverride) {
        ((Rva004DCAD2 *)copy)->rva004DCAD2(ini);
        copy->isOverride = true;
    }
    data->entries.push_back(copy);
}
