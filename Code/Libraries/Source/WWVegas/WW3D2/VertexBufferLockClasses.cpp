// cl: /G7 /DNDEBUG /MD /EHsc

// VertexBufferClass::WriteLockClass constructor at 0x001394A0 and destructor
// at 0x00139530, and AppendLockClass's constructor at 0x001395B0.  The append
// lock's destructor is the same code as the write lock's and retail keeps one
// body for both.
//
// These are Zero Hour's lock classes with BFME's two changes, the same ones
// DynamicIBAccessWriteLock.cpp carries for the index side: the DX8 device
// mutex is held as a member after the two pointers -- every body has an EH
// frame whose only cleanup is that member -- and a failed Lock or Unlock is
// reported through the out-of-line Log_DX8_ErrorCode.  The classes are reduced
// to the offsets the bodies touch: the buffer keeps its reference count at +4,
// its kind at +8 (0 for DX8, 1 for sorting), its FVF record at +0x14 with the
// vertex stride at +0xC, and the D3D buffer or the 44-byte sorting vertices
// at +0x1C.  /G7 is the tell (add [esi+4],1 and add [ecx+4],-1).

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

// upstream layout: d3d9.h IDirect3DVertexBuffer9 (Lock is slot 11, Unlock slot 12)
struct BfmeVertexBuffer9
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
	BUFFER_TYPE_DX8 = 0,
	BUFFER_TYPE_SORTING = 1,
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8fvf.h
class FVFInfoClass
{
public:
	unsigned Get_FVF_Size() const { return fvf_size; }

private:
	unsigned unexamined[3];
	unsigned fvf_size;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
struct VertexFormatXYZNDUV2
{
	float x, y, z;
	float nx, ny, nz;
	unsigned diffuse;
	float u1, v1;
	float u2, v2;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
class VertexBufferClass
{
public:
	virtual void Delete_This();

	void Add_Ref() { ++NumRefs; }
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	unsigned Type() const { return type; }
	const FVFInfoClass &FVF_Info() const { return *fvf_info; }

	class WriteLockClass
	{
		VertexBufferClass *VertexBuffer;
		void *Vertices;
		BFMEDX8DeviceLock device_lock;

	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags = 0);
		~WriteLockClass();
	};

	class AppendLockClass
	{
		VertexBufferClass *VertexBuffer;
		void *Vertices;
		BFMEDX8DeviceLock device_lock;

	public:
		AppendLockClass(VertexBufferClass *vertex_buffer, unsigned start_index, unsigned index_range, int flags = 0);
		~AppendLockClass();
	};

protected:
	int NumRefs;
	unsigned type;
	unsigned short VertexCount;
	int engine_refs;
	FVFInfoClass *fvf_info;
	bool unexamined18;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
class DX8VertexBufferClass : public VertexBufferClass
{
public:
	BfmeVertexBuffer9 *Get_DX8_Vertex_Buffer() { return VertexBuffer; }

private:
	BfmeVertexBuffer9 *VertexBuffer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
class SortingVertexBufferClass : public VertexBufferClass
{
public:
	VertexFormatXYZNDUV2 *VertexBuffer;
};

// Both constructors work through the parameter: retail keeps it in one
// register for every access, where the member would be reread after each
// store.
VertexBufferClass::WriteLockClass::WriteLockClass(VertexBufferClass *VertexBuffer_, int flags)
	: VertexBuffer(VertexBuffer_), Vertices(0)
{
	VertexBuffer_->Add_Ref();
	switch (VertexBuffer_->Type()) {
	case BUFFER_TYPE_DX8:
		{
			DX8_Assert();
			long result = static_cast<DX8VertexBufferClass *>(VertexBuffer_)->Get_DX8_Vertex_Buffer()->Lock(
				0,
				0,
				&Vertices,
				flags);
			if (result != 0)
				Log_DX8_ErrorCode(result);
		}
		break;
	case BUFFER_TYPE_SORTING:
		Vertices = static_cast<SortingVertexBufferClass *>(VertexBuffer_)->VertexBuffer;
		break;
	default:
		break;
	}
}

// ??1WriteLockClass@VertexBufferClass@@QAE@XZ present-unmatched
VertexBufferClass::WriteLockClass::~WriteLockClass()
{
	switch (VertexBuffer->Type()) {
	case BUFFER_TYPE_DX8:
		{
			DX8_Assert();
			long result = static_cast<DX8VertexBufferClass *>(VertexBuffer)->Get_DX8_Vertex_Buffer()->Unlock();
			if (result != 0)
				Log_DX8_ErrorCode(result);
		}
		break;
	case BUFFER_TYPE_SORTING:
		break;
	default:
		break;
	}
	VertexBuffer->Release_Ref();
}

// ??0AppendLockClass@VertexBufferClass@@QAE@PAV1@IIH@Z present-unmatched
VertexBufferClass::AppendLockClass::AppendLockClass(VertexBufferClass *VertexBuffer_, unsigned start_index, unsigned index_range, int flags)
	: VertexBuffer(VertexBuffer_), Vertices(0)
{
	VertexBuffer_->Add_Ref();
	switch (VertexBuffer_->Type()) {
	case BUFFER_TYPE_DX8:
		{
			DX8_Assert();
			long result = static_cast<DX8VertexBufferClass *>(VertexBuffer_)->Get_DX8_Vertex_Buffer()->Lock(
				start_index * VertexBuffer_->FVF_Info().Get_FVF_Size(),
				index_range * VertexBuffer_->FVF_Info().Get_FVF_Size(),
				&Vertices,
				flags);
			if (result != 0)
				Log_DX8_ErrorCode(result);
		}
		break;
	case BUFFER_TYPE_SORTING:
		Vertices = static_cast<SortingVertexBufferClass *>(VertexBuffer_)->VertexBuffer + start_index;
		break;
	default:
		break;
	}
}
