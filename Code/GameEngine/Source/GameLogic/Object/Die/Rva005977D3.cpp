// cl: /GX-
// ?rva005977D3@Rva005977D3@@QAEXXZ @0x005977D3 74B: prune vector<ObjectID> at +0x18 erasing null or float280 below 0 via rowed findObjectByID 0x00049DC5 and erase 0x0025BF5D with virtual slot0(obj 1); caller 0x00597FC5
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	char m_pad00[0x280];
	float m_float280;
};

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

class Rva005977D3
{
public:
	virtual void slot0(Object *obj, int x);
	void rva005977D3();
private:
	char m_pad04[0x18 - 4];
	_STL::vector<ObjectID, _STL::allocator<ObjectID> > m_ids;
};

void Rva005977D3::rva005977D3()
{
	ObjectID *it = m_ids.m_start;
	while (it != m_ids.m_finish)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj == 0)
		{
			it = m_ids.erase(it);
		}
		else if (obj->m_float280 < 0.0f)
		{
			slot0(obj, 1);
			it = m_ids.erase(it);
		}
		else
		{
			++it;
		}
	}
}
