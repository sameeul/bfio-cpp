from .libbfiocpp import OmeTiffReader, Seq



class TSTiffReader:

    READ_ONLY_MESSAGE = "{} is read-only."
    


    def __init__(self, file_name):

        self._image_reader = OmeTiffReader(file_name)
        self._Y = self._image_reader.get_image_height()
        self._X = self._image_reader.get_image_width()
        self._Z = self._image_reader.get_image_depth()
        self._C = self._image_reader.get_channel_count()
        self._T = self._image_reader.get_tstep_count()


        
    
    def data(self, rows, cols, layers, channels, tsteps):
        return self._image_reader.get_image_data(rows, cols, layers, channels, tsteps)
    
    def ome_metadata(self):
        return self._image_reader.get_ome_xml_metadata()

    def send_iter_read_request(self, tile_size, tile_stride):
        self._image_reader.send_iterator_read_requests(tile_size[0], tile_size[1], tile_stride[0], tile_stride[1])


    def __call__(self, tile_size, tile_stride=None) :
        # Iterate through tiles of an image
        self._iter_tile_size = tile_size
        self._iter_tile_stride = tile_stride        
        return self


    def __iter__(self, tile_size, tile_stride=None):

        if tile_size is None:
            raise SyntaxError(
                "Cannot directly iterate over a TSTiffReader object."
                + "Call it (i.e. for i in TSTiffReader(256,256))"
            )

        # input error checking
        assert len(tile_size) == 2, "tile_size must be a list with 2 elements"
        if tile_stride is not None:
            assert len(tile_stride) == 2, "stride must be a list with 2 elements"
        else:
            tile_stride = tile_size


        # request reads
        self.send_iter_read_request(tile_size[0], tile_size[1], tile_stride[0], tile_stride[1])
        # collect views
        col_per_row = self._image_reader.get_column_tile_count()
        for data in self._image_reader.__iter__():
            row_index, col_index = self._image_reader.get_tile_coordiate(data[3], tile_size[0], data[5], tile_size[1])
            yield (row_index, col_index), self._image_reader.get_iterator_requested_tile_data(data[3], data[4], data[5], data[6])
