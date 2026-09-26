// cl: /O1 /EHsc /DNDEBUG /MD
//
// Image::~Image, retail 0x002D91CC (94B) plus its scalar deleting
// destructor 0x002D9262 (28B).
//
// Member layout follows the proven ImageCtor TU in this directory
// (vptr 0xC037B8; m_name +0x04; m_filename +0x08; texture size +0x0C;
// UV coords +0x14; image size +0x24; texture holder +0x2C;
// m_status +0x30). The +0x2C holder is the 4-byte BfmeMapPictureTexture
// allocation from Image::bfmeSetTexture in this directory: its first
// word is the TextureBaseClass whose Release_Ref is the rowed release
// body at 0x61ED10, then the holder itself is freed.
//
// Shape notes, all read off retail:
// - A named holder local keeps the holder in edi across the Release
//   call; a bare member re-read uses eax plus a reload and misses.
// - The filename (+0x08) and name (+0x04) destructions are the implicit
//   member teardown in reverse declaration order through the rowed
//   AsciiString pin at 0x36410; the holder block runs under EH state 1.

typedef unsigned int size_t;
void *__cdecl operator new(size_t);
void __cdecl operator delete(void *);

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

struct ICoord2D
{
	int x;
	int y;
};

struct Coord2D
{
	float x;
	float y;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

struct BfmeMapPictureTexture
{
	TextureBaseClass *m_texture;
};

class Image
{
public:
	virtual ~Image();

private:
	AsciiString m_name;
	AsciiString m_filename;
	ICoord2D m_textureSize;
	Region2D m_UVCoords;
	ICoord2D m_imageSize;
	BfmeMapPictureTexture *m_texture;
	unsigned int m_status;
};

// ??1Image@@UAE@XZ, retail 0x002D91CC (94B).
Image::~Image()
{
	BfmeMapPictureTexture *holder = m_texture;
	if (holder) {
		if (holder->m_texture)
			holder->m_texture->Release_Ref();
		delete holder;
	}
}
