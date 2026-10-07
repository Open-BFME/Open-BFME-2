// cl: /O1 /MD
//
// ?rva0040AA27@Rva0040AA27@@QAEHH@Z @0x0040AA27 76B.
// All-quantifier over the +0x1c/+0x20 array (0x10 stride): run the 0x40A99A
// predicate (unclaimed, address pinned) on each element with our int arg,
// stop at the first false, then require a non-empty full count.
// Evidence: retail push ebx/ebp/esi/edi / esi=this / edi=[esi+0x1c] /
// ebp=0 / bl=0 / loop cmp edi,[esi+0x20] / push [esp+0x14] / ecx=edi /
// call 0x40A99A / test al / je→bl=1 else ebp++ / edi+=0x10 / test bl /
// je loop / test ebp / jbe false / eax=([esi+0x20]-[esi+0x1c])>>4 /
// cmp ebp,eax / jne false / eax=1 / false: eax=0 / pop regs / ret 4.
class Rva0040A99AElem
{
public:
	bool rva0040A99A(int x);
	char m_pad[0x10];
};

class Rva0040AA27
{
public:
	int rva0040AA27(int x);
private:
	char m_pad00[0x1c];
	Rva0040A99AElem *m_begin1c;
	Rva0040A99AElem *m_end20;
};

int Rva0040AA27::rva0040AA27(int x)
{
	Rva0040A99AElem *p = m_begin1c;
	unsigned count = 0;
	bool stop = false;
loop:
	if (p == m_end20)
		goto done;
	if (p->rva0040A99A(x))
		count++;
	else
		stop = true;
	p++;
	if (!stop)
		goto loop;
done:
	if (count > 0 && count == (unsigned)(m_end20 - m_begin1c))
		return 1;
	return 0;
}
