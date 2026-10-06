// cl: /MD /Oi-
// ?rva00542806@Rva00542806@@QAEPAV1@PADHH@Z @0x00542806 116B
// XML buffer init: memset 0x14 + 0x184 via 0x6291AE, stores args at +0x14/+0x18/+0x00,
// flag 1 at +0x0C, skips "<?xml version="1.0"?>" header. Evidence: retail bytes
// unlock lane plus strncmp IAT and header literal 0x0086954C.
#pragma function(memset)

extern "C" void * __cdecl memset(void *dst, int value, unsigned int size);
extern "C" __declspec(dllimport) int __cdecl strncmp(const char *s1, const char *s2, unsigned int n);

class Rva00542806
{
public:
	Rva00542806 *rva00542806(char *a1, int a2, int a3);

private:
	char *m_ptr;
	char m_pad4[8];
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
	char m_buf[0x184];
};

Rva00542806 *Rva00542806::rva00542806(char *a1, int a2, int a3)
{
	m_14 = a2;
	m_18 = a3;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	memset(this, 0, 0x14);
	m_c = 1;
	memset(m_buf, 0, 0x184);
	m_ptr = a1;
	if (m_ptr[0] == '<' && m_ptr[1] == '?') {
		if (strncmp(m_ptr, "<?xml version=\"1.0\"?>", 0x15) != 0)
			m_ptr = 0;
		m_ptr += 0x15;
	}
	return this;
}
