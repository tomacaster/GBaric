#include "Memory/DataObject.h"
#include <mutex>

using namespace Memory;

DataObject::DataObject() : _data(nullptr), _size(0)
{
}

DataObject::DataObject(std::shared_ptr<std::vector<std::byte>> dataPtr) : _data(std::move(dataPtr)), _size(dataPtr->size())
{
}

DataObject::~DataObject()
{
    std::unique_lock lock(_mutex);
    _data->clear();
}

const size_t &DataObject::SetData(const std::vector<std::byte> &data)
{
    std::unique_lock lock(_mutex);
    * _data = data;
    _size = _data->size();

    return _size;
}

std::shared_ptr<std::vector<std::byte>> DataObject::GetData()
{
    std::shared_lock lock(_mutex);

    return _data;
}

void DataObject::Allocate(size_t size)
{
    std::unique_lock lock(_mutex);
    _data = std::make_shared<std::vector<std::byte>>(size);
    _size = size;
}

bool DataObject::resize(size_t size, bool force)
{
    std::unique_lock lock(_mutex);
    if(size <= _size && !force) 
    {
        return false;
    }
    else
    {
        _data->resize(size, std::byte(0));
        _size = size;

        return true;
    }    
}

const size_t&  DataObject::size() const
{   
    std::shared_lock lock(_mutex);
    return _size;
}