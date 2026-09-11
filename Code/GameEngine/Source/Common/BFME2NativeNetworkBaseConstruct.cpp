// cl: /O1 /MD
//
// BFME2NativeNetwork::baseConstruct, retail 0x001B4E63, 17 bytes.
// Dedicated TU so NetworkInterfaceConstructor.cpp stays untouched.

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
	*(void **)this = (void *)0x00BD77A0;
	_ReadWriteBarrier();
	_value = 0;
	_flag = 0;
	return this;
}
