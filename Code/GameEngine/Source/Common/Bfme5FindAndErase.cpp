// cl: /MD -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Two bodies that look a value up in their vector and erase the first match.
//
// The search is written out at the call site -- the value goes into a register
// before the loop and the bound stays in another. The bound has to come from
// an accessor on the vector: read as a member here, MSVC shares it with the
// read the erase makes and the reload inside the erase disappears.
//
// The erase itself is the move-down: copy the tail over the hole unless the
// hole is the last element, then step the finish pointer back by one.

class ObjectTypes;

namespace _STL
{
template <class _Tp>
class allocator
{
};

template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	_Tp *erase(_Tp *__position);

	_Tp *begin(void) const
	{
		return m_start;
	}

	_Tp *end(void) const
	{
		return m_finish;
	}

	_Tp *m_start;						// +0x00
	_Tp *m_finish;						// +0x04
	_Tp *m_end;						// +0x08
};
}

class Gen_0039BE00
{
public:
	void bfmeRemove(int value);

private:
	int m_bfmeHead[2];					// +0x00
	_STL::vector<ObjectTypes *> m_bfmeVector;		// +0x08
};

// ?bfmeRemove@Gen_0039BE00@@QAEXH@Z
void Gen_0039BE00::bfmeRemove(int value)
{
	ObjectTypes **it = m_bfmeVector.begin();
	ObjectTypes **last = m_bfmeVector.end();

	while (it != last)
	{
		if ((int)*it == value)
		{
			m_bfmeVector.erase(it);

			return;
		}

		++it;
	}
}
