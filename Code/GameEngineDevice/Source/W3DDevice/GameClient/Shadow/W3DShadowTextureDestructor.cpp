// cl: /DNDEBUG /MD /EHsc -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// Retail 0x007AF4E0: W3DShadowTexture::~W3DShadowTexture.
//
// The BFME layout keeps the texture reference at +0x30 after the two
// eight-byte RefCountClass/HashableClass bases and the 32-byte name buffer.

class TextureClass
{
public:
	void Release_Ref(void);
};

class RefCountClass
{
public:
	virtual void Delete_This(void);

protected:
	virtual ~RefCountClass(void) {}

private:
	int m_refs;
};

#include "../../../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"

class W3DShadowTexture : public RefCountClass, public HashableClass
{
public:
	~W3DShadowTexture(void);
	virtual const char *Get_Key(void); // W3DShadowTextureCtor.cpp

private:
	char m_namebuf[32];
	TextureClass *m_texture;
};

W3DShadowTexture::~W3DShadowTexture(void)
{
	if (m_texture)
		m_texture->Release_Ref();
}
