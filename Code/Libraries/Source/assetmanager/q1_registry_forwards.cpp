// cl: /O2 /DNDEBUG /MD
//
// Five null-guarded registry forwarders, each 21 bytes: when the global
// Q1 receiver registry at VA 0x00E09C0C is live, forward the argument to
// the rowed Q1Receiver0134FAAC worker. Same guard idiom as
// bfmeBeginResourceEnumeration at 0x0061F110 and
// bfmeInvokeResourceEnumeration at 0x0061EFB0, which guard the same global.

class Q1Receiver0134FAAC
{
public:
	void m009EC970(int which);
	void m009EC9A0(int which);
	void m009F0D40(int value);
	void m009F19E0(int source);
	void m009F0BD0(int value);
};

Q1Receiver0134FAAC *TheQ1Receiver;

void bfmeStepReceiverRecord(int source)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009F19E0(source);
}

void bfmeMergeReceiverKeys(int value)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009F0BD0(value);
}

void bfmeMarkReceiverPayloads(int value)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009F0D40(value);
}

void bfmeSetReceiverFlag(int which)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009EC970(which);
}

void bfmeClearReceiverFlag(int which)
{
	if (TheQ1Receiver != 0)
		TheQ1Receiver->m009EC9A0(which);
}
