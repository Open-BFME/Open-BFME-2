// cl: /G7 /DNDEBUG /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// MatPassTaskClass pool allocation view for target 0x001440C0.
// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp
// (DEFINE_AUTO_POOL(MatPassTaskClass, 256)) and
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/mempool.h
// (ObjectPoolClass implementation).
// Target bytes run 201 bytes through ret at 0x00144188; Ghidra's 198-byte
// extent omits the final add esp,10h; ret. Target calls spin at 0x0006577F
// with this+0x10 as the lock flag and _STL::allocator<char>::allocate at
// 0x000307F0 for 0xC04 bytes. MatPassTaskClass is 12 bytes from its matched
// target ctor/dtor at 0x001438C0/0x001438F0; 256*12 + 4-byte block link = C04.
// ObjectPool fields are free-list +0, block-list +4, free count +8, total
// count +0xC, followed by the four-byte lock at +0x10.

typedef unsigned int uint32;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class MatPassTaskClass
{
	char m_bfmeBody[12];
};

// BFME replaced STLport's allocator with one raw byte allocator that every
// instantiation folds onto (see reference/shims/bfmealloc/stl/_alloc.h); the
// pool's own operator new call was patched to route through the same
// allocator, called as __cdecl (bytes, hint). Pinned at 0x000307F0.
namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
	static char *allocate(unsigned int n, const void *hint = 0);
};
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class FastCriticalSectionClass
{
	unsigned Flag;

public:
	FastCriticalSectionClass() : Flag(0) {}

	class LockClass
	{
		FastCriticalSectionClass& cs;
	public:
		LockClass(FastCriticalSectionClass& critical_section) : cs(critical_section)
		{
			spin(&cs.Flag);
		}

		~LockClass()
		{
			cs.Flag=0;
		}

	private:
		static void __fastcall spin(unsigned *flag);		// pinned 0x0006577F

		LockClass &operator=(const LockClass&);
		LockClass(const LockClass&);
	};

	friend class LockClass;
};

template<class T,int BLOCK_SIZE = 64>
class ObjectPoolClass
{
public:
	T *		Allocate_Object_Memory(void);

protected:

	T	*		FreeListHead;
	uint32 *	BlockListHead;
	int		FreeObjectCount;
	int		TotalObjectCount;
	FastCriticalSectionClass ObjectPoolCS;

};

template<class T,int BLOCK_SIZE>
T * ObjectPoolClass<T,BLOCK_SIZE>::Allocate_Object_Memory(void)
{
	FastCriticalSectionClass::LockClass lock(ObjectPoolCS);

	if ( FreeListHead == 0 ) {

		uint32 * tmp_block_head = BlockListHead;
		BlockListHead = (uint32*)_STL::allocator<char>::allocate( sizeof(T) * BLOCK_SIZE + sizeof(uint32 *));
		*(void **)BlockListHead = tmp_block_head;

		FreeListHead = (T*)(BlockListHead + 1);
		for ( int i = 0; i < BLOCK_SIZE; i++ ) {
			*(T**)(&(FreeListHead[i])) = &(FreeListHead[i+1]);
		}
		*(T**)(&(FreeListHead[BLOCK_SIZE-1])) = 0;

		FreeObjectCount += BLOCK_SIZE;
		TotalObjectCount += BLOCK_SIZE;
	}

	T * obj = FreeListHead;
	FreeListHead = *(T**)(FreeListHead);
	FreeObjectCount--;

	return obj;
}

template MatPassTaskClass * ObjectPoolClass<MatPassTaskClass,256>::Allocate_Object_Memory(void);
