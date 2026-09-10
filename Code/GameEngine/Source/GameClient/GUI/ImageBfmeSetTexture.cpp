// cl: /O1 /DNDEBUG /MD
//
// Image::bfmeSetTexture, retail 0x002D905E, 47 bytes.
// Dedicated TU so AptMapPreviewPictureImage.cpp cannot see this body.
// Allocates a 4-byte holder at this+0x2C if missing then copy-assigns into it.

typedef unsigned int size_t;
void *__cdecl operator new(size_t);

class BfmeMapPictureTexture
{
	void *m_ptr;

public:
	BfmeMapPictureTexture() : m_ptr(0) {}
	BfmeMapPictureTexture &operator=(const BfmeMapPictureTexture &that);
};

class Image
{
public:
	virtual ~Image();
	void bfmeSetTexture(const BfmeMapPictureTexture &texture);

private:
	char pad[0x28];
	BfmeMapPictureTexture *m_texture;
};

void Image::bfmeSetTexture(const BfmeMapPictureTexture &texture)
{
	if (!m_texture)
		m_texture = new BfmeMapPictureTexture;
	*m_texture = texture;
}
