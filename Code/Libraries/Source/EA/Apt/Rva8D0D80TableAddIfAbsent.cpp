// BFME1 donor: Code/Libraries/Source/EA/Apt/Rva8D0D80BuildObject.cpp
// BFME1 ledger identifies ?addIfAbsent@Rva8D0D80Table@@QAEXPAVRva8D0D80String@@PAVRva8D0D80Value@@@Z
// at 0x0089DBC0 (36 bytes). This TU keeps only that method; the donor file's
// 394-byte parent builder has no matching placement and is not copied here.
//
// BFME2 evidence: the refreshed BFME1 sweep found one exact masked placement
// at 0x0070B4C0 (36 bytes, fanout 1). Its two call targets are 0x0070B380
// and 0x0070B410; Ghidra records adjacent lookup and table-helper bodies at
// those addresses. The BFME1 callee names below are donor-derived; the target
// candidate itself has no separate Ghidra function record.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva8D0D80String;
class Rva8D0D80Value;

class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

class Rva8D0D80Table
{
public:
	void add(Rva8D0D80String *name, Rva8D0D80Value *value);
	void addIfAbsent(Rva8D0D80String *name, Rva8D0D80Value *value);
};

void Rva8D0D80Table::addIfAbsent(Rva8D0D80String *name, Rva8D0D80Value *value)
{
	if (!((BfmeTab1024 *)this)->bfmeFind1024((int)name))
		add(name, value);
}
