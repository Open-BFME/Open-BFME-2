// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class TextureClass : public TextureBaseClass
{
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

class BfmeB1137 : public MaterialPassClass
{
public:
	virtual ~BfmeB1137(void);
	virtual void Install_Materials(void) const;
	virtual void UnInstall_Materials(void) const;

private:
	// MaterialPassClass occupies +0x00..+0x37; texture holders start at +0x58.
	unsigned char m_unmodelled[0x20];
	BfmeTexHold1137 m_tex0;
	BfmeTexHold1137 m_tex1;
	BfmeTexHold1137 m_tex2;
	BfmeTexHold1137 m_tex3;
};

// ??1BfmeB1137@@UAE@XZ
BfmeB1137::~BfmeB1137(void)
{
}
