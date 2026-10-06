// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0?$vector@VBfmeThingUBB@@V?$allocator@VBfmeThingUBB@@@_STL@@@_STL@@QAE@ABV01@@Z @0x0032BE3C 68B
// Evidence: caller 0x0032D9A4 copies vector at +0x0C (TeamsInfoRec layout map+0x00 vector+0x0C shorts+0x18/+0x1A);
// retail calls get_allocator 0x0021983A plus _Vector_base<BfmeE16> 0x00421D73 plus __uninitialized_copy<BfmeThingUBB> 0x0032AD32;
// element is 16B (sar 4) with Dict tail as SidesListTeamsInfoRecAddTeam.cpp; donor structs copied from there.

#include <vector>

class Dict
{
public:
	~Dict();
	void clear();
	void Rva00329CF0(const Dict *src);
private:
	void releaseData();
	void *m_data;
};

class BfmeThingUBB
{
public:
	BfmeThingUBB();
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	int m_generation;
	Dict m_dict;
};

template _STL::vector<BfmeThingUBB, _STL::allocator<BfmeThingUBB> >::vector(const _STL::vector<BfmeThingUBB, _STL::allocator<BfmeThingUBB> > &);
