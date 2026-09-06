// cl: /G7 /DNDEBUG /MD /EHsc
// ObjectPoolClass<MultiListNodeClass,256>::Free_Object_Memory,
// retail 0x00196470, 39 bytes.
//
// multilist.h's AutoPoolClass<MultiListNodeClass,256> base pool's free half,
// the twin of Allocate_Object_Memory landed at 0x00610680 in
// ObjectPoolAllocateObjectMemory.cpp. Same FastCriticalSectionClass and the
// same spin() pin (0x0006577F, an out-of-line __fastcall reached via the
// same call shape as the allocate side).

typedef unsigned int uint32;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListNodeClass
{
	char m_bfmeBody[20];
};

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
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mempool.h
class ObjectPoolClass
{
public:
	void		Free_Object_Memory(T * obj);

protected:

	T	*		FreeListHead;
	uint32 *	BlockListHead;
	int		FreeObjectCount;
	int		TotalObjectCount;
	FastCriticalSectionClass ObjectPoolCS;

};

template<class T,int BLOCK_SIZE>
void ObjectPoolClass<T,BLOCK_SIZE>::Free_Object_Memory(T * obj)
{
	FastCriticalSectionClass::LockClass lock(ObjectPoolCS);

	*(T**)(obj) = FreeListHead;		// Link to the Head
	FreeListHead = obj;					// Set the Head
	FreeObjectCount++;
}

template void ObjectPoolClass<MultiListNodeClass,256>::Free_Object_Memory(MultiListNodeClass *);
