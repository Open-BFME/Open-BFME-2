// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva002A7818@Rva002AE5EB@@UAEXPAVXfer@@@Z, retail 0x002A7818, 393 bytes.
// Slot 3 (offset 0x0C) of vtable 0x007FDDB4 (class of ??0Rva002AE5EB rowed
// at 0x002AE5EB in Rva002AE5EBCtor.cpp). Version(1,7) via Xfer slot 0x28,
// ints via slot 0x7C, bool via slot 0x90, IsLoading via slot 0x04; vector
// at +0x20 holds 12B records (int/ObjectID/filter) erased via rowed
// 0x002A7644 and grown via rowed push_back 0x002A778D; per-record fields
// via rowed XferObjectID 0x003060B2, ObjectFilter::DoXfer and rowed ctor/dtor
// 0x002A7400/0x00360D26. Layout matches Rva002AE5EBCtor plus +0x0C/+0x10.
#include "../../../Libraries/Include/Lib/Coord2D.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
#include "../../../Libraries/Include/Lib/Coord3DBase.h"
#include "../../../Libraries/Include/Lib/ICoord3D.h"
#include "../../../Libraries/Include/Lib/Region3D.h"
struct IRegion3D
{
	ICoord3D lo;
	ICoord3D hi;
};
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"
#include "../../Include/Common/RealRange.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
struct RGBAColorReal
{
	float red;
	float green;
	float blue;
	float alpha;
};
#include "../../Include/Common/RGBAColorInt.h"
class Snapshot;
#include "../../Include/Common/BfmeXfer.h"
class Xfer::Version
{
public:
	__declspec(dllimport) __forceinline Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}
	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);

// Verified four-byte ObjectFilter ABI; retain surrounding provisional layouts.
#include "../../Include/GameLogic/ObjectFilter.h"
class Rva003189ADSub10
{
public:
	int m_handle;
};

class Rva00360D26Member : public Rva003189ADSub10
{
public:
	~Rva00360D26Member();
};

struct BfmePod12
{
	int m_a;
	int m_b;
	int m_c;
};

struct Rva002A76A0Element
{
	int m_value;
	ObjectID m_id;
	Rva00360D26Member m_filter;
};

class Rva002A7400
{
public:
	Rva002A7400();
	int m_value;
	ObjectID m_id;
	Rva00360D26Member m_filter;
};

namespace _STL
{
template <class _Tp>
class allocator
{
};
template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	void push_back(const _Tp &item);
	_Tp *erase(_Tp *first, _Tp *last);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_endOfStorage;
};
}

class Rva002AE5EB
{
public:
	virtual ~Rva002AE5EB();
	virtual void v01();
	virtual void v02();
	virtual void rva002A7818(Xfer *xfer);
private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	union
	{
		_STL::vector<BfmePod12> m_vecPod;
		_STL::vector<Rva002A76A0Element> m_vecElem;
	};
	bool m_2C;
};

void Rva002AE5EB::rva002A7818(Xfer *xfer)
{
	Xfer::Version version(1, 7);
	*xfer == version;
	*xfer == m_04;
	*xfer == m_08;
	*xfer == m_14;
	if (version.m_minimum >= 2)
		*xfer == m_18;
	if (version.m_minimum >= 3)
		*xfer == m_1C;
	if (version.m_minimum >= 4)
		*xfer == m_0C;
	if (version.m_minimum >= 5)
	{
		if (xfer->IsLoading())
		{
			_STL::vector<BfmePod12> *pv = &m_vecPod;
			BfmePod12 *last = pv->m_finish;
			BfmePod12 *first = pv->m_start;
			pv->erase(first, last);
			int count = 0;
			*xfer == count;
			for (int i = 0; i < count; ++i)
			{
				Rva002A7400 tmp;
				*xfer == tmp.m_value;
				XferObjectID(xfer, &tmp.m_id);
				reinterpret_cast<ObjectFilter *>(&tmp.m_filter)->DoXfer(xfer);
				m_vecElem.push_back(*(const Rva002A76A0Element *)&tmp);
			}
		}
		else
		{
			int count = m_vecElem.m_finish - m_vecElem.m_start;
			*xfer == count;
			for (Rva002A76A0Element *p = m_vecElem.m_start; p != m_vecElem.m_finish; ++p)
			{
				*xfer == p->m_value;
				XferObjectID(xfer, &p->m_id);
				reinterpret_cast<ObjectFilter *>(&p->m_filter)->DoXfer(xfer);
			}
		}
	}
	if (version.m_minimum >= 6)
		*xfer == m_10;
	if (version.m_minimum >= 7)
		*xfer == m_2C;
}
