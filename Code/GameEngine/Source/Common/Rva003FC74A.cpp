// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?createPickboxObject@LivingWorldVisual@@QAEPAVRenderObjClass@@PBVAsciiString@@@Z @0x003FC74A 54B
// Sets RenderObj at +0x14 from AsciiString name via Create_Render_Obj; empty names return 0.
// Evidence: rowed callees StringBase isEmpty 0x00001E2F Create_Render_Obj 0x00136175 and g_Rva0107301CEmptyString; sibling Rva003FC780 pattern.
#include "ascii_string.h"

class RenderObjClass;

RenderObjClass *Create_Render_Obj(const char *name);


class LivingWorldVisual
{
public:
    RenderObjClass *createPickboxObject(const AsciiString *name);
private:
    char m_pad00[20];
    RenderObjClass *m_obj;
};
RenderObjClass *LivingWorldVisual::createPickboxObject(const AsciiString *name)
{
    if (!((const StringBase<char> *)name)->isEmpty())
    {
        const char *t = *(const char * const *)name;
        const char *s = t ? t + 8 : "";
        RenderObjClass *obj = Create_Render_Obj(s);
        m_obj = obj;
        return obj;
    }
    return 0;
}
