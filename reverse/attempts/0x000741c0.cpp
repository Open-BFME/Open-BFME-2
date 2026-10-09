// ?rva000741C0@Rva000729CC@@QAEXH@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /Ireference/shims/bfmealloc /D_CRTIMP= /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA 0x00727A80, full 708-byte RET4 body. The owner name remains
// address-derived: the older TaintBuffer name is descriptive, not an EA identity.
// Caller 0x00727E00 passes a local rectangle address, unused by this body.
// Fields and the int dirty-cell set are witnessed by the matched constructor,
// collector and setShroudLevel30BC; the erase helper frees 20-byte int nodes.
// VA0x01359544 is independently verified as WINMM!timeGetTime's IAT slot.
// VA0x01121294 contains 0.064f. Equality with stepByte deliberately waits
// until the next pass before removing a dirty key; only strict overshoot removes.
// Native STLport owns the deferred-removal vector and its one EH cleanup.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <vector>

typedef unsigned char UnsignedByte;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

class Rva000729CC
{
public:
	void rva000741C0(int unused);
 void rva00073CC0(int,int,int,int);

private:
	int m_numCellsX;
	int m_numCellsY;
	unsigned char m_padding08[0x10];
	unsigned int *m_taintData;
	unsigned char m_padding1c[0x1c];
	UnsignedByte *m_targetLevels;
	UnsignedByte *m_currentLevels;
	UnsignedByte m_walkDirty;
	unsigned char m_padding41[3];
	_STL::set<int> m_dirty;
};

void Rva000729CC::rva000741C0(int unused)
{
	static unsigned int lastTime = (unsigned int)timeGetTime();
	unsigned int elapsed = (unsigned int)timeGetTime() - lastTime;
	if (elapsed == 0)
		return;
	lastTime += elapsed;

	int step = (int)((float)elapsed * 0.064f);
	if (step > 128)
		step = 128;
	UnsignedByte stepByte = (UnsignedByte)step;

	UnsignedByte *current = m_currentLevels;
	UnsignedByte *target = m_targetLevels;
	if (m_walkDirty)
	{
		int width = m_numCellsX;
		int dirtyCount = (int)m_dirty.size();
		if (width <= 0 || dirtyCount <= 0)
			return;

		_STL::vector<int> remove;
		for (_STL::set<int>::iterator it = m_dirty.begin();
			it != m_dirty.end(); ++it)
		{
			int index = *it;
			UnsignedByte currentLevel = current[index];
			UnsignedByte targetLevel = target[index];

			if (targetLevel != currentLevel)
			{
				if (targetLevel < currentLevel)
				{
					if ((int)currentLevel - (int)targetLevel < (int)stepByte)
					{
						current[index] = targetLevel;
						remove.push_back(index);
					}
					else
						current[index] = (UnsignedByte)(currentLevel - stepByte);
				}
				else
				{
					if ((int)targetLevel - (int)currentLevel < (int)stepByte)
					{
						current[index] = targetLevel;
						remove.push_back(index);
					}
					else
						current[index] = (UnsignedByte)(currentLevel + stepByte);
				}

				int x = index % m_numCellsX;
				int y = index / m_numCellsX;
				rva00073CC0(
					x, y, current[index], true);
			}
			else
				remove.push_back(index);
		}

		for (_STL::vector<int>::iterator it = remove.begin();
			it != remove.end(); ++it)
			m_dirty.erase(*it);
	}
	else
	{
		for (int y = 0; y < m_numCellsY; ++y)
		{
			for (int x = 0; x < m_numCellsX; ++x, ++current, ++target)
			{
				UnsignedByte currentLevel = *current;
				UnsignedByte targetLevel = *target;
				if (targetLevel == currentLevel)
					continue;

				if (targetLevel < currentLevel)
				{
					if ((int)currentLevel - (int)targetLevel < (int)stepByte)
						*current = targetLevel;
					else
						*current = (UnsignedByte)(currentLevel - stepByte);
				}
				else
				{
					if ((int)targetLevel - (int)currentLevel < (int)stepByte)
						*current = targetLevel;
					else
						*current = (UnsignedByte)(currentLevel + stepByte);
				}

				rva00073CC0(
					x, y, *current, true);
			}
		}
	}
}
