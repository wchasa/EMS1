import os
L = range(6,6)
#print L
D = [2,3]
#print D
for l in L:
    cmd = "./test.out /home/wch/codebase/EMS1/yst03r.fasta "+ str(l) +' 2'
    savefile = "./result_" + str(l) +'_2.txt'
    print cmd
    print savefile
    os.system(cmd+" > " +savefile)
cmd = "./test /home/wch/codebase/EMS1/yst03r.fasta 11 3"
savefile = "./result_11_3.txt"
print cmd
print savefile
os.system(cmd+" > " +savefile)
