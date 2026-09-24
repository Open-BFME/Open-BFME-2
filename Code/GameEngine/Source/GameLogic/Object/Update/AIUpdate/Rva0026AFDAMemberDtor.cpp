// cl: /O1 /GX /DNDEBUG /MD
//
// ??1Rva0026AFDAMember@@QAE@XZ, retail 0x0026B03D (75 bytes). Teardown for
// the +0x3E4 DeployStyle member class (constructed through the 0x26AFDA
// thunk, destroyed here by the DeployStyle dtor at +0x3E4 and by two other
// owner dtors): frees the +0x24 buffer through the game free wrapper, then
// the two AsciiString members at +0x20 and +0x1C in reverse order. The class
// identity is unproven so it keeps the TU-local Rva name from
// DeployStyleAIUpdateCtor.cpp; the layout below is the dtor-proven prefix
// (the full member spans 0xC4).
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

extern "C" void __cdecl free(void *block);

class Rva0026AFDAMember
{
public:
	~Rva0026AFDAMember();

protected:
	unsigned char m_pad[0x1C];
	AsciiString m_string1C;			// +0x1C
	AsciiString m_string20;			// +0x20
	char *m_buffer24;			// +0x24
	unsigned char m_tail[0xC4 - 0x28];
};

// ??1Rva0026AFDAMember@@QAE@XZ @0x26B03D
Rva0026AFDAMember::~Rva0026AFDAMember()
{
	if (m_buffer24) {
		free(m_buffer24);
	}
}
