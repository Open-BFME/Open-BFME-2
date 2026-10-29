// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?stopDocking@SiegeDockingBehavior@@AAEXXZ @0x00459C27 49B.
// Clears the +0x24 entry vector: deletes each entry via rowed ??3 0x0002FD60
// behind an explicit null test then empties via rowed voidptr erase 0x0031BD55.
// Callers are the rowed deleting dtor 0x0045A17D via dtor 0x00459DAA at
// 0x00459DDA and the xfer 0x0045A02F at 0x0045A0F9 which clears before reload.
// Donor is BFME1 SiegeDockingBehavior_stopDocking (same delete-plus-erase
// shape; BFME2 binds erase to the rowed voidptr opt). Mixed this-via-ebx
// access is load-bearing for the tail (Glo012F1028 precedent).
#include <vector>

namespace _STL
{
// Bind the range erase to the rowed void-pointer worker.
template <> void **vector<void *, allocator<void *> >::erase(void **first, void **last);
}

class SiegeDockingBehavior
{
private:
	void stopDocking() throw();

private:
	unsigned char m_pad[0x24];
	_STL::vector<void *, _STL::allocator<void *> > m_entries; // +0x24
};

void SiegeDockingBehavior::stopDocking() throw()
{
	_STL::vector<void *, _STL::allocator<void *> > *entries = &m_entries;
	for (void **it = m_entries.begin(); it != m_entries.end(); ++it)
	{
		if (*it)
			::operator delete(*it);
	}
	entries->erase(entries->begin(), entries->end());
}
