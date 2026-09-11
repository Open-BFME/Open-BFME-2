// cl: /G7 /DNDEBUG /MD /EHsc

// DynamicIBAccessClass::WriteLockClass constructor at 0x00138CA0 and
// destructor at 0x00138D80.  dx8indexbuffer.cpp carries the Zero Hour bodies,
// which bracket the lock with a radar reset and the inline DX8_ErrorCode; BFME
// instead holds its DX8 device mutex as a member after the two pointers --
// both bodies carry an EH frame whose only cleanup is that member -- and
// reports a failed Lock or Unlock through the out-of-line Log_DX8_ErrorCode.
// The classes are reduced to the offsets the two bodies touch: the access
// object keeps its type at +0, the index count at +4 and the offset at +6 and
// the buffer at +8; the buffer has its reference count at +4 and, for both
// the DX8 and the sorting kind, its storage pointer at +0x14.  /G7 is the tell
// (add [eax+4],1 and add [ecx+4],-1 for the reference count).

extern void DX8_Assert();
extern void Log_DX8_ErrorCode(unsigned);
extern void BFME_DX8_Thread_Lock(void);
extern void BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

// upstream layout: d3d9.h IDirect3DIndexBuffer9 (Lock is slot 11, Unlock slot 12)
struct BfmeIndexBuffer9
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
	virtual long __stdcall GetDevice(void **) = 0;
	virtual long __stdcall SetPrivateData(const void *, const void *, unsigned long, unsigned long) = 0;
	virtual long __stdcall GetPrivateData(const void *, void *, unsigned long *) = 0;
	virtual long __stdcall FreePrivateData(const void *) = 0;
	virtual unsigned long __stdcall SetPriority(unsigned long) = 0;
	virtual unsigned long __stdcall GetPriority() = 0;
	virtual void __stdcall PreLoad() = 0;
	virtual int __stdcall GetType() = 0;
	virtual long __stdcall Lock(unsigned int, unsigned int, void **, unsigned long) = 0;
	virtual long __stdcall Unlock() = 0;
};

enum
{
	BUFFER_TYPE_DYNAMIC_DX8 = 2,
	BUFFER_TYPE_DYNAMIC_SORTING = 3,
};

enum
{
	D3DLOCK_NOOVERWRITE = 0x00001000L,
	D3DLOCK_DISCARD = 0x00002000L,
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class IndexBufferClass
{
public:
	virtual void Delete_This();

	void Add_Ref() { ++NumRefs; }
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
	unsigned unexamined[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class DX8IndexBufferClass : public IndexBufferClass
{
public:
	BfmeIndexBuffer9 *Get_DX8_Index_Buffer() { return index_buffer; }

	BfmeIndexBuffer9 *index_buffer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class SortingIndexBufferClass : public IndexBufferClass
{
public:
	unsigned short *index_buffer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class DynamicIBAccessClass
{
	unsigned Type;
	unsigned short IndexCount;
	unsigned short IndexBufferOffset;
	IndexBufferClass *IndexBuffer;

public:
	unsigned Get_Type() const { return Type; }
	unsigned short Get_Index_Count() const { return IndexCount; }

	class WriteLockClass
	{
		DynamicIBAccessClass *DynamicIBAccess;
		unsigned short *Indices;
		BFMEDX8DeviceLock device_lock;

	public:
		WriteLockClass(DynamicIBAccessClass *ib_access);
		~WriteLockClass();
	};

	friend class WriteLockClass;
};

DynamicIBAccessClass::WriteLockClass::WriteLockClass(DynamicIBAccessClass *ib_access_)
	: DynamicIBAccess(ib_access_), Indices(0)
{
	DynamicIBAccess->IndexBuffer->Add_Ref();
	switch (DynamicIBAccess->Get_Type()) {
	case BUFFER_TYPE_DYNAMIC_DX8:
		{
			DX8_Assert();
			long result = static_cast<DX8IndexBufferClass *>(DynamicIBAccess->IndexBuffer)->Get_DX8_Index_Buffer()->Lock(
				DynamicIBAccess->IndexBufferOffset * sizeof(unsigned short),
				DynamicIBAccess->Get_Index_Count() * sizeof(unsigned short),
				reinterpret_cast<void **>(&Indices),
				!DynamicIBAccess->IndexBufferOffset ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE);
			if (result != 0)
				Log_DX8_ErrorCode(result);
		}
		break;
	case BUFFER_TYPE_DYNAMIC_SORTING:
		Indices = static_cast<SortingIndexBufferClass *>(DynamicIBAccess->IndexBuffer)->index_buffer;
		Indices += DynamicIBAccess->IndexBufferOffset;
		break;
	default:
		break;
	}
}

DynamicIBAccessClass::WriteLockClass::~WriteLockClass()
{
	switch (DynamicIBAccess->Get_Type()) {
	case BUFFER_TYPE_DYNAMIC_DX8:
		{
			DX8_Assert();
			long result = static_cast<DX8IndexBufferClass *>(DynamicIBAccess->IndexBuffer)->Get_DX8_Index_Buffer()->Unlock();
			if (result != 0)
				Log_DX8_ErrorCode(result);
		}
		break;
	case BUFFER_TYPE_DYNAMIC_SORTING:
		break;
	default:
		break;
	}
	DynamicIBAccess->IndexBuffer->Release_Ref();
}
