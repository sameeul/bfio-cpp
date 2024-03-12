from bfiocpp import BioReader

br = BioReader("testsd")
tmp = br.data()
print(tmp)
print(tmp.shape)
print(type(tmp))
print(tmp.dtype)