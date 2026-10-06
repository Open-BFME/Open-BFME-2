// cl: /DNDEBUG /MD /EHsc
// ?rva00211589@Rva00211589@@QAEXXZ @0x00211589 60B
// Iterates array at +0x24C/+0x250 calling rowed 0x003FD6E0 on each entry.
// Evidence: count via (end-begin)>>2 with je then jb loop; caller 0x002129B4.
class Rva003FD6E0
{
public:
	void rva003FD6E0();
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva00211589
{
	char m_pad[0x24c];
	Rva003FD6E0 **m_begin;
	Rva003FD6E0 **m_end;
public:
	void rva00211589();
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
