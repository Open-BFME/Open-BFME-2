// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same shape as ConstIntGetters.cpp (mov eax,<IMM32> / ret, 6B) but kept in
// a separate TU so this lane does not contend with the hot ConstIntGetters
// appends on origin/master. Rows are opaque address-derived names: each
// body is a CC-island or ret-prev leaf carried by .rdata vtable slots with
// no direct callers and no branch sources, so no class identity is
// witnessed. No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva00742550Get@@YAHXZ @ 0x00742550 (6B): returns 0x1C (28). CC-island
// (16xCC before, 20xCC after), carried by 2 .rdata slots (0x7D3D4C and
// 0x8F1694, same vtable family suffix 4D43D0/4D43D0/46CE6B/87A69C),
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00742550Get(void)
{
	return 0x1C;
}

// ?Rva0018026EGet@@YAHXZ @ 0x0018026E (6B): returns 0x4D455348.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot (0x7D4FC4)
// in a vtable family shared with Rva00180581Get (identical neighbours),
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0018026EGet(void)
{
	return 0x4D455348;
}

// ?Rva00180581Get@@YAHXZ @ 0x00180581 (6B): returns 0x50415254.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot (0x7D5004)
// in the parallel vtable to Rva0018026EGet, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva00180581Get(void)
{
	return 0x50415254;
}

// ?Rva00180AA0Get@@YAHXZ @ 0x00180AA0 (6B): returns 0x41474752.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot (0x7D5084)
// in the 0x180xxx vtable family, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00180AA0Get(void)
{
	return 0x41474752;
}

// ?Rva00180E70Get@@YAHXZ @ 0x00180E70 (6B): returns 0x4E554C4C.
// CC-island (16xCC before and after), carried by 1 .rdata slot (0x7D50C4)
// in the 0x180xxx vtable family, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00180E70Get(void)
{
	return 0x4E554C4C;
}

// Existing getters rehomed after naming their verified factory providers.
// Integer return representation is retained; function addresses now relocate.
class Rva0009FD78; Rva0009FD78 *__stdcall Rva0008F925Create(void *);
class Rva0009FDBD; Rva0009FDBD *__stdcall Rva0008F95FCreate(void *);
class Rva000A0891; Rva000A0891 *__stdcall Rva0008F6E1Create(void *);
class Rva000A08D9; Rva000A08D9 *__stdcall Rva0008F71BCreate(void *);
class Rva000A0CE7; Rva000A0CE7 *__stdcall Rva0008FAF5Create(void *);
class Rva000A0D3A; Rva000A0D3A *__stdcall Rva0008FB2FCreate(void *);
class Rva000A12FE; Rva000A12FE *__stdcall Rva0008FB69Create(void *);
class Rva000A1346; Rva000A1346 *__stdcall Rva0008FBA3Create(void *);
class Rva000A15FE; Rva000A15FE *__stdcall Rva0008FBDDCreate(void *);
class Rva000A1646; Rva000A1646 *__stdcall Rva0008FC17Create(void *);
class Rva000A2137; Rva000A2137 *__stdcall Rva0008FA81Create(void *);
class Rva000A217F; Rva000A217F *__stdcall Rva0008FABBCreate(void *);
class Rva000A2670; Rva000A2670 *__stdcall Rva0008F999Create(void *);
class Rva000A26C7; Rva000A26C7 *__stdcall Rva0008F9D3Create(void *);
class Rva000A26F7; Rva000A26F7 *__stdcall Rva0008FA0DCreate(void *);
class Rva000A270F; Rva000A270F *__stdcall Rva0008FA47Create(void *);
class Rva000A3307; Rva000A3307 *__stdcall Rva0008F8B1Create(void *);
class Rva000A334F; Rva000A334F *__stdcall Rva0008F8EBCreate(void *);
class Rva000A3DE3; Rva000A3DE3 *__stdcall Rva0008F7C9Create(void *);
class Rva000A3E2B; Rva000A3E2B *__stdcall Rva0008F803Create(void *);
class Rva000A435C; Rva000A435C *__stdcall Rva0008F83DCreate(void *);
class Rva000A43A4; Rva000A43A4 *__stdcall Rva0008F877Create(void *);
class Rva000A4916; Rva000A4916 *__stdcall Rva0008F755Create(void *);
class Rva000A4969; Rva000A4969 *__stdcall Rva0008F78FCreate(void *);

