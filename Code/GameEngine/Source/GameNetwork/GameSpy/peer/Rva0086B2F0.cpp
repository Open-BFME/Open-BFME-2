// cl: /DNDEBUG /MD /O2
#include <string.h>

struct piPlayer
{
	char nick[0x40];
	int inRoom[3];
	int local;
	unsigned int IP;
	int profileID;
	int gotIPAndProfileID;
	int flags[3];
};

static void Rva0086B2F0(char *text, piPlayer *player)
{
	int length = (int)strlen(text);
	if (strncmp(text + length - 2, "X\\", 2) == 0)
		return;
	if (!player->inRoom[2])
		return;
	char *flags = strstr(text, "\\$flags$\\");
	if (!flags)
		return;
	flags += 9;
	char value = *flags;
	if (!value)
		goto clearFlag;
	do
	{
		if (value == '\\')
			goto clearFlag;
		++flags;
		if (value == 'r')
			goto setFlag;
		value = *flags;
	} while (value);
clearFlag:
	player->flags[2] &= ~2;
	return;
setFlag:
	player->flags[2] |= 2;
}

// absent-from-retail: This caller makes MSVC pass both pointers in registers.
void Rva0086B2F0PrivateCallAnchor(char *text, piPlayer *player, int enabled)
{
	if (enabled)
		Rva0086B2F0(text, player);
}
