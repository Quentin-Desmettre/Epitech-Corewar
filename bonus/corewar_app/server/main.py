##
## EPITECH PROJECT, 2022
## COREWAR
## File description:
## COREWAR SERVER
##

import _thread as thread
import socket
import sys
import signal

from src.asm import *
from src.corewar import *
from src.matchmaking import *

## GLOBAL
IP = socket.gethostbyname(socket.gethostname())
PORT = 5001
ADDRESS = (IP, PORT)

FORMAT = "utf-8"

"""SOCKET INIT"""
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


#####

def signalHandler(sig, frame):
    print(f"[SERVER] <!!!> Server closing...")
    subprocess.run(["bash", "scripts/clean.sh"])
    server.close()
    sys.exit(0)


def initCorewar():
    make_process = subprocess.run(["bash", "scripts/build.sh"])
    print(f"[MAKE] logs : {make_process}")
    if make_process.returncode != 0:
        print("[SERVER] <!!!> Unable to build corewar")
        sys.exit(1)


def newClient(client_socket, address):
    """GET INFO"""
    received = client_socket.recv(BUFFER_SIZE).decode()
    request, filename, uuid = received.split(SEPARATOR)

    print(f"\n[SERVER] User connected as {uuid}")
    if request == "<COMPILE>":
        receiveFile(client_socket, address, filename, uuid)
    if request == "<QUEUEUP>":
        queueUp(client_socket, address, filename, uuid)
    if request == "<CANCELQ>":
        cancelQueue(client_socket, address, uuid)


def main():
    server.bind(ADDRESS)
    server.listen()
    print("[SERVER] SERVER ONLINE.")
    print(f"[SERVER] Server is listening... ({IP}:{PORT})\n")

    thread.start_new_thread(matchmaking, (PLAYERS, ))
    print(f"[SERVER] Matchmaking is up...\n\n")

    """CONNECTION"""
    while True:
        client_socket, address = server.accept()
        print(f"[SERVER] Connected to {address}.")
        thread.start_new_thread(newClient, (client_socket, address))


if __name__ == '__main__':
    signal.signal(signal.SIGINT, signalHandler)

    print("[SERVER] Server starting... Press CTRL-C to exit")
    initCorewar()
    main()
