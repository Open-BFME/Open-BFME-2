// cl: /Oy /DNDEBUG /MD /EHsc
//
// ?Get_Texture_Name@BFME2ParticleTextureHandle@@QBE?AVStringClass@@XZ,
// retail 0x00129D30, 176 bytes. Dedicated TU so no other unit can see these
// bodies (cf. the ParticleEmitterGetTexture TU).
//
// BFME1 donor: Code/Libraries/Source/WWVegas/WW3D2/TextureHandleGetName.cpp
// (BfmeHandleCX::Get_Texture_Name, matched 231B). BFME2 keeps the null-guarded
// slot-0 virtual name but stages it through the StringClass(const char *, bool)
// 2-arg initializer (row 8729, wwstring_ctor_pbd_bool.cpp) INLINED here:
// empty-init from m_EmptyString, inline strlen, Get_String pre-size, assign,
// then copy to the by-value return slot and Free_String the local. The inline
// context lets the scheduler test the guarded name before the empty store.

#include <string.h>

class BFME2ParticleTextureHandle;

class StringClass
{
	friend class BFME2ParticleTextureHandle;
public:
	StringClass(const char *name, bool flag);
	enum InlineNativeCopy { COPY_NATIVE };
	__forceinline StringClass(const char *name, bool flag, InlineNativeCopy);
	StringClass(const StringClass &that, bool hint_temporary = false);
	__forceinline ~StringClass(void) { Free_String(); }
	const StringClass &operator=(const char *string);


private:
	static char *m_EmptyString;
	void Get_String(int new_len, bool flag);
	void Free_String(void);

	char *m_Buffer;
};

// StringClass::m_EmptyString: defined in wwstring.cpp (= &m_NullChar).

// Preserve the donor initializer expansion in Get_Texture_Name; ordinary
// construction calls the existing public constructor.
__forceinline StringClass::StringClass(const char *name, bool flag, InlineNativeCopy)
{
	int len;

	m_Buffer = m_EmptyString;
	if (name != 0)
		len = (int)strlen(name);
	else
		len = 0;
	if (flag || len > 0)
		Get_String(len + 1, flag);
	*this = name;
}

class TextureClass
{
public:
	virtual const char *Get_Name(void) const = 0;
};

class BFME2ParticleTextureHandle
{
	TextureClass *Ptr;

public:
	StringClass Get_Texture_Name(void) const;
};

// ?Get_Texture_Name@BFME2ParticleTextureHandle@@QBE?AVStringClass@@XZ
StringClass BFME2ParticleTextureHandle::Get_Texture_Name(void) const
{
	const char *name;

	if (Ptr != NULL)
		name = Ptr->Get_Name();
	else
		name = NULL;

	StringClass result(name, false, StringClass::COPY_NATIVE);
	return result;
}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
