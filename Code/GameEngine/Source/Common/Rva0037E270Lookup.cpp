// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ?getThingTemplate@UnitRevivalEntry@@QAEPAXXZ retail 0x0037E270 25 bytes.
// Null-checked global lookup via 0x00DFF000 plus AsciiString at +0xd4.
// Returns 0 when global null else rowed 0x002D06CA result. Callers
// 0x002E1A25 0x0037E3F6 0x0037E7B4 0x0037E93E 0x0037EB8C 0x0037EFB9
// 0x004067DD. Flags from sibling Rva002D06CAGet without EHsc.
#include "ascii_string.h"
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *key); };
#define TheRva00DFF000 (*(Rva002D06CA **)0x00DFF000)
struct Rva0037E3D9Def
{
	char m_pad00[0x4DC];
	float m_float4DC;
	char m_pad4E0[0x5DA - 0x4E0];
	unsigned short m_word5DA;
};
class UnitRevivalEntry {
    char m_pad00[0x94];
    int m_94;
    char m_pad98[4];
    int m_9C;
    bool m_A0;
    char m_padA1[0xD4 - 0xA1];
    AsciiString m_str;
public:
    void *getThingTemplate();
    void setThingTemplateName(const AsciiString &arg);
};
void *UnitRevivalEntry::getThingTemplate()
{
    Rva002D06CA *mgr = TheRva00DFF000;
    if (mgr == 0)
        return 0;
    return mgr->rva002D06CA((const AsciiString *)((char *)this + 0xd4));
}
void UnitRevivalEntry::setThingTemplateName(const AsciiString &arg)
{
    m_str = arg;
    if (m_A0)
        return;
    void *def = getThingTemplate();
    if (!def)
        return;
    m_94 = ((Rva0037E3D9Def *)def)->m_word5DA;
    m_9C = (int)((Rva0037E3D9Def *)def)->m_float4DC;
}
