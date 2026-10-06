// cl: /MD
// ?rva00132FE9@Rva0090E250@@QAEX_N@Z at 0x00132FE9 (18B).
// Bool-to-int forwarder to ?set@Rva0090E250@@QAEXH@Z at 0x00132C9D with this passthrough.
// Evidence: retail xor eax eax; cmp byte [esp+4] al; setne al; push eax; call set; ret 4;
// 5 callers incl 0x00047178 0x0004F628; callee row in Rva0090E250Set.cpp.
class Rva0090E250
{
public:
	void set(int value);
	void rva00132FE9(bool flag);
};

void Rva0090E250::rva00132FE9(bool flag)
{
	set(flag != false);
}
