// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
// ?rva000EA24D@W3DTreeBuffer@@QAEXXZ 0x000EA24D 115B
// Reset after Rva000E6AC0::rva000E65B1: DX8 lock, zero count at +0x44540,
// set dirty at +0x44544, release 0x40 RefItem array at +0x44558 stride 0x5C
// (dec ref at +4, virtual Release on zero), zero tail at +0x45C58.
// Evidence: calls rowed rva000E65B1; callees rowed; count/dirty offsets match
// Rva000EA21A neighbour; callers at 0x000682A2 0x0006D5C0 0x000EDEBE (the
// W3DTreeBuffer ctor, on its own this; offsets match its +0x44540 count and
// +0x44558 type array, past the Rva000E6AC0 base).

#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeRecord.h"
#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeTypeRecord.h"

void BFME_DX8_Thread_Lock(void);
bool BFME_DX8_Thread_Assert(void);

class Rva000E6AC0Base
{
public:
	Rva000E6AC0Base() {}
	virtual ~Rva000E6AC0Base() {}
};

class TextureClass;

template <class T> class RefCountPtr;
template <> class RefCountPtr<TextureClass>
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
	TextureClass *Ptr;
};
class Rva000E6AC0 : public Rva000E6AC0Base
{
public:
	Rva000E6AC0();
	void rva000E65B1();
	virtual ~Rva000E6AC0();
private:
	unsigned char m_storage[0x38 - 4]; // +0x04
protected:
	RefCountPtr<TextureClass> texture38, texture3c; // +0x38
	char list40[0x28], list68[0x28]; // +0x40
private:
	unsigned char m_pad90[0x5BC - 0x90];
protected:
	float m_sinkScale; // +0x5BC
};

class Rva000EBFD1Model;

class Rva000EDA94Ref
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
	Rva000EBFD1Model *Peek_Model(void) const { return m_model; }
private:
	// Reconcile the seed's existing count-at-4 and virtual slot 0 with
	// this body's existing model-at-C4 view; neither offset changes.
	int m_refs;
	unsigned char m_pad08[0xc4 - 8];
	Rva000EBFD1Model *m_model;
};

class Rva0052413E
{
public:
	Rva0052413E() throw();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

struct TTree;

class W3DTreeBuffer : public Rva000E6AC0
{
	friend class Rva000EC9C6;
protected:
	void updateTexture();
	void updateTopplingTree(TTree *tree);
public:
	W3DTreeBuffer();
public:
	void rva000EA24D();
private:
	Rva000EDA94Record m_records[1200];
private:
	int m_count;
private:
	unsigned char m_44544;
private:
	unsigned char m_44545; // +0x44545
private:
	unsigned char m_44546;
private:
	unsigned char m_44547;
private:
	Rva0052413E m_objects;
private:
	unsigned char m_44554;
private:
	unsigned char m_44555;
private:
	unsigned char m_44556;
private:
	unsigned char m_44557;
private:
	Rva000EC67F m_types[64]; // +0x44558
private:
	int m_typeCount;
private:
	int m_45c5c; // +0x45C5C
private:
	int m_45c60;
private:
	unsigned char m_45c64;
public:
	bool rva000EA48D(void *key, const Coord3D *direction, float height);
	bool rva000EA644(void *key);
	void rva000EA2C0(void *key);
	bool rva000EA6A7(void *key);
	void rva000EB2EF(int index);
	void rva000EB0E6(int index);
	bool rva000ECF2A(unsigned key, int mode);
	void startMorph(int index, int mode);
	int addTreeType(const AsciiString &modelName, const AsciiString &nameC, const void *data, int shadowKind,
		const AsciiString &textureName, const AsciiString &templateName);
	int rva000ECDF5(const AsciiString &templateName, int shadowKind, const AsciiString &textureName);
};

struct DX8Guard
{
	DX8Guard() { BFME_DX8_Thread_Lock(); }
	~DX8Guard() { BFME_DX8_Thread_Assert(); }
};

void W3DTreeBuffer::rva000EA24D()
{
	DX8Guard _guard;
	((Rva000E6AC0 *)this)->rva000E65B1();
	m_count = 0;
	m_44544 = 1;
	for (int i = 0; i < 0x40; ++i)
	{
		Rva000EDA94Ref *&slot = m_types[i].m_ref;
		Rva000EDA94Ref *refItem = slot;
		if (refItem != 0)
		{
			refItem->Release_Ref();
			slot = 0;
		}
	}
	m_typeCount = 0;
}
