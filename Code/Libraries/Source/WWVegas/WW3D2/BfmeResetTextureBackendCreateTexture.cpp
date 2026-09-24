// ?CreateTexture@BfmeResetTextureBackend@@QAEXHHHHHHH@Z
// partial score=0.7 date=2026-09-24
// ?CreateTexture@BfmeResetTextureBackend@@QAEXHHHHHHH@Z
// retail 0x001310E3, 199 bytes.
// cl: /O1 /GX /DNDEBUG /MD

// ?CreateTexture@BfmeResetTextureBackend@@QAEXHHHHHHH@Z @0x001310E3,
// retail 197 bytes. Backend texture (re)creation worker: refreshes the saved
// creation fields from its seven arguments, sanitizes the format/usage
// arguments into D3DX-ready values, serializes the device through the rowed
// DX8 thread mutex, creates the texture through the pinned 6-arg helper and
// caches the surface description. Donor-free manual transcription; the three
// sibling call sites (Recreate plus the literal-init) prove the 7-arg
// thiscall shape (ret 0x1C).

struct BfmeResetComTexture
{
	virtual long __stdcall QueryInterface(void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct BfmeResetTextureBackend
{
	void CreateTexture(int width, int height, int createArg4C, int createArg44, int pool, int usage, int createArg48);

	int unused0;                 // +0x00
	int unused4;                 // +0x04
	BfmeResetComTexture *com;    // +0x08
	int field0C;                 // +0x0C: zeroed on recreate
	char pad10[0x28 - 0x10];
	int width;                   // +0x28
	int height;                  // +0x2C
	int desc30;                  // +0x30: surface-desc cache
	int desc34;                  // +0x34
	int desc38;                  // +0x38
	int desc3C;                  // +0x3C
	char pad40[0x44 - 0x40];
	int createArg44;             // +0x44
	int createArg48;             // +0x48
	int createArg4C;             // +0x4C
	int pool;                    // +0x50
	int usage;                   // +0x54
};

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
void *Rva00120720CreateTexture(int a1, int a2, int a3, int a4, int a5, int a6);

class BfmeDX8DeviceLockGuard
{
public:
	BfmeDX8DeviceLockGuard() { BFME_DX8_Thread_Lock(); }
	~BfmeDX8DeviceLockGuard() { BFME_DX8_Thread_Assert(); }
};

// ?CreateTexture@BfmeResetTextureBackend@@QAEXHHHHHHH@Z @0x001310E3
void BfmeResetTextureBackend::CreateTexture(int width, int height, int createArg4C, int createArg44, int pool, int usage, int createArg48)
{
	if (com != 0)
		return;
	this->createArg44 = createArg44;
	this->createArg4C = createArg4C;
	this->pool = pool;
	this->field0C = 0;
	this->usage = usage;
	this->createArg48 = createArg48;
	switch (pool) {
	case 0:
		pool = 0;
		break;
	case 1:
		pool = 1;
		break;
	case 2:
		pool = 2;
		break;
	default:
		pool = 0;
		break;
	}
	int sanitizedUsage;
	switch (usage) {
	case 0:
		sanitizedUsage = 0;
		break;
	case 1:
		sanitizedUsage = 1;
		break;
	case 2:
		sanitizedUsage = 0x200;
		break;
	default:
		sanitizedUsage = 0;
		break;
	}
	BfmeDX8DeviceLockGuard deviceLock;
	com = (BfmeResetComTexture *)Rva00120720CreateTexture(width, height, createArg4C, createArg44, pool, sanitizedUsage);
	this->width = width;
	this->height = height;
	this->desc30 = 1;
	this->desc34 = width;
	this->desc38 = height;
	this->desc3C = 1;
}
