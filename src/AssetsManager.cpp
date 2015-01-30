#include "AssetsManager.h"

AssetsManager AssetsManager::m_instance = AssetsManager();

AssetsManager& AssetsManager::getInstance()
{
    return m_instance;
}

AssetsManager::AssetsManager()
{
}

Texture AssetsManager::getTexture(const char* filename)
{
    PHYSFS_init(NULL);
    PHYSFS_addToSearchPath("assets.cpak", 1);
    PhysFsStream stream;
    stream.open(filename);
    Texture texture;
    texture.loadFromStream(stream);
    return texture;
}

string AssetsManager::getFile(const char* filename)
{
    PHYSFS_init(NULL);
    PHYSFS_addToSearchPath("assets.cpak", 1);
    PHYSFS_file* file = PHYSFS_openRead(filename);
    char *content;
    content = new char[PHYSFS_fileLength(file)];
    PHYSFS_read(file, content, 1, PHYSFS_fileLength(file));
    return content;
}

void AssetsManager::close()
{
    PHYSFS_deinit();
}
