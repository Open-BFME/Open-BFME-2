// cl: /MD
//
// ?OnJoinGameBttn@AptLanLobby@@QAEXPBD@Z, retail 0x00444362, 20 bytes.
// The native constructor 445EE3 binds this address to AptLanLobby::OnJoinGameBttn.
// Conditionally sets state at +0x6A4 from 1 to 7; ignores the text argument.
// Evidence: lea ecx+0x6A4 plus cmp 1 plus mov 7 plus ret 4,
// caller 0x004448AF pushes 0x007BAC1C.

class AptLanLobby
{
public:
	void OnJoinGameBttn(const char *unused);

private:
	unsigned char m_pad00[0x6A4];
	int m_field;
};

void AptLanLobby::OnJoinGameBttn(const char *unused)
{
	(void)unused;
	int *p = &m_field;
	if (*p == 1)
		*p = 7;
}
