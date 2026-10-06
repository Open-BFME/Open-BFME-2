// cl: /MD
// ??1Rva0054C742@@UAE@XZ @ 0x0054C742 18B
// Virtual dtor: stores vtable 0x0086A6A4 then zeroes global g_Va00E05FAC then tail-jmps to base dtor pin ??1Rva0054D2CF@@UAE@XZ. Evidence: retail mov [ecx] vtbl + and [0x00E05FAC] 0 + jmp 0x0054D2CF; caller at 0x0054C754 is deleting dtor calling this then operator delete.
class Rva0054D2CF
{
public:
	virtual ~Rva0054D2CF();
};
class Rva0054C742 : public Rva0054D2CF
{
public:
	virtual ~Rva0054C742();
};
extern int g_Va00E05FAC;
Rva0054C742::~Rva0054C742()
{
	g_Va00E05FAC = 0;
}
