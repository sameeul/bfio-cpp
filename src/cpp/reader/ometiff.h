#pragma once

#include <string>
#include <memory>
#include <vector>
#include <variant>
#include <iostream>
#include "tensorstore/tensorstore.h"
#include "sequence.h"
using image_data = std::variant<std::vector<std::uint8_t>,
                                std::vector<std::uint16_t>, 
                                std::vector<std::uint32_t>, 
                                std::vector<std::uint64_t>, 
                                std::vector<std::int8_t>, 
                                std::vector<std::int16_t>,
                                std::vector<std::int32_t>,
                                std::vector<std::int64_t>,
                                std::vector<float>,
                                std::vector<double>>;


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
    std::string GetDataType() const;
    std::shared_ptr<image_data> GetImageData(const Seq& rows, const Seq& cols, const Seq& layers, const Seq& channels, const Seq& tsteps);


private:
    std::string _filename, _data_type;
    std::int64_t    _image_height, 
                    _image_width, 
                    _image_depth, 
                    _tile_height, 
                    _tile_width, 
                    _tile_depth, 
                    _num_channels,
                    _num_tsteps;
    std::uint16_t _data_type_code;
    tensorstore::TensorStore<void, -1, tensorstore::ReadWriteMode::dynamic> source;

    template <typename T>
    std::shared_ptr<std::vector<T>> GetImageDataTemplated(const Seq& rows, const Seq& cols, const Seq& layers, const Seq& channels, const Seq& tsteps);
                     
};
}

