// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002B2E77Append@@YGXH@Z @0x002B2E77 23B
// __stdcall void(int) wrapper: global factory at 0x00A00950 slot 0x48 creates
// message 0x6B9, then tail-appends the incoming int argument through the rowed
// 0x0030F936. Callers 0x433D6B and 0x436014 push the value; the callee-clean
// ABI is what lets MSVC tail-jmp with the argument still in place. The old
// address-derived YAXXZ guess was void(void) and could only emit call+ret.
class GameMessage { public: void appendIntegerArgument(int v); };
class GlobalHolder {
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17();
	virtual GameMessage* newMessage(int type);
};
extern class MessageStream *TheMessageStream;
void __stdcall Rva002B2E77Append(int x)
{
	GameMessage *msg = (*(GlobalHolder **)&TheMessageStream)->newMessage(0x6B9);
	msg->appendIntegerArgument(x);
}
