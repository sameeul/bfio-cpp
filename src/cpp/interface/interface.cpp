#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include "../reader/ometiff.h"

namespace py = pybind11;
#include "make_binding.h"

#include <iostream>

inline py::array as_pyarray_shared_5d(std::shared_ptr<image_data> seq_ptr, size_t num_rows, size_t num_cols, size_t num_layers=1, size_t num_channels=1, size_t num_tsteps=1 ) {
    switch (seq_ptr->index()) {
        case 0:
        {   
            auto size = std::get<0>(*seq_ptr).size();
            auto data = std::get<0>(*seq_ptr).data();
            auto capsule = py::capsule(new auto (seq_ptr), [](void *p) {delete reinterpret_cast<decltype(seq_ptr)*>(p);});
            return py::array(size, data, capsule).reshape({num_tsteps, num_channels, num_layers, num_rows, num_cols}).squeeze();
            break;
        }

        case 1:
        {
            auto size1 = std::get<1>(*seq_ptr).size();
            auto data1 = std::get<1>(*seq_ptr).data();
            auto capsule1 = py::capsule(new auto (seq_ptr), [](void *p) {delete reinterpret_cast<decltype(seq_ptr)*>(p);});
            return py::array(size1, data1, capsule1).reshape({num_tsteps, num_channels, num_layers, num_rows, num_cols}).squeeze();
            break;
            
        }
    }

 
}

py::array get_image_data(bfiocpp::OmeTiffReader& tl) {
    auto tmp = tl.GetImageData();
    auto ih = tl.GetImageHeight();
    auto iw = tl.GetImageWidth();
    auto id = tl.GetImageDepth();
    auto nc = tl.GetChannelCount();
    auto nt = tl.GetTstepCount();
 
    return as_pyarray_shared_5d(tmp, 10, 10, 1, 1, 1) ;

}


PYBIND11_MODULE(libbfiocpp, m) {
    makeBinding(bfiocpp::OmeTiffReader, "OmeTiffReader");
}