// cl: /MD
// ?rva0010F110@Rva0010F110@@QAEXXZ @0x0010F110 12B.
// ?rva0010F11C@Rva0010F110@@QAE_NH@Z @0x0010F11C 45B.
// Infinite wait on the +0x18 handle via kernel32 WaitForSingleObject, plus
// guarded loop-count check calling the +0x18 wait then reading the volatile
// +0x08 stream via AIL_stream_loop_count. Evidence: IAT WaitForSingleObject
// at 0x00BBA228 and AIL_stream_loop_count at 0x00BBABB0, callers at
// 0x0010F11F and 0x000A8B73 and 0x000A8B63, push -1 (INFINITE) and volatile
// memory-direct cmp/push shape per precedent Rva0010F0C4Dtor. Honest address
// names: 0x0010F11C calls 0x0010F110 with the same this.
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long timeout);
extern "C" __declspec(dllimport) int __stdcall AIL_stream_loop_count(void *stream);

typedef void *HSTREAM;

class Rva0010F110
{
public:
    void rva0010F110();
    bool rva0010F11C(int x);
private:
    char m_pad0[8]; // +0..+7
    volatile HSTREAM m_stream08; // +0x08 volatile for memory-direct cmp/push
    char m_pad0C[0x0C]; // +0x0C..+0x17
    void *m_handle18; // +0x18
    int m_field1C; // +0x1C
};

void Rva0010F110::rva0010F110()
{
    WaitForSingleObject(m_handle18, 0xFFFFFFFF);
}

bool Rva0010F110::rva0010F11C(int x)
{
    rva0010F110();
    if (m_stream08 == 0)
        return true;
    int loops = AIL_stream_loop_count(m_stream08);
    int rem = m_field1C - loops;
    return rem >= x;
}
