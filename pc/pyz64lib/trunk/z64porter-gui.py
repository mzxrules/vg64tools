#!/usr/bin/python

#z64Porter-GUI - tk dialog windows to get vars for setting up porter's arguments
from tkFileDialog import askopenfilename
from tkSimpleDialog import askstring, askinteger
from tkMessageBox import askyesno
from os import getcwd, path, system

def main():
    idir = getcwd()
    argv_ = ""
    argv_ = askopenfilename(title="OoT Debug ROM",filetypes=[('N64 ROM files','*.z64')],initialdir = idir)
    idir = path.split(argv_)[0]
    argv_ += " %s" % (askopenfilename(title="Decompressed MM ROM",filetypes=[('N64 ROM files','*.z64')],initialdir = idir))
    argv_ += " %i" % (askinteger(title = "Scene to", prompt = "Scene to replace in OoT (dec)" ))
    argv_ += " %i" % (askinteger(title = "Scene from", prompt = "Scene to port from MM (dec)" ))
    if (askyesno(title = "Address", message = "Insert at your own address?" )):
        argv_ += " -o 0x%s" % (askstring(title = "Address", prompt = "Address (hex) to insert port at" ))
    if (askyesno(title = "Safe mode", message = "Port in safe mode?" )):
        argv_ += " -s"
    system("python z64porter.py %s" % ( argv_ ) )

if __name__ == "__main__":
    main()
