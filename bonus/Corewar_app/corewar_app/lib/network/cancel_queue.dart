import 'dart:io';

import 'package:corewar_app/my_shared_preferences.dart';
import 'package:corewar_app/navpages/corewar_page.dart';

import '../navpages/asm_page.dart';

Future cancelQueue(context) async {
  final authController = AuthController();
  String? ip = await loadServerIP();
  String? port = await loadServerPort();
  String? uuid = await loadUUID();

  if (CorewarPage.inQueue == false) {
    showSnackBar(context, "You are not in queue...");
    return;
  }
  if (await authController.tryUuid() == false) {
    await AuthController.genUuid();
  }

  void _sendData(Socket socket) async {
    socket.write("<CANCELQ><SEPARATOR><EMPTY><SEPARATOR>$uuid");
    CorewarPage.inQueue = false;
    showSnackBar(context, "You left the queue !");
  }

  Future<void> _callbackHandler(String msg, Socket socket) async {
    if (msg.contains("<ERROR>")) {
      socket.close();
    }
  }

  void connectToServer() async {

    Socket.connect(ip, int.parse(port.toString()), timeout: const Duration(seconds: 5)).then((socket) {
      _sendData(socket);
      socket.listen((onData) async {
        await _callbackHandler(String.fromCharCodes(onData).trim(), socket);
      },
          onDone: () => {
            print("Done !"),
            socket.close(),
          },
          onError: (e) => {
            print(e.toString()),
            socket.close(),
          });
    }).catchError((e) {
      showSnackBar(context, "Can't reach the host ($ip:$port)");
      print(e.toString());
    });
  }
  connectToServer();
}