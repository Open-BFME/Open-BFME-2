// cl: /DNDEBUG /MD
//
// Null-guarded registry forwarders: when the global
// Q1 receiver registry at VA 0x00E09C0C is live, forward the argument to
// the rowed Q1Receiver0134FAAC worker. Same guard idiom as
// bfmeBeginResourceEnumeration at 0x0061F110 and
// bfmeInvokeResourceEnumeration at 0x0061EFB0, which guard the same global.

class Q1Receiver0134FAAC
{
public:
	void m009EC970(int which);
	void m009EC9A0(int which);
	void m009F0D40(int value);
	void m009F19E0(int source);
	void m009F0BD0(int value);
	void m009EC960(void *value);
	void m009F1A60(int source);
	void m009F0CC0(int source);
	void m009F0E50(int value);
};

Q1Receiver0134FAAC *TheQ1Receiver;

void bfmeStepReceiverRecord(int source)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009F19E0(source);
}

void bfmeMergeReceiverKeys(int value)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009F0BD0(value);
}

void bfmeMarkReceiverPayloads(int value)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009F0D40(value);
}

void bfmeSetReceiverFlag(int which)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009EC970(which);
}

void bfmeClearReceiverFlag(int which)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009EC9A0(which);
}

// 0x0061F0F0 (25B): the same guard with the argument tested first. Ported
// from Open-BFME-1 game/GameEngine/Source/Common/Q1GlobalGuardedForwarders.cpp
// Rva009EBBA0 (6d943426), byte-identical once relocations are set aside
// (bfme1_sweep T2; donor held at copy-tier S). The callee is the empty
// receiver m009EC960 (BFME 1: a 3-byte ret 4), here the folded ret-4 stub at
// 0x00180FD0.
void Rva0061F0F0(void *value)
{
	if (value && TheQ1Receiver)
		TheQ1Receiver->m009EC960(value);
}

// Reference: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/Common/Q1GlobalGuardedForwarders.cpp,
// S3GuardedDelegatesBulk.cpp and Bfme/Rva009EC0D0AssetRegistryName.cpp.
// Target evidence: every wrapper loads the same native E09C0C global as
// the six wrappers above. Calls resolve to already recovered providers
// 624710, 623580, 621B10, 6208B0 and 6213B0 respectively. No donor
// class layout or original wrapper name is inferred from byte placement.
void Rva0061EFF0(int source)
{
    if (TheQ1Receiver)
        TheQ1Receiver->m009F1A60(source);
}

void Rva0061F030(int source)
{
    if (TheQ1Receiver)
        TheQ1Receiver->m009F0CC0(source);
}

void Rva0061F050(int value)
{
    if (TheQ1Receiver)
        TheQ1Receiver->m009F0E50(value);
}

// Declaration-only ABI views of the existing provider classes.
class Gen_009EBB60Target {
public:
    int bfmeForward();
};
class AssetRegistry {
public:
    const char *rva006213B0(unsigned int key);
};

// Native null path returns 100; the live path tail-calls the rowed
// registry queue percentage operation at 6208B0.
int Rva0061F0B0()
{
    if (TheQ1Receiver)
        return ((Gen_009EBB60Target *)TheQ1Receiver)->bfmeForward();
    return 100;
}

// Native fallback at C7C5FC is the complete terminated literal below.
// The live path passes the unsigned key to the rowed name lookup.
const char *Rva0061F620(unsigned int key)
{
    if (!TheQ1Receiver)
        return "<no asset manager>";
    return ((AssetRegistry *)TheQ1Receiver)->rva006213B0(key);
}

