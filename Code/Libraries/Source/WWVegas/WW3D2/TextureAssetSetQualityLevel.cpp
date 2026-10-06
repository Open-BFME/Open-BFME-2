// cl: /O2 /Ob0
//
// ?SetQualityLevel@TextureAsset@@QAEXH@Z, retail 0x00132C9D, 16 bytes.
// Identity: WorldBuilder's texture.cpp:1917 TextureAsset::SetQualityLevel
// asserts its factory pointer (+0) and stores the level at the factory's
// +0x38, as here; its unnamed 32-byte bool forwarder calls it just as retail's
// 0x00132FE9 does.

struct TextureAssetFactoryView
{
	char m_lead[0x38];
	int m_value;
};

class TextureAsset
{
	TextureAssetFactoryView *m_factory;

public:
	void SetQualityLevel(int value);
};

void TextureAsset::SetQualityLevel(int value)
{
	if (m_factory)
		m_factory->m_value = value;
}
