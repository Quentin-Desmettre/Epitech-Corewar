##
## EPITECH PROJECT, 2022
## COREWAR
## File description:
## COREWAR SERVER
##

import time
import copy
import subprocess
import _thread as thread

## {'UUID': 'uuid', 'champion': 'champion.cor', 'Socket': 'socket'}
PLAYERS = [{'UUID': None, 'champion': None, 'Socket': None, 'hasFought': None}]


def deleteFightingPlayer(player):
    for i in range(len(PLAYERS)):
        if PLAYERS[i]['UUID'] == player['UUID']:
            PLAYERS.pop(i)
            return


def inList(list, uuid):
    for index in list:
        if index['UUID'] == uuid:
            return 1
    return 0


def launchCorewar(opponents):
    try:
        return_msg = subprocess.check_output(["scripts/corewar.sh", f"-a{opponents[0]['champion']}", f"-x{opponents[0]['UUID']}", f"-b{opponents[1]['champion']}", f"-y{opponents[1]['UUID']}"])
        return_msg = return_msg.decode()
        print(return_msg)
        if return_msg.find("<WINNER>"):
            winner = int(return_msg[return_msg.index("<WINNER>") + 8])
            opponents[winner]['Socket'].send("<LOG>You won ! :)".encode())
            opponents[0 if winner == 1 else 1]['Socket'].send("<LOG>You lost ! :(".encode())
            deleteFightingPlayer(opponents[0])
            deleteFightingPlayer(opponents[1])
    except:
        print("[COREWAR.SH] Unable to run...")
        deleteFightingPlayer(opponents[0])
        deleteFightingPlayer(opponents[1])


def matchmaking(players):
    opponents = []

    while True:
        for player in players:
            if (not player['hasFought'] and player['UUID'] is not None and not inList(opponents, player['UUID'])) and len(opponents) < 2:
                player['hasFought'] = True
                opponents.append({'UUID': player['UUID'], 'champion': player['champion'], 'Socket': player['Socket']})
        for opponent in opponents:
            if not inList(players, opponent['UUID']):
                opponents.remove(opponent)
        if len(opponents) >= 2:
            thread.start_new_thread(launchCorewar, (opponents.copy(), ))
            opponents.clear()
        time.sleep(5)