// ?Rva002BE8CEGet@@YAHXZ @ 0x002BE8CE: verified existing getter.
int Rva002BE8CEGet(void)
{
	return (int)"LivingWorld (client)";
}

// ?Rva0009FDF5Get@@YAHXZ @ 0x0009FDF5: verified existing getter.
int Rva0009FDF5Get(void)
{
	return reinterpret_cast<int>(&Rva0008F925Create);
}

// ?Rva0009FDFBGet@@YAHXZ @ 0x0009FDFB: verified existing getter.
int Rva0009FDFBGet(void)
{
	return reinterpret_cast<int>(&Rva0008F95FCreate);
}

// ?Rva00180E60Get@@YAHXZ @ 0x00180E60: verified existing getter.
int Rva00180E60Get(void)
{
	return (int)"NULL";
}

// ?Rva000A08F1Get@@YAHXZ @ 0x000A08F1: verified existing getter.
int Rva000A08F1Get(void)
{
	return reinterpret_cast<int>(&Rva0008F6E1Create);
}

// ?Rva000A08F7Get@@YAHXZ @ 0x000A08F7: verified existing getter.
int Rva000A08F7Get(void)
{
	return reinterpret_cast<int>(&Rva0008F71BCreate);
}

// ?Rva000A0D52Get@@YAHXZ @ 0x000A0D52: verified existing getter.
int Rva000A0D52Get(void)
{
	return reinterpret_cast<int>(&Rva0008FAF5Create);
}

// ?Rva000A0D58Get@@YAHXZ @ 0x000A0D58: verified existing getter.
int Rva000A0D58Get(void)
{
	return reinterpret_cast<int>(&Rva0008FB2FCreate);
}

// ?Rva000A135EGet@@YAHXZ @ 0x000A135E: verified existing getter.
int Rva000A135EGet(void)
{
	return reinterpret_cast<int>(&Rva0008FB69Create);
}

// ?Rva000A1364Get@@YAHXZ @ 0x000A1364: verified existing getter.
int Rva000A1364Get(void)
{
	return reinterpret_cast<int>(&Rva0008FBA3Create);
}

// ?Rva000A165EGet@@YAHXZ @ 0x000A165E: verified existing getter.
int Rva000A165EGet(void)
{
	return reinterpret_cast<int>(&Rva0008FBDDCreate);
}

// ?Rva000A1664Get@@YAHXZ @ 0x000A1664: verified existing getter.
int Rva000A1664Get(void)
{
	return reinterpret_cast<int>(&Rva0008FC17Create);
}

// ?Rva000A2197Get@@YAHXZ @ 0x000A2197: verified existing getter.
int Rva000A2197Get(void)
{
	return reinterpret_cast<int>(&Rva0008FA81Create);
}

// ?Rva000A219DGet@@YAHXZ @ 0x000A219D: verified existing getter.
int Rva000A219DGet(void)
{
	return reinterpret_cast<int>(&Rva0008FABBCreate);
}

// ?Rva000A2727Get@@YAHXZ @ 0x000A2727: verified existing getter.
int Rva000A2727Get(void)
{
	return reinterpret_cast<int>(&Rva0008F999Create);
}

// ?Rva000A272DGet@@YAHXZ @ 0x000A272D: verified existing getter.
int Rva000A272DGet(void)
{
	return reinterpret_cast<int>(&Rva0008F9D3Create);
}

