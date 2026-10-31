// cl: /MD
// ?rva006FE400@Rva006FE400@@QAEHPAXPAURva008A4570Owner@@@Z @0x006FE400 42B
// Evidence: chain from 0x0070DFB0 landing; calls virtual slot 7 (0x1C) on this+0x20
// with same args then rowed 0x0070DFB0 on this; test-je shares int return; ret 8.
#include "AptObject/AptScriptFunction.h"
struct Rva008A4570Owner;

class Rva006FE400 {
    char m_pad[0x20];
    AptValue *m_stringObject;
public:
    int rva006FE400(void *context, Rva008A4570Owner *memberName);
};

int Rva006FE400::rva006FE400(void *context, Rva008A4570Owner *memberName)
{
    int memberValue = (int)m_stringObject->objectMemberLookup((AptValue *)context, (const EAStringC *)memberName);
    if (memberValue)
        return memberValue;
    return (int)((AptObject *)this)->AptObject::objectMemberLookup((AptValue *)context, (const EAStringC *)memberName);
}
