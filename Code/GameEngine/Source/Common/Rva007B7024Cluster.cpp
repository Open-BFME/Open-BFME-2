// cl: /Ireference/shims/bfme2_ascii /O2 /MD
//
// Four global-object teardowns in the 0x007B700A neighbourhood, continuing the
// Rva007B6880Thunks.cpp page (that file's last row is 0x007B71C0).
//
// 0x007B7024 (26B): refcounted-release for the global at VA 0x00DEE86C, the
//   inlined shape of `if (g) g->Release();` where Release() decrements the +4
//   counter and tail-calls virtual slot 0 when it reaches zero.  Writing the
//   release through the global (not a local alias) is what puts the object in
//   eax and produces retail's mov ecx,eax / add eax,4 counter address.
// 0x007B71D0 and 0x007B7200 (35B each): two guarded operator delete[] calls on
//   consecutive global pointers (VA 0x00DB6344/48 and 0x00DB6354/58).  The
//   first call cleans with add esp,4 and the final one with pop ecx, the /O2
//   shape (the same bodies at /O1 use pop ecx for both, 2 bytes shorter).
//   The global addresses are absolute DIR32 operands the byte gate masks, so
//   the owners are unproven and the bodies are address-named.

class Rva007B7024Object
{
public:
	virtual void release();

	int m_ref;	// +0x04

	void Release()
	{
		if (--m_ref == 0)
			release();
	}
};

// 0x007B700A (26B): target bytes show the same refcount-release shape as the
// adjacent 0x007B7024 body, but through the pointer slot at VA 0x00DEE870.
// The object's owner is unknown; this address-derived helper preserves that.
Rva007B7024Object *g_Va00DEE870;

#pragma optimize("s", on)
void __cdecl rva007B700A()
{
	if (g_Va00DEE870 != 0)
		g_Va00DEE870->Release();
}
#pragma optimize("", on)

// The global address is an absolute DIR32 operand, masked by the byte gate.
Rva007B7024Object *g_Va00DEE86C;

// Retail's release thunk uses the /O1 memory read-modify-write counter shape
// (dec [counter] / cmp [counter],0) while the two delete[] bodies below need
// the /O2 cleanup schedule, so this one body is pinned to favor-size.
#pragma optimize("s", on)
void __cdecl rva007B7024()
{
	if (g_Va00DEE86C != 0)
		g_Va00DEE86C->Release();
}
#pragma optimize("", on)

void operator delete[](void *p);

// g_Va00DB6344 / g_Va00DB6348: global pointer pair at VA 0x00DB6344/48.
void *g_Va00DB6344;
void *g_Va00DB6348;

void __cdecl rva007B71D0()
{
	if (g_Va00DB6344 != 0)
		operator delete[](g_Va00DB6344);
	if (g_Va00DB6348 != 0)
		operator delete[](g_Va00DB6348);
}

// g_Va00DB6354 / g_Va00DB6358: global pointer pair at VA 0x00DB6354/58.
void *g_Va00DB6354;
void *g_Va00DB6358;

void __cdecl rva007B7200()
{
	if (g_Va00DB6354 != 0)
		operator delete[](g_Va00DB6354);
	if (g_Va00DB6358 != 0)
		operator delete[](g_Va00DB6358);
}
