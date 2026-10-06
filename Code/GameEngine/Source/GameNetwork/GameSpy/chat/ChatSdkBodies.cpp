// cl: /DNDEBUG /MD -Ireference/shims/gamespy

// The GameSpy Chat SDK bodies that were converted to C++ rather than
// reconstructed inside the SDK's own .c translation units.
//
// Incoming, all (CHAT, const ciServerMessage *) entries in one handler table:
//   ciErrNoUniqueNickHandler       0x0086FC70   ciKillHandler        0x0086D900
//   ciErrUniqueNickExpiredHandler  0x0086FC90   ciQuitHandler        0x0086D820
//   ciErrErroneusNicknameHandler   0x0086FC10   ciRplWelcomeHandler  0x0086F5D0
//   ciRplLoginHandler              0x0086F7C0   ciRplSecureKeyHandler 0x0086F660
// Outgoing, the API entry points that format a line onto the chat socket:
//   chatBanUserSimpleA             0x00860FF0   chatChangeNickA      0x008604C0
//   chatInviteUserA                0x008614E0   ciSendUserA          0x00860280
//   chatSendChannelMessageA        0x008609F0
//
// All thirteen work on the same object: the CHAT handle IS a ciConnection.
// Split one body per file, each file restated it with only the fields its own
// body touched, so it appeared as two ints in one file, as a 0x8b4-byte body in
// another, and five separate files each opened it with `connected` and a
// nameless run of bytes up to the socket at +0x1c. The offsets never disagreed,
// only the amount each file bothered to name, so one declaration below carries
// all of them:
//
//   +0x00 connected     +0x0c nickErrorCallback   +0x1c chatSocket (0x328 B)
//   +0x04 connecting    +0x10 fillInUserCallback  +0x36c nick    +0x774 server
//   +0x08 disconnected  +0x14 connectCallback     +0x3ac name    +0x824 quiet
//                       +0x18 connectParam        +0x42c user    +0x828 secretKey
//                                                 +0x8a8 loginType
//                                                 +0x8ac userID   +0x8b0 profileID
//
// ciServerMessage likewise: the parsed IRC line is eight char pointers, then
// params at +0x20 and numParams at +0x24. The files that only needed params
// spelled the first eight as an opaque 0x20-byte pad.

#include <stdlib.h>
#include <string.h>

typedef void *CHAT;
typedef int CHATBool;
typedef unsigned char byte;

enum
{
	CHATFalse,
	CHATTrue
};

typedef void (__cdecl *ciConnectCallback)(CHAT chat, CHATBool success,
	int failureReason, void *param);

struct gs_crypt_key
{
	byte state[256];
	byte x;
	byte y;
};

struct ciSocket
{
	char pad00[0x120];
	int secure;						// +0x120
	gs_crypt_key inKey;					// +0x124
	gs_crypt_key outKey;					// +0x226
};

struct ciConnection
{
	CHATBool connected;
	CHATBool connecting;
	CHATBool disconnected;
	void *nickErrorCallback;
	void *fillInUserCallback;
	ciConnectCallback connectCallback;
	void *connectParam;
	ciSocket chatSocket;					// +0x1c
	char pad344[0x36c - 0x344];
	char nick[64];						// +0x36c
	char name[1];						// +0x3ac
	char pad3ad[0x42c - 0x3ad];
	char user[1];						// +0x42c
	char pad42d[0x774 - 0x42d];
	char server[1];						// +0x774
	char pad775[0x824 - 0x775];
	int quiet;						// +0x824
	char secretKey[1];					// +0x828
	char pad829[0x8a8 - 0x829];
	int loginType;						// +0x8a8
	int userID;						// +0x8ac
	int profileID;						// +0x8b0
};

struct chatChannelCallbacks
{
	void *channelMessage;
	void *kicked;
	void *userJoined;
	void *userParted;
	void *userChangedNick;
	void *topicChanged;
	void *channelModeChanged;
	void *userModeChanged;
	void *userListUpdated;
	void *newUserList;
	void *broadcastKeyChanged;
	void *param;
};

struct ciCallbackChannelMessageParams
{
	const char *channel;
	char *user;
	const char *message;
	int type;
};

struct ciCallbackChangeNickParams
{
	CHATBool success;
	char *oldNick;
	char *newNick;
};

struct ciServerMessage
{
	char *message;
	char *server;
	char *nick;
	char *user;
	char *host;
	char *command;
	char *middle;
	char *param;
	char **params;						// +0x20
	int numParams;						// +0x24
};

extern "C" void __cdecl ciNickError(CHAT chat, int type, const char *nick,
	int numSuggestedNicks, char **suggestedNicks);
extern "C" void __cdecl ciUserEnumChannels(CHAT chat, const char *user,
	void (*callback)(CHAT, const char *, const char *, void *), void *param);
extern "C" void ciKillEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *param);
extern "C" void ciQuitEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *reason);
extern "C" void ciSocketSend(void *chatSocket, const char *buffer);
extern "C" void ciSendNickAndUser(void *chat);
extern "C" void ciSendLogin(void *chat);
extern "C" void gs_xcode_buf(char *buffer, int length, char *key);
extern "C" void gs_prepare_key(const byte *key, int length, gs_crypt_key *out);
extern "C" void ciSocketSendf(void *socket, const char *format, ...);
extern "C" int ciGetNextID(CHAT chat);
// Both callers discard the result; retail's own signature returns the ID.
extern "C" int ciAddCallback_(CHAT chat, int type, void *callback,
	void *callbackParams, void *param, int ID, const char *channel,
	unsigned int callbackParamsSize);
