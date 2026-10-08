// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_STLP_NO_CSTD_FUNCTION_IMPORTS
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
