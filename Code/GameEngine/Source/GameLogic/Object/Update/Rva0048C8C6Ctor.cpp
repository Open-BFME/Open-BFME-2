// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
#include "ascii_string.h"
// ??0Rva0048C8C6@@QAE@XZ @0x0048C8C6 23B
// Evidence: and [esi],0 then StringBase(PBD) at +4 with g_Rva0107301CEmptyString; caller 0x0048D671; neighbours stlport_copy_camera_marker and FlammableUpdateDtor.

class Rva0048C8C6
{
public:
	Rva0048C8C6();
private:
	int m_00;
	AsciiString m_04;
};

Rva0048C8C6::Rva0048C8C6() : m_00(0), m_04("")
{
}
