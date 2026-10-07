// cl: /O1 /MD
//
// ?rva003F8509@Rva003F8090@@QAEPAXXZ @0x003F8509 45B.
// Normalize the +0x18 index (negative with nonempty array resets to 0,
// else increment), fetch via rva003F80C3, tail-jump to 0x003F7F4B (pinned).
// Evidence: retail idx=[ecx+0x18] / jge else / count=([ecx+0x10]-[ecx+0xC])>>2 /
// je fetch / and [ecx+0x18],0 / jmp fetch / else inc+mov / call 80C3 /
// test+je null / mov ecx,eax+jmp 7F4B. Same +0xC/+0x10/+0x18 layout and 80C3
// helper as rowed Rva003F8090, so same class.
// ?rva003F8536@Rva003F8090@@QAEEXZ @0x003F8536 39B.
// If m_18+1 < count return 0; fetch via 80C3, null gives 1, else tail-jump
// to rowed rva003F8478.
// Evidence: retail count/next loads / cmp edx,eax+jae / xor al,al+ret /
// call 80C3 / test+jne found / mov al,1+ret / mov ecx,eax+jmp 8478.
class Rva003F7F30
{
public:
	void rva003F7F30();
};

class Rva003F7F4B
{
public:
	void *rva003F7F4B();
};

class Rva003F8052
{
public:
	unsigned char rva003F8478();
};

class Rva003F8090
{
public:
	void *rva003F8509();
	unsigned char rva003F8536();
	void *rva003F80C3();
private:
	char m_00[0xc];
	Rva003F7F30 **m_0c;
	Rva003F7F30 **m_10;
	char m_14[4];
	int m_18;
};

// ?rva003F8509@Rva003F8090@@QAEPAXXZ present-unmatched
void *Rva003F8090::rva003F8509()
{
	int idx = m_18;
	if (idx < 0)
	{
		int count = m_10 - m_0c;
		if (count != 0)
			m_18 = 0;
	}
	else
		m_18 = idx + 1;
	void *it = rva003F80C3();
	if (it == 0)
		return 0;
	return ((Rva003F7F4B *)it)->rva003F7F4B();
}

unsigned char Rva003F8090::rva003F8536()
{
	int count = m_10 - m_0c;
	unsigned next = (unsigned)m_18 + 1;
	if (next < (unsigned)count)
		return 0;
	void *it = rva003F80C3();
	if (it == 0)
		return 1;
	return ((Rva003F8052 *)it)->rva003F8478();
}
