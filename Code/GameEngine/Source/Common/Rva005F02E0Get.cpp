// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?GetButtonImage@StrategicInGameUI@@YAPBVImage@@PAX@Z @0x005F02E0 56B
// Evidence: unlock lane, prev Rva005F0220Get 0x005F0220 next rva005F05E6
// 0x005F05E6 in Common, 3 callers, callees rva002D06CA ThingTemplate
// ButtonImage flows plus tail rva0033BA46, global g_009FF000, literal none.
// Identity: WB 0x01615550 is this StrategicInGameUI::GetButtonImage overload
// (asserts at StrategicInGameUIGetButtonImage.cpp:108..115): the +0x28
// referent's template through ThingFactory::findTemplateInternal, then
// ThingTemplate::getButtonImage, falling back to the template's portrait
// (rowed 0x0033BA46), as retail does. The argument stays void*.
#include "ascii_string.h"

class Image
{
};

class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
};

extern class ThingFactory *TheThingFactory;

class ThingTemplate
{
public:
	const Image *getButtonImage();
	const Image *rva0033BA46();
};

struct Rva005F02E0Mid
{
	char m_pad[0xc];
	AsciiString m_name;
};

struct Rva005F02E0In
{
	char m_pad[0x28];
	Rva005F02E0Mid *m_mid;
};

namespace StrategicInGameUI { const Image *GetButtonImage(void *in); }
const Image *StrategicInGameUI::GetButtonImage(void *in)
{
	Rva005F02E0Mid *mid = ((Rva005F02E0In *)in)->m_mid;
	void *found;
	if (!mid || !(found = (void *)TheThingFactory->findTemplate(mid->m_name)))
		return 0;
	ThingTemplate *tmpl = (ThingTemplate *)found;
	const Image *img = tmpl->getButtonImage();
	if (img)
		return img;
	return tmpl->rva0033BA46();
}
