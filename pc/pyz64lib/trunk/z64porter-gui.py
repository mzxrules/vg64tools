#!/usr/bin/python

#z64Porter-GUI - tk dialog windows to get vars for setting up porter's arguments
from tkFileDialog import askopenfilename
from tkSimpleDialog import askstring
from tkMessageBox import askyesno, showerror, showinfo
from os import getcwd, path#, system
#from sys import executable
from z64porter import main as port_scene

def main():
    try:
        f=open("z64porter.cfg")
        idir = f.read()
        f.close()
    except:
        idir = getcwd()
    f=open("z64porter.cfg","w")
    argv_ = ["z64porter.py"]
    argv_.append( askopenfilename(title="OoT Debug ROM",filetypes=[('N64 ROM files','*.z64')],initialdir = idir) )
    idir = path.split(argv_[1])[0]
    f.write(idir)
    f.close()
    argv_.append( askopenfilename(title="Decompressed MM ROM",filetypes=[('N64 ROM files','*.z64')],initialdir = idir) )
    argv_ .append( askstring(title = "OoT scene", prompt = "Scene to replace in OoT (use 0x if hex):" ))
    argv_ .append( askstring(title = "MM scene", prompt = "Scene to port from MM (use 0x if hex):" ))
    if (askyesno(title = "Address", message = "Insert at your own address?" )):
        argv_.append( "-o" )
        argv_.append( "0x%s" % (askstring(title = "Address", prompt = "Address (hex) to insert port at:" )))
    if (askyesno(title = "Safe mode", message = "Port in safe mode?" )):
        argv_.append( "-s" )
    if (askyesno(title = "Music", message = "Use your own music value?" )):
        argv_.append( "-m" )
        argv_.append(askstring(title = "Music", prompt = "Music value (use 0x if hex):" ))
    argv_.append("-q")
    #result = system("%s z64porter.py %s -q" % ( executable, argv_ ) )
    try:
        port_scene( argv_ )
        showinfo(title="Success", message="Scene ported successfully")
    except:
        showerror(title="Uhoh!", message="Failure :(" )

if __name__ == "__main__":
    main()
