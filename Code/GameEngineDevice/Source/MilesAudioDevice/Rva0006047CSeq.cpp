// cl: /O2 /MD
// Native [0x6047C,0x604A3),39B: pushes esi, runs three no-argument member
// calls on this (the third on the subobject at +0xB90), then makes two
// no-argument calls through .data function pointers, the second as a tail jump.
// Address-derived names: the class and the callee identities are not proven.
typedef void (__cdecl *Rva0006047CFn)(void);
extern Rva0006047CFn g_Va00BBAB78;
extern Rva0006047CFn g_Va00BBAB74;
class Rva0006047CSub
{
public:
	void rva00053D89(void);
};
class Rva0006047CSelf
{
public:
	void rva00060309(void);
	void rva00053352(void);
	void rva0006047C(void);
private:
	char pad00[0xB90];
	Rva0006047CSub m_b90;
};
void Rva0006047CSelf::rva0006047C(void)
{
	rva00060309();
	rva00053352();
	m_b90.rva00053D89();
	g_Va00BBAB78();
	return g_Va00BBAB74();
}
