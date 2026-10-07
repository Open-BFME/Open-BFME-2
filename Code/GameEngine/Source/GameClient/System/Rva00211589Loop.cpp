// cl: /DNDEBUG /MD /EHsc
// ?rva00211589@Rva00211589@@QAEXXZ @0x00211589 60B
// Iterates array at +0x24c/+0x250 calling rowed 0x003FD6E0 on each entry.
// Evidence: count via (end-begin)>>2 with je then jb loop; caller 0x002129B4.
// ?rva00212761@Rva00211589@@QAEXXZ @0x00212761 49B
// Iterates the pointer range at +0x258, calls observed element target
// 0x003FCD71, then clears the range through rowed 0x0031BD55.
// ?rva002110DF@Rva00211589@@QAEXH@Z @0x002110DF 66B
// Applies a forwarded word to each pointer in the same range, reloading its
// bounds after each call to observed target 0x003FCDD5.
// ?rva002129B4@Rva00211589@@QAEXXZ @0x002129B4 41B
// Calls the +0x24c loop, resets a present +0x2c4 child through rowed
// 0x003F934B, clears the +0x258 pointer range, then applies zero to its entries.
// The owning class purpose and element/helper semantics remain unresolved.
class Rva003FD6E0
{
public:
	void rva003FD6E0();
};

class Rva003FCD71
{
public:
	void rva003FCD71();
	void rva003FCDD5(int value);
};

class Rva003F934B
{
public:
	void rva003F934B();
};

class RvaVector
{
public:
	void **m_begin;
	void **m_end;
	void **m_capacity;
	void **erase(void **first, void **last);
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva00211589
{
	char m_pad[0x24c];
	Rva003FD6E0 **m_begin;
	Rva003FD6E0 **m_end;
	char m_pad254[4];
	RvaVector m_items;
	char m_pad264[0x60];
	Rva003F934B *m_child;

public:
	void rva00211589();
	void rva00212761();
	void rva002110DF(int value);
	void rva002129B4();
};

void Rva00211589::rva00211589()
{
	unsigned int i;
	for (i = 0; i < (unsigned int)(m_end - m_begin); ++i)
	{
		_ReadWriteBarrier();
		m_begin[i]->rva003FD6E0();
	}
}

void Rva00211589::rva00212761()
{
	void **end = m_items.m_end;
	RvaVector *vec = &m_items;
	void **it = vec->m_begin;
	while (it != end)
	{
		((Rva003FCD71 *)*it)->rva003FCD71();
		++it;
	}
	vec->erase(vec->m_begin, vec->m_end);
}

void Rva00211589::rva002110DF(int value)
{
	unsigned int i;
	for (i = 0; i < (unsigned int)(m_items.m_end - m_items.m_begin); ++i)
	{
		_ReadWriteBarrier();
		((Rva003FCD71 *)m_items.m_begin[i])->rva003FCDD5(value);
	}
}

void Rva00211589::rva002129B4()
{
	rva00211589();
	if (m_child)
		m_child->rva003F934B();
	rva00212761();
	rva002110DF(0);
}
