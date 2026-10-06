// cl: /DNDEBUG /MD /EHsc /Ob2
// ?xfer@LightningDrawModuleInfo@FXParticleSystem@@MAEXPAVXfer@@@Z @0x005614D9 78B evidence: slot 3 per vtable 0x0081BE80 slot7 and 0x0081BD80 slot3; Version1 then 3x xferRandomVariable 0x00306183 at +4/+0x10/+0x1c then float +0x28 via Xfer slot 0x70 then flag +0x2c via slot 0x90; Ghidra DoXfer.
// Snapshot slot-3 xfer via 4.7 recipe.
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

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
	};

	GameClientRandomVariable();
	void setRange(float low, float high, DistributionType type = UNIFORM);

private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

namespace FXParticleSystem
{

class LightningDrawModuleInfoBase
{
public:
	virtual ~LightningDrawModuleInfoBase();
};

class LightningDrawModuleInfo : public LightningDrawModuleInfoBase
{
public:
	LightningDrawModuleInfo();
	virtual ~LightningDrawModuleInfo();
protected:
	virtual void xfer(Xfer *xfer);

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	float m_28;
	bool m_2c;
};

}

void FXParticleSystem::LightningDrawModuleInfo::xfer(Xfer *xfer)
{
	xfer->Version1();
	xferRandomVariable(*xfer, m_var0);
	xferRandomVariable(*xfer, m_var1);
	xferRandomVariable(*xfer, m_var2);
	*xfer == m_28;
	*xfer == m_2c;
}
