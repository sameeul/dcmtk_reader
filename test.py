from pydicom import dcmread
import numpy as np
ds = dcmread("/mnt/hdd8/axle/dev/dcmtk_reader/data/pydicom-data/data/SC_rgb_16bit_2frame.dcm")
print(ds)
print(ds.pixel_array.shape)
#print(np.sum(ds.pixel_array[:,:]))
print(ds.pixel_array[0:1,0:10:,0:10, 0])