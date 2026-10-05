// ?register_callback@ios_base@_STL@@QAEXP6AXW4event@12@AAV12@H@ZH@Z
// partial score=0.97 date=2026-10-05
// ?register_callback@ios_base@_STL@@QAEXP6AXW4event@12@AAV12@H@ZH@Z
// partial score=0.97 date=2026-10-03
// ?register_callback@ios_base@_STL@@QAEXP6AXW4event@12@AAV12@H@ZH@Z
// cl: /O2 /Ob0 /MD
// ?register_callback@ios_base@_STL@@QAEXP6AXW4event@12@AAV12@H@ZH@Z
// STLport 4.5.3 ios_base::register_callback, retail 0x0001C090, 132 bytes.
// Direct BFME1 byte-identical donor (b1 0x0083F1C0, 132 bytes); the only
// change is the shared "ios failure" literal, which the target pools at the
// same place the rowed iword/pword neighbours use. Layout, flags and the
// callback-array helper pin (0x0001BEC0 grow_array<Callback>) match
// stlport_ios_base_iword.cpp.

namespace _STL
{

struct Callback;

template <class T>
struct GrowPair
{
	T *first;
	unsigned int second;
};

template <class Callback>
GrowPair<Callback> *grow_array(GrowPair<Callback> *, Callback *, unsigned int, unsigned int);

typedef void (__cdecl *IosBaseErrorCall)(void *, void *);
extern IosBaseErrorCall g_call;
extern void *g_global;

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
	ios_base::event_callback fn;
	int index;
};

void ios_base::register_callback(event_callback fn, int index)
{
	GrowPair<Callback> grown;
	grow_array(&grown, m_callbacks, m_num_callbacks, m_callback_index);
	if (grown.first)
	{
		GrowPair<Callback> tmp = grown;
		m_num_callbacks = tmp.second;
		m_callbacks = tmp.first;
		Callback cb = { fn, index };
		m_callbacks[m_callback_index++] = cb;
		return;
	}

	m_iostate |= 1;
	if (m_iostate & m_exception_mask)
		g_call((void *)"ios failure", (char *)g_global + 0x40);
}

}
