// cl: /O1 /DNDEBUG /MD /EHsc
// W3DRopeDraw.cpp: the pool key and tossSegments retail links from this TU
// (tu_map approved), folded from two split units with these exact flags.
//
// stlport
// ?tossSegments@W3DRopeDraw@@AAEXXZ @0x000CA84D 111B: W3DRopeDraw::tossSegments clears m_segments.
// Donor BFME1 Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDraw.cpp tossSegments
// (Remove_Render_Object plus REF_PTR_RELEASE loop plus vector clear). Callers 0x000CA8BC dtor plus
// 0x000CA916 plus 0x000CAC25 call this site. Scene Remove at +0xC and Line Release at slot 0 with
// refcount at +4 per W3DLaserDraw dtor precedent. Vector clear calls rowed BfmePod16 erase 0x002BF70F.
#include <vector>

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmePod16 { int a[4]; };

class Line3DClass
{
public:
	virtual void Release();
};

class BfmeScene
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void Remove_Render_Object(Line3DClass *obj);
};

// W3DDisplay::m_3DScene is an RTS3DScene (W3DLaserDrawDestructor.cpp defines it).
class RTS3DScene : public BfmeScene
{
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class DrawableModule
{
protected:
	virtual ~DrawableModule();
	void *m_moduleData;
	void *m_drawable;
};

class DrawModule : public DrawableModule
{
protected:
	virtual ~DrawModule() {}
};

class RopeDrawInterface
{
public:
	virtual void ropeSlot();
};

struct SegInfo
{
	Line3DClass *line;
	Line3DClass *softLine;
	float wobbleAxisX;
	float wobbleAxisY;
};

class W3DRopeDraw : public DrawModule, public RopeDrawInterface
{
public:
	static NameKeyType rva000CA7F6();

private:
	_STL::vector<BfmePod16> m_segments;
	void tossSegments();
};

void W3DRopeDraw::tossSegments()
{
	for (BfmePod16 *it = m_segments.begin(); it != m_segments.end(); ++it)
	{
		SegInfo *si = reinterpret_cast<SegInfo *>(it);
		if (si->line)
		{
			W3DDisplay::m_3DScene->Remove_Render_Object(si->line);
			Line3DClass *line = si->line;
			if (line)
			{
				if (--reinterpret_cast<int *>(line)[1] == 0)
					line->Release();
				si->line = 0;
			}
		}
		if (si->softLine)
		{
			W3DDisplay::m_3DScene->Remove_Render_Object(si->softLine);
			Line3DClass *soft = si->softLine;
			if (soft)
			{
				if (--reinterpret_cast<int *>(soft)[1] == 0)
					soft->Release();
				si->softLine = 0;
			}
		}
	}
	m_segments.clear();
}

// ?rva000CA7F6@W3DRopeDraw@@SA?AW4NameKeyType@@XZ @0xCA7F6
// (68B): cached pool-name key for W3DRopeDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DRopeDraw"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).
// ?rva000CA7F6@W3DRopeDraw@@SA?AW4NameKeyType@@XZ
NameKeyType W3DRopeDraw::rva000CA7F6()
{
	static NameKeyType TheW3DRopeDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DRopeDraw");
	return TheW3DRopeDrawPoolKey;
}
