#ifndef SAALOADER_H
#define SAALOADER_H

// by Weikton

#include <vector>

struct SAAHeader
{
    char magic[4];
    unsigned short version;
    unsigned int fileSize;
    unsigned int fileCount;
    unsigned char padding[8];
};

typedef unsigned char byte;

class SAALoader {
public:
    SAALoader();
    ~SAALoader();
    std::vector<byte> getFileFromSAA(const char *filename, const char *saaFilename);
};

#endif // SAALOADER_H