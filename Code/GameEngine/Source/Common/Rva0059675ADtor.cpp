// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1FadeInTextRender@@UAE@XZ @0x0059675A 89B
// Dtor with EH frame: vptr store, delete of interface ptr at +0x1c via virtual
// slot0 plus operator delete, StringBase<char> at +0x24 via releaseBuffer,
// then base vtable store. Empty body plus delete.
// Evidence: mov [esi] 0x00870A70, virtual call [eax] with push 0, call delete
// at 0x2FD60, lea ecx [esi+24] call 0x36410, mov [esi] 0x00870A5C.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"
#include "ascii_string.h"


class Text004721F0;
struct ICoord2D;
class GameFont;
class Anim2D;
class Rva0059675ABase
{
public:
    virtual ~Rva0059675ABase();
    virtual void LoadAssets() = 0;
    virtual void rva00596908(Text004721F0 *text, const ICoord2D *pos, unsigned frame) = 0;
    virtual int rva002A98A7() const = 0;
    virtual int rva005C4ACD() const = 0;
};struct Rva0059675AInner
{
	virtual void *slot0(int flag);
};
class Text004721F0;
struct ICoord2D;
struct FadeInTextRender : Rva0059675ABase
{
    FadeInTextRender();
    virtual ~FadeInTextRender();
    virtual void LoadAssets();
    virtual void rva00596908(Text004721F0 *text, const ICoord2D *pos, unsigned frame);
    virtual int rva002A98A7() const { return width; }
    virtual int rva005C4ACD() const { return delay; }
    void bfmeExtend(int left, int top, int right, int bottom);
    GameFont *font;
    int m_bfmeLeft, m_bfmeTop, m_bfmeRight, m_bfmeBottom;
    unsigned effectColor;
    Anim2D *anim;
    float scale;
    AsciiString fontName;
    unsigned color;
    int delay;
    unsigned fontSize;
    unsigned starts[3], ends[3];
    int width, height;
};Rva0059675ABase::~Rva0059675ABase()
{
}
FadeInTextRender::~FadeInTextRender()
{
	void *tmp = anim ? reinterpret_cast<Rva0059675AInner *>(anim)->slot0(0) : 0;
	::operator delete(tmp);
	anim = 0;
}
