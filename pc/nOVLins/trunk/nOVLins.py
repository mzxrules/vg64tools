from sys import argv
from struct import pack, unpack
from z64lib import FindCode, GenActorEntryFmt

#AT_D = 0xF9440
#AT_1.0 = 0xD74D0

#python ovl_ins -e big|little -v debug|1.0 -a 0x123|123 -va 0x8012345 -o 0x35D0000 rom.ext ovl.ext

def _int(string):
    if len(string)>2 and string[:2]=='0x':
        return int(string,16)
    else:
        return int(string)
    
def readargs(args):
    ret = [">",0xF9440,args[-2],args[-1],-1,-1,-1,-1]
    args = args[1:-2]
    arg_no = 0
    while 1:
        if len(args) == arg_no:
            break
        curr_arg = args[arg_no]
        if curr_arg == '-a':
            arg_no+=1
            curr_arg = args[arg_no]
            try:
                ret[4] = _int(curr_arg)
            except:
                print 'Error: invalid actor number supplied (%s)'% curr_arg
                return -1
        elif curr_arg == '-va':
            arg_no+=1
            curr_arg = args[arg_no]
            try:
                ret[5] = _int(curr_arg)
            except:
                print 'Error: invalid virtual offset supplied (%s)'% curr_arg
                return -1
        elif curr_arg == '-o':
            arg_no+=1
            curr_arg = args[arg_no]
            try:
                ret[6] = _int(curr_arg)
            except:
                print 'Error: invalid ROM offset supplied (%s)'% curr_arg
                return -1
        elif curr_arg == '-d':
            arg_no+=1
            curr_arg = args[arg_no]
            try:
                ret[7] = _int(curr_arg)
            except:
                print 'Error: invalid data offset supplied (%s)'% curr_arg
                return -1
        elif curr_arg == '-e':
            arg_no+=1
            curr_arg = args[arg_no]
            if curr_arg == 'big':
                ret[0] = '>'
            elif curr_arg == 'little':
                ret[0] = '<'
            else:
                print 'Error: invalid endianess supplied (%s)'% curr_arg
                return -1
        elif curr_arg == '-v':
            arg_no+=1
            curr_arg = args[arg_no]
            if curr_arg == 'debug':
               ret[1] = 0xF9440
            elif curr_arg == '1.0':
                ret[1] = 0xD74D0
            else:
                print 'Error: invalid ROM version supplied (%s)'% curr_arg
                return -1
        else:
            print 'Error: invalid argument given (%s)'%curr_arg
            return -1
        arg_no+=1
    return ret

def getdataoff(ovlf, bo):
    ovlf.seek(0,2)
    ovlf_e = ovlf.tell()
    ovlf.seek(ovlf_e-4)
    ovlf.seek(ovlf_e - unpack("%sL"%bo,ovlf.read(4))[0])
    return unpack("%sL"%bo, ovlf.read(4))[0]

def main():
    if len(argv) < 3:
        print 'Error: Not enough arguments supplied'
        return -1
    options = readargs(argv)
    
    if options == -1:
        return -1
    #Open ROM
    try:
        rom = open(options[3],"r+b")
    except:
        print 'Error opening rom'
        return -1
    #Open ovl
    try:
        ovl = open(options[2],"rb")
    except:
        print 'Error opening actor'
        return -1
    #Get offset of code within the ROM
    code_off = FindCode(rom,options[0])[0]
    
    if (options[7] == -1):  #If true, get the offset of the ovl's data section
        options[7] = getdataoff(ovl, options[0])
    
    if (options[4] == -1):  #If true, no actor number specified. Use one specified in actor
        ovl.seek(options[7])
        options[4] = unpack('%sH'%(options[0]), ovl.read(2))[0]
        
    #Calculate offset of actor entry within ROM
    actor_entry_off = code_off+ (options[1]) +(32*(options[4]))
    
    if (options[5] == -1):  #If true, no virtual offset specified. Use one used for same actor number
        rom.seek(actor_entry_off+8)
        options[5] = unpack('%sL'%(options[0]), rom.read(4))[0]
    
    #... Unless it is 0.
    if (options[5] == 0):
        print "Error: Invalid virtual offset (%08X)"%(options[5])
        return -1

    if (options[6] == -1):  #If true, no physical offset was specified. Use one used for same actor number
        rom.seek(actor_entry_off)
        options[6] = unpack('%sL'%(options[0]), rom.read(4))[0]
    
    #... Unless it is 0.
    if (options[6] == 0):
        print "Error: Invalid physical offset (%08X)"%(options[6])
        return -1
    
    #Write ovl to ROM
    rom.seek(options[6])
    ovl.seek(0)
    rom.write(ovl.read())
    
    #Update entry in actor table
    ovl_end = ovl.tell()
    rom.seek(actor_entry_off)
    rom.write(pack("%sLLLLLL"%(options[0]), options[6], options[6]+ovl_end,
              options[5], options[5]+ovl_end, 0, options[5]+options[7]))
    #Close files
    rom.close()
    ovl.close()
    
    #Goodbye.
    return 0

if __name__ == "__main__":
    print "nOVLins 1.0" 
    if main() == 0:
        print "Success."
