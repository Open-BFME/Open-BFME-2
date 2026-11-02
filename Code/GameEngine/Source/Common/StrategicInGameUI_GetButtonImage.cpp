// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?GetButtonImage@StrategicInGameUI@@YAPBVImage@@PAX@Z @0x005F02E0 56B
// Evidence: unlock lane, prev Rva005F0220Get 0x005F0220 next GetBuildPlotByIndex
// 0x005F05E6 in Common, 3 callers, callees rva002D06CA ThingTemplate
// ButtonImage flows plus tail rva0033BA46, global g_009FF000, literal none.
// Identity: WB 0x01615550 is this StrategicInGameUI::GetButtonImage overload
// (asserts at StrategicInGameUIGetButtonImage.cpp:108..115): the +0x28
// referent's template through ThingFactory::findTemplateInternal, then
// ThingTemplate::getButtonImage, falling back to the template's portrait
// (rowed 0x0033BA46), as retail does. The argument stays void*.
#include "ascii_string.h"

#include "../../Include/GameClient/ImageClass.h"

class ThingTemplate;
#include "../../Include/Common/ThingFactory.h"

extern class ThingFactory *TheThingFactory;

#include "../../Include/Common/ThingTemplate.h"

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
	ThingTemplate *thingTemplate = (ThingTemplate *)found;
	const Image *img = thingTemplate->getButtonImage();
	if (img)
		return img;
	return thingTemplate->rva0033BA46();
}
