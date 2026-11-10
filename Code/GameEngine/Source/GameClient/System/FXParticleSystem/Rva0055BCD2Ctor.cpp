// cl: /DNDEBUG /MD /EHsc /Ob2
// ??0Rva0055BCD2@@QAE@I@Z @0x0055BCD2 31B
// Ctor overwrites base vtable with 0x00C1D164 and +8 with 0x00C1C780 after rowed base 0x00563FE1.
// Evidence: thiscall 1 arg ret 4; calls rowed ??0Rva00563FE1@@QAE@I@Z 0x00563FE1; vtable VA 0x00C1D164; +8 VA 0x00C1C780; callers 0x0055B544 0x0055BD09; neighbours 0x0055BC8B 0x0055BEE9 same FXParticleSystem.
class Rva00563FE1
{
public:
	Rva00563FE1(unsigned int a);
};

extern const void *const g_00C1D164[];
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");

class Rva0055BCD2 : public Rva00563FE1
{
public:
	Rva0055BCD2(unsigned int a);
};

Rva0055BCD2::Rva0055BCD2(unsigned int a) : Rva00563FE1(a)
{
	*(const void **)this = g_00C1D164;
	*(void **)((char *)this + 8) = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
}
