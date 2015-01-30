#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <PhysFsStream.h>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class AssetsManager
{
    public:
        static AssetsManager& getInstance();
        static Texture getTexture(const char* filename);
        static string getFile(const char* filename);
        static void close();
    protected:
    private:
        AssetsManager();
        static AssetsManager m_instance;
};

#endif // ASSETSMANAGER_H
