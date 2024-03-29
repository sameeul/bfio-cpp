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
