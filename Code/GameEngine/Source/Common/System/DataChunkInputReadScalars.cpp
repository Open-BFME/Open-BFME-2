// cl: /O1 /DNDEBUG /MD /EHsc
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// Donor: BFME 1 GameEngine/Source/Common/System/DataChunk.cpp.
// These target readers share the stream at +0 and matched decrementDataLeft.
// Their float/byte returns and requested byte counts establish the operations;
// the float reader is also used by the four-float parser at RVA 0x538A0B.
struct ChunkInputStream {
    virtual int read(void *data, int bytes);
};

class DataChunkInput {
public:
    float readReal();
    unsigned char readByte();
    void readArrayOfBytes(char *buffer, int length);
protected:
    void decrementDataLeft(int size);
private:
    ChunkInputStream *m_file;
};

float DataChunkInput::readReal()
{
    float value;
    m_file->read(&value, sizeof(value));
    decrementDataLeft(sizeof(value));
    return value;
}

unsigned char DataChunkInput::readByte()
{
    unsigned char value;
    m_file->read(&value, sizeof(value));
    decrementDataLeft(sizeof(value));
    return value;
}

void DataChunkInput::readArrayOfBytes(char *buffer, int length)
{
    m_file->read(buffer, length);
    decrementDataLeft(length);
}
