// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii
// Target 0040351C..0040360E; WB E90720 identifies the named FieldParse
// callback and AttributeModifier.cpp source. Native +CC owns an 8-byte
// upgrade pointer/delay pair. This is the same record cleanup established by
// 004043FF; the original pair type name is unresolved. Native preserves a
// 16-bit narrowed ceil result in the four-byte delay slot.
// The parser family in INI_parseDurationUnsignedShort.cpp supplies the
// already verified scale/import/unsigned conversion shape, not class identity.
#include "ascii_string.h"
#include <string.h>
extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern float g_parseDurationMsecScale;
class UpgradeTemplate;
class UpgradeCenter {
public: const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;
class INI {
public:
    const char *getNextToken(const char *seps);
    const char *getNextTokenOrNull(const char *seps);
    unsigned scanUnsignedInt(const char *token);
    const char *getSepsColon() const { return m_sepsColon; }
private:
    char m_pad[0x420]; const char *m_sepsColon;
};
struct DelayedModifierUpgrade {
    DelayedModifierUpgrade() : upgrade(0), delay(0) {}
    const UpgradeTemplate *upgrade;
    unsigned delay;
};
class AttributeModifierContainer {
public:
    static void parseDelayedUpgradeTemplate(INI *ini, void *instance, void *store, const void *userData);
private:
    char m_pad[0xCC];
    DelayedModifierUpgrade *m_upgrade;
};
void AttributeModifierContainer::parseDelayedUpgradeTemplate(INI *ini, void *instance, void *, const void *)
{
    const char *token = ini->getNextToken(0);
    if (!TheUpgradeCenter) return;
    AttributeModifierContainer *me = (AttributeModifierContainer *)instance;
    me->m_upgrade = new DelayedModifierUpgrade;
    me->m_upgrade->upgrade = TheUpgradeCenter->findUpgrade(AsciiString(token));
    token = ini->getNextTokenOrNull(ini->getSepsColon());
    if (token && strcmp(token, "Delay") == 0) {
        token = ini->getNextToken(0);
        if (token) {
            unsigned value = ini->scanUnsignedInt(token);
            me->m_upgrade->delay = (unsigned short)ceil(g_parseDurationMsecScale * (float)value);
        }
    }
}
