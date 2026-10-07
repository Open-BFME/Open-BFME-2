// ?rva002401DD@GameLogic@@QAEXPAVBfmeThingEC@@IH@Z
// partial score=0.85 date=2026-10-07
// Append to Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp (its GameLogic/Player/RecorderClass/
// GameTextInterface/FileSystem/BfmeThingEC views already carry every member this body uses).
// ?rva002401DD@GameLogic@@QAEXPAVBfmeThingEC@@IH@Z @0x002401DD 1424B (Ghidra
// FUN_006401dd, ret 0xC at 0x0024076A). Called twice by the CRC vote above.
// Donor: BFME 1 bfme_reportDesync (b1 0x00388C10, banked 0.82 in Open-BFME-1
// attempts): flag the mismatch, show the desync dialog once, then write the
// DESYNC-<frame>-<map>-<player>.txt report (game-over lines, the replay
// frame dump and the CRC stream) and, when the binary flag is set, the
// stream itself as BIN_DESYNC-*.bin. Target deltas: dialog code 4 through
// the cdecl forwarder 0x00437E84, the dialog-shown flag and state at
// +0x1BC/+0x1B8, the local player's name at Player+0x4C, the open modes 0x2A
// and 0x4A, and the forced-desync text's two arguments (frame, this+0x40).
class File
{
public:
	virtual void f00(void);
	virtual bool open(const char *filename, int access);
	virtual void close(void);                                            // +0x08
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);                    // +0x10
};

class ScriptActions
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e();
	virtual void closeWindows(bool suppressNewWindows);                  // +0x3C
};
extern ScriptActions *TheScriptActions;

// 0x002036B4, a 12-byte member of the object in TheScriptEngine's slot.
class Rva002036B4GlobalCopier
{
public:
	void apply(void);
};

void Rva00437E84(int type, const UnicodeString &title, const UnicodeString &text);
File *createMemoryReadFile(char *buffer, int size);
void rva0060DFB5(File *input, File *output);

extern "C" __declspec(dllimport) int __stdcall GetComputerNameA(char *buffer, unsigned long *size);

// 0x00A03204: tag the report as an intentionally faked desync.
extern bool g_fakeDesync;
// 0x00A02D89: also write the raw CRC stream next to the text report.
extern bool TheBinaryDeepCRC;

void GameLogic::rva002401DD(BfmeThingEC *stream, unsigned int frame, int player)
{
	m_71 = true;
	if (ignoreCRCMismatches && g_value12A6F38 != m_40)
		return;
	if (!m_1bc)
	{
		m_1bc = true;
		TheRecorder->logCRCMismatch();
		TheScriptActions->closeWindows(true);
		if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK || g_value12A6F38 == m_40)
			Rva00437E84(4, TheGameText->fetch("GUI:DesyncTitle"), TheGameText->fetch("GUI:DesyncText"));
		m_1b8 = 0;
		if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK || g_value12A6F38 == m_40)
			((Rva002036B4GlobalCopier *)TheScriptEngine)->apply();
	}
	if (!stream)
		return;

	const char *map;
	const char *slash = TheWritableGlobalData->m_mapName.reverseFind('\\');
	if (slash)
		map = slash + 1;
	else
		map = "";

	AsciiString playerName(ThePlayerList->getLocalPlayer()->m_4c);
	if (playerName.isEmpty())
	{
		char computerName[256] = { 0 };
		unsigned long size = 256;
		GetComputerNameA(computerName, &size);
		playerName = computerName;
	}

	AsciiString frameName;
	if (stream->m_04.str())
		frameName.format("Frame%s", stream->m_04.str());
	else
		frameName.format("Frame%d", frame);

	AsciiString filename;
	if (frame > 0)
		filename.format("DESYNC-%s-%s-%s.txt", frameName.str(), map, playerName.str());
	else
		filename.format("DESYNC-%s-%s.txt", map, playerName.str());

	File *output = TheFileSystem->openFile(filename.str(), 0x2a, 0);
	if (output)
	{
		int size;
		char *buffer = (char *)stream->bfmeTakeEC(&size);
		File *input = createMemoryReadFile(buffer, size);
		if (input)
		{
			AsciiString text;
			if (frame > 0)
			{
				if (g_fakeDesync)
					text.format("*** Frame #%d -- THIS IS A FAKE DESYNC THAT WAS TRIGGERED INTENTIONALLY BY THIS PLAYER! IGNORE!\n\n", frame);
				else if (g_value12A6F38 == m_40)
					text.format("*** Frame #%d -- THIS IS A FORCED DESYNC TRIGGERED ON FRAME %d USING COMMANDLINE -forceDesyncOnFrame %d! IGNORE!!!!\n\n", frame, m_40);
				else
					text.format("Frame #%d\n\n", frame);
				output->write(text.str(), text.getLength());
			}
			text = m_54;
			output->write(text.str(), text.getLength());
			for (unsigned int i = 0; i < m_58.size(); ++i)
			{
				text = rva0023FB58(i);
				output->write(text.str(), text.getLength());
			}
			text = m_64;
			output->write(text.str(), text.getLength());
			text = m_68;
			output->write(text.str(), text.getLength());
			text.format("\n");
			output->write(text.str(), text.getLength());
			text.format("\n--------------------------------------------------------\nREPLAY FILE\n---------------------------------------------------------\n");
			output->write(text.str(), text.getLength());
			TheRecorder->rva0037BE15(output, frame);
			text.format("---------------------------------------------------------\n\n");
			output->write(text.str(), text.getLength());
			rva0060DFB5(input, output);
			input->close();
			output->close();
			if (TheBinaryDeepCRC)
			{
				if (frame > 0)
					filename.format("BIN_DESYNC-%s-%s-%s.bin", frameName.str(), map, playerName.str());
				else
					filename.format("BIN_DESYNC-%s-%s.bin", map, playerName.str());
				output = TheFileSystem->openFile(filename.str(), 0x4a, 0);
				if (!output)
					return;
				output->write(buffer, size);
				output->close();
			}
			free(buffer);
		}
	}
}
