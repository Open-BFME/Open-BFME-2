// cl: /O1 /DNDEBUG /MD
// ?rva000EA1F3@Rva000E6FC8@@QAEXXZ @0x000EA1F3 39B.
// Same GlobalData gate as 0x000E6FC8. A set +0xD45 passes 0x14.
// Otherwise byte +0x62 selects 7 or 4. Both arms call 0x000E6D94.

extern void *g_00DFE758;

class Rva000E6FC8
{
public:
	void rva000E6D94(int value);
	void rva000EA1F3();
};

void Rva000E6FC8::rva000EA1F3()
{
	unsigned char *globalData = (unsigned char *)g_00DFE758;
	int value;
	if (globalData[0xD45] != 0)
		value = 0x14;
	else
		value = globalData[0x62] != 0 ? 7 : 4;
	rva000E6D94(value);
}
