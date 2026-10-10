// Native singleton VA 0x00DFE77C is GameClient.cpp's class GameClient pointer.
// cl: /O1 /G7 /arch:SSE2 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_STLP_NO_CSTD_FUNCTION_IMPORTS
// BFME1 donor: game/GameEngine/Source/GameClient/GUI/IngameNoticeDisplay.cpp
// at ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f. Its display-resource owner
// constructor is the semantic lead. Native 0x004E594E..0x004E59AE (96 bytes)
// has the same descriptor/resource/unused/identifier fields and operations;
// BFME2 creates the display through manager slot 14 rather than slot 9.
// Use BFME2's shared UnicodeString for the by-value virtual argument, so the
// receiver is reloaded after its owned 0x00037050 copy constructor.
// The 0x004E5B0A caller allocates 0x18 bytes; the last eight bytes are opaque.
// The original owner class name is unproven: retain an RVA-derived name.
// stlport
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a,const unsigned int &b)
{ return a < b ? b : a; }
}
#include <vector>
#include "unicode_string.h"
class DisplayStringManager;
struct Rva004E594EDescriptor
{
	unsigned int field0;
	unsigned int field4;
    unsigned int property() const { return field4; }
    unsigned char unknown08[16];
    unsigned int color;
};

class NoticeResource
{
public:
	virtual void f0();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText(); virtual void f3(); virtual void f4(); virtual void f5();
	virtual void setDescriptor(unsigned int value);
	virtual void f7(); virtual void f8(); virtual void f9();
	virtual void finish(int first, int second);
    virtual void f11(); virtual void f12(); virtual void f13(); virtual void f14();
    virtual void getSize(int *,int *);
    virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
    virtual void f20(); virtual void f21(); virtual void appendChar(unsigned short);
};

class NoticeManager
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
	virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13();
	virtual NoticeResource *create(void);
    virtual void release(NoticeResource *);
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva004E594E
{
public:
	Rva004E594E(const UnicodeString &text,
		Rva004E594EDescriptor *descriptor, int identifier);
private:
	Rva004E594EDescriptor *m_descriptor;
	NoticeResource *m_resource;
	unsigned int m_unused;
	int m_identifier;
    unsigned char unknown10[8];
};

Rva004E594E::Rva004E594E(
	const UnicodeString &text, Rva004E594EDescriptor *descriptor,
	int identifier)
{
	Rva004E594EDescriptor *desc = descriptor;
	m_descriptor = desc;
	m_resource = 0;
	m_unused = 0;
	m_identifier = identifier;
	m_resource = reinterpret_cast<NoticeManager *>(TheDisplayStringManager)->create();
	if (m_resource)
	{
		m_resource->setDescriptor(desc->field4);
		m_resource->setText(text);
		m_resource->finish(0, 0);
	}
}

