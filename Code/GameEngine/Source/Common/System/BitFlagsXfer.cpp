// cl: /O1 /EHsc /MD /DNDEBUG /Ireference/shims/bfme2_ascii
//
// BitFlags<N>::xfer, Zero Hour's Common/BitFlags.h transfer (version, then
// the count and the names of the set bits on save; clear, then set each name
// read on load, throwing on an unknown name), for three more flag sets:
//   0x00292414 316B BitFlags<11>::xfer
//   0x00292550 316B BitFlags<101>::xfer
//   0x00318871 316B BitFlags<15>::xfer
//   0x000BB710 319B BitFlags<591>::xfer
//   0x0029268C 319B BitFlags<154>::xfer
//   0x002AC06A 319B BitFlags<218>::xfer
//   0x000B6586  72B BitFlags<591>::count
//   0x0028F791  72B BitFlags<154>::count
//
// Target evidence. Each body is the rowed BitFlags<104>::xfer 0x002914AF
// (WeaponSetXfer.cpp) and BitFlags<21>::xfer 0x004BE781 shape: version 1/1,
// a light CRC sends the raw bits through the set's own word emitter, save
// counts the bits and names every set one up to N (the loop bound: 0x0B, 0x65,
// 0x0F, 0x24F, 0x9A and 0xDA), every other mode clears the words with memset
// (4, 0x10, 4, 0x4C, 0x14 and 0x1C bytes) and sets each name through the
// set's own setBitByName, throwing XferException tag 0 on a miss. The per-set
// helpers are the rowed callees:
//   N    count         name of a set bit  setBitByName  raw bits
//   11   0x0028F528    0x0028C6FB         0x0028F6BC    0x0029161A
//   101  0x0028F6EB    0x0028C753         0x0028F762    0x00291679
//   15   0x0028F528    0x0031852F         0x00318559    0x003187A8
//   591  0x000B6586    0x000454F3         0x000B65CE    0x000B95B1
//   154  0x0028F791    0x0028C783         0x0028F7D9    0x002916DA
//   218  0x002AACDB    0x002AA2CF         0x002AAD23    0x002ABBBE
// The one-word sets share the one-word popcount 0x0028F528 and the four-word
// sets the four-word count retail folds into BitFlags<104>::count 0x0028F6EB;
// the 19- and 5-word counts are this file's, the 7-word one is rowed. The name
// tables give the sets: disability types (11), body states (101), CommandSet
// names (15), model conditions (591, ObjectSMCHelper's MODELCONDITION_COUNT),
// special powers (154) and KindOf (218). 0x000B65CE is rowed as
// BitFlags<304>::setBitByName, so the 591-bit set calls it under that name.
// Donor-carried: the names and the Zero Hour body.

// Loading clears the words here. The old unused clear() definition emitted
// a competing one-word COMDAT; the eight transfer/count bodies stay exact
// when the same memset is written directly in the load path.
#include <string.h>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

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

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

// Rowed per-set helpers under address names.
class Rva0028F528
{
public:
	Int rva0028F528();
};
class Rva0028C6FB
{
public:
	void *rva0028C6FB(UnsignedInt i);
};
class Rva0028C753
{
public:
	void *rva0028C753(UnsignedInt i);
};
class Rva0031852F
{
public:
	void *rva0031852F(UnsignedInt i);
};
class Rva0028F6BC
{
public:
	Bool rva0028F6BC(const char *token);
};
class Rva0028F762
{
public:
	Bool rva0028F762(const char *token);
};
class Rva0029161AArg;
class Rva0029161A
{
public:
	void rva0029161A(Rva0029161AArg *xfer);
};
class Rva00291679Arg;
class Rva00291679
{
public:
	void rva00291679(Rva00291679Arg *xfer);
};
class Rva003187A8Xfer;
class Rva003187A8Owner
{
public:
	void rva003187A8(Rva003187A8Xfer *xfer);
};
class Rva000454F3
{
public:
	void *rva000454F3(UnsignedInt i);
};
class Rva000B95B1
{
public:
	void rva000B95B1(void *xfer);
};
class Rva0028C783
{
public:
	void *rva0028C783(UnsignedInt i);
};
class Rva0028F7D9
{
public:
	Bool rva0028F7D9(const char *token);
};
class Rva002916DAArg;
class Rva002916DA
{
public:
	void rva002916DA(Rva002916DAArg *xfer);
};
class Rva002AACDB
{
public:
	Int rva002AACDB();
};
class Rva002AA2CF
{
public:
	void *rva002AA2CF(UnsignedInt i);
};
class Rva002AAD23
{
public:
	Bool rva002AAD23(const char *token);
};
class Rva002ABBBE
{
public:
	void rva002ABBBE(void *xfer);
};

template <int NUMBITS> class BitFlags
{
public:
	enum { NUMWORDS = (NUMBITS + 31) / 32 };

	Int count() const;
	const char *getBitNameIfSet(Int i) const;
	Bool setBitByName(const char *token);
	void xferRawBits(Xfer *xfer);
	void xfer(Xfer *xfer);

private:
	UnsignedInt m_bits[NUMWORDS];
};

