// cl: /O1 /DNDEBUG /MD
// ?rva000A9C39@Rva000A9C39@@QAEXPBVTextureBaseClass@@@Z @0x000A9C39 142B
// __thiscall UV scaler: if m_15 set or tex null dword return; fu=1.0f/(float)(unsigned)w via fdivr 1.0f; fv same; u0 u1 u2 *=fu then v0 v1 v2 *=fv with fv kept in ST0.
// Evidence: EBP frame ret4; cmp [esi+0x15] jne end; cmp [edi] je end; calls to TextureBaseClass width 0x001327D8 height 0x00132802; fild-jge-fadd 2^32-fdivr 1.0f g_Va00BBB8D8; fld-fmul-fstp order with fld st0 trick; caller at 0x000AA2C0.
class TextureBaseClass
{
public:
	int rva001327D8() const;
	int rva00132802() const;
};
class Rva000A9C39
{
public:
	void rva000A9C39(const TextureBaseClass *tex);
private:
	char _00[0x15];
	bool m_15;
	char _16[6];
	float m_u0;
	float m_v0;
	float m_u1;
	float m_v1;
	float m_u2;
	float m_v2;
};

void Rva000A9C39::rva000A9C39(const TextureBaseClass *tex)
{
	if (m_15)
		return;
	if (*(const int *)tex == 0)
		return;
	unsigned w = (unsigned)tex->rva001327D8();
	float fu = 1.0f / (float)w;
	unsigned h = (unsigned)tex->rva00132802();
	float fv = 1.0f / (float)h;
	m_15 = 1;
	m_u0 *= fu;
	m_u1 *= fu;
	m_u2 *= fu;
	m_v0 *= fv;
	m_v1 *= fv;
	m_v2 *= fv;
}
