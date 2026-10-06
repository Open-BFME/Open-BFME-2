// cl: /MD
// ?rva0025C010@Rva0025C010@@QAEXXZ, retail 0x0025C010, 53 bytes.
// Prunes the vector<ObjectID> at this+4, erasing entries whose
// GameLogic::findObjectByID (rowed in GameLogicFindObjectByID.cpp) returns
// null via the rowed vector<ObjectID>::erase (VectorObjectIDFillInsert.cpp).
// Evidence: TheGameLogic global at 0x00DFE78C (Rva00203693Host.cpp idiom);
// callers at 0x004DF972/0x005962EA pass this in ecx; prev/next rows live in
// Code/GameEngine/Source/Common (Rva0025BFF8ObjectGetter.cpp /O1 /MD).
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;


namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *erase(_Tp *pos);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Rva0025C010
{
public:
	void rva0025C010();
private:
	int m_unk0;
	_STL::vector<ObjectID, _STL::allocator<ObjectID> > m_ids;
};

void Rva0025C010::rva0025C010()
{
	ObjectID *it = m_ids.m_start;
	while (it != m_ids.m_finish)
	{
		if (TheGameLogic->findObjectByID(*it) == 0)
			it = m_ids.erase(it);
		else
			++it;
	}
}
