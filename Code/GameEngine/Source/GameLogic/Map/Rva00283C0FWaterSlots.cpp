// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Native BC5848/BC5838 slot1 identifies these structural listener views.
// Each listener is one vptr; field offsets below are relative to its entry.
// Two sibling slots of the third base of W3DTerrainLogic (vtable
// W3DTerrainLogic@MiBase3_62AF7), both RET 8 with the first argument unused:
//   ?vslot1@TerrainLogicListenerA@@UAEXHPAVWaterHandle@@@Z @0x00283C0F 49B
//   ?vslot1@TerrainLogicListenerB@@UAEXHPAVWaterHandle@@@Z @0x00283C40 54B
// Each finds the handle's index in the +0x44 list (rowed 0x00280ADF) and
// passes it, the second biased by 0x3FFFFFFF, with a counted copy of the
// handle built in the argument slot, to the +0x40 or +0x3C list's
// 0x0028343D (now rowed), which takes the copy by value. No
// WorldBuilder names are matched.

class WaterHandle
{
public:
	virtual void w0();
	int m_refs;							// +0x04
};

class WaterHandleRef
{
public:
	WaterHandleRef(WaterHandle *handle) : m_handle(handle) { if (handle) ++handle->m_refs; }
	WaterHandleRef(const WaterHandleRef &other);
	~WaterHandleRef();
private:
	WaterHandle *m_handle;
};

class Rva002834C4
{
public:
	int rva00280ADF(const WaterHandle *handle);
};

class Rva0028343D
{
public:
	void rva0028343D(int index, WaterHandleRef handle);
};

// Root tables BC6F34: empty RET4 followed by three pure callbacks.

class TerrainLogicListenerRootA {
public:
 virtual void vslot0(int);
 virtual void vslot1(int, WaterHandle *) = 0;
 virtual void vslot2(void *, void *) = 0;
 virtual void vslot3(void *, void *) = 0;
 ~TerrainLogicListenerRootA() {}
};
class TerrainLogicListenerA : public TerrainLogicListenerRootA {
public:
 virtual void vslot1(int, WaterHandle *);
 virtual void vslot3(void *, void *);
 ~TerrainLogicListenerA();
};
class TerrainLogicListenerRootB {
public:
 virtual void vslot0(int);
 virtual void vslot1(int, WaterHandle *) = 0;
 virtual void vslot2(void *, void *) = 0;
 virtual void vslot3(void *, void *) = 0;
 ~TerrainLogicListenerRootB() {}
};
class TerrainLogicListenerB : public TerrainLogicListenerRootB {
public:
 virtual void vslot1(int, WaterHandle *);
 virtual void vslot3(void *, void *);
 ~TerrainLogicListenerB();
};

struct TerrainListenerWaterFields
{
 unsigned char pad[0x3C];
 Rva0028343D *m_3C;
 Rva0028343D *m_40;
 Rva002834C4 *m_44;
};

void TerrainLogicListenerA::vslot1(int unused, WaterHandle *handle)
{
	int index = reinterpret_cast<TerrainListenerWaterFields *>(this)->m_44->rva00280ADF(handle);
	reinterpret_cast<TerrainListenerWaterFields *>(this)->m_40->rva0028343D(index, WaterHandleRef(handle));
}

void TerrainLogicListenerB::vslot1(int unused, WaterHandle *handle)
{
	int index = reinterpret_cast<TerrainListenerWaterFields *>(this)->m_44->rva00280ADF(handle) + 0x3FFFFFFF;
	reinterpret_cast<TerrainListenerWaterFields *>(this)->m_3C->rva0028343D(index, WaterHandleRef(handle));
}
