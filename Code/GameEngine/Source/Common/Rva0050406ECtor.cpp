// cl: /DNDEBUG /MD /EHsc
// ??0Rva0050406E@@QAE@XZ @ 0x0050406E, 12 bytes.
// Default ctor that forwards to the pinned member/base default ctor at
// 0x003FD398 (??0Rva00064390@@QAE@XZ): push esi, mov esi,ecx, call, mov
// eax,esi, pop esi, ret. Evidence: single caller at 0x00504091 in the 151B
// body at 0x0050407A; neighbours share the plain /DNDEBUG /MD /EHsc record
// shape; no vtable or EH frame in retail.
class Rva00064390
{
public:
	Rva00064390();
};

class Rva0050406E
{
public:
	Rva0050406E();
private:
	Rva00064390 m_base;
};

Rva0050406E::Rva0050406E()
{
}
