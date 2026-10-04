// cl: /O1
// ?rva002E0C68@Rva002E0C68@@QAEHXZ 68B @0x002E0C68: sum of Rva00318FBE over +0x1B8/+0x1BC pointer array.
// Evidence: unlock lane missing callee of 5 frees making 1 ready; callees rowed Rva00318FBE 0x00318FBE; 6 callers incl 0x002E112A 0x002E1155; prev Rva002E0C2BMethod next Rva002E0CD4Get share /O1.
class Rva00318FBE
{
public:
	int rva00318FBE();
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva002E0C68
{
public:
	int rva002E0C68();
private:
	char m_pad[0x1B8];
	Rva00318FBE **m_start;
	Rva00318FBE **m_finish;
};
int Rva002E0C68::rva002E0C68()
{
	int sum = 0;
	for (unsigned i = 0; i < (unsigned)(m_finish - m_start); ++i) {
		_ReadWriteBarrier();
		sum += m_start[i]->rva00318FBE();
	}
	return sum;
}
