// cl: /O1 /G7 /arch:SSE /Oy- /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Target3B3989..3B39B2 and3B3AB9..3B3AE2 are complete41B RET4 leaves.
// Each uses receiver's signed ID4 to select the appropriate rowed script
// template, then copy-returns its string4 through rowed StringBase copy365F0.
// ZH Scripts.cpp's Condition/ScriptAction template selection supplies the
// source lead; the original target getter/receiver names remain unknown.
// Borrowed receiver/template prefixes model accesses only, not full sizes.
#include "ascii_string.h"
class ConditionTemplate;
class ActionTemplate;
class ScriptEngine {
public:
    const ConditionTemplate *getConditionTemplate(int);
    const ActionTemplate *getActionTemplate(int);
};
extern ScriptEngine *TheScriptEngine;
struct Rva003B3989TemplatePrefix {
    unsigned int unknown00;
    AsciiString text;
};
struct Rva003B3989ConditionPrefix {
    unsigned int unknown00;
    int id;
    AsciiString text() const;
};
struct Rva003B3AB9ActionPrefix {
    unsigned int unknown00;
    int id;
    AsciiString text() const;
};
AsciiString Rva003B3989ConditionPrefix::text() const {
    const ConditionTemplate *selected=TheScriptEngine->getConditionTemplate(id);
    return ((const Rva003B3989TemplatePrefix *)selected)->text;
}
AsciiString Rva003B3AB9ActionPrefix::text() const {
    const ActionTemplate *selected=TheScriptEngine->getActionTemplate(id);
    return ((const Rva003B3989TemplatePrefix *)selected)->text;
}
