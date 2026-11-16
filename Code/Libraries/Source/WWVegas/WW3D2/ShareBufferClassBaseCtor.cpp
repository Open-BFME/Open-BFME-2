// cl: /G7 /DNDEBUG /MD /EHsc /O2 /Ob2 /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Retail's RefCountClass inline copies (Release_Ref 0x005D1A7D, scalar deleting
// dtor 0x00072899) are the size form: compile refcount.h for size, as hlod.cpp does.
#include "refcount.h"
#pragma optimize("", on)

class TextureClassPtr
{
public:
	TextureClassPtr();
	~TextureClassPtr();

private:
	unsigned int m_value;
};

class ShareBufferClassBase : public RefCountClass
{
public:
	ShareBufferClassBase(int count, const char *name, int alignment);
	virtual ~ShareBufferClassBase();

private:
	TextureClassPtr *m_rawBuffer;
	TextureClassPtr *m_array;
	int m_count;
	int m_alignment;
};

ShareBufferClassBase::ShareBufferClassBase(int count, const char *name, int alignment)
	: m_count(count),
		m_alignment(alignment)
{
	if (m_alignment == 0) {
		m_rawBuffer = MSGW3DNEWARRAY(name) TextureClassPtr[m_count];
		m_array = m_rawBuffer;
	} else {
		m_rawBuffer = reinterpret_cast<TextureClassPtr *>(
			MSGW3DNEWARRAY(name) char[m_count * sizeof(TextureClassPtr) + m_alignment]);
		m_array = reinterpret_cast<TextureClassPtr *>(
			(reinterpret_cast<unsigned int>(m_rawBuffer) + m_alignment - 1) & ~(m_alignment - 1));
	}
}

// ??1ShareBufferClassBase@@UAE@XZ present-unmatched
ShareBufferClassBase::~ShareBufferClassBase()
{
}
