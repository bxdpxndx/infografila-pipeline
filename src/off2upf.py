#!/usr/bin/env python

import sys

def convert_poly(poly_in):
    poly = poly_in.split()
    poly_out = [poly[0]]
    poly_out.extend([str(int(x) + 1) for x in poly[1:]])
    poly_out.append('\n')
    return " ".join(poly_out)

def main():
    if len(sys.argv) != 3:
        print("Bad arguments, usage: {} <input_file> <output_file>".format(sys.argv[0]))

    try:
        inp = open(sys.argv[1])
    except IOError:
        print("Input file {} doesn't exist".format(sys.argv[1]))

    try:
        out = open(sys.argv[2], 'w')
    except IOError:
        print("Can't open output file {}".format(sys.argv[2]))

    content = inp.readlines()
    header = content[1].split()[0:2]
    nvertexs, npolys = [int(n) for n in header]

    header.append('\n')
    out.write(" ".join(header));

    for vertexs in content[2:2+nvertexs]:
        out.write(vertexs)
    
    for polygon in content[2+nvertexs:]:
        out.write(convert_poly(polygon))

    inp.close()
    out.close()

if __name__ == "__main__":
    main()
