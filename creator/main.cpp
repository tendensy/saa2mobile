#include <fstream>
#include <iostream>
#include <string>

struct SAAHeader
{
    char magic[4];
    unsigned short version;
    unsigned int fileSize;
    unsigned int fileCount;
    unsigned char padding[8];
};

void addFileToSAA(const std::string& fileName, const std::string& archiveName)
{
    std::ofstream archive(archiveName, std::ios::binary | std::ios::app);
    std::ifstream file(fileName, std::ios::binary);
    if (!file || !archive)
    {
        std::cerr << "Error: Failed to open files" << std::endl;
        return;
    }
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    archive.write(reinterpret_cast<const char*>(&fileSize), sizeof(int));

    char buffer[1024];
    int bytesRead = 0;
    file.seekg(0, std::ios::beg);
    while (file.read(buffer, sizeof(buffer)))
    {
        archive.write(buffer, sizeof(buffer));
        bytesRead += sizeof(buffer);
    }
    if (bytesRead < fileSize)
    {
        file.read(buffer, fileSize - bytesRead);
        archive.write(buffer, fileSize - bytesRead);
    }
    file.close();
    archive.close();
}

int main()
{
    printf("Weikton Games");
    addFileToSAA("samp.img", "archive.saa"); 
   // return 0;
}


/*int main()
{ 
    printf("Weikton Games");
    addFileToSAA("samp.1img", "archive.saa"); 
}*/