// ?Rva000A2733Get@@YAHXZ @ 0x000A2733: verified existing getter.
int Rva000A2733Get(void)
{
	return reinterpret_cast<int>(&Rva0008FA0DCreate);
}

// ?Rva000A2739Get@@YAHXZ @ 0x000A2739: verified existing getter.
int Rva000A2739Get(void)
{
	return reinterpret_cast<int>(&Rva0008FA47Create);
}

// ?Rva000A3367Get@@YAHXZ @ 0x000A3367: verified existing getter.
int Rva000A3367Get(void)
{
	return reinterpret_cast<int>(&Rva0008F8B1Create);
}

// ?Rva000A336DGet@@YAHXZ @ 0x000A336D: verified existing getter.
int Rva000A336DGet(void)
{
	return reinterpret_cast<int>(&Rva0008F8EBCreate);
}

// ?Rva000A3E43Get@@YAHXZ @ 0x000A3E43: verified existing getter.
int Rva000A3E43Get(void)
{
	return reinterpret_cast<int>(&Rva0008F7C9Create);
}

// ?Rva000A3E49Get@@YAHXZ @ 0x000A3E49: verified existing getter.
int Rva000A3E49Get(void)
{
	return reinterpret_cast<int>(&Rva0008F803Create);
}

// ?Rva000A43BCGet@@YAHXZ @ 0x000A43BC: verified existing getter.
int Rva000A43BCGet(void)
{
	return reinterpret_cast<int>(&Rva0008F83DCreate);
}

// ?Rva000A43C2Get@@YAHXZ @ 0x000A43C2: verified existing getter.
int Rva000A43C2Get(void)
{
	return reinterpret_cast<int>(&Rva0008F877Create);
}

// ?Rva000A52A2Get@@YAHXZ @ 0x000A52A2: verified existing getter.
int Rva000A52A2Get(void)
{
	return reinterpret_cast<int>(&Rva0008F755Create);
}

// ?Rva000A52A8Get@@YAHXZ @ 0x000A52A8: verified existing getter.
int Rva000A52A8Get(void)
{
	return reinterpret_cast<int>(&Rva0008F78FCreate);
}

// ?Rva00285745Get@@YAHXZ @ 0x00285745: verified existing getter.
int Rva00285745Get(void)
{
	return (int)"FireLogicSystem::BurningCell";
}

// ?Rva0039B81DGet@@YAHXZ @ 0x0039B81D: verified existing getter.
int Rva0039B81DGet(void)
{
	return (int)"ScoreKeeper::PerFrameStats";
}

// ?Rva004B29B8Get@@YAHXZ @ 0x004B29B8: verified existing getter.
int Rva004B29B8Get(void)
{
	return (int)"ReplaceObjectUpdate";
}

// ?Rva004C07ABGet@@YAHXZ @ 0x004C07AB: verified existing getter.
int Rva004C07ABGet(void)
{
	return (int)"HighlanderBody";
}

// ?Rva0033F3E9Get@@YAHXZ @ 0x0033F3E9: verified existing getter.
int Rva0033F3E9Get(void)
{
	return (int)"AIAttackAimAtTargetState";
}

// ?Rva0033F414Get@@YAHXZ @ 0x0033F414: verified existing getter.
int Rva0033F414Get(void)
{
	return (int)"AIAttackPositionAimAtTargetState";
}

// ?Rva0033F437Get@@YAHXZ @ 0x0033F437: verified existing getter.
int Rva0033F437Get(void)
{
	return (int)"AIWaitState";
}

// ?Rva0033F45AGet@@YAHXZ @ 0x0033F45A: verified existing getter.
int Rva0033F45AGet(void)
{
	return (int)"AIWaitUntilFinishedFiringState";
}

// ?Rva0033F47DGet@@YAHXZ @ 0x0033F47D: verified existing getter.
int Rva0033F47DGet(void)
{
	return (int)"AIWaitUntilMembersFinishedBeforeExitState";
}
