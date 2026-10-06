// cl: /DNDEBUG /MD /EHsc
//
// ??0ObjectTypesTemp@@QAE@XZ @0x003BA7FF 64B: ObjectTypesTemp default ctor.
// Evidence: push 0x14 plus rowed operator new 0x0002FDA0 plus rowed
// ObjectTypes ctor 0x003769F9; init-list m_types=0 via and [esi],0 then
// m_types = new ObjectTypes; EH prolog with handler table; 14 callers in
// ScriptConditions evaluate bodies reuse the stack slot and delete via virtual
// dtor (e.g. 0x003E8E23 lea ecx,[ebp+8] then tail delete). Donors: ZH
// ScriptConditions.cpp ObjectTypesTemp plus BFME1
// game/GameEngine/Source/GameLogic/ScriptEngine/ObjectTypesTemp_ctor_Thunk.cpp
// (same // cl: /DNDEBUG /MD /EHsc, same m_types(0) plus new ObjectTypes).

// Local minimal replica of ObjectTypes. Only its size (20 bytes, matching the
// retail push 0x14) and the mangled default ctor matter here; ObjectTypes
// itself is fully defined and matched in ObjectTypesCtor.cpp.
class ObjectTypes
{
public:
	ObjectTypes();
private:
	int m_pad[5];
};

class ObjectTypesTemp
{
public:
	ObjectTypes *m_types;

	ObjectTypesTemp();
};

ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}
