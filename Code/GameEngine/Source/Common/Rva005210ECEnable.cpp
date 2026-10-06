// cl: /GX-
// ?Rva005210ECEnable@@YAX_N@Z retail 0x005210EC 37B
// Evidence: unlock; callees enable 0x00222479 rowed; callers 0x00435F22 plus self region; globals g_Va00E0492C g_Va00A01E48 TheRva00222A8BTarget; precedent Rva0050E9D3Enable same tail-jmp enable pattern.
extern int g_Va00E0492C;
struct GlobalA01E48 { char pad[0x54]; unsigned char flag; };
extern GlobalA01E48 *g_Va00A01E48;
class Rva00222479ByteOneSetter { public: void enable(); };
class Rva00222A8BTarget;
extern class Rva00222A8BTarget *TheRva00222A8BTarget;

void Rva005210ECEnable(bool flag)
{
    if (g_Va00E0492C == 0)
        return;
    if (!flag)
        g_Va00A01E48->flag = 1;
    ((Rva00222479ByteOneSetter *)TheRva00222A8BTarget)->enable();
}
