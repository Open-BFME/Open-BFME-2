// cl: /DNDEBUG /MD
// ??0Rva001F9060@@QAE@XZ @0x001F9060 22B: default ctor zeroing +0/+4 then rowed ObjectCreationList at +8 plus return this.
// Evidence: push esi mov esi ecx and [esi] 0 and [esi+4] 0 lea ecx [esi+8] call 0x001F81BF mov eax esi pop esi ret; callers at 0x001F9CC1 0x001FA5B2; prev is landed 0x001F9006.
class ObjectCreationList
{
public:
	ObjectCreationList();
};

class Rva001F9060
{
public:
	Rva001F9060();
private:
	int m_00;
	int m_04;
	ObjectCreationList m_08;
};

Rva001F9060::Rva001F9060()
	: m_00(0)
	, m_04(0)
{
}
