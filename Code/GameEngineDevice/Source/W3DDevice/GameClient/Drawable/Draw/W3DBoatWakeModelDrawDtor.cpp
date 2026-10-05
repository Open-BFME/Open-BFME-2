// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1W3DBoatWakeModelDraw@@UAE@XZ, retail 0x000D0B69, 90 bytes, and the
// registry removal it calls, retail 0x00082C88, 16 bytes.
//
// Identity: the rowed ??_GW3DBoatWakeModelDraw 0x000D0D08 calls 0x000D0B69,
// whose entry store is the vtable 0x00BCDD70 the rowed ctor 0x000D0B34
// installs. The body unregisters the draw from the host held at +0x18
// (0x00082C88 erases the draw's key from the int-keyed tree at host+0x58
// through the rowed erase-by-key 0x00082536), releases the ref-counted
// object at +0x14 (RefCountClass::Release_Ref inlined: --NumRefs at +4,
// Delete_This through slot 0, then the pointer cleared) and falls to the
// inline DrawModule dtor (vptr 0x00BC9690) and the pinned DrawableModule
// dtor 0x0049B47C, as in W3DLaserDrawDestructor.cpp. The host's identity
// is unproven, so it keeps an address name.

class RefCountClass
{
public:
	virtual void Delete_This();

	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

private:
	int NumRefs; // +0x04
};

class Rva0007E971
{
public:
	unsigned int rva00082536(const int &key);

private:
	unsigned char m_pad[0x0C];
};

class Rva00082C88Host
{
public:
	void rva00082C88(int key);

private:
	unsigned char m_pad00[0x58];
	Rva0007E971 m_registry; // +0x58
};

void Rva00082C88Host::rva00082C88(int key)
{
	m_registry.rva00082536(key);
}

class DrawableModule
{
protected:
	virtual ~DrawableModule();

	const void *m_moduleData; // +0x04
	int m_bfmeField; // +0x08
};

class DrawModule : public DrawableModule
{
protected:
	virtual ~DrawModule() {}
};

class W3DBoatWakeModelDraw : public DrawModule
{
public:
	virtual ~W3DBoatWakeModelDraw();

private:
	float m_0C;
	bool m_flag10;
	RefCountClass *m_14;
	Rva00082C88Host *m_18;
};

W3DBoatWakeModelDraw::~W3DBoatWakeModelDraw()
{
	if (m_18)
		m_18->rva00082C88((int)this);
	if (m_14)
	{
		m_14->Release_Ref();
		m_14 = 0;
	}
}
