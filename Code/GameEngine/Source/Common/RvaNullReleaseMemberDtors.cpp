// cl: /O1 /EHs /MD
//
// Destructors whose only nontrivial member is a null-checked owning pointer
// released through an already-rowed callee (both bodies are 13B: load the
// member and when set tail-jump to the release).
//
// ??1Rva000FC5AADtor@@QAE@XZ @0x000FC5AA: existing pin (target of thunks
// 0x007B6F08 and 0x007B6F12); member +0x08 released via TextureClass::Release_Ref.
// ??1BfmeVectorRecord002AF478@@QAE@XZ @0x005EA85F: existing pin (callers
// 0x005EA96E and 0x005EAA8C); member +0x20 released via the fastcall
// ReleaseTreeHintRef00217D4C. Owner layouts are otherwise unknown.

class TextureClass
{
public:
	void Release_Ref();
};

class Rva000FC5AADtor
{
public:
	~Rva000FC5AADtor();

private:
	char m_pad00[0x8];
	TextureClass *m_texture;
};

Rva000FC5AADtor::~Rva000FC5AADtor()
{
	if (m_texture)
		m_texture->Release_Ref();
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class BfmeVectorRecord002AF478
{
public:
	~BfmeVectorRecord002AF478();

private:
	char m_pad00[0x20];
	TargetRef00217D4C *m_ref;
};

BfmeVectorRecord002AF478::~BfmeVectorRecord002AF478()
{
	if (m_ref)
		ReleaseTreeHintRef00217D4C(m_ref);
}
