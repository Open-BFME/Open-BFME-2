// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ?deinit@GameTextManager@@UAEXXZ 0x002E6551 96B
// Evidence: chain from 0x002E6158 and 0x002E5711; clears +0x2c +0x30 GameTextTable ptrs plus +0x24 Rva002E5711 list then byte +0x1d; caller 0x002E6710.
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

class Rva002E5711
{
public:
	~Rva002E5711();
};

class GameTextManager
{
public:
	virtual void deinit();

private:
	char m_pad04[0x1d - 4];
	unsigned char m_initialized;
	char m_pad1e[0x06];
	Rva002E5711 *m_noStringList;
	char m_pad28[0x04];
	GameTextTable *m_textTable;
	GameTextTable *m_mapTable;
};

void GameTextManager::deinit()
{
	GameTextTable *ptr = m_textTable;
	if (ptr)
	{
		ptr->~GameTextTable();
		::operator delete(ptr);
		m_textTable = 0;
	}
	ptr = m_mapTable;
	if (ptr)
	{
		ptr->~GameTextTable();
		::operator delete(ptr);
		m_mapTable = 0;
	}
	Rva002E5711 *cur = reinterpret_cast<Rva002E5711 *>(m_noStringList);
	if (cur)
	{
		do
		{
			Rva002E5711 *next = *(Rva002E5711 **)cur;
			cur->~Rva002E5711();
			::operator delete(cur);
			cur = next;
		} while (cur);
	}
	m_noStringList = 0;
	m_initialized = 0;
}