//-------------------------------------------------------------------------------------------------
template <int NUMBITS>
Int BitFlags<NUMBITS>::count() const
{
	Int c = 0;
	for (UnsignedInt i = 0; i < NUMWORDS; ++i)
	{
		UnsignedInt v = m_bits[i];
		UnsignedInt pairs = v - ((v >> 1) & 0x55555555u);
		UnsignedInt nibbles = (pairs & 0x33333333u) + ((pairs >> 2) & 0x33333333u);
		UnsignedInt bytes = (nibbles + (nibbles >> 4)) & 0x0F0F0F0Fu;
		c += (bytes * 0x01010101u) >> 24;
	}
	return c;
}

template <> inline Int BitFlags<11>::count() const { return ((Rva0028F528 *)this)->rva0028F528(); }
template <> inline const char *BitFlags<11>::getBitNameIfSet(Int i) const { return (const char *)((Rva0028C6FB *)this)->rva0028C6FB(i); }
template <> inline Bool BitFlags<11>::setBitByName(const char *token) { return ((Rva0028F6BC *)this)->rva0028F6BC(token); }
template <> inline void BitFlags<11>::xferRawBits(Xfer *xfer) { ((Rva0029161A *)this)->rva0029161A((Rva0029161AArg *)xfer); }

template <> inline Int BitFlags<101>::count() const { return ((const BitFlags<104> *)this)->count(); }
template <> inline const char *BitFlags<101>::getBitNameIfSet(Int i) const { return (const char *)((Rva0028C753 *)this)->rva0028C753(i); }
template <> inline Bool BitFlags<101>::setBitByName(const char *token) { return ((Rva0028F762 *)this)->rva0028F762(token); }
template <> inline void BitFlags<101>::xferRawBits(Xfer *xfer) { ((Rva00291679 *)this)->rva00291679((Rva00291679Arg *)xfer); }

template <> inline Int BitFlags<15>::count() const { return ((Rva0028F528 *)this)->rva0028F528(); }
template <> inline const char *BitFlags<15>::getBitNameIfSet(Int i) const { return (const char *)((Rva0031852F *)this)->rva0031852F(i); }
template <> inline void BitFlags<15>::xferRawBits(Xfer *xfer) { ((Rva003187A8Owner *)this)->rva003187A8((Rva003187A8Xfer *)xfer); }

template <> inline const char *BitFlags<591>::getBitNameIfSet(Int i) const { return (const char *)((Rva000454F3 *)this)->rva000454F3(i); }
template <> inline Bool BitFlags<591>::setBitByName(const char *token) { return ((BitFlags<304> *)this)->setBitByName(token); }
template <> inline void BitFlags<591>::xferRawBits(Xfer *xfer) { ((Rva000B95B1 *)this)->rva000B95B1(xfer); }

template <> inline const char *BitFlags<154>::getBitNameIfSet(Int i) const { return (const char *)((Rva0028C783 *)this)->rva0028C783(i); }
template <> inline Bool BitFlags<154>::setBitByName(const char *token) { return ((Rva0028F7D9 *)this)->rva0028F7D9(token); }
template <> inline void BitFlags<154>::xferRawBits(Xfer *xfer) { ((Rva002916DA *)this)->rva002916DA((Rva002916DAArg *)xfer); }

template <> inline Int BitFlags<218>::count() const { return ((Rva002AACDB *)this)->rva002AACDB(); }
template <> inline const char *BitFlags<218>::getBitNameIfSet(Int i) const { return (const char *)((Rva002AA2CF *)this)->rva002AA2CF(i); }
template <> inline Bool BitFlags<218>::setBitByName(const char *token) { return ((Rva002AAD23 *)this)->rva002AAD23(token); }
template <> inline void BitFlags<218>::xferRawBits(Xfer *xfer) { ((Rva002ABBBE *)this)->rva002ABBBE(xfer); }

//-------------------------------------------------------------------------------------------------
template <int NUMBITS>
void BitFlags<NUMBITS>::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	if (xfer->IsLightCRC())
	{
		xferRawBits(xfer);
	}
	else if (xfer->IsStoring())
	{
		Int c = count();
		*xfer == c;
		for (Int i = 0; i < NUMBITS; ++i)
		{
			const char *bitName = getBitNameIfSet(i);
			if (bitName == 0)
				continue;
			AsciiString bitNameA = bitName;
			*xfer == bitNameA;
			--c;
		}
	}
	else
	{
		memset(m_bits, 0, sizeof(m_bits));
		Int c;
		*xfer == c;
		AsciiString string;
		for (Int i = 0; i < c; ++i)
		{
			*xfer == string;
			Bool ok = setBitByName(string.str());
			if (ok == false)
				throw XferException(0, 0);
		}
	}
}

template void BitFlags<11>::xfer(Xfer *xfer);
template void BitFlags<101>::xfer(Xfer *xfer);
template void BitFlags<15>::xfer(Xfer *xfer);
template void BitFlags<591>::xfer(Xfer *xfer);
template void BitFlags<154>::xfer(Xfer *xfer);
template void BitFlags<218>::xfer(Xfer *xfer);
