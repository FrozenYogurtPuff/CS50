from sys import argv
import csv

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

csvfile = open(argv[1], 'r')
for row in csv.DictReader(csvfile):
    dna_select = list(row.keys())[1:]
    break
csvfile.close()

dna = {}
dnafile = open(argv[2], 'r')
dnadata = dnafile.readline()

for dna_pair in dna_select:
    temp = 0
    maxn = 0
    i = 0
    while i < len(dnadata):
        if dnadata[i:i+len(dna_pair)] == dna_pair:
            temp += 1
            if temp > maxn:
                maxn = temp
            i += len(dna_pair)
        else:
            temp = 0
            i += 1
    dna[dna_pair] = maxn

csvfile = open(argv[1], 'r')
total = False
for row in csv.DictReader(csvfile):
    flag = True
    for i in dna.keys():
        if int(row[i]) != dna[i]:
            flag = False
    if flag:
        print(row['name'])
        total = True
if not total:
    print("No match")
    