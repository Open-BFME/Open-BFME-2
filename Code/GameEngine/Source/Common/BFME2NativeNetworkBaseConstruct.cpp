// cl: /MD
//
// BFME2NativeNetwork::baseConstruct, retail 0x001B4E63, 17 bytes.
// Dedicated TU so NetworkInterfaceConstructor.cpp stays untouched.

extern "C" const void *const vtbl_00BD77A0[];  // folded, 2 classes; via ??_7GameEngineDeletingBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD77A0=??_7GameEngineDeletingBase@@6B@")

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();

private:
	virtual void unused();
	char _flag;
	int _value;
};

BFME2NativeNetwork *BFME2NativeNetwork::baseConstruct()
{
	*(void **)this = (void *)((unsigned int)vtbl_00BD77A0);
	_ReadWriteBarrier();
	_value = 0;
	_flag = 0;
	return this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?baseConstruct@BFME2NativeNetwork@@QAEXXZ=?baseConstruct@BFME2NativeNetwork@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:??0GenBase009A1A30@@QAE@XZ=?baseConstruct@BFME2NativeNetwork@@QAEPAV1@XZ")
