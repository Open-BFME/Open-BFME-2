// ?register_callback@ios_base@_STL@@QAEXP6AXW4event@12@AAV12@H@ZH@Z
// partial score=0.98 date=2026-10-09
// cl: /Ob0 /MD
// STLport 4.5.3 ios_base::register_callback (src/ios.cpp), retail 0x0001C090,
// 132 bytes; sits between pword (0x0001C010) and the ios_base ctor
// (0x0001C1A0) and calls the rowed Callback grow_array (0x0001BEC0). Layout
// and failure tail follow the matched iword/pword unit
// (stlport_ios_base_iword.cpp): grow the callback array to hold the next
// index, store the (fn, index) pair there and advance the index; on
// allocation failure set badbit and report "ios failure" on stderr.
// BANKED NEAR MISS (~0.98, 3 bytes): the whole body matches except the
// failure tail's &_iob[2] temp, which retail puts in edx (like pword's tail)
// and this build in ecx. The tmp copy of the grown pair (BFME 1 attempt
// 0x0083F1C0) fixes the store order and the pointer reload. Tried: if/else,
// inverted branch, inline STLport state helpers, pair ctors, unsigned/int
// fields, /O2 /Ob1 /Ox /G6 /G7 /O1.

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

struct Callback;

class ios_base
{
public:
	enum event { erase_event = 0, imbue_event = 1, copyfmt_event = 2 };
	typedef void (*event_callback)(event, ios_base &, int);

	void register_callback(event_callback fn, int index);

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
	Callback *m_callbacks;
	unsigned int m_num_callbacks;
	unsigned int m_callback_index;
	long *m_iwords;
	unsigned int m_num_iwords;
	void **m_pwords;
	unsigned int m_num_pwords;
};

struct Callback
{
	ios_base::event_callback first;
	int second;
};

void ios_base::register_callback(event_callback fn, int index)
{
	GrowPair<Callback> grown;
	grow_array(&grown, m_callbacks, m_num_callbacks, m_callback_index);
	if (grown.first != 0)
	{
		GrowPair<Callback> tmp = grown;
		m_num_callbacks = tmp.second;
		m_callbacks = tmp.first;
		Callback cb;
		cb.first = fn;
		cb.second = index;
		m_callbacks[m_callback_index++] = cb;
		return;
	}

	m_iostate |= 1;
	if ((m_iostate & m_exception_mask) != 0)
		fputs("ios failure", &_iob[2]);
}

}
