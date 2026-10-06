// cl: /MD
// ?Rva0008A185Copy@@YAPAVRva00089822@@PAV1@00@Z, retail 0x0008A185, 38 bytes.
// Uninitialized_copy helper: copy [first last) via rowed 0x0008A173, return dst end.
// Evidence: jmp to cmp, push dst push src call 0x8A173 in loop with 0x18 strides cmp jne mov eax esi bare ret. Callers pass 4 args and clean 0x10. Owner unknown so honest Rva name.
class Rva00089822
{
public:
	Rva00089822(const Rva00089822 &other);

private:
	char m_pad[0x18];
};

void __cdecl Rva0008A173Copy(Rva00089822 *dst, const Rva00089822 &src);

Rva00089822 *__cdecl Rva0008A185Copy(Rva00089822 *first, Rva00089822 *last, Rva00089822 *dst)
{
	Rva00089822 *d = dst;
	Rva00089822 *s = first;
	while (s != last)
	{
		Rva0008A173Copy(d, *s);
		++s;
		++d;
	}
	return d;
}
