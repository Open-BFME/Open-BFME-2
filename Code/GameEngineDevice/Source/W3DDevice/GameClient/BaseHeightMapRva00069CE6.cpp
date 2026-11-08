// cl: /D_OPERATOR_NEW_DEFINED_ /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva00069CE6@BaseHeightMapRenderObjClass@@QAEXABVRva000E3A8D@@H@Z
// retail 0x00069CE6..0x00069DB1 (203 bytes) thiscall ret 8; slot 91 of
// the terrain render-object vtable at 0x007C5E5C (WB 0x0075DFD0 by vtable).
// With a map (+0x37C0) a non-empty update list (first argument: begin and
// end words compared) and no update in progress (+0x37C5): the three list
// receivers at +0x3850/+0x3854/+0x3858 copy the list (rowed setters
// 0x000EDF23 / 0x000E9CFB / 0x000EF137) the busy byte is set the road
// buffer (+0x386C) gets the rowed byte-one setter 0x000D4A7C; when +0x37D4
// is set the bridge buffer (+0x3870) +0xD7B5 and the +0x3860 buffer +0x21
// bytes are raised; then the bridge buffer runs the rowed 0x000DF745 with
// the list and the second argument and the +0x3860 buffer the rowed
// 0x000E585A with the list; finally the busy byte is cleared. Callee row
// spellings are placeholders so the list address is passed through casts.
// Road and bridge buffer offsets agree with BaseHeightMapLoadRoadsAndBridges.cpp.
class Rva000E3A8D
{
public:
	bool isEmpty() const { return m_begin == m_end; }

private:
	int *m_begin;
	int *m_end;
	int *m_capacity;
};

class Rva000EDF23
{
public:
	void rva000EDF23(const Rva000E3A8D &other);
};

class Rva000E9BAC
{
public:
	void rva000E9CFB(const Rva000E3A8D &other);
};

class Rva000EF137
{
public:
	void rva000EF137(const Rva000E3A8D &other);
};

class Rva000D4A7COneSetter
{
public:
	void enable();
};

class W3DBridgeBuffer
{
public:
	void rva000DF745(int first, int second);

	char m_pad0000[0xD7B5];
	unsigned char m_d7b5;
};

class Rva000E488F;

class Rva000E585A
{
public:
	void rva000E585A(Rva000E488F *arg);

	char m_pad00[0x21];
	unsigned char m_21;
};

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// The header types the receivers only by their buffer classes; this body
// reaches them through the rowed placeholder spellings of their setters.
template<class View, class Field>
static __forceinline View *bufferView(Field *field)
{
	return reinterpret_cast<View *>(field);
}

void BaseHeightMapRenderObjClass::rva00069CE6(const Rva000E3A8D &list, int arg)
{
	if (m_map == 0)
		return;
	if (list.isEmpty())
		return;
	if (m_updating)
		return;
	if (m_treeBuffer)
		bufferView<Rva000EDF23>(m_treeBuffer)->rva000EDF23(list);
	if (m_shrubBuffer)
		bufferView<Rva000E9BAC>(m_shrubBuffer)->rva000E9CFB(list);
	if (m_propBuffer)
		bufferView<Rva000EF137>(m_propBuffer)->rva000EF137(list);
	m_updating = true;
	if (m_roadBuffer)
		bufferView<Rva000D4A7COneSetter>(m_roadBuffer)->enable();
	if (m_disableTextures) {
		if (m_bridgeBuffer)
			m_bridgeBuffer->m_d7b5 = 1;
		if (field3860)
			bufferView<Rva000E585A>(field3860)->m_21 = 1;
	}
	if (m_bridgeBuffer)
		m_bridgeBuffer->rva000DF745((int)&list, arg);
	if (field3860)
		bufferView<Rva000E585A>(field3860)->rva000E585A((Rva000E488F *)&list);
	m_updating = false;
}
