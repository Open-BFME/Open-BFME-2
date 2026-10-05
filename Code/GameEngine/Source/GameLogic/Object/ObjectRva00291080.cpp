// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva00291080@Object@@QAEX_N@Z, retail 0x00291080 55B.
// TARGET FACTS (retail decode in-lane via build.read_target_bytes + capstone):
// - thiscall bool setter, ret 4: 56 8B F1 80 7C 24 08 00 ... C2 04 00.
// - single call to rowed ?setStatus@Object@@QAEXW4ObjectStatusTypes@@_N@Z at
//   0x0023DB0E with (0x35, flag01): cmp-byte-[esp+8] + mov-ecx-esi +
//   je-push1-jmp-push0 (6A01/EB02/6A00) + 6A35 + single E8.
// - walks +0x274 chain (8B 86 74 02 00 00); each next gated by its +0x04
//   flag object byte +0x115 bit 0x20 (8B 48 04 F6 81 15 01 00 00 20);
//   two je to shared pop-esi-ret epilogue; induction mov-esi-eax + jmp to cmp.
// - caller ObjectSetChanting registration at 0x33860F (push 0x7357E0 +
//   literal 0xC0E5E8 'ObjectSetChanting') proves consumer; REL32 at 0x735845
//   decodes to VA 0x691080 (this provider, sole open callee).
// DONOR FACTS CARRIED ONLY (reference/open-bfme-1 at 6583b3c1):
// - LuaScriptBindingsLuaA.cpp ObjectSetChanting control shape (gettop/lookup/
//   type/findObject/flag/call) and ObjectRva001CF8F0.cpp containedBy loop
//   shape; donor provider uses ModelCondition 0x34 via apply/clear, NOT target
//   ObjectStatus 0x35. Nothing about 0x35/0x274/0x115/0x20 is donor-carried.
// INFERENCE (to verify by build): explicit if/else with two setStatus calls
// (true/false) lets /O1 merge to the single-call push1/push0 branch per the
// ObjectWeaponSetFlags.cpp setWeaponLock precedent; while(true) infinite loop
// with bottom induction preserves jmp-to-cmp without for-loop rotation.
// (ObjectStatusTypes)0x35 cast keeps genuine rowed mangling without inventing
// a status name.

enum ObjectStatusTypes
{
	OBJECT_STATUS_PLACEHOLDER = 0
};

class Object
{
public:
	void setStatus( ObjectStatusTypes status, bool flag );
	void rva00291080( bool flag );
private:
	unsigned char m_pad00[ 0x04 ];
	void *m_04;
	unsigned char m_pad08[ 0x274 - 0x08 ];
	Object *m_containedBy;
};

struct FlagObj
{
	unsigned char m_pad[ 0x115 ];
	unsigned char m_flag115;
};

void Object::rva00291080( bool flag )
{
	Object *obj = this;
	while( true )
	{
		if( flag )
			obj->setStatus( (ObjectStatusTypes)0x35, true );
		else
			obj->setStatus( (ObjectStatusTypes)0x35, false );
		Object *next = obj->m_containedBy;
		if( !next )
			return;
		FlagObj *f = (FlagObj *)next->m_04;
		if( ( f->m_flag115 & 0x20 ) == 0 )
			return;
		obj = next;
	}
}
