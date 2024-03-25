#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include "../reader/ometiff.h"
#include "../reader/sequence.h"
namespace py = pybind11;
using bfiocpp::Seq;

#define EXTRACT_FROM_VARIANT_AND_RETURN(N) \
    case N: { \
        auto size = std::get<N>(*seq_ptr).size(); \
        auto data = std::get<N>(*seq_ptr).data(); \
        auto capsule = py::capsule(new auto (seq_ptr), [](void *p) {delete reinterpret_cast<decltype(seq_ptr)*>(p);}); \
        return py::array(size, data, capsule).reshape({num_tsteps, num_channels, num_layers, num_rows, num_cols}).squeeze(); \
        break; \
    }

inline py::array as_pyarray_shared_5d(std::shared_ptr<image_data> seq_ptr, size_t num_rows, size_t num_cols, size_t num_layers=1, size_t num_channels=1, size_t num_tsteps=1 ) {
    switch (seq_ptr->index()) {
        EXTRACT_FROM_VARIANT_AND_RETURN(0)
        EXTRACT_FROM_VARIANT_AND_RETURN(1)
        EXTRACT_FROM_VARIANT_AND_RETURN(2)
        EXTRACT_FROM_VARIANT_AND_RETURN(3)    
        EXTRACT_FROM_VARIANT_AND_RETURN(4)
        EXTRACT_FROM_VARIANT_AND_RETURN(5)
        EXTRACT_FROM_VARIANT_AND_RETURN(6)
        EXTRACT_FROM_VARIANT_AND_RETURN(7)    
        EXTRACT_FROM_VARIANT_AND_RETURN(8)
        EXTRACT_FROM_VARIANT_AND_RETURN(9)
    }
}

py::array get_image_data(bfiocpp::OmeTiffReader& tl, const Seq& rows, const Seq& cols, const Seq& layers, const Seq& channels, const Seq& tsteps) {
    auto tmp = tl.GetImageData(rows, cols, layers, channels, tsteps);
    auto ih = rows.Stop() - rows.Start() + 1;
    auto iw = cols.Stop() - cols.Start() + 1;
    auto id = layers.Stop() - layers.Start() + 1;;
    auto nc = channels.Stop() - channels.Start() + 1;
    auto nt = tsteps.Stop() - tsteps.Start() + 1;
 
    return as_pyarray_shared_5d(tmp, ih, iw, id, nc, nt) ;
}


PYBIND11_MODULE(libbfiocpp, m) {
    py::class_<Seq, std::shared_ptr<Seq>>(m, "Seq")  
        .def(py::init<const size_t, const size_t, const size_t>());
    
    py::class_<bfiocpp::OmeTiffReader, std::shared_ptr<bfiocpp::OmeTiffReader>>(m, "OmeTiffReader") 
    .def(py::init<const std::string &>()) 
    .def("get_image_height", &bfiocpp::OmeTiffReader::GetImageHeight) 
    .def("get_image_width", &bfiocpp::OmeTiffReader::GetImageWidth) 
    .def("get_image_depth", &bfiocpp::OmeTiffReader::GetImageDepth) 
    .def("get_tile_height", &bfiocpp::OmeTiffReader::GetTileHeight) 
    .def("get_tile_width", &bfiocpp::OmeTiffReader::GetTileWidth) 
    .def("get_tile_depth", &bfiocpp::OmeTiffReader::GetTileDepth) 
    .def("get_channel_count", &bfiocpp::OmeTiffReader::GetChannelCount) 
    .def("get_tstep_count", &bfiocpp::OmeTiffReader::GetTstepCount) 
    .def("get_image_data",  
        [](bfiocpp::OmeTiffReader& tl, const Seq& rows, const Seq& cols, const Seq& layers, const Seq& channels, const Seq& tsteps) { 
            return get_image_data(tl, rows, cols, layers, channels, tsteps);
        }, py::return_value_policy::reference); 


}