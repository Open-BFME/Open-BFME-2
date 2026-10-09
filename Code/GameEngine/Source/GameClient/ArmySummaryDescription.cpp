// cl: /O1 /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// ??0Rva00220B04@@QAE@H@Z, retail 0x00220B04 124B.
// Constructor and destructor share the native 36-byte layout: owning ASCII
// strings at +8, integer category counts at +0x14, rule at +0x20, tables at +0/+4.
// The 12-byte category records are counted through the existing global view.
// The existing Drawable-pointer resize has the same four-byte zero-value ABI.
// Callers 0x00220B80
// and 0x00220E30 construct and destroy this same stack object. Evidence:
// Native destructor 0x00220AA6..0x00220AEB calls the actual ASCII-vector
// destructor 0x0002CC70 and frees the count storage, restoring 0x00C1C780.
// Rowed Vector_base 0x00211E58 is a verified fold for both member types.
// rowed Drawable resize 0x000E6D39, holder g_00DFE490.
#include <vector>
#include "ascii_string.h"
extern const void *const g_00C1C780[];


class Drawable;

extern const void *const g_00BE6A68[];
extern const void *const g_00BE6A64[];
extern "C" char s_slot3E4first;
extern void *g_00DFE490;

_STLP_BEGIN_NAMESPACE
template <>
class vector<Drawable *, allocator<Drawable *> > : public _Vector_base<Drawable *, allocator<Drawable *> >
{
public:
	void resize(unsigned int n, Drawable *x);
};
_STLP_END_NAMESPACE

struct LocomotorStore12 { char d[12]; };
struct Pointed10 {
	char m_pad[16];
	LocomotorStore12 *m_begin;
	LocomotorStore12 *m_finish;
};

class EmptyBase220B04 {
public:
	EmptyBase220B04() {}
	~EmptyBase220B04() { *(unsigned *)this = (unsigned)g_00C1C780; }
};

struct Root220B04 {
	unsigned m_v0;
	unsigned m_v4;
	Root220B04()
	{
		*(volatile unsigned *)&m_v4 = (unsigned)&s_slot3E4first;
	}
};

struct Base220B04 : public Root220B04 {
    ~Base220B04() {}
	Base220B04()
	{
		m_v0 = (unsigned)g_00BE6A68;
		m_v4 = (unsigned)g_00BE6A64;
	}
};

class Rva00220B04 : public EmptyBase220B04, public Base220B04 {
public:
	Rva00220B04(int a);
    ~Rva00220B04();
public:
	_STL::vector<AsciiString> m_vec08;
	_STL::vector<int> m_vec14raw;
	int m_20;
};

Rva00220B04::Rva00220B04(int a)
	: EmptyBase220B04(),
	  Base220B04(),
	  m_vec08(_STL::allocator<AsciiString>()),
	  m_vec14raw(_STL::allocator<int>())
{
	m_20 = a;
	Pointed10 *p = *(Pointed10 **)&g_00DFE490;
	int count = (int)(p->m_finish - p->m_begin);
	((_STL::vector<Drawable *, _STL::allocator<Drawable *> > *)&m_vec14raw)->resize((unsigned)count, (Drawable *)0);
}

// ?g_00DFE490@@3PAXA: matched references place it at VA 0xdfe490; also referenced as ?g_00DFE490@@3VRva00575674@@A.
void * g_00DFE490 = 0;

Rva00220B04::~Rva00220B04() {}

#include "unicode_string.h"
#include "../Common/BattlePromptCounterView.h"
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
class ThingFactory;
extern ThingFactory *TheThingFactory;
class GameTextInterface;
extern GameTextInterface *TheGameText;
class DescriptionTextView {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13();
    virtual UnicodeString fetchName(const AsciiString *, bool *);
    virtual UnicodeString fetchText(const char *, bool *);
};
struct DescriptionCategory {
    AsciiString singular,plural;
    int unknown;
};
struct DescriptionDataView {
    char pad[16];
    _STL::vector<DescriptionCategory> categories;
};
struct DescriptionTemplateView { char pad[0x58]; UnicodeString displayName; };
class Rva0037DCA5 { public: void *rva0040C64A(); };
void Rva00220DCDInit();
static void BuildDescriptionString(UnicodeString *result, Rva00220B04 *items)
{
    if(!items->m_vec08.empty()) {
        int count=items->m_vec08.size();
        for(int i=0;i<count;++i) {
            DescriptionTemplateView *thing=(DescriptionTemplateView *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&items->m_vec08[i]);
            if(!result->isEmpty()) result->concat((const unsigned short *)L", ");
            result->concat(thing->displayName);
        }
    }
    int categories=items->m_vec14raw.size();
    for(int i=0;i<categories;++i) {
        int count=items->m_vec14raw[i];
        if(count>0) {
            const DescriptionCategory &category=((DescriptionDataView *)g_00DFE490)->categories[i];
            UnicodeString text=((DescriptionTextView *)TheGameText)->fetchText("BANNERUI:SummaryUnitQuantity",0);
            const AsciiString *label=count==1 ? &category.singular : &category.plural;
            text.format(text.str(),((DescriptionTextView *)TheGameText)->fetchName(label,0).str());
            text.format(text.str(),count);
            if(!result->isEmpty()) result->concat((const unsigned short *)L"\n");
            result->concat(text);
        }
    }
}
UnicodeString GetArmySummaryEntryDescription(Rva0037DCA5 *entry,int rule)
{
    switch(rule) {
    case 0: {
        Rva00220B04 items(0);
        ((Rva0040CFC7Pred *)&items)->rva005FED99((Rva005FED99Arg *)entry);
        UnicodeString result;
        BuildDescriptionString(&result,&items);
        return result;
    }
    case 1: return *(UnicodeString *)entry->rva0040C64A();
    default: return UnicodeString::TheEmptyString;
    }
}
UnicodeString GetArmySummaryDescription(Rva0040CFC7 *army,int rule)
{
    if(!g_00DFE490) Rva00220DCDInit();
    Rva00220B04 items(rule);
    army->rva0040CFC7((Rva0040CFC7Pred *)&items);
    UnicodeString result;
    BuildDescriptionString(&result,&items);
    return result;
}

