// ?rva006C17B0@Rva006C17B0@@QAEX_N0@Z @0x006C17B0 144B - array-of-chains clear with two conditional callbacks; evidence callers 0x006C21B4 0x006C3929 0x006C3CF9 set ecx plus two 0/1 pushes; ret 8 two args whose low bytes are tested; unlocks 0x006C21B0 0x006C3CC0 0x006C38D0
#include "../../Include/Common/Rva006C17B0Node.h"

class Rva006C17B0
{
public:
	void rva006C17B0(bool flag1, bool flag2);
	void rva006C21B0();
private:
	void **m_array;
	int m_pad4;
	unsigned int m_count;
	int m_padC;
	int m_10;
	int m_pad14;
	void (__cdecl *m_callback)(void *a, void *b);
	void *m_cbArg;
};

void Rva006C17B0::rva006C17B0(bool flag1, bool flag2)
{
	if (m_array == 0)
		return;
	unsigned int i = 0;
	if (m_count > 0u)
	{
		do
		{
			Rva006C17B0Node *cur = (Rva006C17B0Node *)m_array[i];
			if (cur != 0)
			{
				do
				{
					void *data = cur->m_data;
					Rva006C17B0Node *next = cur->m_next;
					if (data != 0 && flag2)
						m_callback(data, m_cbArg);
					m_callback(cur, m_cbArg);
					cur = next;
				} while (cur != 0);
			}
			m_array[i] = 0;
			++i;
		} while (i < m_count);
	}
	if (flag1)
	{
		m_callback(m_array, m_cbArg);
		m_array = 0;
		m_count = 0;
	}
	m_10 = 0;
}

void Rva006C17B0::rva006C21B0()
{
	rva006C17B0(true, false);
}
