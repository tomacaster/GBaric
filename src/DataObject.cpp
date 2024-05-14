#include "DataObject.h"

DataObject::DataObject(std::shared_ptr<std::vector<std::byte>> dataPtr) : _data(std::move(dataPtr)), _size(dataPtr->size())
{
}

DataObject::~DataObject()
{
    std::scoped_lock(_mutex);
    _data->clear();
}

void DataObject::allocate(size_t size)
{
    _data->reserve(size);
}

bool DataObject::resize(size_t size)
{
    if(size <= _size) 
    {
        return false;
    }
    else
    {
        _data->resize(size, std::byte(0));
        return true;
    }    
}

size_t DataObject::size()
{
    return _size;
}
