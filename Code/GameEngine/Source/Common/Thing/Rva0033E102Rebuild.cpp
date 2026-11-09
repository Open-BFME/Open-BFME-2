// cl: /DNDEBUG /MD
//
// ?rva0033E102@@YAXPAXPAVThingTemplate@@@Z @0x0033E102 123B.
//
// Container-record rebuild: when the +0x5e9 flag is set, clear it and erase
// the +0x370 record vector, then construct a record temp (0x0033B0EF),
// fill it from arg1 (0x0033C247), push it (rowed 0x0033E080) and clear the
// +0x37c tree (rowed 0x002CF7DE). Cdecl free function; EH frame over the
// record temp whose string member tears down via the 0x36410 fold.
//
// Evidence: the erase-all reads begin/end through the vec address in ecx
// (the explicit vector pointer local reproduces the lea-first order);
// push_back takes the record by const-ref (the MyRecord-to-record cast is
// layout-only: same 12B {4, string, 4}); the record ctor/fill/erase ride
// TU-local-spelling pins. Member and pad names past the proven offsets
// carry no identity claim. The begin/end inlines emit 3-4B loads identical
// to stlport's own, so they fold at link.
class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}

private:
	void *m_data;
};

struct MyRecord
{
	MyRecord();
	void rva0033C247(void *arg);
	char m_00[4];
	Rva0033B84ETok m_text; // +4, torn down via the 0x36410 fold
	int m_08;
};

struct BfmeContainerRecord002CF46E
{
	char m_00[4];
	char m_text[4];
	int m_08;
};

namespace _STL
{
	template <class T>
	class allocator
	{
	};
	template <class T, class Ax>
	class vector
	{
	public:
		void erase(BfmeContainerRecord002CF46E *a, BfmeContainerRecord002CF46E *b);
		void push_back(const BfmeContainerRecord002CF46E &v);
		T *begin() { return _M_start; }
		T *end() { return _M_finish; }

		T *_M_start;
		T *_M_finish;
		T *_M_end;
	};
}

class Rva002CF7DE
{
public:
	void rva002CF7DE();

private:
	void *m_header;
	int m_size;
};

#include "../../../Include/Common/ThingTemplate.h"

void rva0033E102(void *arg1, ThingTemplate *thingTemplate)
{
	if (thingTemplate->m5E9 == 1) {
		_STL::vector<BfmeContainerRecord002CF46E, _STL::allocator<BfmeContainerRecord002CF46E> > *v = reinterpret_cast<_STL::vector<BfmeContainerRecord002CF46E, _STL::allocator<BfmeContainerRecord002CF46E> > *>(thingTemplate->m_weaponTemplateSets);
		thingTemplate->m5E9 = 0;
		v->erase(v->begin(), v->end());
	}

	MyRecord rec;
	rec.rva0033C247(arg1);
	reinterpret_cast<_STL::vector<BfmeContainerRecord002CF46E, _STL::allocator<BfmeContainerRecord002CF46E> > *>(thingTemplate->m_weaponTemplateSets)->push_back((const BfmeContainerRecord002CF46E &)rec);
	reinterpret_cast<Rva002CF7DE *>(thingTemplate->m_weaponTemplateSetFinder)->rva002CF7DE();
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x00036410 reads ??1?$StringBase@D@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva0033B84ETok@@QAE@XZ=??1?$StringBase@D@@QAE@XZ")
//   0x000C059B reads ?erase@?$vector@URva000B435F@@V?$allocator@URva000B435F@@@_STL@@@_STL@@QAEPAURva000B435F@@PAU3@0@Z
#pragma comment(linker, "/alternatename:?erase@?$vector@UBfmeContainerRecord002CF46E@@V?$allocator@UBfmeContainerRecord002CF46E@@@_STL@@@_STL@@QAEXPAUBfmeContainerRecord002CF46E@@0@Z=?erase@?$vector@URva000B435F@@V?$allocator@URva000B435F@@@_STL@@@_STL@@QAEPAURva000B435F@@PAU3@0@Z")
