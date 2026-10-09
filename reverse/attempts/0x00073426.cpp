// ?rva00073426@W3DShroud@@QAEXPAUtagRECT@@@Z
// partial score=0.96 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <set>
#include <vector>
typedef float Real;
typedef bool Bool;
struct tagRECT; typedef tagRECT RECT;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class TextureClass;
struct ShroudTextureHandle { TextureClass *m_p; };
void Rva00030830GameFree(void *);
namespace _STL { template<> inline void allocator<int>::deallocate(int *p, unsigned) const {
 if(p) Rva00030830GameFree(p);
} }
class ModuleData;
namespace _STL { template<> void vector<const ModuleData*>::push_back(const ModuleData* const&); }
struct Rva00072FE6 { unsigned rva000733D8(const int &); };
inline void appendFogIndex(_STL::vector<int>& values, const int &index) {
 reinterpret_cast<_STL::vector<const ModuleData*>&>(values).push_back(
  reinterpret_cast<const ModuleData* const&>(index));
}
class W3DShroud
{
public:
	Bool ReAcquireResources();
 void rva00073628(void *unused);
 void rva00073426(RECT *unused);
	void setShroudLevel(int, int, unsigned char, bool);

private:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	Real m_cellWidth;
	Real m_cellHeight;
	unsigned short *m_shroudData;
	ShroudTextureHandle m_dstTexture;
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	int m_shroudFilter;
	Real m_drawOriginX;
	Real m_drawOriginY;
	unsigned char m_drawFogOfWar;
	unsigned char m_clearDstTexture;
	unsigned char m_borderShroudLevel;
	unsigned char m_pad37;
	unsigned char *m_finalFogData;
	unsigned char *m_currentFogData;
 unsigned char m_partialRenderer[8];
 unsigned char m_trackDirtyCells;
 unsigned char m_pad49[3];
 _STL::set<int> m_dirty;
};

// BF1 9cbfb551 W3DShroudBfme interpolation semantic donor; native 73426..73628.
// WB7FDD90 unnamed method; target dirty flag48/tree4C and rate0.255 are independently observed.
void W3DShroud::rva00073426(RECT *rect)
{
	static unsigned int prevTime = (unsigned int)timeGetTime();
	unsigned int timeDiff = (unsigned int)timeGetTime() - prevTime;
	if (timeDiff == 0)
		return;
	prevTime += timeDiff;

	int maxFogChange = (int)((float)timeDiff * 0.255f);
	if (maxFogChange > 255)
		maxFogChange = 255;
	unsigned char levelDelta = (unsigned char)maxFogChange;

	unsigned char *startLevel = m_currentFogData;
	unsigned char *finalLevel = m_finalFogData;
	if (m_trackDirtyCells)
	{
		int dirtyCount = (int)m_dirty.size();
		int width = m_numCellsX;
		if (width <= 0 || dirtyCount <= 0)
			return;

		_STL::vector<int> remove;
		for (_STL::set<int>::iterator it = m_dirty.begin();
			it != m_dirty.end(); ++it)
		{
			int index = *it;
			unsigned char *current = startLevel + index;
   unsigned char *target = finalLevel + index;
   unsigned char final = *target;
   unsigned char start = *current;

			if (final != start)
			{
				if (final < start)
				{
					if ((int)start - (int)final < (int)levelDelta)
					{
						*current = final;
						appendFogIndex(remove, index);
					}
					else
						*current = (unsigned char)(start - levelDelta);
				}
				else
				{
					if ((int)final - (int)start < (int)levelDelta)
					{
						*current = final;
						appendFogIndex(remove, index);
					}
					else
						*current = (unsigned char)(start + levelDelta);
				}

				setShroudLevel(index % m_numCellsX, index / m_numCellsX,
					*current, true);
			}
			else
				appendFogIndex(remove, index);
		}

		for (_STL::vector<int>::iterator it = remove.begin();
			it != remove.end(); ++it)
			reinterpret_cast<Rva00072FE6 *>(&m_dirty)->rva000733D8(*it);
	}
	else
	{
		for (int j = 0; j < m_numCellsY; ++j)
		{
			for (int i = 0; i < m_numCellsX; ++i, ++startLevel, ++finalLevel)
			{
				unsigned char start = *startLevel;
				unsigned char final = *finalLevel;
				if (final == start)
					continue;

				if (final < start)
				{
					if ((int)start - (int)final < (int)levelDelta)
						*startLevel = final;
					else
						*startLevel = (unsigned char)(start - levelDelta);
				}
				else
				{
					if ((int)final - (int)start < (int)levelDelta)
						*startLevel = final;
					else
						*startLevel = (unsigned char)(start + levelDelta);
				}

				setShroudLevel(i, j, *startLevel, true);
			}
		}
	}
}
