// cl: /O1 /arch:SSE
// ??0Rva00261790@@QAE@PAVArg00261790@@_N@Z, retail 0x00261790, 88 bytes.
// Filter ctor: base +4 zero via and, vtable 0x007F9000, +8/+C/+10 from arg +0x38/+0x3C/+0x40, +0x18 flag, +0x14 globalD4*const7F8FFC+argB8.
// Evidence: caller 0x00272B3E; GlobalData 0x00DFE758+0xD4 precedent TerrainLogic_setActiveBoundary; neighbours 0x00261723/0x0026185B.
extern class GlobalData *TheWritableGlobalData;

#define TheGlobalData758 (*(void **)&TheWritableGlobalData)
#define TheConst7F8FFC 0.70710677f
class Arg00261790
{
public:
	char m_pad[0x38];
	int m_38;
	int m_3C;
	int m_40;
	char m_pad44[0x74];
	float m_B8;
};
class Rva00261790
{
public:
	Rva00261790(Arg00261790 *arg, bool flag);
	Rva00261790(class Drawable *arg, bool flag);
	virtual void dummy();
private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	float m_14;
	bool m_18;
};
Rva00261790::Rva00261790(Arg00261790 *arg, bool flag) : m_04(0)
{
	m_08 = arg->m_38;
	m_0C = arg->m_3C;
	m_10 = arg->m_40;
	m_18 = flag;
	float base = arg->m_B8;
	m_14 = base;
	float g = *(float *)((char *)TheGlobalData758 + 0xD4);
	m_14 = g * TheConst7F8FFC + base;
}

// ICF-folded twin of the constructor above (same 88 bytes at 0x00261790):
// the Drawable spelling reads the same position/radius words at the same
// offsets (+0x38/+0x3C/+0x40/+0xB8) as integer bits, so every store,
// float expression and vtable setup matches exactly.
class Drawable
{
public:
	char m_pad00[0x38];
	float m_38;
	float m_3C;
	float m_40;
	char m_pad44[0xB8 - 0x44];
	float m_B8;
};

Rva00261790::Rva00261790(Drawable *drawable, bool flag) : m_04(0)
{
	m_08 = *(int *)&drawable->m_38;
	m_0C = *(int *)&drawable->m_3C;
	m_10 = *(int *)&drawable->m_40;
	m_18 = flag;
	float base = drawable->m_B8;
	m_14 = base;
	float scale = *(float *)((char *)TheGlobalData758 + 0xD4);
	m_14 = scale * TheConst7F8FFC + base;
}
// ?dummy@Rva00261790@@UAEXXZ present-unmatched
void Rva00261790::dummy() {}
