// cl: /O1 /MD
// ?rva004F0656@Rva004F0656@@QAEEXZ @0x004F0656 43B TeamInQueue-area list predicate.
// Evidence: head at +0x14 matches TeamInQueue::m_workOrders; node next +0x0C matches WorkOrder; contiguous with 0x004F0681 (next); caller 0x004F1653+0xA1; prev/next share /O1.
struct Rva004F0656Node
{
	char m_pad00[0x0C];
	Rva004F0656Node *m_next;
	int m_10;
	int m_14;
	char m_pad18[0x11];
	unsigned char m_29;
};

class Rva004F0656
{
public:
	virtual ~Rva004F0656();
	unsigned char rva004F0656();

private:
	char m_pad04[0x10];
	Rva004F0656Node *m_14;
};

unsigned char Rva004F0656::rva004F0656()
{
	int sum = 0;
	Rva004F0656Node *cur = m_14;
	if (cur == 0)
		goto fail;
	do
	{
		if (cur->m_29 == 0)
		{
			if (cur->m_14 > cur->m_10)
				goto fail;
		}
		sum += cur->m_10;
		cur = cur->m_next;
	} while (cur != 0);
	if (sum > 0)
		return 1;
fail:
	return 0;
}
