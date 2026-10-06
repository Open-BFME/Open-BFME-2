// cl: /DNDEBUG /MD /Ob2
// Readable out-of-line body of ??0TexBufferClass@@QAE@ABV0@@Z (retail 0x0015D0C0, 25B).
// Retail's copy forwards to the ShareBufferClass base copy only: unlike the
// ZH/BFME1 reference copy it keeps no per-element Add_Ref loop, so this TU
// carries the retail shape instead of reusing meshmatdesc.cpp's looped copy
// (which cannot take the row). Base-copy address pinned from the retail call.

class TextureClass;

template <class T>
class ShareBufferClass
{
public:
	ShareBufferClass(const ShareBufferClass & that);
	virtual ~ShareBufferClass();
};

class TexBufferClass : public ShareBufferClass<TextureClass *>
{
public:
	TexBufferClass(const TexBufferClass & that);
};

// ??0TexBufferClass@@QAE@ABV0@@Z
TexBufferClass::TexBufferClass(const TexBufferClass & that)
	: ShareBufferClass<TextureClass *>(that)
{
}
