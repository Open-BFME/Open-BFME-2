// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ?reset@GameTextManager@@UAEXXZ 0x002E6431 32B
// Evidence: chain from 0x002E6158; clears +0x30 GameTextTable ptr via dtor plus scalar delete; callers none yet.
// Slot 9 (reset) of the GameTextManager vtable 0x00C04FA8; +0x30 is m_mapTable (GameText.cpp), freed as in ZH reset.
class Rva002E5791
{
public:
	~Rva002E5791();
};

class GameTextTable
{
public:
	~GameTextTable();
};

class GameTextManager
{
public:
	virtual void reset();

private:
	char m_pad[0x2C];
	GameTextTable *m_mapTable;
};

void GameTextManager::reset()
{
	GameTextTable *ptr = m_mapTable;
	if (ptr)
	{
		ptr->~GameTextTable();
		::operator delete(ptr);
		m_mapTable = 0;
	}
}
