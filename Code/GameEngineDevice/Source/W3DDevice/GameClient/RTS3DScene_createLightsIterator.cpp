// cl: /DNDEBUG /MD /EHsc

#include "../../../Include/W3DDevice/GameClient/RTS3DScene.h"

RefMultiListIterator<RenderObjClass> *RTS3DScene::createLightsIterator()
{
	return new RefMultiListIterator<RenderObjClass>(&LightList);
}
