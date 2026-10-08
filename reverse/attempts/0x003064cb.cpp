// ?rva003064CB@@YAXPAVXfer@@PAVRva00291440@@@Z
// partial score=0.98 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /DNDEBUG /G7
// Native 003064CB..00306629: complete 350-byte upgrade-mask transfer.
// Semantic donor: BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f
// game/GameEngine/Source/Common/System/XferUpgradeMask.cpp.
// Native storage is 1024 bits, template name/index/next are +8/+38/+64.
// Inline bit operations fix the previous bank's Xfer/bitset register swaps.
// Remaining wall: count comparison uses SI=0 instead of immediate zero,
// shifting the load suffix by one byte. Two getter calls are unresolved.
// getFirstTemplate is a provisional descriptive declaration, not an admitted
// original name or pin. Native calls 001DB0A8, a folded four-byte +C getter;
// UpgradeCenterFindUpgradeByKey independently establishes list head at +C.
// Formatter uses the real bfmeFormatText symbol and 8-byte result ABI.
// No new pin, ledger row, or live Code source is asserted by this bank.
// ?rva003064CB@@YAXPAVXfer@@PAVRva00291440@@@Z present-unmatched
#include "ascii_string.h"
#include <cstring>

class Xfer;
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

class Rva00291440 {
public:
 unsigned int words[32];
 __forceinline bool testBit(unsigned int bit) const { return (words[bit>>5] & (1u<<(bit&31))) != 0; }
 __forceinline void setBit(unsigned int bit) { words[bit>>5] |= 1u<<(bit&31); }
};
class UpgradeTemplate
{
public:
	char m_pad0[8]; // +0x00 so m_name lands at +0x08 per retail lea [esi+8]
	AsciiString m_name; // +0x08
	char m_pad1[0x38 - 0x0C]; // +0x0C..0x37
	unsigned int m_bitIndex; // +0x38
	char m_pad2[0x64 - 0x3C]; // +0x3C..0x63
	UpgradeTemplate *m_next; // +0x64
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
	const UpgradeTemplate *getFirstTemplate() const;
};

extern "C" UpgradeCenter *TheUpgradeCenter;
struct BfmeFormattedText { char *text; int tag; };
extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result,int tag,const char *format,...);
extern int g_guardTargetTypeThrowInfo;
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	int getParticleType() const;
};
}

// ?Rva003064CBXfer@@YAXPAVXfer@@PAI@Z
void __cdecl rva003064CB(Xfer *xfer, Rva00291440 *bits)
{
	Xfer *x = xfer;
	Rva00291440 *b = bits;
	x->Version1();
	if (x->IsStoring()) {
		AsciiString tmp;
		unsigned int count = 0;
		const UpgradeTemplate *t = TheUpgradeCenter->getFirstTemplate();
		while (t) {
			unsigned int bit = t->m_bitIndex;
			if (b->testBit(bit))
				count++;
			t = t->m_next;
		}
		*x == *reinterpret_cast<unsigned short*>(&count);
		t = TheUpgradeCenter->getFirstTemplate();
		while (t) {
			unsigned int bit = t->m_bitIndex;
			if (b->testBit(bit)) {
				tmp.set(t->m_name);
				*x == tmp;
			}
			t = t->m_next;
		}
	} else {
		AsciiString tmp;
		unsigned short count;
		*x == count;
		memset(b, 0, 0x80);
		if (count > 0) {
			unsigned short i = 0;
			do {
				*x == tmp;
				const UpgradeTemplate *up = TheUpgradeCenter->findUpgrade(tmp);
				if (!up) {
					BfmeFormattedText error;
					bfmeFormatText(&error, 0, 0);
					_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
					__assume(0);
				}
				unsigned int bit = up->m_bitIndex;
				b->setBit(bit);
				++i;
			} while (i < count);
		}
	}
}
