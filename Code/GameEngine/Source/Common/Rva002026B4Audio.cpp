// cl: /DNDEBUG /MD
//
// ?Rva002026B4Audio@@YAXXZ @0x002026B4 19B. Null-guarded TheAudio tail call
// to vtable slot 0x188 (slot 98). Evidence: mov ecx,[TheAudio 0x009FE6E8]
// test/je plus mov eax,[ecx] plus jmp [eax+0x188]; caller 0x00202790 takes
// int 0..1 at +0x1770 then calls this with no args; unblocks 0x00202790.
// TheAudio linkage uses the real AudioManager* mangling; the call goes
// through a TU-local view so no method name is invented for the real class:
// slot index alone is proven by the retail jmp displacement.
class AudioManager;
extern AudioManager *TheAudio;

class Rva002026B4AudioView
{
public:
	virtual void _pad0() = 0;
	virtual void _pad1() = 0;
	virtual void _pad2() = 0;
	virtual void _pad3() = 0;
	virtual void _pad4() = 0;
	virtual void _pad5() = 0;
	virtual void _pad6() = 0;
	virtual void _pad7() = 0;
	virtual void _pad8() = 0;
	virtual void _pad9() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void _pad27() = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	virtual void _pad52() = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual void _pad77() = 0;
	virtual void _pad78() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	virtual void _pad88() = 0;
	virtual void _pad89() = 0;
	virtual void _pad90() = 0;
	virtual void _pad91() = 0;
	virtual void _pad92() = 0;
	virtual void _pad93() = 0;
	virtual void _pad94() = 0;
	virtual void _pad95() = 0;
	virtual void _pad96() = 0;
	virtual void _pad97() = 0;
	virtual void _slot98() = 0;
};

void __cdecl Rva002026B4Audio()
{
	if (TheAudio != 0)
		reinterpret_cast<Rva002026B4AudioView*>(TheAudio)->_slot98();
}
