#ifndef PHYSFSSTREAM_H
#define PHYSFSSTREAM_H

#include <iostream>
#include <physfs.h>
#include <SFML/Graphics.hpp>

class PhysFsStream : public sf::InputStream
{
    public:
        PhysFsStream(const char* filename=0x0) :
            m_File(0x0)
        {
            if (filename)
                open(filename);
        }

        virtual ~PhysFsStream()
        {
            close();
        }

        bool isOpen() const
        {
            return (m_File != 0x0);
        }

        bool open(const char* filename)
        {
            close();
            m_File = PHYSFS_openRead(filename);
            return isOpen();
        }

        void close()
        {
            if (isOpen())
                PHYSFS_close(m_File);
            m_File=0x0;
        }

        virtual sf::Int64 read(void* data, sf::Int64 size)
        {
            if (!isOpen())
                return -1;

            return PHYSFS_read(m_File, data, 1, static_cast<PHYSFS_uint32>(size));
        }

        virtual sf::Int64 seek(sf::Int64 position)
        {
            if (!isOpen())
                return -1;

        if (PHYSFS_seek(m_File, position))
                return tell();
            else
                return -1;
        }

        virtual sf::Int64 tell()
        {
            if (!isOpen())
                return -1;

            return PHYSFS_tell(m_File);
        }

        virtual sf::Int64 getSize()
        {
            if (!isOpen())
                return -1;

            return PHYSFS_fileLength(m_File);
        }

    private:
        PHYSFS_File* m_File;

};

#endif // PHYSFSSTREAM_H
