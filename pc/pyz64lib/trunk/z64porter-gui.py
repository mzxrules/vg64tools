#!/usr/bin/python

#z64Porter-GUI - tk dialog windows to get vars for setting up porter's arguments
from tkFileDialog import askopenfilename
from tkSimpleDialog import askstring
from tkMessageBox import askyesno, showerror, showinfo
from os import getcwd, path, system
from sys import executable

def main():
    try:
        f=open("z64porter.cfg")
        idir = f.read()
        f.close()
    except:
        idir = getcwd()
    f=open("z64porter.cfg","w")
    argv_ = ""
    argv_ = askopenfilename(title="OoT Debug ROM",filetypes=[('N64 ROM files','*.z64')],initialdir = idir)
    idir = path.split(argv_)[0]
    f.write(idir)
    f.close()
    argv_ += " %s" % (askopenfilename(title="Decompressed MM ROM",filetypes=[('N64 ROM files','*.z64')],initialdir = idir))
    argv_ += " %s" % (askstring(title = "OoT scene", prompt = "Scene to replace in OoT (use 0x if hex):" ))
    argv_ += " %s" % (askstring(title = "MM scene", prompt = "Scene to port from MM (use 0x if hex):" ))
    if (askyesno(title = "Address", message = "Insert at your own address?" )):
        argv_ += " -o 0x%s" % (askstring(title = "Address", prompt = "Address (hex) to insert port at:" ))
    if (askyesno(title = "Safe mode", message = "Port in safe mode?" )):
        argv_ += " -s"
    if (askyesno(title = "Music", message = "Use your own music value?" )):
        argv_ += " -m %s" % (askstring(title = "Music", prompt = "Music value (use 0x if hex):" ))
    result = system("%s z64porter.py %s -q" % ( executable, argv_ ) )
    if ( result ):
        showerror(title="Uhoh!", message="Failure :(\nExit status %i" % result )
    else:
        showinfo(title="Success", message="Scene ported successfully")

if __name__ == "__main__":
    main()
