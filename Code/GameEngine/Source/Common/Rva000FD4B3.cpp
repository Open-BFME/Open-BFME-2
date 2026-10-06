// cl: /MD
// ?rva000FD4B3@Rva000FD4B3@@QAEHXZ @0x000FD4B3 27B; chain of Rva000F630CGet.
// Retail: push esi / mov esi,ecx / call 0x000F630C / test al,al / jne / xor eax,eax / pop esi / ret / xor eax,eax / mov [0x00DE1F34],esi / inc eax / pop esi / ret.
// Target facts: calls rowed ?Rva000F630CGet@@YAHXZ; tests low byte so false path needs xor; stores this into data 0x009E1F34 then returns 1 else 0.
// Callers: none; callees: 0x000F630C only. Owner unknown so class is address-derived.
// Not established: owning class identity beyond this-pointer store; global identity.
extern unsigned int g_Va00DE1F34;
// g_Va00DE1F34: matched references place it at VA 0xde1f34 (zero-filled .bss).
unsigned int g_Va00DE1F34;
int Rva000F630CGet(void);
class Rva000FD4B3
{
public:
	int rva000FD4B3();
};

int Rva000FD4B3::rva000FD4B3()
{
	if ((unsigned char)Rva000F630CGet() == 0)
		return 0;
	g_Va00DE1F34 = (unsigned int)this;
	return 1;
}
