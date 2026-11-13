// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// platformsdk
// stlport
// W3DTaint per-frame taint level interpolation, retail 0x000741C0..0x000743C2
// (RET 4) and its EH handler 0x0075EEC7. Original method name unknown: WB
// 0x82E370 is the unnamed callee of the named W3DTaint::render (WB 0x82DC70,
// retail 0x000743C2), which passes a local RECT address this body never reads.
// Retail is byte-for-byte the W3DShroud::interpolateFogLevels shape
// (W3DShroudInterpolate.cpp, Zero Hour/BFME 1 donor) with rate 0.064f, a
// 128 clamp, dirty flag +0x40, dirty set +0x44 and setTaintLevel 0x00073CC0.
// Same-TU lever: the visible STLport push_back body proves it does not keep the
// address of `index`, so retail holds the cell index in EBX across the appends.
// Keep the inlined vector-growth comparison local: the standalone unsigned
// max template emitted with these flags differs from retail's provider.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
 return a < b ? b : a;
}
}
#include <set>
#include <vector>
#include <windows.h>
// Compare typed tree iterators locally; the incidental base comparison
// COMDAT differs from the selected provider under this unit's flags.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
typedef float Real;
typedef bool Bool;
class TextureClass;
struct ShroudTextureHandle { TextureClass *m_p; };
void Rva00030830GameFree(void *);
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<int>::deallocate(int *p,unsigned)const{if(p)Rva00030830GameFree(p);}
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<int*,int,allocator<int> >::deallocate(int*p,size_t n){__stl_alloc_rebind(static_cast<allocator<int>&>(*this),(int*)0).deallocate(p,n);}
}

// The retiring list appends through the ICF-folded 4-byte pointer-vector
// push_back (0x004DFCB0); the int instance at 0x00688940 is a different body.
class ModuleData;
inline void appendTaintIndex(_STL::vector<int> &values, const int &index)
{
	reinterpret_cast<_STL::vector<const ModuleData *> &>(values).push_back(
		reinterpret_cast<const ModuleData * const &>(index));
}

// set<int>::erase(const key_type &), rowed at 0x000733D8.
#include "../../../../GameEngine/Include/Common/Rva00072FE6.h"
// setTaintLevel, rowed at 0x00073CC0 (W3DTaint.cpp view).
#include "../../../Include/W3DDevice/GameClient/Rva000729CC.h"

class W3DTaint
{
public:
	void rva000741C0(RECT *rect);

private:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	Real m_cellWidth;
	Real m_cellHeight;
	unsigned int *m_taintData;
	ShroudTextureHandle m_dstTexture;
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	int m_taintFilter;
	Real m_drawOriginX;
	Real m_drawOriginY;
	unsigned char m_drawTaint;
	unsigned char m_clearDstTexture;
	unsigned char m_borderTaintLevel;
	unsigned char m_pad37;
	unsigned char *m_cellLevels;
	unsigned char *m_referenceCellLevels;
	unsigned char m_trackDirtyCells;
	unsigned char m_pad41[3];
	_STL::set<int> m_dirty;
};

void W3DTaint::rva000741C0(RECT *rect)
{
	static unsigned int prevTime = (unsigned int)timeGetTime();
	unsigned int timeDiff = (unsigned int)timeGetTime() - prevTime;
	if (timeDiff == 0)
		return;
	prevTime += timeDiff;

	int maxStep = (int)((float)timeDiff * 0.064f);
	if (maxStep > 128)
		maxStep = 128;
	unsigned char levelDelta = (unsigned char)maxStep;

	unsigned char *startLevel = m_referenceCellLevels;
	unsigned char *finalLevel = m_cellLevels;
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
			unsigned char start = *current;
			unsigned char final = *target;

			if (final != start)
			{
				if (final < start)
				{
					if ((int)start - (int)final < (int)levelDelta)
					{
						*current = final;
						appendTaintIndex(remove, index);
					}
					else
						*current = (unsigned char)(start - levelDelta);
				}
				else
				{
					if ((int)final - (int)start < (int)levelDelta)
					{
						*current = final;
						appendTaintIndex(remove, index);
					}
					else
						*current = (unsigned char)(start + levelDelta);
				}

				reinterpret_cast<Rva000729CC *>(this)->rva00073CC0(index % m_numCellsX, index / m_numCellsX,
					*current, true);
			}
			else
				appendTaintIndex(remove, index);
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

				reinterpret_cast<Rva000729CC *>(this)->rva00073CC0(i, j, *startLevel, true);
			}
		}
	}
}
