#pragma once 

#include <memory>
#include <cstddef>
#include <vector>
#include <mutex>

class DataObject
{
    public:
        explicit DataObject(std::shared_ptr<std::vector<std::byte>> dataPtr);
        ~DataObject();
        void allocate(size_t size);
        bool resize(size_t size);
        size_t size();

    protected:
        std::shared_ptr<std::vector<std::byte>> _data;
        size_t _size;
        std::mutex _mutex;
};