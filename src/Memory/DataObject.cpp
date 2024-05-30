#include "Memory/DataObject.h"
#include <iostream>

using namespace Memory;

DataObject::DataObject() : _data(nullptr), _size(0)
{
}

DataObject::DataObject(std::shared_ptr<std::vector<char>> dataPtr) : _data(dataPtr), _size(dataPtr->size())
{
}

DataObject::~DataObject()
{

}

size_t DataObject::SetData(const std::vector<char>& data) 
{
    _data = std::make_shared<std::vector<char>>(data);
    _size = _data->size();
    return _size;
}

std::shared_ptr<std::vector<char>> DataObject::GetData() const
{
    try
    {
        if(_data)
        {
            return _data;
        }
        else
        {
            return nullptr;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}

void DataObject::Allocate(size_t size)
{
    _data = std::make_shared<std::vector<char>>(size);
    _size = size;
}

bool DataObject::resize(size_t size, bool force)
{
    if(size <= _size && !force) 
    {
        return false;
    }
    else
    {

        _data->resize(size, char(size));
        _size = _data->size();

        return true;
    }    
}

const size_t&  DataObject::size() const
{   
    return _size;
}