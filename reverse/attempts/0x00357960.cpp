// ?rva00357960@ScriptEngine@@QAEXABVAsciiString@@PAVObject@@@Z
// partial score=0.85 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O2 /DNDEBUG /MD /Oy-
// ?rva00357960@ScriptEngine@@QAEXABVAsciiString@@PAVObject@@@Z @0x00357960 163B
// ScriptEngine record set for Object indicator colors. If Object null or name
// empty return. If Object+0x88 string non-empty clear old record via rowed
// rva00203FA8 then set it. Search +0x1A120 8B records by name compare. On hit
// update color via rowed Object get/set/remove and store Object. Else return.
// Evidence: pin name callers rowed callees prev/next TU flags.
#include "ascii_string.h"

class Object
{
public:
    int getIndicatorColor() const;
    void setCustomIndicatorColor(int color);
    void removeCustomIndicatorColor();
    char m_pad00[0x88];
    StringBase<char> m_name88;
    char m_pad8C[0x30C - 0x8C];
    int m_flag30C;
};

struct Rva00357960Rec
{
    AsciiString m_name;
    Object *m_obj;
};

class ScriptEngine
{
public:
    void rva00357960(const AsciiString &name, Object *obj);
    void rva00203FA8(int needle);
private:
    char m_pad[0x1A120];
    Rva00357960Rec *m_begin;
    Rva00357960Rec *m_end;
};

void ScriptEngine::rva00357960(const AsciiString &name, Object *obj)
{
    if (!obj)
        return;
    if (name.isEmpty())
        return;
    StringBase<char> *slot = &obj->m_name88;
    if (!slot->isEmpty()) {
        rva00203FA8((int)obj);
    }
    slot->set((const StringBase<char> &)name);
    Rva00357960Rec *it = m_begin;
    for (; it != m_end; ++it) {
        if (((const StringBase<char> &)name).compare((const StringBase<char> &)it->m_name) == 0) {
            Object *cur = it->m_obj;
            if (cur) {
                if (cur->m_flag30C == 0) {
                    obj->removeCustomIndicatorColor();
                } else {
                    int c = cur->getIndicatorColor();
                    obj->setCustomIndicatorColor(c);
                }
            }
            it->m_obj = obj;
            return;
        }
    }
}
