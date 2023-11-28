
# f = open("table.csv", 'w')
# for i in range(1, 500):
#     for j in range(1, 500):
#         r = (i**2 + j**2)**1.5
#         f.write(f"{(i / r * 1000000):.2f}")
#         if(j != 500):
#             f.write(',')
#     f.write('\n')
XMAX = 501
YMAX = 501
lowValue = 0
bigValue = 0
expansion = 1
while lowValue == 0:
    expansion *= 10
    lowValue = 65535
    bigValue = 0
    f = open("vectorizedTables.h", 'w')
    f.write("// This is header file of f(x,y) = x / sqrt(x^2 + y^2)^3 fast lookup table\n ")
    f.write(f"#include <stdint.h>\nconst uint32_t xyDivR3LookupTable[{YMAX}][{XMAX}] = {{")

    for i in range(0, 500):
        f.write("{")
        for j in range(0, 500):
            if i == 0 and j == 0:
                v = 0
            else: 
                v = int((i / ((i**2 + j**2)**1.5)) * expansion)
            
            if i == 29 and j == 106:
                print(v)

            if v < lowValue:
                if i != 0 and j != 0:
                    lowValue = v
            if v > bigValue:
                bigValue = v

            f.write(f"{hex(v)}")
            if(j != 500):
                f.write(',')
        f.write('}')
        if(i != 500):
            f.write(',\n')
    f.write("};\n\n")
    print(lowValue)
f.write(f"#define TABLE_MULTIPLIER {expansion}")

print(f"expansion: {expansion}")
print(f"biggest: {bigValue}")
