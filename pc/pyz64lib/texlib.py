import struct

def BMP24_TO_5551(infile,alpha=(1,1,1)):
    infile.seek(0x12)
    xs, ys = struct.unpack("<LL",infile.read(8))
    tex = ''
    infile.seek(0x36)
    for y in range(ys):
        line = ''
        for x in range(xs):
            rgb=struct.unpack(">BBB",infile.read(3))[::-1]
            if rgb== alpha:
                line+='\x00\x00'
            else:
                line+=struct.pack(">H",(int(r/8.226)<<11)|
                                  (int(g/8.226)<<6)|
                                  (int(b/8.226)<<6)|1)
        tex+=line
        del line
    return (xs, ys), tex

def BMP24_TO_CI5551(infile,alpha=(1,1,1)):
    infile.seek(0x12)
    xs, ys = struct.unpack("<LL",infile.read(8))
    tex = ''
    pal = []
    infile.seek(0x36)
    for y in range(ys):
        line = ''
        for x in range(xs):
            rgb=struct.unpack(">BBB",infile.read(3))[::-1]
            if rgb == alpha:
                rgba = "\x00\x00"
            else:
                rgba=struct.pack(">H",(int(r/8.226)<<11)|
                                 (int(g/8.226)<<6)|
                                 (int(b/8.226)<<6)|1)
            try:
                ci_no = pal.index(rgba)
            except:
                if len(pal) < 255:
                    pal.append(rgba)
                    ci_no = len(pal)-1
                else:
                    return -1
            line += struct.pack(">B", ci_no)
        tex+=line
        del line
    pal_ = ''
    for rgba in pal:
        pal_+=struct.pack(">H",rgba)
    del pal
    lp=len(pal_)
    if lp&7:
        pal_ += '/x00' * (lp - lp&0xFFF8+8)
    return (xs,ys),tex, pal_

def BMP32_TO_8888(infile):
    infile.seek(0x12)
    xs, ys = struct.unpack("<LL",infile.read(8))
    tex = ''
    infile.seek(0x36)
    for y in range(ys):
        line = ''
        for x in range(xs):
            rgba=infile.read(4)[::-1]
            line+=rgba
        tex+=line
        del line
    return (xs, ys), tex

def BMP32_TO_CI8888(infile):
    infile.seek(0x12)
    xs, ys = struct.unpack("<LL",infile.read(8))
    tex = ''
    pal = []
    infile.seek(0x36)
    for y in range(ys):
        line = ''
        for x in range(xs):
            rgba=infile.read(4)[::-1]
            try:
                ci_no = pal.index(rgba)
            except:
                if len(pal)<255:
                    pal.append(rgba)
                    ci_no = len(pal)-1
                else:
                    return -1
            line+=struct.pack(">B",ci_no)
        tex+=line
        del line
    pal_ = ''
    for rgba in pal:
        pal_+=rgba
    del pal
    lp=len(pal_)
    if lp&7:
        pal_ += '/x00' * (lp - lp&0xFFF8+8)
    return (xs,ys),tex, pal_
