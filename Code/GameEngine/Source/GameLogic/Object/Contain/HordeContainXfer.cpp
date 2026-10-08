// cl: /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// HordeContain::xfer, the snapshot slot of the HordeContain module vftable.
// No BFME1 donor body exists (the BFME1 reference has no HordeContain::xfer at
// revision ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f), so every member name
// below is an offset label taken from the target.
//
// Target facts (0x00474EA8, 2081 bytes, __EH_prolog frame): TransportContain::
// xfer 0x00466DBC, the light-CRC gate (Xfer slot +0x10) and Version 13/1.
// Bools +0x120/+0x121/+0x2A4 and UnsignedInt +0x19C; the int list at +0x194
// (push_back 0x0005548F), the id->int map at +0x17C (operator[] 0x0028932C),
// BitFlags<591>::xfer 0x000BB710 on +0x124 and the id set at +0x170 (insert
// 0x000BC15D). Below minimum version 3 a vector of 8-byte records at +0x270 is
// read through operator new 0x0002FDA0, the record xfer 0x00468FB4 and
// vector<const ModuleData *>::push_back 0x004DFCB0; below 8 a dead Bool
// replaces ObjectID +0x2A0. The owner's stance comes from the module found by
// Object::findModule 0x0028B6D6 with key 0x0045EE2C (stance at +0x30), is
// transferred by XferStancesEnum 0x0045ED66 and restored on load through
// StancesBehavior::changeStanceFromXfer 0x0045EDD5. The helper at +0x2C8 is
// transferred through its vftable slot +0x3C, followed by the scalar block
// +0x288..+0x294 (Coord3D +0x2B8 chained with Bool +0x2C4) and BitFlags +0x124
// again. The id->{Coord3D, UnsignedInt} map at +0x1A0 is filled through the
// subscript 0x00473F81, whose record is zeroed in place and copied memberwise
// (Coord3D block then the int), as the out-of-line ctor 0x00469155 and
// operator= 0x0046916D do. ObjectIDs +0x1AC/+0x1B0, BitFlags +0x1B4/+0x200,
// the id->int map at +0x24C, the 16-bit-key float map at +0x258 (subscript
// 0x00470041), then version-gated fields up to +0x308; version 9 adds the
// helpers 0x0046EFDB, 0x00473FD4 (with a temporary map destroyed by
// 0x0046AB1B below version 10) and 0x00470222.
//
// /G7 and /arch:SSE follow the target's movss/xorps and the 16-bit load
// without a preceding xor. The m_24C count is block-scoped so it shares the
// dead parameter slot; the record pointer is stored as const ModuleData * so it
// is spilled before the record xfer call.
#include <map>
#include <set>
#include <list>
#include <vector>
#include "ascii_string.h"
#include "Lib/Coord3D.h"

class UnicodeString;
class PooledString;
struct XferUnknown11;
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

	virtual ~Xfer();

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
	virtual Xfer &operator==(Coord3D &value);
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
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

class ModuleData;
class Module;

enum ObjectID
{
	INVALID_ID = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);
void XferStancesEnum(Xfer *xfer, int *stances);
NameKeyType Rva0045EE2CGet();

class HordeContain;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class HordeContain;
};

class StancesBehavior
{
public:
	Int getStance() const { return m_stance; }
	bool changeStanceFromXfer(int arg);
private:
	char m_pad00[0x30];
	Int m_stance; // +0x30
};

template <int NUMBITS> class BitFlags
{
public:
	void xfer(Xfer *xfer);
private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<591> ModelConditionFlags;

class Rva00468FB4
{
public:
	Rva00468FB4() : m_00(0), m_04(-1) {}
	void rva00468FB4(Xfer *xfer);
private:
	Int m_00;
	Int m_04;
};

class Rva00469155
{
public:
	Rva00469155() : m_value(0)
	{
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = 0.0f;
	}
	Rva00469155(const Rva00469155 &o) : m_pos(o.m_pos), m_value(o.m_value) {}
	Rva00469155 &operator=(const Rva00469155 &o)
	{
		m_pos = o.m_pos;
		m_value = o.m_value;
		return *this;
	}

	Coord3D m_pos;
	UnsignedInt m_value;
};

class Rva00473F81 : public _STL::map<Int, Rva00469155>
{
public:
	Rva00469155 &rva00473F81(const Int &key);
};

class Rva00470041 : public _STL::map<UnsignedShort, Real>
{
public:
	Real &rva00470041(const UnsignedShort &key);
};

class Rva0046A93E : public _STL::map<Int, void *>
{
public:
	~Rva0046A93E();
};

Xfer *Rva0046EFDBXfer(Xfer *xfer, _STL::vector<const ModuleData *> *value);
Xfer *Rva00473FD4Xfer(Xfer *xfer, _STL::map<Int, Bool> *value);
Xfer *Rva00470222Xfer(Xfer *xfer, _STL::map<Int, Int> *value);

class HordeMeleeSwarmInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void xfer(Xfer *xfer);
};

class TransportContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x120 - 0x0C];
};

class HordeContain : public TransportContain
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Bool m_120;
	Bool m_121;
	ModelConditionFlags m_124;
	_STL::set<Int> m_170;
	_STL::map<Int, Int> m_17C;
	_STL::vector<Int> m_188;
	_STL::list<Int> m_194;
	Bool m_198;
	UnsignedInt m_19C;
	Rva00473F81 m_1A0;
	ObjectID m_1AC;
	ObjectID m_1B0;
	ModelConditionFlags m_1B4;
	ModelConditionFlags m_200;
	_STL::map<Int, Int> m_24C;
	Rva00470041 m_258;
	ObjectID m_264;
	Int m_268;
	ObjectID m_26C;
	_STL::vector<const ModuleData *> m_270;
	UnsignedInt m_27C;
	Int m_280;
	Int m_284;
	ObjectID m_288;
	UnsignedInt m_28C;
	UnsignedInt m_290;
	Bool m_294;
	UnsignedInt m_298;
	ObjectID m_29C;
	ObjectID m_2A0;
	Bool m_2A4;
	Int m_2A8;
	Bool m_2AC;
	ObjectID m_2B0;
	Bool m_2B4;
	Coord3D m_2B8;
	Bool m_2C4;
	Bool m_2C5;
	HordeMeleeSwarmInterface *m_2C8;
	_STL::vector<const ModuleData *> m_2CC;
	Int m_2D8;
	_STL::map<Int, Int> m_2DC;
	Bool m_2E8;
	Real m_2EC;
	ObjectID m_2F0;
	Int m_2F4;
	Coord3D m_2F8;
	Bool m_304;
	UnsignedInt m_308;
};

typedef char HordeContainSizeCheck[sizeof(HordeContain) == 0x30C ? 1 : -1];

