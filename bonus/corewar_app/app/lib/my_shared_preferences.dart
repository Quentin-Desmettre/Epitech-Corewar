import 'package:get/get.dart';
import 'package:get/get_core/src/get_main.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:uuid/uuid.dart';

void storeServerIP(String ip) async {
  SharedPreferences sp = await SharedPreferences.getInstance();

  sp.setString("serverIP", ip);
}

Future<String?> loadServerIP() async {
  SharedPreferences sp = await SharedPreferences.getInstance();

  return (sp.getString("serverIP"));
}

void storeServerPort(String port) async {
  SharedPreferences sp = await SharedPreferences.getInstance();

  sp.setString("serverPort", port);
}

Future<String?> loadServerPort() async {
  SharedPreferences sp = await SharedPreferences.getInstance();

  return (sp.getString("serverPort"));
}

Future<String?> loadUUID() async {
  SharedPreferences sp = await SharedPreferences.getInstance();

  return (sp.getString("UUID"));
}

class AuthController {
  static genUuid() async {
    final SharedPreferences sp = await SharedPreferences.getInstance();
    Uuid uuidGen = const Uuid();
    String uuid = uuidGen.v1();

    sp.setString('UUID', uuid.toString());
  }

  Future<bool> tryUuid() async {
    SharedPreferences sp = await SharedPreferences.getInstance();

    if (!sp.containsKey("UUID")) {
      return false;
    } else {
      return true;
    }
  }
}