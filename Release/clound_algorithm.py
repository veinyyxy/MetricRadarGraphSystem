import sys

def run_CloundBase_algorithm( list ):
    reslut=[]
    for pV in list:
        if (pV - (-32768) < 0.0001):
            continue
        else:
            reslut.append(pV)
    return reslut

def run_CloundTop_algorithm( list ):
    reslut=[]
    for pV in list:
        if (pV - (-32768) < 0.0001):
            continue
        else:
            reslut.append(pV)
    return reslut
