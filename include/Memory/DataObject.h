#pragma once 

#include <memory>
#include <cstddef>
#include <vector>
#include <mutex>

namespace Memory
{
    class DataObject
    {
        public:
            DataObject();
            explicit DataObject(std::shared_ptr<std::vector<std::byte>> dataPtr);
            ~DataObject();
            const size_t& SetData(const std::vector<std::byte>& data);
            std::shared_ptr<std::vector<std::byte>> GetData();
            void Allocate(size_t size);
            bool resize(size_t size, bool force = false);
            const size_t& size() const;
        protected:
            std::shared_ptr<std::vector<std::byte>> _data;
            size_t _size;
            mutable std::mutex _mutex;
    };
}
