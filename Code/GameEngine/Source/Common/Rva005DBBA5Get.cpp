// cl: /DNDEBUG /MD
// PortNegotiationSchema::getTimeToSendPing (WorldBuilder name, line 381: the +0x718 per-port table).
// was ?rva005DBBA5@Rva005DBBA5@@QAEHG@Z 0x005DBBA5 28B
// Bounds-checked dword lookup at +0x718 or -1.
// Evidence: caller 0x5A6F5A; unblocks 0x5A6EF2.
class PortNegotiationSchema
{
	char m_pad[0x718];
	int m_arr[8];
public:
	int getTimeToSendPing(unsigned short idx);
};

int PortNegotiationSchema::getTimeToSendPing(unsigned short idx)
{
	if (idx >= 8)
		return -1;
	return m_arr[idx];
}