class NoticeDescriptorLimitsView {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual unsigned int widthLimit();
};
// Native 0x004DFCB0 is the owned raw-pointer vector append. Its ModuleData
// specialization stores pointer bits without accessing the pointed-to class.
class ModuleData;
// The retail growth helper releases storage through the game allocator.
namespace _STL {
void free(void *);
template<> void vector<const ModuleData *>::_M_clear();
template<> vector<const ModuleData *>::~vector();
template<> _Vector_base<const ModuleData *,allocator<const ModuleData *> >::~_Vector_base();
// STLport's POD overflow algorithm, with retail's game free entry point.
template<> inline void vector<const ModuleData *>::_M_insert_overflow(
    const ModuleData **position, const ModuleData * const &value,
    const __true_type &, unsigned int fillLength, bool atEnd)
{
    const unsigned int oldSize=size();
    const unsigned int newLength=oldSize+(max)(oldSize,fillLength);
    pointer newStart=this->_M_end_of_storage.allocate(newLength);
    pointer newFinish=(pointer)__copy_trivial(this->_M_start,position,newStart);
    newFinish=fill_n(newFinish,fillLength,value);
    if (!atEnd) newFinish=(pointer)__copy_trivial(position,this->_M_finish,newFinish);
    if (this->_M_start) _STL::free(this->_M_start);
    _M_set(newStart,newFinish,newStart+newLength);
}
}
// Native 0x004E5B0A..0x004E5CB0 builds wrapped display rows.
// The recovered BFME1-led resource owner supplies each rendered row.
// Native retail controls wrapping and the descriptor virtual width limit.
// The caller allocates 20 bytes; the two trailing words remain opaque.
class Rva004E5B0A {
public:
    Rva004E5B0A(const UnicodeString &,Rva004E594EDescriptor *);
    void rva004E59DB();
private:
    _STL::vector<const ModuleData *> lines;
    unsigned char unknown0C[8];
};
Rva004E5B0A::Rva004E5B0A(const UnicodeString &text,Rva004E594EDescriptor *descriptor)
    : lines(_STL::allocator<const ModuleData *>())
{
    int length=text.getLength();
    if (!length) return;
    int index=0;
    NoticeResource *display=reinterpret_cast<NoticeManager *>(TheDisplayStringManager)->create();
    display->setDescriptor(descriptor->property());
    UnicodeString lineText;
    unsigned int limit=reinterpret_cast<NoticeDescriptorLimitsView *>(descriptor)->widthLimit();
    unsigned int currentWidth=limit;
    for (;index<length;) {
        unsigned short ch=text.getCharAt(index);
        ++index;
        display->appendChar(ch);
        int width,height;
        display->getSize(&width,&height);
        if ((unsigned)width>limit) {
            const ModuleData *line=reinterpret_cast<const ModuleData *>(new Rva004E594E(lineText,descriptor,currentWidth));
            lines.push_back(line);
            currentWidth=width-currentWidth;
            lineText.clear();
            lineText += ch;
            display->setText(lineText);
        } else {
            currentWidth=width;
            lineText += ch;
        }
    }
    if (lineText.getLength()) {
        const ModuleData *line=reinterpret_cast<const ModuleData *>(new Rva004E594E(lineText,descriptor,currentWidth));
        lines.push_back(line);
    }
    reinterpret_cast<NoticeManager *>(TheDisplayStringManager)->release(display);
}

// Callers expose this 24-byte line-input view; it is distinct from the row owner.
struct NoticeLineInputView {
    NoticeLineInputView(int w,int c,_STL::vector<const ModuleData *> *o,NoticeResource *d)
        :maxWidth(w),center(c),offsets(o),display(d),width(0) {}
    int maxWidth;
    int center;
    _STL::vector<const ModuleData *> *offsets;
    NoticeResource *display;
    UnicodeString text;
    int width;
};
class IngameNoticeDisplay {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void reset();
    virtual void update();
    void Start(const UnicodeString &,int);
    void rva004E5CCB(NoticeLineInputView *);
    void AddWord(NoticeLineInputView *,int,const UnicodeString &);
    void rva004E59F4();
private:
    unsigned char unknown04[8];
    Rva004E594EDescriptor *descriptor;
    _STL::vector<const ModuleData *> groups;
    int startFrame,endFrame,fadeFrame;
    float xFraction,yFraction,widthFraction;
};
// 0x004E5CCB..0x004E5D4D: WB 0x0131FFB0 call graph and field accesses.
// Both retail appends use the same owned four-byte storage operation.
void IngameNoticeDisplay::rva004E5CCB(NoticeLineInputView *line)
{
    const ModuleData *group=reinterpret_cast<const ModuleData *>(new Rva004E5B0A(line->text,descriptor));
    groups.push_back(group);
    int centered=line->center-line->width/2;
    const ModuleData *word=reinterpret_cast<const ModuleData *>(centered);
    line->offsets->push_back(word);
    line->text.clear();
    line->width=0;
}

