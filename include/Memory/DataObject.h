#pragma once 

#include <memory>
#include <cstddef>
#include <vector>

namespace Memory
{
    class DataObject
    {
        public:
            DataObject();
            DataObject(std::shared_ptr<std::vector<char>> dataPtr);
            ~DataObject();
            size_t SetData(const std::vector<char>& data);
            std::shared_ptr<std::vector<char>> GetData() const;
            void Allocate(size_t size);
            bool resize(size_t size, bool force = false);
            const size_t& size() const;
        private:
            std::shared_ptr<std::vector<char>> _data;
            size_t _size;
    };
}