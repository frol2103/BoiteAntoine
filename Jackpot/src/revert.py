import fluentpy as _
 
a =[ 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe, 0x00 ]

def revert(n):
    return (
    _(range(0,8)).map(lambda i: ((n >> i) & 1) << (8-i-1))
    .reduce(lambda a,b: a | b)
    )

def format(n):
    "{0:b:8}"

print("{" + ",".join(_(a).map(lambda x: "B{0:08b}".format(revert(x)._))._) + "}")
