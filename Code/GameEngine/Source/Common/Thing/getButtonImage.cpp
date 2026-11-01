// cl: /MD
// ?getButtonImage@@YAPBVImage@@PAVThingTemplate@@PAVObject@@@Z @0x0033B634 67B linkbody
// Evidence: LINK 2 files wait via 0x00525CC5; tail-jmp row getButtonImage ThingTemplateButtonImage; pin rva002197A6 via TheCreateAHeroManager same pattern as Rva0028F2F8; 8 callers; prev next same Thing dir
struct Rva0028F2F8Aux {
	unsigned char m_pad[0x11F];
	unsigned char m_11F;
};
// The rowed lookup ?rva002197A6@CreateAHeroManager@@QAEPAVCreateAHeroData@@H@Z.
class CreateAHeroData;
#include "../../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;
class Object {
public:
	unsigned char m_pad00[4];
	Rva0028F2F8Aux *m_04;
	unsigned char m_pad08[0x74 - 0x8];
	int m_74;
};
class Image;
#include "../../../Include/Common/ThingTemplate.h"
const Image *getButtonImage(ThingTemplate *thingTemplate, Object *object)
{
	if (thingTemplate == 0 || object == 0)
		return 0;
	if ((object->m_04->m_11F & 0x40) == 0)
		goto fallback;
	{
		void *r = TheCreateAHeroManager->rva002197A6(object->m_74);
		if (r == 0)
			goto fallback;
		void *img = *(void **)((char *)r + 0x13c);
		if (img != 0)
			return (const Image *)img;
	}
fallback:
	return thingTemplate->getButtonImage();
}
