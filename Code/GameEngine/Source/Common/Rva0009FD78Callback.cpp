// cl: /O1
// Donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BfmeConv934.cpp. Whole unit: one placement.
// Target entry: slot 5 at RVA 0x007C8C68 in the table installed by
// 0x0009FD60 (Ghidra 24B). Twenty-four .rdata pointers name 0x0009FD78.
// Its 21 bytes end in two returns, immediately before the next table entry
// 0x0009FD8D; it is absent from the current Ghidra function list.
// Target proves callback field +0x1F0, one pushed this argument, caller
// cleanup, and a full int result indicating whether the callback was called.
// Owner/name are unknown; callback's void result is a source inference.
class Rva0009FD78
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual int dispatch();
private:
	char reserved[0x1EC];
	void (__cdecl *callback)(Rva0009FD78 *);
};

int Rva0009FD78::dispatch()
{
	void (__cdecl *fn)(Rva0009FD78 *) = callback;
	if (fn) {
		fn(this);
		return 1;
	}
	return 0;
}
