// cl: /O1 /DNDEBUG /MD
//
// BFME2's create-a-hero screen Apt callbacks, 0x00513A47 onward, bound by
// these names ("AptCreateAHero::PrepareToTakePicture" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The class is named for the strings' prefix. The rotate and
// zoom buttons pass "true" while held: only the first character is tested.

class AptCreateAHero
{
public:
	void PrepareToTakePicture(const char *unused);
	void OnTakePicture(const char *unused);
	void RotateLeft(const char *pressed);
	void RotateRight(const char *pressed);
	void ZoomIn(const char *pressed);
	void ZoomOut(const char *pressed);

private:
	unsigned char m_pad000[0x42F];
	bool m_takePicture; // +0x42F
	bool m_rotateLeft; // +0x430
	bool m_rotateRight; // +0x431
	bool m_zoomIn; // +0x432
	bool m_zoomOut; // +0x433
	int m_pictureFrames; // +0x434
};

// Retail 0x00513A47, 10 bytes: "AptCreateAHero::PrepareToTakePicture".
void AptCreateAHero::PrepareToTakePicture(const char *unused)
{
	m_pictureFrames = 0;
}

// Retail 0x00513A51, 19 bytes: "AptCreateAHero::OnTakePicture", once two
// frames have passed.
void AptCreateAHero::OnTakePicture(const char *unused)
{
	if (m_pictureFrames >= 2)
		m_takePicture = true;
}

// Retail 0x00513AA8, 19 bytes: "AptCreateAHero::RotateLeft".
void AptCreateAHero::RotateLeft(const char *pressed)
{
	m_rotateLeft = *pressed == 't';
}

// Retail 0x00513ABB, 19 bytes: "AptCreateAHero::RotateRight".
void AptCreateAHero::RotateRight(const char *pressed)
{
	m_rotateRight = *pressed == 't';
}

// Retail 0x00513ACE, 19 bytes: "AptCreateAHero::ZoomIn".
void AptCreateAHero::ZoomIn(const char *pressed)
{
	m_zoomIn = *pressed == 't';
}

// Retail 0x00513AE1, 19 bytes: "AptCreateAHero::ZoomOut".
void AptCreateAHero::ZoomOut(const char *pressed)
{
	m_zoomOut = *pressed == 't';
}
