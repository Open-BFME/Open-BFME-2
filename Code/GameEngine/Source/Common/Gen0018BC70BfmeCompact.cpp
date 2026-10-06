// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport
//
// ?bfmeCompact@Gen_0018BC70@@QAEPAVBfmeVecAK@@_N@Z @0x004D6D4F 70B
// LINK 1 file 47B. Reference transfer from BFME1 Bfme5CompactAlive.cpp:61
// Gen_0018BC70::bfmeCompact with rowed callees liveObjects/rva004D6CAC and
// Object::isSelectable plus rowed vector<void*>::erase. Evidence pin plus
// LINK BONUS name plus donor loop shape plus callers in PlayerHotkeySquads.
namespace _STL
{
template <typename T> class allocator;
template <typename T, typename A = allocator<T> > class vector
{
public:
	void **erase(void **pos);
};
}
class Object
{
public:
	bool isSelectable() const;
};
class Squad
{
public:
	const _STL::vector<Object *> &getAllObjectsAndRemoveDead();
	const _STL::vector<Object *> &rva004D6CAC();
};
class BfmeVecAK
{
public:
	void **m_start;
	void **m_finish;
	void **m_end;
};
class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(bool restart);
	int m_00[4];
	BfmeVecAK m_10;
};
BfmeVecAK *Gen_0018BC70::bfmeCompact(bool restart)
{
	if (restart)
		((Squad *)this)->getAllObjectsAndRemoveDead();
	else
		((Squad *)this)->rva004D6CAC();
	void ***vec = (void ***)&m_10;
	void **it = m_10.m_start;
	while (it != m_10.m_finish)
	{
		Object *obj = (Object *)*it;
		if (!obj->isSelectable())
			it = (void **)((_STL::vector<void *> *)vec)->erase(it);
		else
			++it;
	}
	return &m_10;
}
