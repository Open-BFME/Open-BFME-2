// cl: /EHsc
// ?rva000B4A9F@Rva000B4A9F@@QAEPBDXZ @0x000B4A9F 22B.
// Empty-aware char pointer at +0x4C via finish at +0x50.
// Evidence: unlock plus 10 callers plus empty literal at 0x009E0878; prev Rva000B49F9 plus next Rva000B4AB5 same region flags.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva000B4A9F
{
public:
	const char *rva000B4A9F();

private:
	char m_pad00[0x4C];
	const char *m_start4C;
	const char *m_finish50;
};

// ?rva000B4A9F@Rva000B4A9F@@QAEPBDXZ
const char *Rva000B4A9F::rva000B4A9F()
{
	int d = m_finish50 - m_start4C;
	_ReadWriteBarrier();
	if ((d & ~3) == 0)
		return "";
	return m_start4C;
}
