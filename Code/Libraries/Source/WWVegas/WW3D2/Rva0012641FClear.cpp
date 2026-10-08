// cl: /DNDEBUG /MD
// ?Rva0012641FClear@@YAXXZ @0x0012641F 20B unlock lane free clear via two holders.
// Evidence: mov ecx g_00DEE870 call rowed rva005F2577 0x005F2577 then mov ecx g_00DEE86C tail-jmp same; callers 0x000434E8 0x0004A00C 0x0020245A.
class Rva005F2577Holder
{
public:
    void rva005F2577();
};

class Rva007B7024Object;
extern Rva007B7024Object *g_Va00DEE870;	// Rva007B7024Cluster.cpp
extern Rva007B7024Object *g_Va00DEE86C;

void Rva0012641FClear()
{
    ((Rva005F2577Holder *)&g_Va00DEE870)->rva005F2577();
    ((Rva005F2577Holder *)&g_Va00DEE86C)->rva005F2577();
}
