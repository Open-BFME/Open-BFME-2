// ?rva00332975@Rva0026E7C8Ctor@@QAEXPAVXfer@@@Z
// partial score=0.91 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00332975@Rva0026E7C8Ctor@@QAEXPAVXfer@@@Z, retail 0x00332975, 378 bytes.
//
// Slot 3 (offset 0xC) of vtable 0x007FA3A4, class of ??0Rva0026E7C8Ctor.
// Donor: BFME1/ZH xfer patterns plus PoisonedBehaviorXfer Xfer declaration.
// Evidence: Version1 row 0x53EE, reserve/push_back rows for Rva003328B6Element,
// keyToName pin, set row, nameToKey row, Rva00331EAD row, PoolMember release,
// Rva0029FB3BMember reset, xferSTLObjectIDList row, TheNameKeyGenerator extern.

#include "ascii_string.h"
#include <vector>

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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
	NameKeyType nameToKey(const AsciiString &s);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_prev;
	int m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	void push_back(const int &value);
	BridgeBehaviorObjectIDNode *m_node;
};

Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list);

class PoolMember
{
public:
	void Rva00268902();
};

class Rva0029FB3BMember : public PoolMember
{
public:
	void *init(void *context);
	void reset();
};

class Rva00331EAD
{
public:
	int m_00;
	int m_04;
	Rva0029FB3BMember m_08;

	Rva00331EAD(int a, int b);
};

struct Rva003328B6Element
{
	int m_key1;
	int m_key2;
	BridgeBehaviorObjectIDList m_list;
};

class Rva0026E7C8Ctor
{
public:
	Rva0026E7C8Ctor();
	void rva00332975(Xfer *xfer);

private:
	void *m_unk0;
	_STL::vector<Rva003328B6Element> m_vec;
};

// ?rva00332975@Rva0026E7C8Ctor@@QAEXPAVXfer@@@Z present-unmatched
void Rva0026E7C8Ctor::rva00332975(Xfer *xfer)
{
	xfer->Version1();
	int count = (int)m_vec.size();
	*xfer == count;
	m_vec.reserve(count);
	int i = 0;
	if (count <= 0)
		return;
	for (int off = 0; i < count; ++i, off += 12)
	{
		AsciiString s1;
		AsciiString s2;
		Rva003328B6Element *e = (Rva003328B6Element *)((char *)m_vec.begin() + off);
		BridgeBehaviorObjectIDList *plist = 0;
		if (xfer->IsStoring())
		{
			s1.set(TheNameKeyGenerator->keyToName((NameKeyType)e->m_key1));
			s2.set(TheNameKeyGenerator->keyToName((NameKeyType)e->m_key2));
			*xfer == s1;
			*xfer == s2;
			plist = &e->m_list;
		}
		else if (!xfer->IsLoading())
		{
			continue;
		}
		else
		{
			*xfer == s1;
			*xfer == s2;
			NameKeyType k1 = TheNameKeyGenerator->nameToKey(s1);
			NameKeyType k2 = TheNameKeyGenerator->nameToKey(s2);
			Rva00331EAD tmp((int)k1, (int)k2);
			m_vec.push_back(*(Rva003328B6Element *)&tmp);
			tmp.m_08.Rva00268902();
			Rva003328B6Element &back = m_vec.back();
			plist = (BridgeBehaviorObjectIDList *)&back.m_list;
			((Rva0029FB3BMember *)plist)->reset();
		}
		xferSTLObjectIDList(xfer, plist);
	}
}
