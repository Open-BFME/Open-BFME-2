// cl: /MD
// ?rva00132FE9@TextureAsset@@QAEX_N@Z at 0x00132FE9 (18B).
// Bool-to-int forwarder to ?SetQualityLevel@TextureAsset@@QAEXH@Z at 0x00132C9D with this passthrough
// (WorldBuilder's texture.cpp has the same unnamed forwarder; name not recovered).
// Evidence: retail xor eax eax; cmp byte [esp+4] al; setne al; push eax; call set; ret 4;
// 5 callers incl 0x00047178 0x0004F628; callee row in WW3D2/TextureAssetSetQualityLevel.cpp.
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/TextureAsset.h"

void TextureAsset::rva00132FE9(bool flag)
{
	SetQualityLevel(flag != false);
}
