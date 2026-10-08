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
    void Start(const UnicodeString &,int);
    void rva004E5CCB(NoticeLineInputView *);
    void AddWord(NoticeLineInputView *,int,const UnicodeString &);
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

class Display; class ClientFrameSubsystem;
extern Display *TheDisplay;
extern ClientFrameSubsystem *TheGameClient;
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
