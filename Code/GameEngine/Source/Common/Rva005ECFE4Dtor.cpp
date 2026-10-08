// cl: /GX /DNDEBUG /MD
// ??1Rva005ECFE4@@MAE@XZ @ 0x005ECFE4 (11B): derived dtor stores vtable RVA
// 0x008785B4 (image VA 0x00C785B4), then tail-jmps to base 0x005ECAD0.
// Slot 0 of that vtable is the rowed deleting dtor at 0x005ECFC8.
extern const void *const g_00C785B4[];

class Rva005ECA91
{
protected:
	virtual ~Rva005ECA91();
};

class Rva005ECFE4 : public Rva005ECA91
{
public:
	Rva005ECFE4(void *arg0, void *arg1, void *arg2);
	static void *rva005ED15D(void *arg0, void *arg1, void *arg2);

protected:
	virtual ~Rva005ECFE4();

private:
	// The factory allocates 0x1C bytes; the inherited member meanings remain
	// unmodeled in this TU.
	char m_unrecovered04[0x18];
};

typedef char Rva005ECFE4SizeCheck[sizeof(Rva005ECFE4) == 0x1C ? 1 : -1];

Rva005ECFE4::~Rva005ECFE4()
{
	*(const void **)this = g_00C785B4;
}

// Target 0x005ED15D (59B) allocates 0x1C bytes and forwards three stack
// arguments to 0x005ECE81. That target routine calls the rowed base ctor at
// 0x005ECA91 and writes the same vtable as the rowed dtor at 0x005ECFE4.
// The outer method and argument meanings are not recovered, so keep its
// address-derived name.
// ?Rva005ECFE4::rva005ED15D present-unmatched
void *Rva005ECFE4::rva005ED15D(void *arg0, void *arg1, void *arg2)
{
	return new Rva005ECFE4(arg0, arg1, arg2);
}
