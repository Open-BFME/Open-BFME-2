// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Two sibling slots of the third base of Rva0062AF7 (vtable
// Rva0062AF7@MiBase3_62AF7), both RET 8 with the first argument unused:
//   ?rva00283C0F@Rva00283C0F@@QAEXHPAVWaterHandle@@@Z @0x00283C0F 49B
//   ?rva00283C40@Rva00283C0F@@QAEXHPAVWaterHandle@@@Z @0x00283C40 54B
// Each finds the handle's index in the +0x44 list (rowed 0x00280ADF) and
// passes it, the second biased by 0x3FFFFFFF, with a counted copy of the
// handle built in the argument slot, to the +0x40 or +0x3C list's
// 0x0028343D (not yet rowed; pinned), which takes the copy by value. No
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

class Rva00283C0F
{
public:
	void rva00283C0F(int unused, WaterHandle *handle);
	void rva00283C40(int unused, WaterHandle *handle);
private:
	unsigned char m_pad00[0x3C];
	Rva0028343D *m_3C;
	Rva0028343D *m_40;
	Rva002834C4 *m_44;
};

void Rva00283C0F::rva00283C0F(int unused, WaterHandle *handle)
{
	int index = m_44->rva00280ADF(handle);
	m_40->rva0028343D(index, WaterHandleRef(handle));
}

void Rva00283C0F::rva00283C40(int unused, WaterHandle *handle)
{
	int index = m_44->rva00280ADF(handle) + 0x3FFFFFFF;
	m_3C->rva0028343D(index, WaterHandleRef(handle));
}
