// cl: /DNDEBUG /MD /EHsc
//
// SidesListNotifier's two walks, the dispatch half of the post() pair rowed
// in SidesList_sidesInfo.cpp (0x0032B522, 0x0032B540).  They are the
// LatchRestore listener walk recovered in Rva00308AA4Notifiers.cpp: latch
// the index at +0x0C with Zero Hour's LatchRestore (vtable 0x00BFB1CC), call
// every listener through the posted member pointer with the owner (and the
// side index for dispatchIndexed), and re-read the index after each call.
//
// SidesList_sidesInfo.cpp types the posted callback as a plain function
// pointer, which is all post() needs; the walk calls it with ecx = listener,
// so here it is the member pointer it is (the vcall thunks 0x005CB260 /
// 0x005CB26A the posting sides push).  The listener class is unidentified.
// SidesList_sidesInfo.cpp compiles without /EHsc, so the walks live here.

template <typename T>
class LatchRestore
{
protected:
	T valueToRestore;
	T &whereToRestore;

public:
	LatchRestore(T &dest, const T &src) : whereToRestore(dest)
	{
		valueToRestore = dest;
		dest = src;
	}

	virtual ~LatchRestore()
	{
		whereToRestore = valueToRestore;
	}
};

class SidesListListener
{
public:
	virtual void notify(void *owner);
};

class SidesListNotifier
{
public:
	struct Post
	{
		void (SidesListListener::*callback)(void *);
		void *owner;
	};
	struct PostIndexed
	{
		void (SidesListListener::*callback)(void *, int);
		void *owner;
		int index;
	};
	void dispatch(const Post *p);
	void dispatchIndexed(const PostIndexed *p);

private:
	SidesListListener **m_begin;		// +0x00
	SidesListListener **m_end;		// +0x04
	SidesListListener **m_capacity;	// +0x08
	unsigned int m_index;			// +0x0C
};

void SidesListNotifier::dispatch(const Post *p)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*p->callback)(p->owner);
		i = m_index;
	}
}

void SidesListNotifier::dispatchIndexed(const PostIndexed *p)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*p->callback)(p->owner, p->index);
		i = m_index;
	}
}
