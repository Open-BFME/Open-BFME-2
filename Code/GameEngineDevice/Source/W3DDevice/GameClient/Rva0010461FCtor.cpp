// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ??0Rva0010461F@@QAE@XZ retail 0x0010461F..0x00104723 (260 bytes EH).
// Constructor of the 0x88-byte object the factory 0x0008F32C creates and
// stores in TheRva002D3627Host (0x009FF028). Base is Rva002D3573 (ctor
// 0x002D638E; MI with vtables at +0 and +0xC; WB names the base
// Palantir::Palantir as a lead only); this class stores vtables 0x00BCF770
// and 0x00BCF760. Members: three zeroed words (+0x14) the mapped image
// "RadarViewBoxEdge" looked up through TheMappedImageCollection
// (findImageByName 0x002D92F6) a texture slot (+0x24; assignment 0x000424D0)
// and three Coord2D[4] arrays (+0x28 +0x48 +0x68) built by the eh vector
// constructor iterator with the exported Coord2D ctor/dtor. When the image
// exists its name is loaded through BFME2LoadParticleTexture 0x00132D89
// and stored in the slot; the returned handle releases its texture
// (0x0061ED10). The unwind funclet also destroys the slot (its destructor is
// declared only). Class and member names are unresolved.
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "BFME2ParticleTextureHandles.h"

// class-gate: allow Coord2D the element ctor 0x0047A6A9 and dtor 0x000B3FD0 run through the eh vector constructor iterator; BFME 2's Coord2D exports both (rowed ??0Coord2D@@QAE@XZ / ??1Coord2D@@QAE@XZ) and the canonical data-only header declares neither
class Coord2D
{
public:
	Coord2D();
	~Coord2D();

	float x;
	float y;
};

class Image
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad00[8];
	AsciiString m_name; // +0x08
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);

struct CursorTextureSlot
{
	CursorTextureSlot() : Ptr(0) {}
	~CursorTextureSlot();
	void operator=(const BFME2ParticleTextureHandle &handle);
	void *Ptr;
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Rva002D3573 : public GameEngineDeletingBase, public Snapshot
{
public:
	Rva002D3573();
	virtual ~Rva002D3573();

private:
	void *m_holder; // +0x10
};

class Rva0010461F : public Rva002D3573
{
public:
	Rva0010461F();
	virtual ~Rva0010461F();

private:
	int m_14;
	int m_18;
	int m_1C;
	const Image *m_edgeImage; // +0x20
	CursorTextureSlot m_edgeTexture; // +0x24
	Coord2D m_28[4];
	Coord2D m_48[4];
	Coord2D m_68[4];
};

Rva0010461F::Rva0010461F()
	: m_14(0), m_18(0), m_1C(0),
	  m_edgeImage(TheMappedImageCollection->findImageByName(AsciiString("RadarViewBoxEdge")))
{
	if (m_edgeImage != 0)
		m_edgeTexture = BFME2LoadParticleTexture(m_edgeImage->getName().str(), 1, 0);
}
