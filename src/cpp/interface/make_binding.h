#define makeBinding(ReaderType, Name)	\
  py::class_<ReaderType, std::shared_ptr<ReaderType>>(m, Name) \
    .def(py::init<const std::string &>()) \
    .def("get_image_height", &ReaderType::GetImageHeight) \
    .def("get_image_width", &ReaderType::GetImageWidth) \
    .def("get_image_depth", &ReaderType::GetImageDepth) \
    .def("get_tile_height", &ReaderType::GetTileHeight) \
    .def("get_tile_width", &ReaderType::GetTileWidth) \
    .def("get_tile_depth", &ReaderType::GetTileDepth) \
    .def("get_channel_count", &ReaderType::GetChannelCount) \
    .def("get_tstep_count", &ReaderType::GetTstepCount) \
    .def("get_image_data",  \
        [](ReaderType& tl) { \
            if (tl.GetDataType() == 1) \
            {return get_image_data(tl);}\
            else {return get_image_data(tl);}\
        }, py::return_value_policy::reference); 
   