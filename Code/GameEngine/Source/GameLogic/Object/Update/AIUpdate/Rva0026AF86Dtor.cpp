// cl: /EHs /DNDEBUG /MD /Ireference/shims/moduledata
// ??1Rva0026AF86@@UAE@XZ retail 0x0026AF86 75B: dtor freeing +0x10 then +4 via rowed free then restoring Snapshot vtable BBB554.
// Evidence: EH_prolog scopetable plus push ecx push esi mov esi ecx with state 1 free +0x10 then state 0 free +4 then mov [esi] g_00BBB554; caller 0x0026AF6A deleting dtor with operator delete.
#include "Common/Snapshot.h"
extern "C" void __cdecl free(void *block);
// Members at +4/+0x10 are NOT AsciiString: their inlined dtor calls free
// directly while the kept ??1AsciiString@@QAE@XZ is jmp releaseBuffer, so
// this 4-byte pointer wrapper is renamed Rva0026AF86String per LINK-COMDAT.
class Rva0026AF86String
{
public:
	~Rva0026AF86String()
	{
		if (m_data != 0)
			free(m_data);
	}
private:
	void *m_data;
};
class __declspec(novtable) Rva0026AF86 : public Snapshot
{
public:
	virtual ~Rva0026AF86();
private:
	Rva0026AF86String m_04;
	char m_pad08[8];
	Rva0026AF86String m_10;
};
Rva0026AF86::~Rva0026AF86()
{
}
