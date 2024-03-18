#pragma once

#include <string>
#include <memory>
#include <vector>
#include <variant>
#include <iostream>

#include "sequence.h"
using image_data = std::variant<std::vector<std::uint16_t>, std::vector<std::int16_t>>;


namespace bfiocpp{

class OmeTiffReader{
public:
    OmeTiffReader(const std::string& fname);
    std::int64_t GetImageHeight() const ;
    std::int64_t GetImageWidth () const ;
    std::int64_t GetImageDepth () const ;
    std::int64_t GetTileHeight () const ;
    std::int64_t GetTileWidth () const ;
    std::int64_t GetTileDepth () const ;
    std::int64_t GetChannelCount () const;
    std::int64_t GetTstepCount () const;
    std::int64_t GetDataType() const;
    std::shared_ptr<image_data> GetImageData(const Seq& rows, const Seq& cols, const Seq& layers = Seq(0,0), const Seq& channels = Seq(0,0), const Seq& tsteps = Seq(0,0));


private:
    std::string _filename;
    std::int64_t    _image_height, 
                    _image_width, 
                    _image_depth, 
                    _tile_height, 
                    _tile_width, 
                    _tile_depth, 
                    _num_channels,
                    _num_tsteps,
                    _data_type; 
};

OmeTiffReader::OmeTiffReader(const std::string& fname){
    _filename = fname;
    if (_filename == "test"){
        _data_type = 1;
    } else {
        _data_type = 2;
    }
    _image_height = 10;
    _image_width = 10;
    _image_depth = 1;    
    _tile_height = 10;
    _tile_width = 10;
    _image_depth = 1;    
    _num_channels = 1;
    _num_tsteps = 1;
}

std::int64_t OmeTiffReader::GetImageHeight() const {return _image_height;} 
std::int64_t OmeTiffReader::GetImageDepth() const {return _image_depth;} 
std::int64_t OmeTiffReader::GetImageWidth() const {return _image_width;} 
std::int64_t OmeTiffReader::GetTileHeight() const {return _tile_height;} 
std::int64_t OmeTiffReader::GetTileDepth() const {return _tile_depth;} 
std::int64_t OmeTiffReader::GetTileWidth() const {return _tile_width;} 
std::int64_t OmeTiffReader::GetChannelCount() const {return _num_channels;} 
std::int64_t OmeTiffReader::GetTstepCount() const {return _num_tsteps;} 
std::int64_t OmeTiffReader::GetDataType() const {return _data_type;} 

std::shared_ptr<image_data> OmeTiffReader::GetImageData(const Seq& rows, const Seq& cols, const Seq& layers = Seq(0,0), const Seq& channels = Seq(0,0), const Seq& tsteps = Seq(0,0)) {
    if (_data_type == 1){

        auto data = std::make_shared<std::vector<std::uint16_t>>(_image_height*_image_width); 
        data->at(0) = 1;
        return std::make_shared<image_data>(std::move(*data));

    } else {
        auto data = std::make_shared<std::vector<std::int16_t>>(_image_height*_image_width); 
        data->at(0) = -1;
        return std::make_shared<image_data>(std::move(*data));
    }
} 
}