// Native 0x004E5DB2..0x004E5EBE; WB 0x0131FCF0 names AddWord,
// IngameNoticeDisplay.cpp line 383, and proves the input/rendering fields.
void IngameNoticeDisplay::AddWord(NoticeLineInputView *line,int spaces,const UnicodeString &word)
{
    UnicodeString candidate=line->text;
    for (int count=spaces;count>0;--count) candidate+=(unsigned short)' ';
    candidate+=word;
    line->display->setText(candidate);
    int width,height;
    line->display->getSize(&width,&height);
    if (width>line->maxWidth) {
        if (!line->text.isEmpty()) {
            rva004E5CCB(line);
            line->display->setText(word);
            line->display->getSize(&width,&height);
        } else if (spaces>0) {
            AddWord(line,0,word);
            return;
        }
    }
    line->text=line->display->getText();
    line->width=width;
}

class Display; class GameClient;
extern Display *TheDisplay;
extern class GameClient *TheGameClient;
extern int g_009BA4E8;
class NoticeScreenView {
public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual unsigned int width(); virtual unsigned int height();
};
class NoticeClientView {
public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual int frame();
};
// The native temporary stores signed horizontal offsets as four-byte words.
// This local storage view uses its own template identity and game-free binding.
struct NoticeOffsetStorageWord { int value; };
namespace _STL {
template<> inline void allocator<NoticeOffsetStorageWord>::deallocate(
    NoticeOffsetStorageWord *p,unsigned int) const { if (p) _STL::free(p); }
}
struct NoticeFontView { unsigned char unknown0[16]; int height; };
struct Rva004E592CPair { int m_0,m_4; };
class Rva004E592C { public: void rva004E592C(Rva004E592CPair *); };
class Rva0048E730Layout { public: Rva0048E730Layout(int x):m_offset(x){} int m_offset; };
class Rva004E5911 { public: void rva004E5911(Rva0048E730Layout); };
class NoticeDescriptorStateView {
public:
    virtual void s0(); virtual void prepare();
};
struct NoticeTextLayout {
    struct Header { int refs; unsigned short length,allocated; unsigned short chars[1]; };
    Header *header;
    unsigned short charAt(int index) const { return header ? header->chars[index] : 0; }
};
extern "C" __declspec(dllimport) int __cdecl iswspace(unsigned short);
// Native 0x004E5EBE..0x004E61C8; WB 0x01320090 names Start at line 449.
// Retail proves reset slot 9, screen dimensions, frame timing and tokenization.
// The inline line-input initialization also emits the standalone constructor
// at 0x004E58C5..0x004E58ED, followed by its owned Unicode member destructor.
void IngameNoticeDisplay::Start(const UnicodeString &text,int duration)
{
    reset();
    UnicodeString copy=text;
    reinterpret_cast<NoticeDescriptorStateView *>(descriptor)->prepare();
    int length=copy.getLength();
    if (!length) return;
    float center=(float)(reinterpret_cast<NoticeScreenView *>(TheDisplay)->width()/2);
    int maximum=(int)(reinterpret_cast<NoticeScreenView *>(TheDisplay)->width()*widthFraction);
    startFrame=reinterpret_cast<NoticeClientView *>(TheGameClient)->frame();
    if (duration) {
        endFrame=startFrame+g_009BA4E8*duration;
        fadeFrame=endFrame-g_009BA4E8;
    } else {
        fadeFrame=startFrame+g_009BA4E8*15;
        endFrame=0;
    }
    descriptor->color=0xff000000;
    NoticeResource *display=reinterpret_cast<NoticeManager *>(TheDisplayStringManager)->create();
    if (!display) return;
    display->setDescriptor(descriptor->property());
    _STL::vector<NoticeOffsetStorageWord> offsets((_STL::allocator<NoticeOffsetStorageWord>()));
    {
        NoticeLineInputView line(maximum,(int)center,
            reinterpret_cast<_STL::vector<const ModuleData *> *>(&offsets),display);
        int spaces=0;
        UnicodeString word;
        int index=0;
        bool whitespace=true;
        unsigned short ch=reinterpret_cast<const NoticeTextLayout *>(&copy)->charAt(0);
        for (;;) {
            if (whitespace) {
                if (!iswspace(ch)) { whitespace=false; continue; }
                if (ch==' ') ++spaces;
                else if (ch=='\n') { rva004E5CCB(&line); spaces=0; }
            } else {
                if (iswspace(ch)) {
                    AddWord(&line,spaces,word);
                    spaces=0;
                    word.clear();
                    whitespace=true;
                    continue;
                }
                word+=ch;
            }
            if (++index>=length) {
                if (!whitespace) AddWord(&line,spaces,word);
                break;
            }
            ch=reinterpret_cast<const NoticeTextLayout *>(&copy)->charAt(index);
        }
        rva004E5CCB(&line);
    }
    int height=reinterpret_cast<NoticeFontView *>(descriptor->field4)->height;
    int y=(int)(reinterpret_cast<NoticeScreenView *>(TheDisplay)->height()*yFraction);
    int stamp=startFrame;
    for (const ModuleData **it=groups.begin();it!=groups.end();++it) {
        Rva004E592CPair point;
        point.m_0=(int)(reinterpret_cast<NoticeScreenView *>(TheDisplay)->width()*xFraction);
        point.m_4=y;
        y=(int)(y+height*1.25f);
        reinterpret_cast<Rva004E592C *>(const_cast<ModuleData *>(*it))->rva004E592C(&point);
        reinterpret_cast<Rva004E5911 *>(const_cast<ModuleData *>(*it))->rva004E5911(Rva0048E730Layout(stamp));
        stamp+=g_009BA4E8;
    }
    reinterpret_cast<NoticeManager *>(TheDisplayStringManager)->release(display);
}

