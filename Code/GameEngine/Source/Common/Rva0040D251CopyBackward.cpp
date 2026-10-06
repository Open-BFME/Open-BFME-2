// cl: /MD
// ?Rva0040D251CopyBackward@@YAPAVRva0040D0A4Entry@@PAV1@00@Z, retail 0x0040D251, 47 bytes.
// copy_backward for Rva0040D0A4Entry 8-byte entries using rowed assignment
// 0x0040D0A4. Same shape as Rva005EF000CopyBackward for holders. Caller at
// 0x0040D67E.

class Rva002B2F97
{
public:
	Rva002B2F97 &operator=(const Rva002B2F97 &other);

private:
	void *m_ptr;
};

class Rva0040D0A4Entry
{
public:
	Rva0040D0A4Entry &operator=(const Rva0040D0A4Entry &other);

private:
	int m_first;
	Rva002B2F97 m_second;
};

Rva0040D0A4Entry * __cdecl Rva0040D251CopyBackward(Rva0040D0A4Entry *first, Rva0040D0A4Entry *last, Rva0040D0A4Entry *dest)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		--last;
		--dest;
		*dest = *last;
	}
	return dest;
}
