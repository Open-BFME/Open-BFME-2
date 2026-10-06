// cl: /DNDEBUG /MD
// ?Rva0031968ACopy@@YAPAVRva00318B5C@@PBV1@0PAV1@@Z, retail 0x0031968A, 29 bytes.
// Three-arg uninitialized_copy wrapper over rowed 0x00318DEC five-arg copy:
// forwards first last result plus stack tag address and 0. Evidence: call
// 0x0031969D to rowed Rva00318DECCopy; pushes 0 plus ebp-1 plus three stack
// args with add esp 0x14; callers 0x00319BAB 0x00319C30 0x00319C50 0x00538E05.
class Rva00318B5C
{
public:
	virtual ~Rva00318B5C();
	int m_4;
	int m_8;
	int m_C;
};
Rva00318B5C *Rva00318DECCopy(const Rva00318B5C *first, const Rva00318B5C *last, Rva00318B5C *result, void *unused, int unused2);
Rva00318B5C *Rva0031968ACopy(const Rva00318B5C *first, const Rva00318B5C *last, Rva00318B5C *result)
{
	char tag;
	return Rva00318DECCopy(first, last, result, &tag, 0);
}
