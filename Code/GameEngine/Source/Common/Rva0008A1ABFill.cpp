// cl: /MD
// ?Rva0008A1ABFill@@YAPAVRva00089822@@PAV1@IABV1@@Z, retail 0x0008A1AB, 37 bytes.
// Fill_n helper: copy-construct count copies of value via rowed 0x0008A173, return end.
// Evidence: test count jbe, push value push dst call 0x8A173 in loop with 0x18 stride dec jne mov eax esi bare ret. Caller 0x8B6C0 passes 4 args and cleans 0x10. Owner unknown so honest Rva name.
class Rva00089822
{
public:
	Rva00089822(const Rva00089822 &other);

private:
	char m_pad[0x18];
};

void __cdecl Rva0008A173Copy(Rva00089822 *dst, const Rva00089822 &src);

Rva00089822 *__cdecl Rva0008A1ABFill(Rva00089822 *dst, unsigned int count, const Rva00089822 &value)
{
	Rva00089822 *p = dst;
	while (count > 0)
	{
		Rva0008A173Copy(p, value);
		++p;
		--count;
	}
	return p;
}
