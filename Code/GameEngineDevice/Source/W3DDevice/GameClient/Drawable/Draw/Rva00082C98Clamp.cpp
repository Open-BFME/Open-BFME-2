// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
// ?rva00082C98@Rva00082C98Host@@QAEXIHHH@Z @0x00082C98 73B
// Vector clamp-erase wrapper over 12-byte Coord3D elements; count is (end-begin)/12 via idiv; if a0<count erase at begin+a0*12 via rowed 0x00081A24 else call pinned 0x00082719 with (end; a0-count; &a1); four int args to match ret 0x10; a2-a3 unused. Evidence: callers 0x00082D31 0x00082DAD 0x000E3E0F; callees 0x00081A24 0x00082719; stash reverse/attempts/0x00082c98.cpp score 0.96; EXACT under region flags.

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

namespace _STL
{
	template <typename T>
	class allocator
	{
	};

	template <typename T, typename A>
	class vector
	{
	public:
		T *erase(T *first, T *last);
	};
}

#include "../../../../../Include/W3DDevice/GameClient/Rva00082719Vector.h"

class Rva00082C98Host
{
public:
	void rva00082C98(unsigned int newSize, int fillX, int fillY, int fillZ);

	void *m_begin;
	void *m_end;
};

void Rva00082C98Host::rva00082C98(unsigned int newSize, int fillX, int fillY, int fillZ)
{
	(void)fillY;
	(void)fillZ;
	unsigned int count = ((char *)m_end - (char *)m_begin) / 12;
	if (newSize < count)
	{
		void *newEnd = (char *)m_begin + newSize * 12;
		((_STL::vector<Coord3D, _STL::allocator<Coord3D> > *)this)->erase((Coord3D *)newEnd, (Coord3D *)m_end);
	}
	else
	{
		((Rva00082719Vector *)this)->fillInsert((Coord3D *)m_end, newSize - ((char *)m_end - (char *)m_begin) / 12, *(const Coord3D *)&fillX);
	}
}
