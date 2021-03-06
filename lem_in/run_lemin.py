#!python3
import sys
import os
import subprocess as spr

def print_usage():
    print(
    '''usage: run_lemin arg1 arg2
    arg1 = name of lem-in file
    arg2 = file with anthill (z or no_z)

    this program do:
        1. run lem-in < [map....no_z]
        2. remake res of lem-in to map with z coordinate
        3. run ./visu with res with z coordinate
    ''')

def convert_res_noz_to_z(anthill_z, res_no_z, res_z):
    if (len(sys.argv) != 3):
        for i in sys.argv:
            print(i)
        #print(len(sys.argv))
        print_usage()
        exit()

    anthill_print = []

    with open(anthill_z, 'r') as fd:
        for line in fd:
            anthill_print.append(line)

    with open(res_no_z, 'r') as fd:
        for line in fd:
            if line[0] == "L":
                anthill_print.append(line)

    with open(res_z, 'w') as fd:
        for line in anthill_print:
            print(line)
            fd.write(line)

if len(sys.argv) != 3:
    print_usage()
    exit()

prog_name = sys.argv[1]
prog_name_base = os.path.basename(sys.argv[1])
map_name = sys.argv[2]

if "_no_z" in map_name:
    map_name_no_z = map_name
    map_name_z = map_name.replace("_no_z", "_z")
elif "_z" in map_name:
    map_name_z = map_name
    map_name_no_z = map_name.replace("_z", "_no_z")
else:
    print("error map name")
    exit()

if os.path.isfile(prog_name) == False:
    print("error name program")
    exit()

if os.path.isfile(map_name_z) == False or \
    os.path.isfile(map_name_no_z) == False:
    print("error name map or not exist")
    exit()

res_name_no_z = map_name_no_z + "_res_" + prog_name_base
res_name_z = map_name_z + "_res_" + prog_name_base

p = spr.Popen("rm " + res_name_no_z, shell=True)
p.wait()
p = spr.Popen("rm " + res_name_z, shell=True)
p.wait()

start_str = prog_name + " < " + map_name_no_z + " > " + res_name_no_z
print(start_str)
p = spr.Popen(start_str, shell=True)
p.wait()

convert_res_noz_to_z(map_name_z, res_name_no_z, res_name_z)

# start_convert_str = "python3 _convert_res_noz_to_z.py " + map_name_z + " " + res_name_no_z + " > " + res_name_z

# print(start_convert_str)
# p = spr.Popen(start_convert_str, shell=True)
# p.wait()

p = spr.Popen("./visu " + res_name_z, shell=True)
print("finished")
