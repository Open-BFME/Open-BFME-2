// cl: /MD /ICode/Libraries/Include/Lib
// ?rva0055D3F5@Rva0055D3F5@@UAEXPAVXfer@@@Z at 0x0055D3F5 size 45
// Evidence: vslot slot3 of 0x0081D07C and 0x0081C7B8; Version1 rowed 0x000053EE plus 2 Xfer slots 0x90/0x70 over +0x20/+0x24; xfer recipe precedent FXParticleSystemLineXfer.cpp.

#include "Coord3D.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class TacticalView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(const Coord3D *center, float radius, unsigned int color);
};

extern TacticalView *TheTacticalView;

class Rva0055D3F5
{
public:
	virtual void rva0055D3F5(Xfer *xfer);
	void rva0055D422(Coord3D pos);
private:
	char m_pad[0x1C];
	bool m_20;
	char m_pad2[3];
	float m_24;
};

void Rva0055D3F5::rva0055D3F5(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_20;
	*xfer == m_24;
}

// Native 0x0055D422..0x0055D48C (106 bytes, RET 0xC): slot 4 of the same
// sphere-volume tables (0x0081C7C8, 0x0081CBC4, 0x0081D08C), the debug draw
// beside the line volume's 0x0055CD70: two TacticalView slot-12 circles of
// the +0x24 radius in 0xCCAAFFFF, half a radius below and above the centre.
// The centre arrives by value and is moved in place.
void Rva0055D3F5::rva0055D422(Coord3D pos)
{
	pos.z -= m_24 * 0.5f;
	TheTacticalView->slot12(&pos, m_24, 0xCCAAFFFF);
	pos.z += m_24;
	TheTacticalView->slot12(&pos, m_24, 0xCCAAFFFF);
}
