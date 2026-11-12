// flags: region default (reverse/retail_inventory/flag_regions.csv)

#include "../../Include/GameNetwork/Rva007E8810Message.h"

#include "../../Include/GameNetwork/BfmeThingRF.h"

class Rva007F0460BlobHeader
{
public:
    Rva007F0460BlobHeader(Rva007E8810Message *message);

private:
    Rva007E8810Message *m_message;
    int m_field04;
    __int64 m_blobId;
    int m_decodedLength;
};

Rva007F0460BlobHeader::Rva007F0460BlobHeader(Rva007E8810Message *message)
{
    m_message = message;
    m_blobId = m_message->getInt64("blobId", -1);
    int size = (int)((BfmeThingRF *)m_message)->bfmeGoRF((void *)"size", (void *)-1);
    m_decodedLength = (size / 4) * 3 - 1;
}
