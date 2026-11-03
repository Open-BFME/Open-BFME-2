// Rva001EAE6FHelper: 0x80 bytes that clear80 (0x001EAE6F) fills with zero; Rva0025342CMember::construct
// (0x0025342C) calls it at +0 and +0x80. Not registered yet: 33 units still keep a private copy.
#pragma once

#ifndef BFME2_RVA001EAE6FHELPER_H
#define BFME2_RVA001EAE6FHELPER_H

class Rva001EAE6FHelper
{
public:
    Rva001EAE6FHelper *clear80();

private:
    char m_pad[0x80];
};

#endif
