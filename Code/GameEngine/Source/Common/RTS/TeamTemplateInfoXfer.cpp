// cl: /Ireference/shims/moduledata /O1 /MD
// ?xfer@TeamTemplateInfo@@MAEXPAVXfer@@@Z retail 0x0039D5C1 323 bytes. TeamTemplateInfo slot 3 xfer Version 1-3 with ints uints array and KindOf gating. Evidence: VTABLE slot 3 of 0x0081AE70 class TeamTemplateInfo; REF slot 0x0081AE7C; rowed getNthPlayer pattern plus Version 1-2 precedent TeamPrototypeXfer 0x003A3E74; rowed rva0039D533 0x0039D533 pin xferKindOf 0x002AC06A rowed bitcopy 0x002ABBBE; neighbours D5A9 D704 same region /O1 arch SSE G7.
#include "Common/Snapshot.h"
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
class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}
	unsigned char m_current;
	unsigned char m_minimum;
};
// KindOfMaskType is the donor's BitFlags typedef. Target 0x2AC06A's loop
// bound 218 and seven-word payload establish this target specialization.
template <int NUMBITS>
class BitFlags
{
public:
	void xfer(Xfer *xfer);
private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<218> KindOfMaskType;
class Rva002ABBBE
{
public:
	void rva002ABBBE(void *xfer);
};
struct Rva0039D533Src
{
	virtual void v00(); virtual bool v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(int *out); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(int *out);
};
struct Rva0039D533
{
	int m_00; int m_04; int m_08; int m_0c; int m_10; int m_14;
	void rva0039D533(Rva0039D533Src *src);
};
class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};
class TeamTemplateInfo : public Snapshot
{
public:
	virtual ~TeamTemplateInfo();
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	Rva0039D533 m_units[7];
	int m_numUnits;
	char m_padB0[0xf0 - 0xb0];
	int m_f0;
	char m_padF4[0x198 - 0xf4];
	unsigned int m_198;
	unsigned int m_19c;
	unsigned int m_1a0;
	unsigned int m_1a4;
	unsigned int m_1a8;
	unsigned int m_1ac;
	unsigned int m_1b0;
	KindOfMaskType m_1b4;
	KindOfMaskType m_1d0;
};
void TeamTemplateInfo::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	*xfer == m_f0;
	*xfer == m_198;
	*xfer == m_1a4;
	*xfer == m_1a8;
	*xfer == m_1ac;
	*xfer == m_1b0;
	unsigned int tmp = m_19c;
	*xfer == tmp;
	if (xfer->IsLoading())
		m_19c = tmp;
	tmp = m_1a0;
	*xfer == tmp;
	if (xfer->IsLoading())
		m_1a0 = tmp;
	if ((int)m_1ac != -1)
	{
		*xfer == m_numUnits;
		int n = 0;
		n &= 0;
		if ((unsigned int)m_numUnits > 0)
		{
			Rva0039D533 *elem = m_units;
			do
			{
				elem->rva0039D533((Rva0039D533Src *)xfer);
				++n;
				elem = (Rva0039D533 *)((char *)elem + 0x18);
			} while ((unsigned int)n < (unsigned int)m_numUnits);
		}
	}
	if (version.m_minimum >= 3)
	{
		m_1b4.xfer(xfer);
		m_1d0.xfer(xfer);
	}
	else if (version.m_minimum >= 2)
	{
		((Rva002ABBBE *)&m_1b4)->rva002ABBBE(xfer);
		((Rva002ABBBE *)&m_1d0)->rva002ABBBE(xfer);
	}
}