// BF1 9cbfb551fe AnimateButtons004B1C80.cpp emits a one-word mem_fun result
// adapter with these bytes; that template and owner identity are unproven here.
// Native 004E59D0..004E59DB independently stores stackarg8 through stackarg4
// and returns that same pointer in EAX with RET0. The preceding body ends in
// RET at4E59CF and the next starts with a separate PUSH/CALL sequence. No
// literal function-pointer or direct E8/E9 references were found. Word and
// pointer types describe only the observed raw operation; original name and
// semantic type remain unknown, including any hidden result-pointer role.
unsigned int *__cdecl rva004E59D0(unsigned int *result, unsigned int value)
{
    *result = value;
    return result;
}

// Native4E59DB..4E59F4 is a complete25-byte method after RET4E59DA.
// It consumes the existing row group's pointer vector0/4 via the actual
// rowed4E59AE member-pointer foreach operation, passing the independently
// rowed4E583D frame-gated dispatch. No original wrapper name is asserted.
// These are declarations of existing opaque providers; no objects or new
// aliases are introduced. The provider's single-inheritance member pointer
// carries the observed one-word target unchanged across the opaque views.
struct Rva004E59AE { void rva(); };
class Rva004E583D { public: void rva004E583D(); };
typedef void (Rva004E59AE::*NoticeObservedMember)();
void __cdecl Rva004E59AEFunc(NoticeObservedMember *,Rva004E59AE **,
    Rva004E59AE **,NoticeObservedMember);
void Rva004E5B0A::rva004E59DB()
{
    NoticeObservedMember result;
    Rva004E59AEFunc(&result,
        reinterpret_cast<Rva004E59AE **>(const_cast<ModuleData **>(lines.begin())),
        reinterpret_cast<Rva004E59AE **>(const_cast<ModuleData **>(lines.end())),
        reinterpret_cast<NoticeObservedMember>(&Rva004E583D::rva004E583D));
}

// Complete native4E59F4..4E5A24 follows the row-group dispatch RET. Its
// vtable pointer atVA C623FC lies in the same C623CC table established by
// the owned4E5A24 constructor; descriptor+C and vector+10/+14 agree with
// this existing notice view. Original method and field meanings are unknown.
// Retail resets four descriptor words before dispatching each group through
// the actual owned4E59DB method via the existing4E59AE foreach provider.
void IngameNoticeDisplay::rva004E59F4()
{
    unsigned int *words = reinterpret_cast<unsigned int *>(descriptor);
    words[5] = ~0u;
    words[4] = ~0u;
    words[3] = 0xffffu;
    words[2] = 0xffffu;
    NoticeObservedMember result;
    Rva004E59AEFunc(&result,
        reinterpret_cast<Rva004E59AE **>(const_cast<ModuleData **>(groups.begin())),
        reinterpret_cast<Rva004E59AE **>(const_cast<ModuleData **>(groups.end())),
        reinterpret_cast<NoticeObservedMember>(&Rva004E5B0A::rva004E59DB));
}

