// cl: /MD /EHsc
// ?rva001F5D4F@Rva001F5D4F@@QAEXH@Z @0x001F5D4F 34B.
// Null-checked virtual slot 3 at +0 with int arg, then rowed Rva001F42BA::call on this+4.
// Sibling of 0x001F5D38 (same shape without args); callers at 0x001F6502 and
// 0x001F8DD9, jmp-ins at 0x001F648D, 0x001F820E and 0x001F895B. Honest Rva names.
struct Rva001F42BA {
    void call(int);
};
class Helper001F5D4F {
public:
    virtual ~Helper001F5D4F();
    virtual void pad1();
    virtual void pad2();
    virtual void slot3(int);
};
class Rva001F5D4F {
public:
    void rva001F5D4F(int x);
private:
    Helper001F5D4F* m_ptr;
    Rva001F42BA m_next;
};

// ?rva001F820B@Rva001F820BOwner@@QAEXH@Z @0x001F820B 8B: offsets this to the Rva001F5D4F embedded at +0x4 and
// tail-jumps Rva001F5D4F::rva001F5D4F. Owner and name are address-derived; no
// referencing site was found in this pass.
class Rva001F820BOwner
{
public:
	void rva001F820B(int x);
};

void Rva001F820BOwner::rva001F820B(int x)
{
	((Rva001F5D4F *)((char *)this + 0x4))->rva001F5D4F(x);
}

// ?rva001F8958@Rva001F8958Owner@@QAEXH@Z @0x001F8958 8B: offsets this to the Rva001F5D4F embedded at +0x8 and
// tail-jumps Rva001F5D4F::rva001F5D4F. Owner and name are address-derived; no
// referencing site was found in this pass.
class Rva001F8958Owner
{
public:
	void rva001F8958(int x);
};

void Rva001F8958Owner::rva001F8958(int x)
{
	((Rva001F5D4F *)((char *)this + 0x8))->rva001F5D4F(x);
}
