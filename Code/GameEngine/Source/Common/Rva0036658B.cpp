// cl: /MD
// ?rva0036658B@Rva0036658B@@QAE_NPAX0@Z 0x0036658B 48B via two-dword empty check at +0x34/+0x38 then init from args
// Evidence: retail xor/cmp/jne shape; neighbours Rva0036666B.cpp (/O1 /MD); caller 0x0052F75F

class Rva0036658B
{
public:
	bool rva0036658B(void *a, void *b);
private:
	char m_pad00[0x28];
	void *m_28;
	int m_2c;
	unsigned char m_30;
	char m_pad31[3];
	void *m_34;
	void *m_38;
	int m_3c;
};

bool Rva0036658B::rva0036658B(void *a, void *b)
{
	if (m_34 != 0 || m_38 != 0)
		return false;
	m_38 = a;
	int tmp = *(int *)((char *)a + 0x30);
	m_2c = -1;
	m_3c = tmp;
	m_28 = b;
	m_30 = 0;
	return true;
}
