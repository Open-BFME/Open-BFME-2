// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?getTooltipName@MultiplayerColorDefinition@@QBE?AVAsciiString@@XZ @0x002E4336
// Shard TU: the ctor/op= TU calls this out-of-line; defining it there
// inlines and breaks op=, so it lives here.

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	char *m_data;
};

class MultiplayerColorDefinition
{
public:
	AsciiString getTooltipName() const;

private:
	AsciiString m_tooltipName;
};

// ?getTooltipName@MultiplayerColorDefinition@@QBE?AVAsciiString@@XZ
AsciiString MultiplayerColorDefinition::getTooltipName() const
{
	return m_tooltipName;
}
