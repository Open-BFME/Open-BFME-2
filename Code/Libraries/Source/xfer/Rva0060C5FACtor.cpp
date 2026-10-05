// cl: /DNDEBUG /MD /O1
// ??0Rva0060C5FA@@QAE@PAX00@Z @0x0060C5FA (47B):
// Xfer-family ctor with manual vtable: currentBlock -1 at +1c, +4/+8/+0c
// from arg1/arg3/arg2, vtable 0x00C7AF18 stored 5th, then zeroes for the
// Xfer isLoading/stream/blockCount slots at +10/+14/+18. No virtuals
// (manual void* vtable, absolute VA per Snapshot precedent) so no implicit
// vptr store and the retail order falls out of body assignments. Caller
// 0x00409A0C destroys the object via ??1Xfer, so the class dtor is
// implicit. Eight ctor callers. Honest-address name.

extern const void *const g_00C7AF18[];

class Rva0060C5FA
{
public:
	Rva0060C5FA(void *a1, void *a2, void *a3);

private:
	void *m_vtable;
	void *m_04;
	void *m_08;
	void *m_0c;
	bool m_isLoading;
	unsigned char m_pad11[3];
	void *m_stream;
	int m_blockCount;
	int m_currentBlock;
};

Rva0060C5FA::Rva0060C5FA(void *a1, void *a2, void *a3)
{
	m_currentBlock = -1;
	m_04 = a1;
	m_08 = a3;
	m_0c = a2;
	m_vtable = (void *)g_00C7AF18;
	m_isLoading = false;
	m_stream = 0;
	m_blockCount = 0;
}
