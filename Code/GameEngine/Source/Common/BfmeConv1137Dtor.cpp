// cl: /DNDEBUG /MD /EHsc

// Both existing Release_Ref ledger names resolve to retail RVA 0x0061ED10.
// Use the same TextureClass declaration as the destination TU.
class TextureClass
{
public:
	void Release_Ref(void);
};

class BfmeTexHold1137
{
public:
	~BfmeTexHold1137(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

private:
	TextureClass *m_texture;
};

#include "../../../Libraries/Source/WWVegas/WW3D2/MaterialPassClass.h"

// Retail ctor 0x00094EBF and dtor 0x00094F38 establish the 0x38-byte
// MaterialPassClass base and four owning texture holders at +0x58..+0x64.
// UnInstall_Materials reads +0x54 and clears +0x68; retain those accesses
// while exposing the same owning members to the destructor.
class BfmeB1137 : public MaterialPassClass
{
public:
	virtual ~BfmeB1137(void);
	virtual void Install_Materials(void) const;
	virtual void UnInstall_Materials(void) const;

private:
	char m_pad38[0x1C];
	mutable volatile unsigned char m_guard54;
	char m_pad55[3];
	BfmeTexHold1137 m_tex0;
	BfmeTexHold1137 m_tex1;
	BfmeTexHold1137 m_tex2;
	BfmeTexHold1137 m_tex3;
	mutable volatile unsigned char m_clear68;
};

// ??1BfmeB1137@@UAE@XZ
BfmeB1137::~BfmeB1137(void)
{
}
