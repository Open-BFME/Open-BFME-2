// cl: /MD
// ??1Rva005E3258@@UAE@XZ @0x005E3258 14B
// Virtual dtor storing vtable 0x00877BB4 then tail-jmping to member clear
// 0x005E30CE at +4. Layout from retail add ecx 4: Rva005E30CE subobject at +4.
// Caller 0x005E3271 plus chain from 0x005E30CE. Precedent SubtitleEntry 14B tail-jmp.
// Evidence: chain lane; vtable g_00C77BB4; callee rowed.
class Rva005E30CE
{
public:
	void rva005E30CE();
};

extern const void *const g_00C77BB4[];

class Rva005E3258
{
public:
	virtual ~Rva005E3258();
private:
	Rva005E30CE m_04;
};
Rva005E3258::~Rva005E3258()
{
	m_04.rva005E30CE();
}
