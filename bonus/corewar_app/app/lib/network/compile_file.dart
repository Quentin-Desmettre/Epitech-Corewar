import 'dart:async';
import 'dart:io';

import 'package:corewar_app/my_shared_preferences.dart';
import 'package:corewar_app/navpages/asm_page.dart';
import 'package:corewar_app/navpages/corewar_page.dart';
import 'package:shared_preferences/shared_preferences.dart';

void writeString() async {
  final prefs = await SharedPreferences.getInstance();
  await prefs.setStringList('Champion', CorewarPage.listChampion);
}

void newChamp(String newChamp) {
  if (CorewarPage.listChampion[0] == "") {
    CorewarPage.listChampion[0] = newChamp;
    CorewarPage.valueChoose = newChamp;
  }
  for (int i = 0; i < CorewarPage.listChampion.length; i++) {
    if (CorewarPage.listChampion[i] == newChamp) {
      return;
    }
  }
  CorewarPage.listChampion.add(newChamp);
}

Future<bool> sendRawFile(String filename, String filesize, String filecontent, context, ip, port) async {
  String? uuid = await loadUUID();

  void _sendFileData(Socket socket) async {
    socket.write("<COMPILE><SEPARATOR>$filename<SEPARATOR>$uuid");
  }

  void _sendFile(Socket socket) {
    socket.write(filecontent);
  }

  void _handleError(String err) {
    showSnackBar(context, err);
    Asm_page.isCompiling = false;
  }

  void _onSuccess() {
    showSnackBar(context, "$filename successfully sent and compiled !");
    newChamp("$filename.cor");
    writeString();
    Asm_page.isCompiling = false;
  }

  Future<void> _callbackHandler(String msg, Socket socket) async {
    if (msg == "<GOTCHA>") {
      _sendFile(socket);
      socket.write("<EOS>");
    }
    if (msg.contains("<ERROR>")) {
      _handleError(msg);
      socket.close();
    }
    if (msg.contains("<COMPILED>")) {
      _onSuccess();
      socket.close();
    }
  }

  void connectToServer() async {

    Socket.connect(ip, int.parse(port.toString()), timeout: const Duration(seconds: 5)).then((socket) {
      _sendFileData(socket);
      socket.listen((onData) async {
        await _callbackHandler(String.fromCharCodes(onData).trim(), socket);
      },
          onDone: () => {
                socket.close(),
                Asm_page.isCompiling = false,
              },
          onError: (e) => {
                print(e.toString()),
                socket.close(),
                Asm_page.isCompiling = false,
              });
    }).catchError((e) {
      showSnackBar(context, "Can't reach the host ($ip:$port)");
      print(e.toString());
      Asm_page.isCompiling = false;
    });
  }
  connectToServer();
  return true;
}

Future compileButton(name, program, isCompiling, context) async {
  final authController = AuthController();
  String? ip = await loadServerIP();
  String? port = await loadServerPort();

  if (isCompiling) {
    showSnackBar(context, "Already compiling...");
    return;
  }
  if (name.text == '' || program.text == '') {
    showSnackBar(context, "Missing field...");
    return;
  }
  if (ip == null || port == null) {
    showSnackBar(context, "No IP / Port specified !");
    return;
  }
  if (await authController.tryUuid() == false) {
    await AuthController.genUuid();
  }

  Asm_page.isCompiling = true;
  await sendRawFile(name.text, program.text.length.toString(), program.text, context, ip, port);
}
