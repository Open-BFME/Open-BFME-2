// cl: /DNDEBUG /MD /EHsc
// stlport
// ?tossSegments@W3DRopeDraw@@AAEXXZ @0x000CA84D 111B: W3DRopeDraw::tossSegments clears m_segments.
// Donor BFME1 Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDraw.cpp tossSegments
// (Remove_Render_Object plus REF_PTR_RELEASE loop plus vector clear). Callers 0x000CA8BC dtor plus
// 0x000CA916 plus 0x000CAC25 call this site. Scene Remove at +0xC and Line Release at slot 0 with
// refcount at +4 per W3DLaserDraw dtor precedent. Vector clear calls rowed BfmePod16 erase 0x002BF70F.
#include <vector>

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

class W3DDisplay
{
public:
	static BfmeScene *m_3DScene;
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

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?m_3DScene@W3DDisplay@@2PAVBfmeScene@@A=?m_3DScene@W3DDisplay@@2PAVRTS3DScene@@A")
