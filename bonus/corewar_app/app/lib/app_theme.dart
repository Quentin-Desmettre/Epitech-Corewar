import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class DarkModeButton extends StatelessWidget {
  const DarkModeButton({Key? key}) : super(key: key);
  static bool darkMode = false;

  @override
  Widget build(BuildContext context) {
    ThemeData mode = Theme.of(context);
    darkMode = (mode.brightness == Brightness.light) ? false : true;

    return IconButton(
      icon: const Icon(Icons.dark_mode),
      iconSize: 40,
      onPressed: () {
        final provider = Provider.of<ThemeProvider>(context, listen: false);
        darkMode = !darkMode;
        provider.toggleTheme(darkMode);
      },
    );
  }
}

class ThemeProvider extends ChangeNotifier {
  ThemeMode themeMode = ThemeMode.system;

  bool get isDarkMode => themeMode == ThemeMode.dark;

  void toggleTheme(bool isOn) {
    themeMode = isOn ? ThemeMode.dark : ThemeMode.light;
    notifyListeners();
  }
}

class AppTheme {
  static final darkTheme = ThemeData(
      scaffoldBackgroundColor: Colors.grey.shade800,
      bottomNavigationBarTheme:
          const BottomNavigationBarThemeData(selectedItemColor: Colors.white),
      colorScheme: const ColorScheme.dark());
  static final lightTheme = ThemeData(
      scaffoldBackgroundColor: Colors.white,
      bottomNavigationBarTheme:
          const BottomNavigationBarThemeData(selectedItemColor: Colors.black),
      colorScheme: const ColorScheme.light());
}
