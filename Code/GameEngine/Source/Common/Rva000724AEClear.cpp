// cl: /MD
// ?rva000724AE@Rva000724AE@@QAEXXZ, RVA 0x000724AE, 25B. Triple clear: call
// rowed cleanup@Rva00739C70 on +0x00 then clear@BfmeResetTextureRef on +0x08
// then tail-jump to rva000723AC@W3DRadarResetSurface on +0x0c. Evidence:
// chain from just-landed 0x723AC; callers at 0x7259D/0x7262D/0x72697 pass
// W3DVideoBuffer+0x2c; layout matches Rva00739C70State 0x14-byte shape in
// W3DVideoBufferCtorBfme.cpp (+8 texture ref +0xc surface +0x10 flags).
class Rva00739C70
{
public:
	void cleanup();
private:
	int m_00;
	int m_04;
};
struct BfmeResetTextureRef
{
	void clear();
private:
	void *m_ptr;
};
class W3DRadarResetSurface
{
public:
	void rva000723AC();
private:
	void *m_surface;
};
class Rva000724AE
{
public:
	void rva000724AE();
private:
	Rva00739C70 m_00;
	BfmeResetTextureRef m_08;
	W3DRadarResetSurface m_0c;
};
void Rva000724AE::rva000724AE()
{
	m_00.cleanup();
	m_08.clear();
	m_0c.rva000723AC();
}