// BF1 f989 MemFunForEachInstantiations.cpp compiled O2/x87/G7 emits
// three indistinguishable member-call adapters. That supplies the expression,
// not a target template name, element identity or original result type.
// Native 4E58BA..4E58C5 is a separate complete entry after RET 4E58B9:
// receiver word 0 is called with stack word 4 moved into ECX, no pushed
// arguments or receiver adjustment, followed by this wrapper's RET 4.
// No literal-address or direct-call references identify the callback target.
// These independent address-owned views describe only that consumed ABI.
// The single-inheritance declaration selects its witnessed one-word method
// representation; no original inheritance or complete object layout is claimed.
// A void observation ignores any physical callback result, whose type is unknown.
class __single_inheritance Rva004E58BATarget;
typedef void (Rva004E58BATarget::*Rva004E58BAMethod)();
class Rva004E58BAHolder
{
public:
    void invoke(Rva004E58BATarget *target);
private:
    Rva004E58BAMethod method;
};

void Rva004E58BAHolder::invoke(Rva004E58BATarget *target)
{
    (target->*method)();
}

// update, native 0x004E5724..0x004E57E6 (194 bytes): slot 10 of the notice
// display's table (0x008623D0 + 0x28), between the rowed reset at slot 9
// and slot 12's 0x004E59F4. Once the end frame has passed it resets (tail
// call through slot 9). While the mouse is inside the descriptor's screen
// rectangle the fade start keeps moving to the next client frame; after it,
// the colour's alpha falls linearly to zero over g_009BA4E8 frames (floored
// at 0x40 for a notice without an end frame). It then asks TheInGameUI
// (slot 109) for a redraw two logic frames ahead.
#include "../../../Source/Common/GameLogicObjectLookupView.h"
struct NoticeMouseView
{
    unsigned char unknown0000[0x4F0C];
    int x; // +0x4F0C
    int y; // +0x4F10
};
struct NoticeRectView
{
    unsigned int field0;
    unsigned int field4;
    int left, top, right, bottom; // +0x08
    unsigned int color; // +0x18
};
class NoticeInGameUIView
{
public:
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void requestRedraw(int frame);
};
class Mouse; class InGameUI;
extern Mouse *TheMouse;
extern InGameUI *TheInGameUI;
extern GameLogic *TheGameLogic;

void IngameNoticeDisplay::update()
{
    if (!startFrame)
        return;
    unsigned int now = reinterpret_cast<NoticeClientView *>(TheGameClient)->frame();
    unsigned int end = endFrame;
    if (end && end < now)
    {
        reset();
        return;
    }
    NoticeRectView *rect = reinterpret_cast<NoticeRectView *>(descriptor);
    const NoticeMouseView *mouse = reinterpret_cast<const NoticeMouseView *>(TheMouse);
    int x = mouse->x;
    int y = mouse->y;
    if (x > rect->left && x < rect->right && y > rect->top && y < rect->bottom && now > (unsigned int)fadeFrame)
        fadeFrame = now + 1;
    if (now > (unsigned int)fadeFrame)
    {
        int elapsed = now - fadeFrame;
        unsigned int alpha;
        if (elapsed > g_009BA4E8)
            alpha = 0;
        else
            alpha = 255 - elapsed * 255 / g_009BA4E8;
        if (!end && alpha < 0x40)
            alpha = 0x40;
        rect->color = alpha << 24;
    }
    else
        rect->color = 0xFF000000;
    reinterpret_cast<NoticeInGameUIView *>(TheInGameUI)->requestRedraw(TheGameLogic->getFrame() + 2);
}
