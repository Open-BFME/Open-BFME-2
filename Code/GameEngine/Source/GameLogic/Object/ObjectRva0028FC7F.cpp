// cl: /DNDEBUG /MD
// ?rva0028FC7F@Rva0028FC7F@@QAEXPBX@Z @0x0028FC7F 16B. Forwards ecx plus
// (0xA, src, 1) to pinned rva0028EC68 0x0028EC68.
// Evidence: single caller 0x004CEA3A; neighbours ObjectOnDestroy and
// Object_attemptHealing share these flags; callee signature
// (int, const void *, int) from ActiveBodySlot22 and Detonate donors.
class Object
{
public:
	void rva0028EC68(int a, void *b, int c);
};

class Rva0028FC7F
{
public:
	void rva0028FC7F(const void *src);
};

void Rva0028FC7F::rva0028FC7F(const void *src)
{
	((Object *)this)->rva0028EC68(0xA, const_cast<void *>(src), 1);
}
