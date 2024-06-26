import numpy as np
from typing import Tuple
from .libbfiocpp import OmeTiffReader


class TSTiffReader:

    READ_ONLY_MESSAGE: str = "{} is read-only."

    def __init__(self, file_name: str) -> None:
        self._image_reader: OmeTiffReader = OmeTiffReader(file_name)
        self._Y: int = self._image_reader.get_image_height()
        self._X: int = self._image_reader.get_image_width()
        self._Z: int = self._image_reader.get_image_depth()
        self._C: int = self._image_reader.get_channel_count()
        self._T: int = self._image_reader.get_tstep_count()

    def data(
        self, rows: int, cols: int, layers: int, channels: int, tsteps: int
    ) -> np.ndarray:
        return self._image_reader.get_image_data(rows, cols, layers, channels, tsteps)

    def ome_metadata(self) -> str:
        return self._image_reader.get_ome_xml_metadata()

    def send_iter_read_request(
        self, tile_size: Tuple[int, int], tile_stride: Tuple[int, int]
    ) -> None:
        self._image_reader.send_iterator_read_requests(
            tile_size[0], tile_size[1], tile_stride[0], tile_stride[1]
        )

    def close(self):
        pass

    def __enter__(self) -> "TSTiffReader":
        """Handle entrance to a context manager.

        This code is called when a `with` statement is used. This allows a
        BioBase object to be used like this:

        with bfio.BioReader('Path/To/File.ome.tif') as reader:
            ...

        with bfio.BioWriter('Path/To/File.ome.tif') as writer:
            ...
        """
        return self

    def __del__(self) -> None:
        """Handle file deletion.

        This code runs when an object is deleted..
        """
        self.close()

    def __exit__(self, type_class, value, traceback) -> None:
        """Handle exit from the context manager.

        This code runs when exiting a `with` statement.
        """
        self.close()
