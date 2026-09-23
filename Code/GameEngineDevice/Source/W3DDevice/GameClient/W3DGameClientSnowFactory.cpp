// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour/BFME1 W3DGameClient::createSnowManager with target object extent.
// Only the verified destructor/init virtual prefix is represented here.
class SnowManager {
public:
    virtual ~SnowManager();
    virtual void init();
private:
    unsigned char m_targetBase[0x70];
};

class W3DSnowManager : public SnowManager {
public:
    W3DSnowManager();
    virtual ~W3DSnowManager();
    virtual void init();
private:
    unsigned char m_targetDerived[0x3C];
};

typedef char SnowBaseSizeCheck[sizeof(SnowManager) == 0x74 ? 1 : -1];
typedef char W3DSnowSizeCheck[sizeof(W3DSnowManager) == 0xB0 ? 1 : -1];

class W3DGameClient {
protected:
    virtual SnowManager *createSnowManager();
};

SnowManager *W3DGameClient::createSnowManager()
{
    return new W3DSnowManager;
}
