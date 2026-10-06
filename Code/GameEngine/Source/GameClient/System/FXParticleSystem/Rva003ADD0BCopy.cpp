// cl: /EHs-c-
// ??0Rva003ADD0B@@QAE@ABV0@@Z @0x003ADD0B 38B copy ctor via rowed base 0x003ADD31 with three derived stores. Evidence: callee rowed; caller 0x003ADD00; chain from just-landed 0x003ADD31.
class Rva003ADD31
{
public:
	Rva003ADD31(const Rva003ADD31 &other);
private:
	char m_pad[176];
};
extern const void *const g_00C1C954[];
extern const void *const g_00C1C950[];
class Rva003ADD0B : public Rva003ADD31
{
public:
	Rva003ADD0B(const Rva003ADD0B &other);
};
Rva003ADD0B::Rva003ADD0B(const Rva003ADD0B &other)
	: Rva003ADD31(other)
{
	*(const void **)this = g_00C1C954;
	*(const void **)((char *)this + 8) = g_00C1C950;
	*(const char **)((char *)this + 12) = "HZz";
}
