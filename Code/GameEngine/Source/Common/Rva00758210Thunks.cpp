// cl: /O1 /MD
//
// ?rva00758210@Rva00758210@@QAEXXZ @0x00758210 8B,
// ?rva00758230@Rva00758230@@QAEXPAURva009A29A0Window@@@Z @0x00758230 8B,
// ?rva00758240@Rva00758240@@QAEXPAVRva009A36F0Param@@@Z @0x00758240 8B.
// Homogeneous member thunks: mov ecx,[ecx+0x10] then tail-jmp to the rowed
// target (markState 0x758900, WindowManager::set 0x758940, Owner::apply
// 0x7592E0). Callers are 0x243FEE and the CritterEmitter vslot 0x4C8DE2.
// Honest address names; wrapper holds the target pointer at +0x10. Shape
// follows Rva007B6880Thunks (/O1 tail-jmp).

class Rva009A2960
{
public:
	void markState();
    void markState3();
};

struct Rva009A29A0Window;
class Rva009A29A0WindowManager
{
public:
	void set(Rva009A29A0Window *window);
};

class Rva009A36F0Param;
class Rva009A36F0Owner
{
public:
	void apply(Rva009A36F0Param *param);
};

class Rva00758210
{
public:
	void rva00758210();

private:
	char m_pad[0x10];
	Rva009A2960 *m_ptr;
};

void Rva00758210::rva00758210()
{
	return m_ptr->markState();
}

class Rva00758230
{
public:
	void rva00758230(Rva009A29A0Window *window);

private:
	char m_pad[0x10];
	Rva009A29A0WindowManager *m_ptr;
};

void Rva00758230::rva00758230(Rva009A29A0Window *window)
{
	return m_ptr->set(window);
}

class Rva00758240
{
public:
	void rva00758240(Rva009A36F0Param *param);

private:
	char m_pad[0x10];
	Rva009A36F0Owner *m_ptr;
};

void Rva00758240::rva00758240(Rva009A36F0Param *param)
{
	return m_ptr->apply(param);
}

// Whole clean BF1 UnclaimedMemberTailForwarders.cpp supplies the pattern;
// donor revision6583b3c1ff21db4a561285717028fdafc780b7db.
// Native758220 uses owner+10 (BF1 counterpart owner+C); original owner identity
// is unproven. Complete8B boundary ends758228 before8CC; target758920 is the
// independently verified state3 update. No entry xrefs were observed.
class Rva00758220 {
public:
    void rva00758220();
private:
    char m_pad[0x10];
    Rva009A2960 *m_ptr;
};
void Rva00758220::rva00758220() {
    return m_ptr->markState3();
}
