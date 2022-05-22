##
## EPITECH PROJECT, 2022
## COREWAR
## File description:
## COREWAR SERVER
##

import subprocess

ERROR = "<ERROR>"
COMPILED = "<COMPILED>"
SEPARATOR = "<SEPARATOR>"
GOTCHA = "<GOTCHA>"
BUFFER_SIZE = 1024


def compileFile(filename, uuid, client_socket):
    try:
        return_msg = subprocess.check_output(["scripts/compile.sh", f"-f{filename}", f"-u{uuid}"])
        print(return_msg.decode())
        index = return_msg.decode().find("Error")
        if index != -1:
            response = return_msg.decode()[index:]
            client_socket.send(f"{ERROR}{response}".encode())
        else:
            client_socket.send(COMPILED.encode())
    except:
        print("[COMPILE.SH] Unable to run...")
        client_socket.send(f"{ERROR} Unable to compile...".encode())


def receiveFile(client_socket, address, filename, uuid):
    try:
        """TELLS THE SERVER IS READY TO READ"""
        client_socket.send(GOTCHA.encode())

        """READ FILE FROM TCP TUNEL"""
        total_bytes = 0
        with open(f"tmp/{filename}.s", "wb") as f:
            while True:
                bytes_read = client_socket.recv(BUFFER_SIZE)  # Received bytes
                total_bytes += len(bytes_read)
                if bytes_read.decode().find("<EOS>") != -1:  # File transmitting is done.
                    bytes_read = bytes_read[:-5]
                    f.write(bytes_read)
                    break
                f.write(bytes_read)
        f.close()
        compileFile(filename, uuid, client_socket)
        client_socket.close()
    except:
        """CLOSE SOCKET ON ERROR"""
        print(f"[SERVER] <!!!> ERROR WITH: {address}...")
        client_socket.close()
