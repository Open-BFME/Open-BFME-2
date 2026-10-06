// cl: /DNDEBUG /MD

// ?rva00141DC0@Rva00141DC0@@QAEPAXPAX@Z, retail 0x00141DC0, 44 bytes.
// List push_front via global 8-byte pool at 0x009B424C (VA 0x00DB424C):
// pops a node through landed Rva0006EFC8::rva00141800, stores *(void**)arg
// into node+4 when the derived value pointer is non-null (dead lea-test-je
// like Rva001EB9ACCreateNode), then links node at this->m_head. The
// redundant node->next=0 store survives for aliasing like retail; /O2 gives
// mov [eax],0 where /O1 gives and [eax],0. Callers await; no callers rowed
// yet. Evidence: pool/call shapes read off retail bytes and the landed
// grow/pop pair.

class Rva0006EFC8
{
public:
	void *rva00141800();
};

extern Rva0006EFC8 g_Rva0006EFC8Pool00DB424C;

class Rva00141DC0
{
public:
	void *rva00141DC0(void *arg);

private:
	void *m_head;
};

void *Rva00141DC0::rva00141DC0(void *arg)
{
	void *node = g_Rva0006EFC8Pool00DB424C.rva00141800();
	void **valuePtr = (void **)((char *)node + 4);
	if (valuePtr != 0)
		valuePtr[0] = *(void **)arg;
	((void **)node)[0] = 0;
	((void **)node)[0] = m_head;
	m_head = node;
	return node;
}
