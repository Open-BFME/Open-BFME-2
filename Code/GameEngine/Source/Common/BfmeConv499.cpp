// cl: /O1 /MD /EHsc /DNDEBUG
// Existing EF966..EF981 27B owner initialized one owned texture word.
// Native6B3F3 constructs that frame object, passes its returned address to
// counted-holder assignment, then conditionally releases it under EH2.
// BFME1 f989 BaseHeightMapRva006CB080 supplies the owning-handle constructor
// relationship; the original class name and unused argument type are unknown.
// Keep an address-derived owner and a neutral one-word mip argument. Native
// ignores that argument; the shared132D89 loader receives exscorch01.tga.
// The loader is TextureAsset::Get (0x00132D89, TextureAssetGet.cpp), which
// returns its handle through the hidden result pointer: the owner's handle base
// is built in place from it, so the call passes `this` as that pointer.
class TextureClass;
class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
	~BFME2ParticleTextureHandle();
};
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/TextureAsset.h"
class Rva0006B3F3ScorchTexture : public BFME2ParticleTextureHandle
{
public:
	Rva0006B3F3ScorchTexture(int mipCount);
};
Rva0006B3F3ScorchTexture::Rva0006B3F3ScorchTexture(int mipCount)
	: BFME2ParticleTextureHandle(TextureAsset::Get("exscorch01.tga", 0, 0))
{
}
