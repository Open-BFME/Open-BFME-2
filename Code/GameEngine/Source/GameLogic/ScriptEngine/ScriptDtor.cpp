// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1Script@@MAE@XZ, retail 0x003B35B1 (177 bytes): Script::~Script.
//
// Target facts (retail bytes + vtable 0x00C1F424 + unwind evidence):
// - The body re-stores vtable 0x00C1F424, so this is Script's own destructor
//   (protected virtual: MAE), called by the slot-0 scalar deleting
//   destructor 0x003B41F8. It ends by restoring the Snapshot base vtable
//   0x00BBB554 (Snapshot's inline destructor).
// - Members released: the owned pointer at +0x30, the two-element owned
//   array at +0x34, and AsciiString members at +0x04/+0x08/+0x0C, at +0x0C
//   of the 16-byte subrecord at +0x10, and at +0x44. Member names and the
//   subrecord shape follow the TU-local Script view in
//   ScriptWriteDataChunk.cpp (m_text0/1/2, Rva003B3536 m_subrecord,
//   m_condition, m_actions[2], m_runtimeName44); the untouched middle
//   regions stay padding.
// - Each owned pointer is released through its slot-0 virtual with flag 0
//   and the returned block goes to the global operator delete, including
//   for null (xor + push + call): the global-scope ::delete through a
//   virtual destructor (the lowering ScriptConditionActionDtors.cpp proves
//   in BFME 2). The Zero Hour donor (Scripts.cpp) calls deleteInstance() at
//   the same sites.
// - Body shape from the WorldBuilder debug twin 0x00AA79E0: ::delete of
//   +0x30 (::delete's two operand temporaries), then
//   `for (i = 0; i < 2; i++) ::delete m_actions[i]` with i the first local
//   ([ebp-0x10]), then the member strings in reverse order.
// - AsciiString's destructor is the compiler-generated one
//   (BFME_ASCII_IMPLICIT_DTOR, see ascii_string.h): the WB twin's per-member
//   this-temporaries show the extra inline level, and only that structure
//   puts retail's trip count in [ebp-0x10] (166 bytes with an EBX counter
//   otherwise). The unwind map (FuncInfo 0x00D2D678: Snapshot 0x0049B47C,
//   AsciiString 0x0048BA39, subrecord 0x0004F82B) is unchanged by it.
// - Script is not novtable: retail stores 0x00C1F424 on entry.
// Carried from the donor: class, member and owned-type names.

#define BFME_ASCII_IMPLICIT_DTOR
#include "ascii_string.h"
class Xfer;
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

// Owned types per the ScriptWriteDataChunk.cpp view; only the virtual
// destructor (vtable slot 0) is used here.
class OrCondition
{
public:
	virtual ~OrCondition();
};

#include "../../../Include/GameLogic/ScriptAction.h"

#include "../../../Include/GameLogic/ScriptClass.h"


Script::~Script()
{
	int i;
	::delete m_condition;
	for (i = 0; i < 2; i++)
		::delete m_actions[i];
}

// ?GetSnapshotName@Script@@MBEPBDXZ: slot 2 of vtable 0x00C1F424.
// The ledger rowed this body at 0x003B3662 under the placeholder name
// ?name@Rva003B3662Named@@QBEPBDXZ (SubsystemNameGetters4.cpp); the rename
// moves the definition here so the Script link can resolve it by its real
// name. Six bytes: mov eax,offset "Script" / ret.
const char *Script::GetSnapshotName() const
{
	return "Script";
}
