#include <new>

// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0SequentialScript@@QAE@XZ @0x0020479E 43B, call sites 0x0020756E 0x0020A0B9
// 0x0020A936. Installs the vtable at 0x00BE3A90, zeroes +0x04..+0x10, then the
// +0x14..+0x20 block (0, -1, 0, -1), the +0x24 byte and +0x28.
// Structural inference: retail stores both -1s before both zeros of the
// +0x14 block; a 16-byte member sub-object with its own inline constructor
// reproduces that order (plain members put the or -1 first; the banked
// attempt also wrote the vtable as a literal address).
class Xfer;

struct SequentialScriptQuad
{
public:
	SequentialScriptQuad() : m_count0(0), m_index0(-1), m_count1(0), m_index1(-1) {}
	int m_count0; // +0x00
	int m_index0; // +0x04
	int m_count1; // +0x08
	int m_index1; // +0x0C
};
class SequentialScript {
public:
    __declspec(noinline) inline SequentialScript();
    virtual ~SequentialScript();
protected:
    virtual void loadPostProcess();
public:
    virtual const char *GetSnapshotName();
protected:
    virtual void xfer(Xfer *xfer);
public:
    int m_04;
    int m_08;
    int m_0c;
    int m_10;
    SequentialScriptQuad m_14;
    unsigned char m_24;
    int m_28;
};
SequentialScript::SequentialScript() : m_04(0), m_08(0), m_0c(0), m_10(0), m_24(0), m_28(0) {
}

// Keep the rowed constructor emitted as a selectable copy; no retail caller.
// ?bfmeEmitSequentialScriptCtor absent-from-retail
SequentialScript *bfmeEmitSequentialScriptCtor(void *storage)
{
    return new (storage) SequentialScript;
}
