// cl: /DNDEBUG /MD
// ?rva00466398@Rva00466398@@QAEXPAUOut00466398@@@Z retail 0x00466398 26B
// Branchless out-param writer: out->a = this ? this+4 : 0 via neg/sbb/and
// then out->b = this+0x10. Evidence: mov edx ecx neg lea sbb and sequence
// plus two stores and ret 4; 8 callers passing out pairs e.g. 0x00466A7C
// with mov ecx eax call; neighbours share /O1 /DNDEBUG /MD. Honest Rva name.
struct Out00466398
{
	void *a;
	void *b;
};
class Rva00466398
{
public:
	void rva00466398(Out00466398 *out);
private:
	char m_pad[20];
};
void Rva00466398::rva00466398(Out00466398 *out)
{
	out->a = this ? (void *)((char *)this + 4) : (void *)0;
	out->b = (void *)((char *)this + 16);
}
