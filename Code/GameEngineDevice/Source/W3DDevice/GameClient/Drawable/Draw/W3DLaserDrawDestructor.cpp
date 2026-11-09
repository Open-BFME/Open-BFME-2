// cl: /DNDEBUG /MD /EHsc
// BFME W3DLaserDraw destructor.  The shipped BFME class has a larger
// DrawableModule base and a texture-vector member than the later reference
// header, so keep this recovered layout local to the destructor TU.

class W3DLaserDrawModuleData
{
public:
	char m_padding20[0x20];
	unsigned int m_numBeams;
	char m_padding24[0x14];
	unsigned int m_segments;
};

#include "../../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"
inline DrawModule::~DrawModule() {} // retail inlines this into the derived destructors

// Same slot views as W3DLaserDrawBfmeConstructor.cpp, so both units emit one pair of
// W3DLaserDraw tables.
class LaserDrawInterface
{
public:
	virtual float getLaserTemplateWidth() const = 0;
};

class SegmentedLineClass
{
public:
	virtual void Release();
};

// The texture vector dies through the rowed 0x000C9A12 (the call at 0x000C9BA8).
#include <stdlib.h>

template <class T> class RefCountPtr;
class TextureClass;

template <class E> struct RvaVectorFamilyBase
{
	E *m_start;
	E *m_finish;
	E *m_endOfStorage;
	~RvaVectorFamilyBase()
	{
		if (m_start)
			free(m_start);
	}
};

// Share the vector shell with W3DLaserDraw.cpp. Its rowed destructor destroys
// RefCountPtr<TextureClass> elements before the storage base frees the block.
struct Rva000C9A12 : RvaVectorFamilyBase<RefCountPtr<TextureClass> >
{
	~Rva000C9A12();
};

class RTS3DScene
{
public:
	virtual void bfmeSceneSlot0();
	virtual void bfmeSceneSlot1();
	virtual void bfmeSceneSlot2();
	virtual void Remove_Render_Object(SegmentedLineClass *line);
};

class RTS2DScene;

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
	static RTS2DScene *m_2DScene;
};

// Matched DIR32 references place W3DDisplay::m_3DScene at VA 0x00DE1B34;
// the four retail bytes are zero, so the scene pointer starts null.
RTS3DScene *W3DDisplay::m_3DScene = 0;
// Its neighbour W3DDisplay::m_2DScene (VA 0x00DE1B38, W3DView::draw's DIR32
// reference) is likewise a null-initialised static.
RTS2DScene *W3DDisplay::m_2DScene = 0;

class W3DLaserDraw : public DrawModule, public LaserDrawInterface
{
public:
	virtual void doDrawModule(const class Matrix3D *transform);
	virtual float getLaserTemplateWidth() const;

protected:
	virtual ~W3DLaserDraw();

	SegmentedLineClass **m_line3D;
	Rva000C9A12 m_textureVector;
};

#include <new>

// ??1W3DLaserDraw@@MAE@XZ
W3DLaserDraw::~W3DLaserDraw()
{
	const W3DLaserDrawModuleData *data =
		reinterpret_cast<const W3DLaserDrawModuleData *>(m_moduleData);

	for (int i = 0; i < data->m_numBeams * data->m_segments; i++)
	{
		W3DDisplay::m_3DScene->Remove_Render_Object(m_line3D[i]);
		SegmentedLineClass *line = m_line3D[i];
		if (line)
		{
			if (--reinterpret_cast<int *>(line)[1] == 0)
				line->Release();
			m_line3D[i] = 0;
		}
	}

	void *block = m_line3D;
	operator delete[](block);
}
