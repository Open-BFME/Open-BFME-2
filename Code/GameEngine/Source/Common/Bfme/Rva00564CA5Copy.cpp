// cl: /DNDEBUG /MD
// ?Rva00564CA5Copy@@YAPAVDynamicAudioEventRTS@@PAV1@00@Z, retail 0x00564CA5, 47 bytes.
// Range-copy loop over 8-byte DynamicAudioEventRTS elements: count is
// (last-first), assigns each slot through the rowed operator= 0x00200BC0,
// advances src/dst, returns final dst. Caller at 0x00565614; unblocks 0x00565601.

class DynamicAudioEventRTS
{
public:
	DynamicAudioEventRTS &operator=(const DynamicAudioEventRTS &other);
private:
	char m_pad[8];
};

DynamicAudioEventRTS *Rva00564CA5Copy(DynamicAudioEventRTS *first, DynamicAudioEventRTS *last, DynamicAudioEventRTS *dest)
{
	if (last - first <= 0)
		return dest;
	int n = last - first;
	do
	{
		*dest = *first;
		++first;
		++dest;
	} while (--n != 0);
	return dest;
}
