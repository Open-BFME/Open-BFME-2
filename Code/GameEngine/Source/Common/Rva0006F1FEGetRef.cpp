// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 0x0006F1FE..0x0006F219, 27B, RET4 (hidden return slot). Returns a new
// counted reference to the rendering method held at +0x40 of the shroud (null
// stays null, otherwise its count at +4 is incremented); the 0x6F219 add
// routine follows it. The receiver is W3DShroud and the result
// RefCountPtr<FXShader::RenderingMethod>, as the pinned REL32 callers
// W3DPropBuffer::drawProps (0x000EE7A9, TheTerrainRenderObject +0x3878) and
// RTS3DScene::renderOneObject spell it; the method name stays address-derived.
// RefCountClass and RefCountPtr are RTS3DSceneRenderOneObject.cpp's views, so
// the inline copies this unit emits are that unit's.
#include "../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr(void) { if (Referent) Referent->Release_Ref(); }
private:
	T *Referent;
};

namespace FXShader { class RenderingMethod : public RefCountClass {}; }

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DShroudClass.h"

RefCountPtr<FXShader::RenderingMethod> W3DShroud::rva0006F1FE(void)
{
	return *reinterpret_cast<const RefCountPtr<FXShader::RenderingMethod> *>(&m_renderingMethod);
}
