import os

root = os.getcwd() + '/src/kernel/sys'

with open(root + '/interruption.template','r') as ff, open(root + '/interruption.hpp','w') as sf:
    for line in ff:
        sf.write(line)
    all_tramplins = ''
    indent = '\n\t\t\t\t\t'
    for i in range(255):
        sf.write('__gen_tramplin(%s)\n' % hex(i).split('x')[-1])
        all_tramplins += 'tramplin_%s,%s' % (hex(i).split('x')[-1], indent if (i + 1) % 8 == 0 else ' ')
    sf.write('__gen_tramplin(ff)\n')
    all_tramplins += 'tramplin_ff'
    sf.write('__gen_tramplins(%s)\n' % all_tramplins)