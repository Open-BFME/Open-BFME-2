// Open-BFME5 conversions.

extern "C" void *__identifier("??_7Gen008030A0@@6B@")[];

class BfmeLogUUA
{
public:
	virtual void bfmeV0UUA() = 0;
	virtual void bfmeV1UUA() = 0;
	virtual void bfmeV2UUA() = 0;
	virtual void bfmeWarnUUA(const char *msg, const char *file, int line) = 0;
};

struct Rva007EB810Diag; Rva007EB810Diag *Rva007EB810Get();

class GameBrowserPinger
{
public:
	void bfmeGoUUA();
	void *m_bfmeVft;
	char m_bfmePad[4];
	void *m_protoPingRef;
	void *m_pendingQueue;
	int m_numPendingRequests;
};

void GameBrowserPinger::bfmeGoUUA()
{
	m_bfmeVft = __identifier("??_7Gen008030A0@@6B@");
	if (m_protoPingRef)
		((BfmeLogUUA *)Rva007EB810Get())->bfmeWarnUUA((char *)"mProtoPingRef == 0", (char *)"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp", 0x45);
	if (m_pendingQueue)
		((BfmeLogUUA *)Rva007EB810Get())->bfmeWarnUUA((char *)"mPendingQueue == 0", (char *)"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp", 0x46);
	if (m_numPendingRequests)
		((BfmeLogUUA *)Rva007EB810Get())->bfmeWarnUUA((char *)"mNumPendingRequests == 0", (char *)"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp", 0x47);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Gen008030A0@@UAE@XZ=?bfmeGoUUA@GameBrowserPinger@@QAEXXZ")
// The vtable this body installs is Gen008030A0's (same 0x14-byte class; the
// dtor binding above names it). Y2ScalarDeleters emits that vtable; bind this
// unit's invented global spelling to it so the reference links.
