// cl: /DNDEBUG /MD /EHa /Oy-
//
// ??0DebugCmdInterfaceDebug@@QAE@XZ, retail 0x00038670 (70 bytes).
// Ported from Open-BFME-1 WWDebug/DebugCmdInterfaceDebugConstructorThunk.cpp
// verbatim: empty DebugCmdInterfaceDebug ctor. Same two-vtable EH shape as
// DebugIOOds / DebugIONet: inlines the DebugCmdInterface vtable store, then
// stores the derived vtable, with the EH state around the derived store
// because the base has a virtual destructor. Dedicated TU so the other
// WWDebug TUs keep their matched bodies.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_cmd.h
// Retail's kept ??_GDebugCmdInterface is frameless; this TU builds /Oy-
// (framed) for its 70B ctor row, so emit the COMDAT frameless here. The
// row below keeps TU flags; only the inline copy follows the pragma.
#pragma optimize("y", on)
class Debug;
class DebugCmdInterface
{
protected:
	virtual ~DebugCmdInterface() {}

public:
	DebugCmdInterface() {}

	enum CommandMode { Normal, Structured, MAX };

	virtual bool Execute(Debug &dbg, const char *cmd, CommandMode cmdmode,
		unsigned argn, const char *const *argv) = 0;
	virtual void Delete(void) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal.h
class DebugCmdInterfaceDebug : public DebugCmdInterface
{
public:
	explicit DebugCmdInterfaceDebug(void);
	virtual bool Execute(Debug &dbg, const char *cmd, CommandMode cmdmode,
		unsigned argn, const char *const *argv);
	virtual void Delete(void);
};
#pragma optimize("", on)

// ??0DebugCmdInterfaceDebug@@QAE@XZ
inline DebugCmdInterfaceDebug::DebugCmdInterfaceDebug(void)
{
}

// Anchor: emits the implicit ??1 scalar-dtor COMDAT plus the ??_G
// scalar-deleting-destructor COMDAT. The dtor MUST stay implicit (no
// declaration): an explicitly-defined empty dtor emits the derived vtable
// reinstall at entry (61B), while retail's implicit dtor keeps only the
// EH state plus the base reinstall (55B). Probe-proven in build/.
void deleteCmdInterfaceDebug(DebugCmdInterfaceDebug *p)
{
	delete p;
}

// ?Delete@DebugCmdInterfaceDebug@@UAEXXZ present-unmatched
void DebugCmdInterfaceDebug::Delete(void)
{
	delete this;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeDebugCmdInterfaceDebugInlineAnchor@@YAXPAVDebugCmdInterfaceDebug@@@Z absent-from-retail
void _bfmeDebugCmdInterfaceDebugInlineAnchor(DebugCmdInterfaceDebug *p)
{
    p->DebugCmdInterfaceDebug::DebugCmdInterfaceDebug();
}
#pragma inline_depth()
