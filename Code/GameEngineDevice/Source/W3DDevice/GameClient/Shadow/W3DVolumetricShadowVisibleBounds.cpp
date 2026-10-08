// cl: /DNDEBUG /MD
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowVisibleBounds.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x00106FB6 (144B).

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/aabox.h
class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

extern const float g_rva01075350;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadow.h
class W3DVolumetricShadow
{
private:
	unsigned char m_unreconstructed_000[ 0x74 ];
	RenderObjClass *m_robj;
	unsigned char m_unreconstructed_078[ 8 ];
	float m_robjExtent;
	float m_extraExtrusionPadding;
	unsigned char m_unreconstructed_088[ 8 ];
	float m_lightOffsetX;
	float m_lightOffsetY;
	float m_lightOffsetZ;

public:
	int bfmeIntersectsVisibleBounds(const AABoxClass &box) const;
};

__declspec(noinline) int W3DVolumetricShadow::bfmeIntersectsVisibleBounds(const AABoxClass &box) const
{
	Vector3 pos = m_robj->Get_Position();

	return pos.X + m_robjExtent > box.Center.X - box.Extent.X &&
			pos.X - m_robjExtent < box.Center.X + box.Extent.X &&
			pos.Y + m_robjExtent > box.Center.Y - box.Extent.Y &&
			pos.Y - m_robjExtent < box.Center.Y + box.Extent.Y;
}

// BF1 9cbfb551fe Common/Rva006C8CC0DisplacedStubs.cpp is the clean semantic donor.
// Target 106FA5..106FB6 RET4 follows precedingRET4; MOVSS stackfloat to receiver8C
// Original owner/purpose is unproven; retain an independent address-owned type.
class Rva00106FA5Fields
{
public: void setFloat(float value);
private: char unknown[0x8C]; float value8C;
};
void Rva00106FA5Fields::setFloat(float value) { value8C=value; }
