def shiftr_(value, amount, size):
    return (value>>amount)&((1<<size)-1)
def myfavfunc(myfavword):
    w0 = myfavword >> 32
    w1 = myfavword & 0xFFFFFFFF
    print "G_SETTILE 0x%X" % shiftr_(w0, 24, 8)
    print "fmt       0x%X" % shiftr_(w0, 21, 3)
    print "siz       0x%X" % shiftr_(w0, 19, 2)
    print "line      0x%X" % shiftr_(w0, 9, 9)
    print "them      0x%X" % shiftr_(w0, 0, 9)
    print "tile      0x%X" % shiftr_(w1, 24, 3)
    print "palette   0x%X" % shiftr_(w1, 20, 4)
    print "cmt       0x%X" % shiftr_(w1, 18, 2)
    print "maskt     0x%X" % shiftr_(w1, 14, 4)
    print "shiftt    0x%X" % shiftr_(w1, 10, 4)
    print "cms       0x%X" % shiftr_(w1, 8, 2)
    print "masks     0x%X" % shiftr_(w1, 4, 4)
    print "shifts    0x%X" % shiftr_(w1, 0, 4)
