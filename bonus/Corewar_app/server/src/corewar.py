##
## EPITECH PROJECT, 2022
## COREWAR
## File description:
## COREWAR SERVER
##

import os
import time
import random

from .matchmaking import *

SEPARATOR = "<SEPARATOR>"
ERROR = "<ERROR>"
COMPILED = "<COMPILED>"
GOTCHA = "<GOTCHA>"
BUFFER_SIZE = 1024

RANDOMMSG = ["In queue... Waiting for opponents",
             "Be patient !",
             "Get ready !",
             "Joining arena... I think !",
             "Wrong way... we are getting you back in the arena !"]


def queueUp(client_socket, address, filename, uuid):
    try:
        """DOES CHAMPION EXIST IN DB?"""
        if not os.path.exists(f"cor_file/{filename}.{uuid}"):
            client_socket.send("<NOCHAMP>".encode())
            client_socket.send("<CANCELQ>".encode())
            client_socket.close()
            return

        """TELLS THE SERVER IS READY"""
        client_socket.send(GOTCHA.encode())
        client_socket.send("<LOG>You joined the queue... Waiting for opponents".encode())
        PLAYERS.append({'UUID': uuid, 'champion': filename, 'Socket': client_socket, 'hasFought': False})
        print(f"[SERVER] {uuid} added to the queue.")

        """WAIT FROM MATCHMAKING / CHECK IF THE CLIENT IS CONNECTED"""
        start = time.time()
        while True:
            is_connected = False
            if time.time() - start > 5.0:
                client_socket.send(f"<LOG>{RANDOMMSG[random.randint(0, 4)]}".encode())
                print(f"<LOG>{RANDOMMSG[random.randint(0, 4)]}")
                start = time.time()
            for i in range(len(PLAYERS)):
                if PLAYERS[i]['UUID'] == uuid:
                    is_connected = True
                    break
            if not is_connected:
                client_socket.send("<CANCELQ>".encode())
                client_socket.close()
                return
            time.sleep(2)
    except:
        """CLOSE SOCKET ON ERROR"""
        print(f"[SERVER] <!!!> ERROR WITH: {address}...")
        client_socket.close()


def cancelQueue(client_socket, address, uuid):
    try:
        """TELLS THE SERVER IS READY"""
        for i in range(len(PLAYERS)):
            if PLAYERS[i]['UUID'] == uuid:
                PLAYERS.pop(i)
                break
        print(f"[SERVER] {uuid} removed from the queue.")
        client_socket.send("<LOG>You have been removed from the queue".encode())
    except:
        """CLOSE SOCKET ON ERROR"""
        print(f"[SERVER] <!!!> ERROR WITH: {address}...")
        client_socket.close()
