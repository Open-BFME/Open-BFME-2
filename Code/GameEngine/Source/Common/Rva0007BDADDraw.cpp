// cl: /MD
//
// ?rva0007BDAD@Rva0007BDAD@@QAEXXZ @ 0x0007BDAD (113B):
// __thiscall texture-list draw: validates list at +0x24, queries count via
// slot 2 Get(&count, 0xFFFF), iterates with slot 3 Select(i), binds
// BFME2Set_Texture stage 0 from TextureBaseClass at +0x14, draws extents via
// rowed rva00132784/rva0013275A and rowed Rva00075A23Draw, advancing with
// slot 5 and releasing with slot 6. Class honest-address (caller 0x0007DC01
// unclaimed); interface slots from retail offsets +8/+C/+14/+18.
// Evidence: rowed BFME2Set_Texture 0x0011F4B0, rowed Texture getters
// 0x00132784/0x0013275A, rowed Draw 0x00075A23; neighbours share // cl: /O1 /MD.
class TextureBaseClass
{
public:
	int rva00132784() const;
	int rva0013275A() const;
};

struct BFME2TextureRef
{
	void *Ptr;
};

void __cdecl BFME2Set_Texture(unsigned int stage, const struct BFME2TextureRef &texture);
void __cdecl Rva00075A23Draw(int a, int b);

class Rva0007BDADList
{
public:
	virtual void v0();
	virtual void v1();
	virtual bool GetCount(int *count, int param);
	virtual void Select(int index);
	virtual void v4();
	virtual void Advance();
	virtual void Release();
};

class Rva0007BDAD
{
public:
	void rva0007BDAD();
private:
	char m_pad00[0x14];
	TextureBaseClass m_tex14;
	char m_pad18[0xC];
	Rva0007BDADList *m_list24;
};

void Rva0007BDAD::rva0007BDAD()
{
	Rva0007BDADList *list = m_list24;
	if (list == 0)
		return;
	int count;
	if (!list->GetCount(&count, 0xFFFF))
		return;
	for (int i = 0; i < count; ++i) {
		m_list24->Select(i);
		BFME2Set_Texture(0, reinterpret_cast<const struct BFME2TextureRef &>(m_tex14));
		Rva00075A23Draw(m_tex14.rva0013275A(), m_tex14.rva00132784());
		m_list24->Advance();
	}
	m_list24->Release();
}
