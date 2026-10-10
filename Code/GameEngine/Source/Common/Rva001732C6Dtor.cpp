// cl: /O1 /MD /EHsc
// ??1Rva001732C6@@QAE@XZ, retail 0x0018C57C..0x0018C5FB (127 bytes, EH):
// the non-virtual destructor the rowed scalar deleting destructor 0x001732C6
// calls. Under the DirectX thread lock (the same lock/assert guard the rowed
// 0x000E6B99 uses) it releases the COM object at +0x08 through its stdcall
// Release slot and the two reference-counted objects at +0x0C/+0x10, each
// cleared; after the lock the +0x14 buffer is freed through GameFree.
// Owner and field identities are not established; names stay address-
// derived.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
void __cdecl Rva00030830GameFree(void *);

struct Rva0018C57CDeviceLock
{
	Rva0018C57CDeviceLock() { BFME_DX8_Thread_Lock(); }
	~Rva0018C57CDeviceLock() { BFME_DX8_Thread_Assert(); }
};

struct Rva0018C57CComObject
{
	virtual long __stdcall QueryInterface(const void *iid, void **out);
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
};

class Rva0018C57CRef
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
private:
	int m_refs;
};

struct Rva0018C57CBuffer
{
	~Rva0018C57CBuffer() { if (m_data) Rva00030830GameFree(m_data); }
	void *m_data;
};

class Rva001732C6
{
public:
	~Rva001732C6();
private:
	int m_00;
	int m_04;
	Rva0018C57CComObject *m_object08;	// +0x08
	Rva0018C57CRef *m_ref0C;		// +0x0C
	Rva0018C57CRef *m_ref10;		// +0x10
	Rva0018C57CBuffer m_buffer14;		// +0x14
};

Rva001732C6::~Rva001732C6()
{
	Rva0018C57CDeviceLock lock;
	if (m_object08)
	{
		m_object08->Release();
		m_object08 = 0;
	}
	if (m_ref0C)
	{
		m_ref0C->Release_Ref();
		m_ref0C = 0;
	}
	if (m_ref10)
	{
		m_ref10->Release_Ref();
		m_ref10 = 0;
	}
}
