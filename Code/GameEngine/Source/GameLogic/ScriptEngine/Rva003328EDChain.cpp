// cl: /O1 /DNDEBUG /MD
// Retail RE: ?rva002628C3@Rva002628C3@@QAEXPAXHH@Z @0x002628C3 (29B).
//
// BFME2 ScriptEngine event/spy adapter from ObjectSpy 0x335B88.
// Target facts from retail bytes (writer-2 this round):
// - Boundary 0x2628C3..0x2628E0 29B; prev 0x2628B6/13 ends at start;
//   next 0x2628E0 starts at end; single ret 0xC at 0x2628DD (C20C00).
// - ABI thiscall void (void* object; int eventKey; int spyKey); ret 12.
//   push [esp+0xC] (spyKey) + mov eax [esp+8] (object) +
//   push [esp+0xC] (eventKey) + add ecx 0x224 (module+0x224) +
//   push [eax+0x74] ([object+0x74]) + E8 at 0x2628D8 targets 0x3328ED
//   (pinned this seat; Ghidra FUN_007328ed 136B) + ret 12.
// - Caller ObjectSpy 0x335B88 at 0x335C55 E869CCF2FF targets 0x2628C3
//   with ecx [edi+0x258] module null-guarded; event/spy keys are NameKeys
//   from TheNameKeyGenerator nameToKey 0x148E1A via ObjectSpy.
// - Layout: Object+0x74 payload (void*) + module+0x224 dispatcher;
//   Object+0x258 module proven by ObjectSpy siblings; +0x74/+0x224 read
//   directly off retail immediates; no further layout claimed.
// Donor-carried only: none (no BFME1/ZH same-name donor; tiny forwarder
// shape modeled on byte-proven Vslot neighbors, not copied).
// No shared-header edits; TU-scoped views only.

class Rva003328ED
{
public:
	void rva003328ED(void *arg1, int arg2, int arg3);
};

class Rva002628C3
{
public:
	void rva002628C3(void *object, int eventKey, int spyKey);
};

struct Rva002628C3Object74
{
	char m_pad[0x74];
	void *m_74;
};

void Rva002628C3::rva002628C3(void *object, int eventKey, int spyKey)
{
	Rva003328ED *disp = (Rva003328ED *)((char *)this + 0x224);
	disp->rva003328ED(((Rva002628C3Object74 *)object)->m_74, eventKey, spyKey);
}
