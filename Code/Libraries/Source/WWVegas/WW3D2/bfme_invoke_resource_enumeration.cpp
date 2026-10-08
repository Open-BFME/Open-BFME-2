// cl: /DNDEBUG /MD
//
// bfmeInvokeResourceEnumeration, retail 0x0061EFB0, 26 bytes.
// Null-guarded forward into Gen_009EBA60Target::bfmeInvoke at 0x00621080:
// when the global registry at VA 0x00E09C0C is live, invoke the named entry
// with the source key set. Sibling of bfmeBeginResourceEnumeration at
// 0x0061F110, which guards the same registry for Begin.

class Gen_009EBA60Target
{
public:
	void bfmeInvoke(void *name, void *source);
};

extern class Q1Receiver0134FAAC *TheQ1Receiver;

void bfmeInvokeResourceEnumeration(void *name, void *source)
{
	if ((*(Gen_009EBA60Target **)&TheQ1Receiver) != 0)
		(*(Gen_009EBA60Target **)&TheQ1Receiver)->bfmeInvoke(name, source);
}
