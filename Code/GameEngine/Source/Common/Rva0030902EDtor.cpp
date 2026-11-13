// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0030902E@@UAE@XZ, retail 0x0030902E..0x0030912A (252 bytes, EH):
// the destructor of the owner whose broadcast slots Rva00308AA4Notifiers.cpp
// rows (scalar deleting destructor 0x00309332; tables 0x00C07F80 at +0,
// 0x00C07F4C at +0x30, 0x00C07F30 on the shared virtual base behind its
// vtordisp). The same three-base shape as Rva0030CAA9OwnerDtor.cpp: it tells
// every listener through slot 0 (the generic vcall thunk 0x001FF3A9), frees
// its +0x98 array, releases the +0x84 reference, sets +0x88 and runs the
// rowed StandingWaterArea::rva003080CE on itself. Then its +0x8C/+0x80
// strings, the two +0x78 strings, the listener storage (GameFree; unwind copy
// 0x0007FAB3), the secondary base (rowed 0x002E3E51) and the primary base
// (0x00538133) die. The virtual base sits at +0xD8.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);
#include <new>

#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../Include/Common/Rva0030B72CPoint.h"

// Native seven-slot polygon interface, as in Rva00330C50Ctor.cpp.
#include "../../Include/Common/Rva00330C50Interface.h"

#include "../../Include/Common/Rva00538133Root.h"

class Rva0053805DBase : public Rva00538133Root, public virtual Rva00330C50Interface
{
public:
	virtual ~Rva0053805DBase();
	virtual bool slot1() const;
	virtual void rva0053805D();
	virtual void rva0053806C();
	virtual void rva0053807B() = 0;
	virtual void rva0053808A() = 0;
	virtual void primary6(int);
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

class Rva00330C50 : public virtual Rva00330C50Interface
{
public:
	virtual ~Rva00330C50();
	virtual int slot0() const;
	virtual Rva0030B72CPoint slot1(int index) const;
	virtual int slot2() const;
	virtual Region2D slot3();
	virtual float slot4() const;
	virtual float slot5() const;
	virtual Rva0030B72CPoint slot6() const;
	virtual void primary1() = 0;
	virtual void primary2() = 0;
	virtual void primary3() = 0;
	virtual void primary4() = 0;
	virtual void primary5() = 0;
	virtual void primary6(int);
private:
	void *m_08;
	unsigned char m_pad0C[0x38 - 0x0C];
};

class Rva00308AA4Owner;

class Rva00308AA4Listener
{
public:
	virtual void notify00(Rva00308AA4Owner *owner);
};

class Rva003089CFList
{
public:
	~Rva003089CFList() { if (m_begin) Rva00030830GameFree(m_begin); }
	void forEach(void (Rva00308AA4Listener::*notify)(Rva00308AA4Owner *), Rva00308AA4Owner *owner);
private:
	Rva00308AA4Listener **m_begin;
	Rva00308AA4Listener **m_end;
	Rva00308AA4Listener **m_capacity;
	unsigned int m_index;
};

class AsciiString;
struct Rva003080AARef;
struct StandingWaterPCARecord;
class StandingWaterArea
{
public:
	void loadFXShaderSetup();
	void rva003080CE();
	unsigned char *getDepthColoringTexturePixels(int *width, int *height);
	void rva00308A12(float position, int *red, int *green, int *blue);
	char m_pad00[0x80];
	AsciiString shaderName; // +0x80
	Rva003080AARef *shader; // +0x84
	char m_pad88[0x4];
private:
	AsciiString name; // +0x8C
	int width; // +0x90
	int height; // +0x94
	unsigned char *pixels; // +0x98
	bool reload; // +0x9C
	char m_pad9D[0xB];
	StandingWaterPCARecord *mean; // +0xA8
	StandingWaterPCARecord *channels[9]; // +0xAC
};

class Rva0030902ERef
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
private:
	int m_refs;
};

class Rva0030902E : public Rva0053805DBase, public Rva00330C50, public Rva003089CFList
{
public:
	virtual ~Rva0030902E();
	virtual void primary6(int) = 0;
private:
	AsciiString m_78[2];			// +0x78
	AsciiString m_80;			// +0x80
	Rva0030902ERef *m_84;			// +0x84
	bool m_88;				// +0x88
	AsciiString m_8C;			// +0x8C
	int m_90;
	int m_94;
	unsigned char *m_98;			// +0x98
	unsigned char m_pad9C[0xD4 - 0x9C];
};

Rva0030902E::~Rva0030902E()
{
	forEach(&Rva00308AA4Listener::notify00, (Rva00308AA4Owner *)this);
	if (m_98)
	{
		delete[] m_98;
		m_98 = 0;
	}
	if (m_84)
	{
		m_84->Release_Ref();
		m_84 = 0;
	}
	m_88 = true;
	((StandingWaterArea *)this)->rva003080CE();
}
