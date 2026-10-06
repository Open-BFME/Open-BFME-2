// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?cacheButtonImage@CommandButton@@QAEXXZ @0x0035B77D 92B: image-name array resolve loop
// over AsciiString slots [+0xB4,+0xB8) pushing found Images into the ModuleData
// vector at +0xEC then clearing each slot. Skips empty names and misses via
// rowed isEmpty 0x00001E2F plus rowed findImageByName 0x002D92F6 plus rowed
// push_back plus rowed releaseBuffer 0x00036410 plus global 0x00DFF078.
// Evidence: ECX=this plus void ret plus same four callees plus global as
// sibling Rva0026F216ImageResolve; caller 0x0031AC39 walks +0x18 list calling this.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

#include "ascii_string.h"


class ModuleData
{
};

class Image : public ModuleData
{
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class CommandButton
{
public:
	void cacheButtonImage();
private:
	char m_pad00[0xB4];
	AsciiString *m_b4begin;
	AsciiString *m_b8end;
	char m_padBC[0xEC - 0xBC];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_ec;
};

void CommandButton::cacheButtonImage()
{
	if (TheMappedImageCollection != 0)
	{
		for (AsciiString *it = m_b4begin; it != m_b8end; ++it)
		{
			if (!it->isEmpty())
			{
				const ModuleData *found = TheMappedImageCollection->findImageByName(*it);
				if (found != 0)
					m_ec.push_back(found);
				it->clear();
			}
		}
	}
}
