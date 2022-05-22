import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'my_shared_preferences.dart';

class SettingsPage extends StatefulWidget {
  SettingsPage({Key? key}) : super(key: key);
  Future<String?> serverAddress = loadServerIP();
  Future<String?> serverPort = loadServerPort();

  @override
  _SettingsPageState createState() => _SettingsPageState();
}

class _SettingsPageState extends State<SettingsPage> {
  @override
  Widget build(BuildContext context) {
    ThemeData mode = Theme.of(context);

    return Scaffold(
      body: GestureDetector(
        onTap: () {
          FocusScope.of(context).requestFocus(FocusNode());
        },
        child: Scaffold(
          body: Column(
            children: const [ServerAddressBox(), ServerPortBox()],
          ),
          floatingActionButton: FloatingActionButton(
            onPressed: () {
              Navigator.pop(context);
            },
            backgroundColor: mode.brightness == Brightness.dark ? Colors.white : Colors.black,
            child: Icon(
              Icons.arrow_left_outlined,
              size: 50,
              color: mode.brightness == Brightness.dark ? Colors.black : Colors.white,
            ),
          ),
        ),
      ),
    );
  }
}

class ServerAddressBox extends StatefulWidget {
  const ServerAddressBox({Key? key}) : super(key: key);

  @override
  _ServerAddressBoxState createState() => _ServerAddressBoxState();
}

class _ServerAddressBoxState extends State<ServerAddressBox> {
  @override
  Widget build(BuildContext context) {
    ThemeData mode = Theme.of(context);

    return Padding(
      padding: const EdgeInsets.fromLTRB(20, 70, 20, 0),
      child: TextField(
        onChanged: (value) => storeServerIP(value),
        decoration: InputDecoration(
          filled: true,
          fillColor: Colors.white,
          hintText: "IP: 12.34.567.89",
          hintStyle: const TextStyle(color: Colors.grey),
          prefixIcon: Icon(Icons.http, color: mode.brightness == Brightness.dark ? Colors.blue.shade400 : Colors.blue.shade900),
          enabledBorder: OutlineInputBorder(
            borderRadius: BorderRadius.circular(16),
            borderSide: BorderSide(width: 3, color: mode.brightness == Brightness.dark ? Colors.blue.shade400 : Colors.blue.shade900),
          ),
          focusedBorder: OutlineInputBorder(
            borderRadius: BorderRadius.circular(16),
            borderSide: const BorderSide(color: Colors.blue, width: 5),
          ),
        ),
        keyboardType: TextInputType.multiline,
        textInputAction: TextInputAction.done,
        style: const TextStyle(color: Colors.black),
      ),
    );
  }
}

class ServerPortBox extends StatefulWidget {
  const ServerPortBox({Key? key}) : super(key: key);

  @override
  State<ServerPortBox> createState() => _ServerPortBoxState();
}

class _ServerPortBoxState extends State<ServerPortBox> {
  @override
  Widget build(BuildContext context) {
    ThemeData mode = Theme.of(context);

    return Padding(
      padding: const EdgeInsets.fromLTRB(20, 70, 20, 0),
      child: TextField(
        onChanged: (value) => storeServerPort(value),
        decoration: InputDecoration(
          filled: true,
          fillColor: Colors.white,
          hintText: "Port: 0000",
          hintStyle: const TextStyle(color: Colors.grey),
          prefixIcon: Icon(Icons.account_tree_rounded, color: mode.brightness == Brightness.dark ? Colors.blue.shade400 : Colors.blue.shade900),
          enabledBorder: OutlineInputBorder(
            borderRadius: BorderRadius.circular(16),
            borderSide: BorderSide(width: 3, color: mode.brightness == Brightness.dark ? Colors.blue.shade400 : Colors.blue.shade900),
          ),
          focusedBorder: OutlineInputBorder(
            borderRadius: BorderRadius.circular(16),
            borderSide: const BorderSide(color: Colors.blue, width: 5),
          ),
        ),
        keyboardType: TextInputType.multiline,
        textInputAction: TextInputAction.done,
        style: const TextStyle(color: Colors.black),
      ),
    );
  }
}
