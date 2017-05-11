import os
L = range(6,11)
#print L
D = [2,3]
#print D
for l in L:
    cmd = "./test.out /home/wch/codebase/EMS1/planted_l16_d3.txt "+ str(l) +' 2'
    savefile = "./result_" + str(l) +'_2_fix.txt'
    print cmd
    print savefile
    os.system(cmd+" > " +savefile)
#cmd = "./test /home/wch/codebase/EMS1/planted_l16_d3.txt 11 3"
#savefile = "./result_11_3_fix.txt"
cmd = "./test /home/wch/codebase/EMS1/planted_l16_d3.txt 11 3"
savefile = "./result_11_3_fix2.txt"
print cmd
print savefile
os.system(cmd+" > " +savefile)
