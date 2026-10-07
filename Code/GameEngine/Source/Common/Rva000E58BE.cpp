// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva000E58BE@Rva000E58BE@@QAEXXZ @0x000E58BE 205B
// Rva000E58BE::rva000E58BE, retail 0x000E58BE (205 bytes, EBP frame with
// __EH_prolog): null-guards the index/vertex buffers at +8/+4 and the +0x20
// flag/+0x1C pointer, zeroes the +0xC/+0x10 counts, locks both buffers
// (WriteLock ctors 0x00138790/0x001394A0 with 0x2000, dtors 0x00138840/
// 0x00139530), walks the +0x18 list calling rowed 0x000E585F
// (Rva006F8700Owner::rva000E585F) per node, then Thread_Assert. Beside
// Rva000E585F.cpp and Rva000E59D3Dtor.cpp; Thread_Lock/Assert rows from
// BfmeDX8ThreadLock.cpp. Honest address name: caller 0x000E5AAD is unclaimed.

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }

	void *m_handle;
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(IndexBufferClass *index_buffer, int flags);
		~WriteLockClass();

		IndexBufferClass *m_buffer; // +0
		void *m_vertices; // +4
		BFMEDX8DeviceLock m_deviceLock; // +8
	};
};

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags);
		~WriteLockClass();

		VertexBufferClass *m_buffer; // +0
		void *m_vertices; // +4
		BFMEDX8DeviceLock m_deviceLock; // +8
	};
};

class Rva006F8700Owner
{
public:
	void rva000E585F(void *arg1, void *arg2, int *arg3, int *arg4);
};

struct Rva000E58BEListNode
{
	Rva000E58BEListNode *m_next; // +0
	Rva000E58BEListNode *m_prev; // +4
	Rva006F8700Owner *m_owner; // +8
};

class Rva000E58BE
{
public:
	void rva000E58BE();

private:
	char m_pad00[4]; // +0
	VertexBufferClass *m_vertexBuffer; // +4
	IndexBufferClass *m_indexBuffer; // +8
	int m_countC; // +0xC
	int m_count10; // +0x10
	char m_pad14[4]; // +0x14
	Rva000E58BEListNode *m_listHead; // +0x18
	void *m_ptr1C; // +0x1C
	unsigned char m_flag20; // +0x20
};

// ?rva000E58BE@Rva000E58BE@@QAEXXZ
void Rva000E58BE::rva000E58BE()
{
	if (m_indexBuffer == 0)
		return;
	if (m_vertexBuffer == 0)
		return;
	if (m_flag20 == 0)
		return;
	if (m_ptr1C == 0)
		return;
	m_countC = 0;
	m_count10 = 0;
	BFMEDX8DeviceLock deviceLock;
	IndexBufferClass::WriteLockClass indexLock(m_indexBuffer, 0x2000);
	VertexBufferClass::WriteLockClass vertexLock(m_vertexBuffer, 0x2000);
	void *vertexData = vertexLock.m_vertices;
	void *indexData = indexLock.m_vertices;
	for (Rva000E58BEListNode *node = m_listHead->m_next; node != m_listHead; node = node->m_next)
		node->m_owner->rva000E585F(indexData, vertexData, &m_count10, &m_countC);
}