extern "C" int ciAddNICKFilter(CHAT chat, const char *oldNick,
	const char *newNick, void *callback, void *param);
extern "C" chatChannelCallbacks *ciGetChannelCallbacks(CHAT chat, const char *channel);
// Retail ciThink reads the CHAT out of ESI (already live in every caller here)
// and takes only the ID as a pushed argument. C linkage keeps the row name
// _ciThink (chatMain.c) while emitting the single-push shape.
extern "C" void ciThink(int ID);
extern "C" void msleep(unsigned int milliseconds);
extern "C" int ciCheckFiltersForID(CHAT chat, int ID);
extern "C" int ciCheckCallbacksForID(CHAT chat, int ID);

// Retail compares the nicks with msvcr71!_strcmpi (IAT 0x00BBA518).
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);

static __forceinline int ciCheckForID(CHAT chat, int ID)
{
	return ciCheckFiltersForID(chat, ID) || ciCheckCallbacksForID(chat, ID);
}

// The three nick failures the server can report while we are still connecting.
// They differ only in the code they hand ciNickError and in whether the nick we
// asked for is worth repeating back.

// _ciErrErroneusNicknameHandler, retail 0x0086FC10
// ciErrErroneusNicknameHandler: defined in chatHandlers.c (its row's unit).
extern "C" void ciErrErroneusNicknameHandler(CHAT chat, const ciServerMessage *message);

// _ciErrUniqueNickExpiredHandler, retail 0x0086FC90
// ciErrUniqueNickExpiredHandler: defined in chatHandlers.c (its row's unit).
extern "C" void ciErrUniqueNickExpiredHandler(CHAT chat, const ciServerMessage *message);

// _ciErrNoUniqueNickHandler, retail 0x0086FC70
// ciErrNoUniqueNickHandler: defined in chatHandlers.c (its row's unit).
extern "C" void ciErrNoUniqueNickHandler(CHAT chat, const ciServerMessage *message);

// _ciQuitHandler, retail 0x0086D820
// ciQuitHandler: defined in chatHandlers.c (its row's unit).
extern "C" void ciQuitHandler(CHAT chat, const ciServerMessage *message);

// _ciKillHandler, retail 0x0086D900
// ciKillHandler: defined in chatHandlers.c (its row's unit).
extern "C" void ciKillHandler(CHAT chat, const ciServerMessage *message);

// _ciRplWelcomeHandler, retail 0x0086F5D0 -- the server accepted us, so the
// connection is up and the caller's connect callback finally fires.
// ciRplWelcomeHandler: defined in chatHandlers.c (its row's unit).
extern "C" void ciRplWelcomeHandler(CHAT chat, const ciServerMessage *message);

// _ciRplLoginHandler, retail 0x0086F7C0
// ciRplLoginHandler: defined in chatHandlers.c (its row's unit).
extern "C" void ciRplLoginHandler(void *chat, const ciServerMessage *message);

// _ciRplSecureKeyHandler, retail 0x0086F660 -- both halves of the stream key
// arrive in one message, xcoded with the secret key we were built with.
// ciRplSecureKeyHandler: defined in chatHandlers.c (its row's unit).
extern "C" void ciRplSecureKeyHandler(void *chat, const ciServerMessage *message);

// The outgoing half: everything below formats a line onto the chat socket at
// +0x1c, and the two that can fail locally report it through the same callback
// queue the handlers above drain.

// _chatBanUserSimpleA, retail 0x00860FF0
extern "C" void chatBanUserSimpleA(CHAT chat, const char *channel, const char *user)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected)
		return;

	ciSocketSendf(&connection->chatSocket, "MODE %s +b %s", channel, user);
}

// _chatInviteUserA, retail 0x008614E0
// chatInviteUserA: defined in chatMain.c (its row's unit).
extern "C" void chatInviteUserA(CHAT chat, const char *channel, const char *user);

// _ciSendUserA, retail 0x00860280 -- the IRC USER registration line.
extern "C" void ciSendUserA(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	ciSocketSendf(&connection->chatSocket, "USER %s %s %s :%s",
		connection->user, "127.0.0.1", connection->server, connection->name);
}

// _chatSendChannelMessageA, retail 0x008609F0
// chatSendChannelMessageA: defined in chatMain.c (its row's unit).
extern "C" void chatSendChannelMessageA(CHAT chat, const char *channel,
	const char *message, int type);

// _chatChangeNickA, retail 0x008604C0
extern "C" void chatChangeNickA(CHAT chat, const char *newNick,
	void *callback, void *param, CHATBool blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	if (!chat || !connection->connected)
		return;

	{
	CHATBool success = 1;
	if (!newNick || !newNick[0] || strlen(newNick) >= 64 ||
		_strcmpi(newNick, connection->nick) == 0)
		success = 0;

	if (!success)
	{
		if (callback)
		{
			ciCallbackChangeNickParams callbackParams;
			callbackParams.success = 0;
			callbackParams.oldNick = connection->nick;
			callbackParams.newNick = (char *)newNick;
			ID = ciGetNextID(chat);
			ciAddCallback_(chat, 26, callback, &callbackParams, param, ID,
				0, sizeof(callbackParams));

			if (blocking)
			{
				do
				{
					ciThink(ID);
					msleep(10);
				}
				while (ciCheckForID(chat, ID));
			}
		}
		return;
	}

	ciSocketSendf(&connection->chatSocket, "NICK :%s", newNick);
	ID = ciAddNICKFilter(chat, connection->nick, newNick, callback, param);
	if (blocking)
	{
		do
		{
			ciThink(ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
	}
}
