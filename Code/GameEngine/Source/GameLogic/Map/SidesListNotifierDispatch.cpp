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

#include "../../../Include/Common/SidesListNotifier.h"

// The shared header keeps the raw callback word and untyped listener storage.
// These views restore the dispatch ABI without changing the canonical layout.

void SidesListNotifier::dispatch(const Post *post)
{
	typedef void (SidesListListener::*Callback)(void *);
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(reinterpret_cast<unsigned int &>(field0C), i);
	while (i < (unsigned int)(reinterpret_cast<SidesListListener **>(field04) - reinterpret_cast<SidesListListener **>(field00)))
	{
		reinterpret_cast<unsigned int &>(field0C)++;
		(reinterpret_cast<SidesListListener **>(field00)[i]->*reinterpret_cast<const Callback &>(post->callback))(post->owner);
		i = field0C;
	}
}

void SidesListNotifier::dispatchIndexed(const PostIndexed *postIndexed)
{
	typedef void (SidesListListener::*Callback)(void *, int);
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(reinterpret_cast<unsigned int &>(field0C), i);
	while (i < (unsigned int)(reinterpret_cast<SidesListListener **>(field04) - reinterpret_cast<SidesListListener **>(field00)))
	{
		reinterpret_cast<unsigned int &>(field0C)++;
		(reinterpret_cast<SidesListListener **>(field00)[i]->*reinterpret_cast<const Callback &>(postIndexed->callback))(postIndexed->owner, postIndexed->index);
		i = field0C;
	}
}
