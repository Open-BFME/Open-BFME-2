// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderSettingDestructor.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x0007E7E2 (61B).
//
// Clean reconstruction of the two-texture WaterRenderObjClass setting cleanup
// at retail 0x007A03F0.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureRef
{
public:
	~TextureRef()
	{
		if (texture != 0)
			texture->Release_Ref();
	}

private:
	TextureClass *texture;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
	struct Setting
	{
		Setting();
		~Setting();

		TextureRef skyTexture;
		TextureRef waterTexture;
	};
};

WaterRenderObjClass::Setting::~Setting()
{
}
