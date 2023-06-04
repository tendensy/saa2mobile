#include "SAALoader.h"
#include <fstream>

/*
* t.me/weikton
*/

SAALoader::SAALoader() 
{
              /* code */
}

SAALoader::~SAALoader() 
{
              /* code */
}

std::vector<byte> SAALoader::getFileFromSAA(const char *filename, const char *saaFilename) 
{
    std::ifstream saaFile(saaFilename, std::ios::binary);

    // Проверка на правильное открытиe SAA
    if (!saaFile.is_open()) 
    {
        return std::vector<byte>();
    }

    // SAA header
    byte header[14];
    saaFile.read((char *)header, 14);

    int numFiles = header[5] * 256 + header[4];

    // Поиск в SAA archive
    bool fileFound = false;
    for (int i = 0; i < numFiles; i++) 
    {
        byte fileNameLength = 0;
        saaFile.read((char *)&fileNameLength, 1);

        char *currentFileName = new char[fileNameLength + 1];
        saaFile.read(currentFileName, fileNameLength);
        currentFileName[fileNameLength] = '\0';

        int fileSize = header[7] * 256 + header[6];
        for (int j = 0; j < i; j++)
        {
            int fileOffset = (header[1] * 256 + header[0]) * 1024 + j * fileSize;
            saaFile.seekg(fileOffset, std::ios::beg);
            byte curFileNameLength;
            saaFile.read((char *)&curFileNameLength, 1);
            char *curFileName = new char[curFileNameLength + 1];
            saaFile.read(curFileName, curFileNameLength);
            curFileName[curFileNameLength] = '\0';
            delete[] curFileName;
        }
        int fileOffset = (header[1] * 256 + header[0]) * 1024 + i * fileSize;
        saaFile.seekg(fileOffset, std::ios::beg);

        if (strcmp(currentFileName, filename) == 0) 
        {
            fileFound = true;

            // Чтение файла
            std::vector<byte> fileData(fileSize);
            saaFile.read((char *)&fileData[0], fileSize);
            delete[] currentFileName;
            saaFile.close();
            return fileData;
        }

        delete[] currentFileName;
    }

    saaFile.close();

    // Если файл не найден
    return std::vector<byte>();
}