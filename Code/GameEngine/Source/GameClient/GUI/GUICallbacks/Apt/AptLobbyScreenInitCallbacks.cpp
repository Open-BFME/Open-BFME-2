// cl: /O1 /DNDEBUG /MD
//
// Small OnInitialized / Continue Apt callbacks of four BFME2 screens, each
// bound by the name it carries ("AptMessenger::OnInitialized" ...) as a
// member pointer by its screen's registration; that binding is the only
// reference. Each class is a one-method view named for its string's prefix.

// TheShell (VA 0x00E01E48, the ledger's g_Va00A01E48).
struct GlobalA01E48
{
	unsigned char m_pad[0x54];
	bool m_54; // +0x54
	unsigned char m_pad55[0x5D - 0x55];
	bool m_5d; // +0x5D
};

extern struct GlobalA01E48 *g_Va00A01E48;

// Rva0051280EEnable.cpp's 0x0051280E.
void Rva0051280EEnable();

class AptMessenger
{
public:
	void OnInitialized(const char *unused);

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	unsigned char m_pad280[0x29C - 0x280];
	bool m_initialized; // +0x29C
};

class AptInGameChat
{
public:
	void OnInitialized(const char *unused);

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
};

class AptDisconnectScreen
{
public:
	void OnInitialized(const char *unused);

private:
	unsigned char m_pad000[0x284];
	bool m_initialized; // +0x284
};

class AptCampaignReview
{
public:
	void Continue(const char *unused);
};

// Retail 0x00511540, 27 bytes: "AptMessenger::OnInitialized".
void AptMessenger::OnInitialized(const char *unused)
{
	m_initialized = true;
	if (m_state == 0)
		m_state = 1;
}

// Retail 0x004E81FF, 20 bytes: "AptInGameChat::OnInitialized".
void AptInGameChat::OnInitialized(const char *unused)
{
	if (m_state == 0)
		m_state = 1;
}

// Retail 0x00512CDF, 10 bytes: "AptDisconnectScreen::OnInitialized".
void AptDisconnectScreen::OnInitialized(const char *unused)
{
	m_initialized = true;
}

// Retail 0x00512823, 21 bytes: "AptCampaignReview::Continue".
void AptCampaignReview::Continue(const char *unused)
{
	if (g_Va00A01E48)
		g_Va00A01E48->m_5d = true;
	Rva0051280EEnable();
}
