// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// Two chained 8-byte member forwarders (each: mov ecx,[ecx+4]; jmp):
//   ?rva0057539C@Rva00575383@@QAEXXZ @0x0057539C -- slot 1 of Rva00575383's
//     vtable (its constructor 0x00575383 is rowed) -- hands off to the
//     object at +0x04,
//   ?rva005750C7@Rva005750C7@@QAEXXZ @0x005750C7, which hands off in turn to
//     its own +0x04 object's 0x00575038 (143 bytes, not yet rowed; pinned).
// No WorldBuilder names are matched.

class Rva00575038
{
public:
	void rva00575038();
};

class Rva005750C7
{
public:
	__declspec(noinline) void rva005750C7();
private:
	int m_00;
	Rva00575038 *m_04;
};

void Rva005750C7::rva005750C7()
{
	m_04->rva00575038();
}

class Rva00575383
{
public:
	void rva0057539C();
private:
	void *m_vtable00;
	Rva005750C7 *m_04;
};

void Rva00575383::rva0057539C()
{
	m_04->rva005750C7();
}
