// cl: /O1 /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
//
// ?rva00376C50@Rva00376C50Owner@@QAEIAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@AAV?$vector@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@3@@Z
// retail 0x00376C50, 82B, ret 8.
// Walks the owner's AsciiString vector (begin +8, end +0xC), resolves each name
// through the rowed ThingFactory::findTemplate 0x002D06CA on the 0x00DFF000 registry,
// appends every hit to the first vector through the rowed pointer push_back 0x004DFCB0,
// then sizes the second vector to the result through the rowed Drawable-pointer
// resize 0x000E6D39 and returns the count. The element type of the first vector is
// the rowed ModuleData-pointer instantiation (an ICF-shared address); the receiver's
// own name is not recovered.
#include <vector>
#include "ascii_string.h"

class Drawable;
class ModuleData;
class ThingTemplate;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

_STLP_BEGIN_NAMESPACE
template <>
class vector<Drawable *, allocator<Drawable *> > : public _Vector_base<Drawable *, allocator<Drawable *> >
{
public:
	void resize(unsigned int n, Drawable *x);
};
_STLP_END_NAMESPACE

typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > ModulePtrVector;
typedef _STL::vector<Drawable *, _STL::allocator<Drawable *> > DrawablePtrVector;

class Rva00376C50Owner
{
public:
	unsigned int rva00376C50(ModulePtrVector &found, DrawablePtrVector &slots);

private:
	int m_pad0;
	int m_pad4;
	AsciiString *m_namesBegin;
	AsciiString *m_namesEnd;
};

unsigned int Rva00376C50Owner::rva00376C50(ModulePtrVector &found, DrawablePtrVector &slots)
{
	for (AsciiString *name = m_namesBegin; name != m_namesEnd; ++name)
	{
		const ModuleData *data = (const ModuleData *)TheThingFactory->findTemplate(*name);
		if (data)
			found.push_back(data);
	}
	unsigned int count = (unsigned int)(found.size());
	slots.resize(count, 0);
	return count;
}
