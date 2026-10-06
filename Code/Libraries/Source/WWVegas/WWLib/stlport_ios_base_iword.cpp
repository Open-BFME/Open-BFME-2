// cl: /Ob0 /MD
// Open-BFME5: STLport ios_base::iword, retail 0x0083F0C0, 117 bytes.

struct FILE
{
	unsigned char _reserved[32];
};

extern "C" __declspec(dllimport) FILE _iob[];
extern "C" __declspec(dllimport) int __cdecl fputs(const char *string, FILE *stream);

namespace _STL
{

template <class T>
struct GrowPair
{
	T *first;
	unsigned int second;
};

template <class T>
GrowPair<T> *grow_array(GrowPair<T> *, T *, unsigned int, unsigned int);

class ios_base
{
public:
	long &iword(int index);
	void *&pword(int index);

private:
	char m_vtable[4];
	int m_fmtflags;
	int m_iostate;
	int m_openmode;
	int m_seekdir;
	int m_exception_mask;
	int m_precision;
	int m_width;
	char m_locale[4];
	void *m_callbacks;
	unsigned int m_num_callbacks;
	unsigned int m_callback_index;
	long *m_iwords;
	unsigned int m_num_iwords;
	void **m_pwords;
	unsigned int m_num_pwords;
};

long &ios_base::iword(int index)
{
	GrowPair<long> grown;
	grow_array(&grown, m_iwords, m_num_iwords, index);
	if (grown.first)
	{
		m_iwords = grown.first;
		m_num_iwords = grown.second;
		return m_iwords[index];
	}

	m_iostate |= 1;
	if (m_iostate & m_exception_mask)
		fputs("ios failure", &_iob[2]);
	static long fallbackIword;
	return fallbackIword;
}

void *&ios_base::pword(int index)
{
	GrowPair<void *> grown;
	grow_array(&grown, m_pwords, m_num_pwords, index);
	if (grown.first)
	{
		m_pwords = grown.first;
		m_num_pwords = grown.second;
		return m_pwords[index];
	}

	m_iostate |= 1;
	if (m_iostate & m_exception_mask)
		fputs("ios failure", &_iob[2]);
	static void *fallbackPword;
	return fallbackPword;
}

}
