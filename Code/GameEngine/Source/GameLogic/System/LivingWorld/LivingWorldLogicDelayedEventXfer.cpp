// cl: /Ireference/shims/moduledata /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport46
// Native 2BB49C..2BB5DD RET8: counted transfer of a delayed-event pointer
// vector, called twice by both stream bodies 2BB5DD and 2BBA45 (this, xfer,
// vector). Load reads a kind through rowed 2B2275 and builds one of four
// events: inlined ctors installing vtables BFE024 (kind 1) and BFE1B0
// (kind 2), each nulling +0x0C; BFE058 (kind 4, 0x20-byte object); rowed
// ctor 2BAE57 (kind 8, 0x1C bytes); then the event's xfer slot and the
// rowed 49-byte push_back 4DFCB0. Save takes each element's kind from slot
// 6, transfers it, then calls the element's xfer slot. Event class names
// remain address-derived; their common base is a structural inference from
// the shared slot use, not a target name.
#include <vector>
#include "Common/Snapshot.h"
// Import-inline: every _STL::max<unsigned int> use here is inlined, and this
// unit's out-of-line copy (referenced from .debug$F alone) is not the one the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline const unsigned int &max<unsigned int>(const unsigned int &__a, const unsigned int &__b) { return __a < __b ? __b : __a; } }

typedef int Int;
typedef bool Bool;

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../../Include/Common/BfmeXfer.h"

struct Rva002B2275Obj;
int __cdecl Rva002B2275Get(Rva002B2275Obj *xfer, void *type);

class Rva002BB49CEvent : public Snapshot
{
public:
	__declspec(noinline) virtual void loadPostProcess() {}
	__declspec(noinline) virtual void crc(Xfer *xfer) {}
	__declspec(noinline) virtual void xfer(Xfer *xfer) {}
	__declspec(noinline) virtual Bool slot4() { return 0; }
	__declspec(noinline) virtual void slot5() {}
	__declspec(noinline) virtual Int getType() { return 0; }
};

class OpaqueRefCounted;
struct Rva000A8C9B
{
	OpaqueRefCounted *m_ptr;
	Rva000A8C9B() : m_ptr(0) {}
};
class Rva003FD3EF : public Rva002BB49CEvent
{
public:
	__declspec(dllimport) __forceinline Rva003FD3EF() {}
	virtual ~Rva003FD3EF();
	__declspec(noinline) virtual void loadPostProcess() {}
	__declspec(noinline) virtual void crc(Xfer *xfer) {}
	__declspec(noinline) virtual void xfer(Xfer *xfer) {}
	__declspec(noinline) virtual Bool slot4() { return 0; }
	__declspec(noinline) virtual void slot5() {}
	__declspec(noinline) virtual Int getType() { return 0; }
	char m_pad04[8];
	Rva000A8C9B m_0c;
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	T *m_data;
};
class Rva003FD4DA : public Rva002BB49CEvent
{
public:
	__declspec(dllimport) __forceinline Rva003FD4DA() {}
	virtual ~Rva003FD4DA();
	__declspec(noinline) virtual void loadPostProcess() {}
	__declspec(noinline) virtual void crc(Xfer *xfer) {}
	__declspec(noinline) virtual void xfer(Xfer *xfer) {}
	__declspec(noinline) virtual Bool slot4() { return 0; }
	__declspec(noinline) virtual void slot5() {}
	__declspec(noinline) virtual Int getType() { return 0; }
	char m_pad04[8];
	StringBase<char> m_0c;
};

class __declspec(novtable) Rva002B30CA : public Rva002BB49CEvent
{
public:
	// RvaSmallVtableCtors.cpp owns the standalone constructor.
	__declspec(dllimport) __forceinline Rva002B30CA() {}
	virtual ~Rva002B30CA();
	char m_pad04[0x1C];
};

class Rva003C2F40Owner : public Rva002BB49CEvent
{
public:
	Rva003C2F40Owner();
	virtual ~Rva003C2F40Owner();
	char m_pad04[0x18];
};

struct RecVec : public _STL::vector<Rva002BB49CEvent *> {};

class Rva002BB49C {public: void rva002BB49C(Xfer *, RecVec *);};

void Rva002BB49C::rva002BB49C(Xfer *xfer, RecVec *records)
{
	Int count = records->size();
	*xfer == count;
	if (xfer->IsLoading())
	{
		for (Int i = 0; i < count; ++i)
		{
			Int type;
			Rva002B2275Get((Rva002B2275Obj *)xfer, &type);
			switch (type)
			{
				case 1:
				{
					Rva003FD3EF *event = new Rva003FD3EF;
					event->xfer(xfer);
					records->push_back(event);
					break;
				}
				case 2:
				{
					Rva003FD4DA *event = new Rva003FD4DA;
					event->xfer(xfer);
					records->push_back(event);
					break;
				}
				case 4:
				{
					Rva002B30CA *event = new Rva002B30CA;
					event->xfer(xfer);
					records->push_back(event);
					break;
				}
				case 8:
				{
					Rva003C2F40Owner *event = new Rva003C2F40Owner;
					event->xfer(xfer);
					records->push_back(event);
					break;
				}
			}
		}
	}
	else
	{
		for (Int i = 0; i < count; ++i)
		{
			Int type = (*records)[i]->getType();
			Rva002B2275Get((Rva002B2275Obj *)xfer, &type);
			(*records)[i]->xfer(xfer);
		}
	}
}
