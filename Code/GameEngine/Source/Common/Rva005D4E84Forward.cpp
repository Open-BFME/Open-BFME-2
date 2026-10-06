// cl: /EHsc
// ?rva005D4E84@Rva005D4E84@@QAEXXZ @0x005D4E84 7B
// Tail forwarder via member at +0x0 into rowed 0x005D4E63.
// Evidence: chain callee 0x005D4E63 rowed; mov ecx,[ecx] then jmp;
// caller at 0x0057BBF8 in 0x0057BBBB 101B.
class Rva005D4E63
{
public:
	void rva005D4E63();
};
class Rva005D4E84
{
public:
	void rva005D4E84();
private:
	Rva005D4E63 *m_next00;
};
void Rva005D4E84::rva005D4E84()
{
	m_next00->rva005D4E63();
}
