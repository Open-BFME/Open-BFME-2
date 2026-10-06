// cl: /DNDEBUG /MD
// PortNegotiationSchema::getActionID (WorldBuilder name, PortNegotiationSchema.cpp line 421: the +0x118 action table lookup).
// was ?rva005DBCA6@Rva005DBCA6@@QAEHGG@Z 0x005DBCA6 43B
// Bounds-checked 2D dword lookup at +0x118 (8x8).
// Evidence: callers 0x5A6FD4 0x5A80B4 0x5A81EA 0x5A820E; same shape as Rva005DB9BC 2D dword.
class PortNegotiationSchema
{
	char m_pad[0x118];
	int m_arr[64];
public:
	int getActionID(unsigned short x, unsigned short y);
};

int PortNegotiationSchema::getActionID(unsigned short x, unsigned short y)
{
	if (x < 8)
	{
		if (y < 8)
			return m_arr[y + x * 8];
	}
	return 0;
}
