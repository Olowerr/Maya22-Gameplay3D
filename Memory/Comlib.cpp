#include "Comlib.h"

Comlib::Comlib(LPCWSTR bufferName, size_t bufferSize, ProcessType type)
    : type(type)
    , sharedMemory(new Memory(bufferName, bufferSize))
    , mutex(new Mutex(L"MutexMap"))
{
    messageData = sharedMemory->GetMemoryBuffer();

    head = sharedMemory->GetControlBuffer();
    tail = head + 1;
    freeMemory = tail + 1;

    if (type == Producer)
    {
        std::cout << "Producer activated\n";

        *head = 0;
        *tail = 0;
        *freeMemory = bufferSize * MB;
    }

    else if (type == Consumer)
    {
        std::cout << "Consumer activated\n";

        *tail = 0;
    }
}

Comlib::~Comlib()
{    

}

bool Comlib::Send(char* message, SectionHeader* secHeader)
{       
    mutex->Lock();

    size_t memoryLeft = sharedMemory->GetBufferSize() - *head;

    // Not enough space?
    if (secHeader->messageLength + sizeof(SectionHeader) >= memoryLeft)
    {
        // 
        if (*tail != 0)
        {
            secHeader->messageID = 0;
            memcpy(messageData + *head, secHeader, sizeof(SectionHeader));

            *freeMemory -= secHeader->messageLength + sizeof(SectionHeader);
            *head = 0;

            mutex->Unlock();
            return false;
        }
    }

    // Has enough space?
    else if (secHeader->messageLength + sizeof(SectionHeader) < *freeMemory - 1) // - 1 for saftey
    {
        secHeader->messageID = 1;

        memcpy(messageData + *head, secHeader, sizeof(SectionHeader));
        memcpy(messageData + *head + sizeof(SectionHeader), message, secHeader->messageLength);

        *freeMemory -= (secHeader->messageLength + sizeof(SectionHeader));
        *head = (*head + secHeader->messageLength + sizeof(SectionHeader)) % sharedMemory->GetBufferSize();

        mutex->Unlock();
        return true;
    }
  

    mutex->Unlock();
    return false;
}

bool Comlib::Recieve(char*& message, SectionHeader*& secHeader)
{   
    mutex->Lock();

    size_t msgLength = 0;

    if (*freeMemory < sharedMemory->GetBufferSize())
    {
        if (*head != *tail)
        {
            secHeader = ((SectionHeader*)&messageData[*tail]);

            msgLength = secHeader->messageLength;
            if (secHeader->messageID == 0)
            {
                *freeMemory += msgLength + sizeof(SectionHeader);
                *tail = 0;

                mutex->Unlock();
                return false;
            }
            else
            {
                message = new char[msgLength];
                memcpy(message, &messageData[*tail + sizeof(SectionHeader)], msgLength);

                *tail = (*tail + msgLength + sizeof(SectionHeader)) % sharedMemory->GetBufferSize();
                *freeMemory += (msgLength + sizeof(SectionHeader));

                mutex->Unlock();
                return true;
            }
        }
    }

    mutex->Unlock();
    return false;
}