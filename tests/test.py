from bfiocpp import TSTiffReader, Seq
import numpy as numpy

br = TSTiffReader("/home/samee/axle_dev/bfio-cpp/tests/p01_x01_y01_wx0_wy0_c1.ome.tif")
rows = Seq(0,1023,1)
cols = Seq(0,1023,1)
layers = Seq(0,0,1)
channels = Seq(0,0,1)
tsteps = Seq(0,0,1)
tmp = br.data(rows, cols, layers, channels, tsteps)
print(tmp.sum())
print(tmp.shape)
print(type(tmp))
print(tmp.dtype)

# from bfio import BioReader as BioReader
# br = BioReader("/home/samee/axle_dev/bfio-cpp/tests/p01_x01_y01_wx0_wy0_c1.ome.tif")
# tmp2 = br[:]
# tmp = tmp2[0:1024, 0:1024]
# print(tmp.sum())
# print(tmp.shape)
# print(type(tmp))
# print(tmp.dtype)