void HordeContain::xfer(Xfer *xfer)
{
	TransportContain::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 13);
	*xfer == version;

	*xfer == m_120;
	*xfer == m_19C;
	*xfer == m_121;
	*xfer == m_2A4;

	Int listCount = m_194.size();
	*xfer == listCount;
	if (xfer->IsLoading())
	{
		Int value = 0;
		for (Int i = 0; i < listCount; ++i)
		{
			*xfer == value;
			m_194.push_back(value);
		}
	}
	else
	{
		for (_STL::list<Int>::iterator it = m_194.begin(); it != m_194.end(); ++it)
		{
			Int value = *it;
			*xfer == value;
		}
	}

	Int mapCount = m_17C.size();
	*xfer == mapCount;
	if (xfer->IsLoading())
	{
		Int key = 0;
		Int value = 0;
		for (Int i = 0; i < mapCount; ++i)
		{
			XferObjectID(xfer, (ObjectID *)&key);
			*xfer == value;
			m_17C[key] = value;
		}
	}
	else
	{
		for (_STL::map<Int, Int>::iterator it = m_17C.begin(); it != m_17C.end(); ++it)
		{
			Int key = (*it).first;
			Int value = (*it).second;
			XferObjectID(xfer, (ObjectID *)&key);
			*xfer == value;
		}
	}

	m_124.xfer(xfer);

	Int setCount = m_170.size();
	*xfer == setCount;
	if (xfer->IsLoading())
	{
		Int id = 0;
		for (Int i = 0; i < setCount; ++i)
		{
			XferObjectID(xfer, (ObjectID *)&id);
			m_170.insert(id);
		}
	}
	else
	{
		for (_STL::set<Int>::iterator it = m_170.begin(); it != m_170.end(); ++it)
		{
			Int id = *it;
			XferObjectID(xfer, (ObjectID *)&id);
		}
	}

	if (version.m_minimum < 3)
	{
		Int count = m_270.size();
		*xfer == count;
		if (xfer->IsLoading())
		{
			for (Int i = 0; i < count; ++i)
			{
				const ModuleData *entry = (const ModuleData *)new Rva00468FB4;
				((Rva00468FB4 *)entry)->rva00468FB4(xfer);
				m_270.push_back(entry);
			}
		}
		else
		{
			for (Int i = 0; i < count; ++i)
				((Rva00468FB4 *)m_270[i])->rva00468FB4(xfer);
		}
	}

	if (version.m_minimum < 8)
	{
		Bool unused;
		*xfer == unused;
		m_2A0 = INVALID_ID;
	}
	else
	{
		XferObjectID(xfer, &m_2A0);
	}

	Int stance = 1;
	StancesBehavior *stances = (StancesBehavior *)getObject()->findModule(Rva0045EE2CGet());
	if (stances)
		stance = stances->getStance();
	XferStancesEnum(xfer, &stance);
	if (xfer->IsLoading() && stances)
		stances->changeStanceFromXfer(stance);

	m_2C8->xfer(xfer);
	XferObjectID(xfer, &m_288);
	*xfer == m_28C;
	XferObjectID(xfer, &m_264);
	*xfer == m_268;
	XferObjectID(xfer, &m_26C);
	*xfer == m_27C;
	*xfer == m_280;
	*xfer == m_284;
	(*xfer == m_2B8) == m_2C4;
	*xfer == m_290;
	*xfer == m_294;
	m_124.xfer(xfer);

	if (xfer->IsStoring())
	{
		Int count = m_1A0.size();
		*xfer == count;
		for (Rva00473F81::iterator it = m_1A0.begin(); it != m_1A0.end(); ++it)
		{
			Int id = (*it).first;
			Rva00469155 info = (*it).second;
			XferObjectID(xfer, (ObjectID *)&id);
			*xfer == info.m_pos;
			*xfer == info.m_value;
		}
	}
	else
	{
		Int count;
		*xfer == count;
		for (Int i = 0; i < count; ++i)
		{
			Rva00469155 info;
			Int id;
			XferObjectID(xfer, (ObjectID *)&id);
			*xfer == info.m_pos;
			*xfer == info.m_value;
			m_1A0.rva00473F81(id) = info;
		}
	}

	XferObjectID(xfer, &m_1AC);
	XferObjectID(xfer, &m_1B0);
	m_1B4.xfer(xfer);
	m_200.xfer(xfer);

	{
	Int count;
	if (xfer->IsStoring())
	{
		count = m_24C.size();
		*xfer == count;
		for (_STL::map<Int, Int>::iterator it = m_24C.begin(); it != m_24C.end(); ++it)
		{
			Int key = (*it).first;
			Int value = (*it).second;
			XferObjectID(xfer, (ObjectID *)&key);
			*xfer == value;
		}
	}
	else
	{
		*xfer == count;
		for (Int i = 0; i < count; ++i)
		{
			Int key;
			Int value;
			XferObjectID(xfer, (ObjectID *)&key);
			*xfer == value;
			m_24C[key] = value;
		}
	}
	}

	if (xfer->IsStoring())
	{
		Int count = m_258.size();
		*xfer == count;
		for (Rva00470041::iterator it = m_258.begin(); it != m_258.end(); ++it)
		{
			UnsignedShort key = (*it).first;
			Real value = (*it).second;
			*xfer == key;
			*xfer == value;
		}
	}
	else
	{
		Int count;
		*xfer == count;
		for (Int i = 0; i < count; ++i)
		{
			UnsignedShort key;
			Real value;
			*xfer == key;
			*xfer == value;
			m_258.rva00470041(key) = value;
		}
	}

	*xfer == m_290;
	XferObjectID(xfer, &m_29C);
	*xfer == m_2A8;
	if (version.m_minimum < 11)
	{
		Bool unused;
		*xfer == unused;
	}
	*xfer == m_2AC;
	XferObjectID(xfer, &m_2B0);
	if (version.m_minimum > 1)
		*xfer == m_2C5;
	if (version.m_minimum >= 4)
		*xfer == m_2EC;
	if (version.m_minimum >= 5)
	{
		Bool unused = false;
		*xfer == unused;
	}
	if (version.m_minimum >= 6)
	{
		*xfer == m_304;
		*xfer == m_2F8;
	}
	if (version.m_minimum >= 7)
		XferObjectID(xfer, &m_2F0);
	if (version.m_minimum >= 9)
	{
		*Rva0046EFDBXfer(&(*xfer == m_298), &m_2CC) == m_2D8;
		if (version.m_minimum < 10)
		{
			Rva0046A93E unused;
			Rva00473FD4Xfer(xfer, (_STL::map<Int, Bool> *)&unused);
		}
		Rva00470222Xfer(xfer, &m_2DC);
		*xfer == m_2E8;
	}
	if (version.m_minimum >= 12)
		*xfer == m_308;
	if (version.m_minimum >= 13)
		*xfer == m_2F4;
}
