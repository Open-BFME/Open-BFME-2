// cl: /O1 /DNDEBUG /MD /EHsc
// ??0RenderableRiverArea@@QAE@PAX@Z, retail 0x00083547..0x000835D0 (137 bytes,
// EH, RET 4; callers 0x000837F1 and 0x00083959). Over the rowed water-area
// base (0x00082EF5, two table pointers at +0 and +8) and an observer base at
// +0x3C it keeps its owner at +0x40, four texture references at +0x44
// (RefCountPtr<TextureClass>, built and unwound through the EH vector
// iterators), a cleared +0x54 member (destructor 0x0007B724) and a set
// +0x58 flag, then registers its observer in the owner's +0x30 list and
// runs the rowed RenderableRiverArea 0x00082061. Each base and member
// destructor is the retail unwind action; the observer and member keep their
// address-derived names.
class TextureClass;
template <class T> class RefCountPtr
{
public:
	RefCountPtr();
	~RefCountPtr();
private:
	T *m_ptr;
};

class Rva00082EF5Base1
{
public:
	virtual ~Rva00082EF5Base1();
	int m_04;
};
class Rva00082EF5Second
{
public:
	virtual ~Rva00082EF5Second();
	unsigned char m_pad04[0x3c - 0x0c];
};
class Rva00082EF5 : public Rva00082EF5Base1, public Rva00082EF5Second
{
public:
	Rva00082EF5(void *owner);		// 0x00082EF5
	virtual ~Rva00082EF5();			// 0x00081C7F
};

class Rva0081FDDSecond
{
public:
	Rva0081FDDSecond() {}
	virtual ~Rva0081FDDSecond() {}			// 0x0007DE9A
};

class Rva00087A93
{
public:
	Rva00087A93() : m_value(0) {}
	~Rva00087A93();					// 0x0007B724
private:
	int m_value;
};

struct Rva002BA8F1Listener;
#include "../../../../Include/Common/Rva005A0B4CList.h"
struct RenderableRiverAreaOwner
{
	unsigned char m_pad00[0x30];
	Rva005A0B4CList m_observers;	// +0x30
};

class RenderableRiverArea : public Rva00082EF5, public Rva0081FDDSecond
{
public:
	RenderableRiverArea(void *owner);
	virtual ~RenderableRiverArea();
	void rva00082061();				// 0x00082061
private:
	RenderableRiverAreaOwner *m_owner;	// +0x40
	RefCountPtr<TextureClass> m_textures[4];	// +0x44
	Rva00087A93 m_54;				// +0x54
	bool m_58;						// +0x58
};

RenderableRiverArea::RenderableRiverArea(void *owner)
	: Rva00082EF5(owner), m_owner((RenderableRiverAreaOwner *)owner)
{
	m_58 = true;
	((RenderableRiverAreaOwner *)owner)->m_observers.append((Rva002BA8F1Listener *)static_cast<Rva0081FDDSecond *>(this));
	rva00082061();
}
