// cl: /DNDEBUG /MD
//
// ?rva0023C641@Rva0023C641@@QAEXPBD@Z @0x0023C641, 37B.
// File-write helper: if m_file18 then fputs(str,m_file) plus fflush(m_file).
// Retail: push esi; mov esi,ecx; mov eax,[esi+0x18]; test; je end;
// push eax; push [esp+0xC]; call fputs; push [esi+0x18]; call fflush;
// add esp,0xC; pop esi; ret 4.
// Evidence: callers 0x0023D5C2 and 0x0024367D pass string arg; FILE* at
// +0x18 unproven so Rva class; imports fputs/fflush are IAT (FF 15) so
// dllimport. Flags from sibling Rva0023C6A4Check.cpp (/O1 /DNDEBUG /MD).

extern "C" __declspec(dllimport) int __cdecl fputs(const char *str, void *file);
extern "C" __declspec(dllimport) int __cdecl fflush(void *file);

class Rva0023C641
{
public:
	void rva0023C641(const char *str);

private:
	char m_pad[0x18];
	void *m_file18; // +0x18
};

void Rva0023C641::rva0023C641(const char *str)
{
	if (m_file18) {
		fputs(str, m_file18);
		fflush(m_file18);
	}
}
