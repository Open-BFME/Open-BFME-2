// cl: /O1 /DNDEBUG /MD /GX
// Destructors whose only non-trivial member sits at +4 and whose bodies are
// therefore the 8B add ecx 4 / jmp tail into that member's destructor:
// 0x005011B4 -> rowed ??1Rva00500E3D@@QAE@XZ (RvaVectorDtorFamily.cpp) with
// callers 0x00501610 and 0x00501F4A; 0x0023863E -> rowed
// ??1VersionBlockParserInner@@QAE@XZ (VersionDestructor.cpp). The word at +0
// is trivially destructible (no vptr store). Original names unknown so
// address-derived Rva names are used.
struct Rva00500E3D
{
	~Rva00500E3D();
	void *m_start;
	void *m_finish;
	void *m_end;
};
class Rva005011B4
{
public:
	~Rva005011B4();
	int m_00;
	Rva00500E3D m_04;
};
Rva005011B4::~Rva005011B4()
{
}
class VersionBlockParserInner
{
public:
	~VersionBlockParserInner();
};
class Rva0023863E
{
public:
	~Rva0023863E();
	int m_00;
	VersionBlockParserInner m_04;
};
Rva0023863E::~Rva0023863E()
{
}
