// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??0Rva005970ED@@QAE@XZ 33B @0x005970ED: ctor over base AIUpgrade ctor
// at 0x00597331, then sets dword at +0x3C to -1 (retail `or [m],-1` /O1
// idiom), byte at +0x34 and dwords at +0x38/+0x40 to 0, and installs vtable
// 0x00870B88. Evidence: base call plus or-minus-one plus zero stores plus
// vptr store, callers at 0x004EAF8E 0x004EB21B 0x00597CFB. Base layouts
// from landed siblings Rva005DAAB6Slot15.cpp and Rva0059734BCtor.cpp;
// owner identity unproven so honest address name.

#include "ascii_string.h"

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
	unsigned char m_major;
	unsigned char m_minor;
	Version(unsigned char a, unsigned char b) : m_major(a), m_minor(b) {}
};




enum ObjectID
{
	INVALID_ID = 0
};

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
private:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

class AIUpgrade : public Rva0055B0CC
{
public:
	AIUpgrade();
	virtual ~AIUpgrade();
	virtual void DoXfer(Xfer *xfer, void *context);
private:
	int m_2C;
	int m_30;
};

class Rva0059710EHelper
{
public:
	virtual int f0(int x);
	virtual void *f1(int flags);
};

class Rva005970ED : public AIUpgrade
{
public:
	Rva005970ED();
	virtual ~Rva005970ED();
	__declspec(noinline) void rva00597123();
	void rva0059710E(int x);
	void rva0059717F(int id);
	void rva0059728F(Xfer *xfer, void *context);
private:
	bool m_34;
	Rva0059710EHelper *m_38;
	int m_3C;
	int m_40;
};

Rva005970ED::Rva005970ED()
	: m_34(false)
	, m_38(0)
	, m_3C(-1)
	, m_40(0)
{
}

void Rva005970ED::rva0059710E(int x)
{
	m_40 = m_38->f0(x);
}

// Native 0x597123..0x597147 uses the constructor-established +0x38
// child and +0x3C id: only a nonnull child with id other than -1 or zero
// receives virtual slot1(flags0); its returned allocation is deleted.
// The virtual destructor 0x597147..0x59717F calls that helper, then the
// rowed AIUpgrade base destructor at 0x59734B. The existing slot0 deleting
// destructor at 0x597315 already names this derived destructor.
void operator delete(void *);
void Rva005970ED::rva00597123()
{
 Rva0059710EHelper *child = m_38;
 if (child != 0) {
  int id = m_3C;
  if (id != -1 && id != 0)
   ::operator delete(child->f1(0));
 }
}
Rva005970ED::~Rva005970ED()
{
 rva00597123();
}

// Native complete RET8 body 0x0059728F..0x00597315. Matched owning
// constructor and destructor establish +34 flag / +3C id / +40 result.
// WB 15377F0 is an unnamed callgraph lead, corroborating version1/2 and
// load-only child selection. Xfer primitive ABI is reused from matched
// Rva00380200Getter.cpp; base DoXfer provider is independently rowed5974CC.
// Native59717F is the same receiver's RET4 child selector; its original name
// and the derived owner identity remain unresolved, so both stay address names.
void Rva005970ED::rva0059728F(Xfer *xfer, void *context)
{
 Xfer::Version version(1, 2);
 *xfer == version;
 AIUpgrade::DoXfer(xfer, context);
 *xfer == m_34;
 int id = m_3C;
 *xfer == id;
 m_3C = id;
 if (version.m_minor >= 2) {
  int result = m_40;
  *xfer == result;
  m_40 = result;
 }
 if (xfer->IsLoading())
  rva0059717F(id);
}
