// ?addBuff@W3DBuffBuffer@@QAEPAVTBuff@@PAVDrawable@@PBUBuffInfoView@@@Z
// partial score=0.86 date=2026-10-09
// Identity: WB 0x00836A90 names W3DBuffBuffer::addBuffType at W3DBuffBuffer.cpp
// lines 872..882; the native 0x000D21B5..0x000D2294 body has the same calls,
// branches and ten 12-byte entries at +0x18, with count at +0x90.
// The view names below describe only consumed storage and virtual slots.
// Target uses Display slot +0x88 (WB +0x8C), render class IDs 25/0 at +0x0C,
// The caller passes info's AsciiString +8 by reference as the model argument.
// info's AsciiString +8 and byte +C, and direct StringBase cleanup 0x36410.
// No clean BFME1 or ZH W3DBuffBuffer donor was found at BFME1 9cbfb551fe.
// This is retail/WB reconstruction; the original info type is unidentified.
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
#include "ascii_string.h"
#include <set>
class Drawable;
class TBuff {
    unsigned char storage[0x58];
public:
    TBuff(Drawable *, int);
};
struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *> BuffPointerSetView;
template <> _STL::pair<BuffPointerSetView::iterator, bool>
BuffPointerSetView::insert(Rva001408C0Target *const &);
class Display;
extern Display *TheDisplay;
class RenderObjClass;
extern RenderObjClass *Create_Render_Obj(const char *);
struct BuffDisplaySlots {
    virtual void slot00();
    virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33();
    virtual AsciiString resolveModel(const AsciiString &);
};
struct BuffRenderSlots {
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual int classID();
};
struct BuffInfoView { unsigned char unknown[8]; AsciiString name; bool flag; };
struct BuffTypeView { RenderObjClass *render; AsciiString name; bool flag; };
class W3DBuffBuffer {
    unsigned char unknown[0x18];
    BuffTypeView types[10];
    int count;
    BuffPointerSetView buffs[10];
    bool enabled;
public:
    TBuff *addBuff(Drawable *, const BuffInfoView *);
    int addBuffType(const AsciiString &, const BuffInfoView *);
};
int W3DBuffBuffer::addBuffType(const AsciiString &model, const BuffInfoView *info) {
    if (count >= 10) return 0;
    types[count].render = 0;
    AsciiString name = reinterpret_cast<BuffDisplaySlots *>(TheDisplay)->resolveModel(model);
    RenderObjClass *render = Create_Render_Obj(name.str());
    if (!render) return 0;
    BuffRenderSlots *slots = reinterpret_cast<BuffRenderSlots *>(render);
    if (slots->classID() == 25 || slots->classID() == 0) types[count].render = render;
    types[count].name = info->name;
    types[count].flag = info->flag;
    ++count;
    return count - 1;
}

// WB 0x836DA0 names addBuff; retail D3B27..D3BFD uses 0x58-byte TBuff,
// descriptors +18 and pointer sets +94 (12 bytes each), gate byte +10C.
// The pointer set view reuses the existing rowed 80691 insert instantiation:
// all consumed values are pointers and no target-object fields are accessed.
TBuff *W3DBuffBuffer::addBuff(Drawable *drawable, const BuffInfoView *info) {
    if (!drawable || !enabled) return 0;
    int index = -1;
    for (int i = 0; i < count; ++i) {
        if (types[i].name.compareNoCase(info->name) == 0) {
            index = i;
            break;
        }
    }
    if (index < 0) index = addBuffType(info->name, info);
    if (index < 0) return 0;
    BuffPointerSetView *set = &buffs[index];
    if (set->size() >= 1000) return 0;
    TBuff *buff = new TBuff(drawable, index);
    Rva001408C0Target *pointer = reinterpret_cast<Rva001408C0Target *>(buff);
    set->insert(pointer);
    return buff;
}
