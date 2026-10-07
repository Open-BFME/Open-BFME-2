// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BfmeB1137's virtual material-pass cleanup at retail 0x006E1EB0.
// The constructor/destructor neighbors install vtable 0x00D1E23C; slot 3 is
// this body.  Its witnessed fields are the guard byte at +0x54 and the byte
// cleared at +0x68.  The state-cache and device names below are TU-local ABI
// shims; DIR32 relocation verification supplies their retail addresses.

class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureBaseClass;

class StageTextureRef
{
	TextureClass *Texture;

public:
	StageTextureRef(void) : Texture(0) {}
	~StageTextureRef(void)
	{
		if (Texture)
			Texture->Release_Ref();
	}
	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&Texture;
	}
};

void BoxSetTexture(unsigned int stage, TextureBaseClass *&texture);

class StringClass
{
	char *m_Buffer;
	static char *m_EmptyString;
	static char m_NullChar;

	void Get_String(int length, bool temporary);
	void Free_String(void);

public:
#pragma optimize("t", off)
#pragma optimize("s", on)

	StringClass(int length, bool temporary) : m_Buffer(m_EmptyString)
	{
		Get_String(length, temporary);
		m_Buffer[0] = m_NullChar;
	}
#pragma optimize("", on)

	__forceinline ~StringClass(void) { Free_String(); }
};

struct Device;
struct DeviceVtable
{
	char m_pad[0x10c];
	int (__stdcall *SetTextureStageState)(Device *, unsigned int,
		unsigned long, unsigned int);
};
struct Device
{
	DeviceVtable *v;
};

extern Device *ScreenDevice;
extern unsigned ScreenTextureStageStates[8][32];
extern bool ScreenSnapshot;
// ?ScreenSnapshot@@3_NA: the global at this VA is ?SnapshotActivated@WW3D@@0_NA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?ScreenSnapshot@@3_NA=?SnapshotActivated@WW3D@@0_NA")
extern unsigned number_of_DX8_calls;
extern unsigned ScreenTextureStageStateChanges;
// ?ScreenTextureStageStateChanges@@3IA: the global at this VA is ?texture_stage_state_changes@DX8Wrapper@@1IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?ScreenTextureStageStateChanges@@3IA=?texture_stage_state_changes@DX8Wrapper@@1IA")

class DX8Wrapper
{
public:
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &,
		unsigned long, unsigned int);

	static __forceinline void Set_DX8_Texture_Stage_State(unsigned int stage,
		unsigned long state, unsigned int value)
	{
		if (stage >= 8)
		{
			ScreenDevice->v->SetTextureStageState(ScreenDevice, stage, state, value);
			++number_of_DX8_calls;
			return;
		}
		if (ScreenTextureStageStates[stage][state] == value)
			return;
		if (ScreenSnapshot)
		{
			StringClass name(0, true);
			Get_DX8_Texture_Stage_State_Value_Name(name, state, value);
		}
		ScreenTextureStageStates[stage][state] = value;
		ScreenDevice->v->SetTextureStageState(ScreenDevice, stage, state, value);
		++number_of_DX8_calls;
		++ScreenTextureStageStateChanges;
	}
};

class BfmeB1137
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void UnInstall_Materials(void) const;

private:
	char m_pad04[0x50];
	mutable volatile unsigned char m_guard54;
	char m_pad55[0x13];
	mutable volatile unsigned char m_clear68;
};

// ?UnInstall_Materials@BfmeB1137@@UBEXXZ
void BfmeB1137::UnInstall_Materials(void) const
{
	if (!m_guard54)
		return;

	m_clear68 = 0;
	{
		StageTextureRef texture;
		BoxSetTexture(0, texture);
	}
	{
		StageTextureRef texture;
		BoxSetTexture(1, texture);
	}

	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 0x0b, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 0x18, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 0x0b, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 0x18, 0);
}
// ?ScreenDevice@@3PAUDevice@@A: the global at VA 0xdeda34 is ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A.
#pragma comment(linker, "/alternatename:?ScreenDevice@@3PAUDevice@@A=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")
// ?ScreenTextureStageStates@@3PAY0CA@IA: the global at VA 0xdeca38 is ?TextureStageStates@DX8Wrapper@@1PAY0CA@IA.
#pragma comment(linker, "/alternatename:?ScreenTextureStageStates@@3PAY0CA@IA=?TextureStageStates@DX8Wrapper@@1PAY0CA@IA")

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
