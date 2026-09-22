// cl: /DNDEBUG /MD /EHs-c-
//
// Free wrapper at retail 0x000385E0 (14 bytes): asks the Debug singleton
// (theDebug, 0x00DE0880) whether the game runs windowed, through the
// virtual at Debug vtable slot 0xAC (0x000397D0), as a tail call. The
// RaiseException hook at 0x0003E1C0 calls it before reporting a C++ throw.
// The name is descriptive; no symbol survives for it.

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
	virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
	virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
	virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39();
	virtual void pad40(); virtual void pad41(); virtual void pad42();
	virtual bool IsWindowed();
};

extern Debug *theDebug;

// ?DebugIsWindowed@@YA_NXZ
bool DebugIsWindowed()
{
	return theDebug->IsWindowed();
}
