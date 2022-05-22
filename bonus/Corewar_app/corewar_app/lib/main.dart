import 'package:corewar_app/navpages/navBar.dart';
import 'package:flutter/material.dart';
import 'package:get/get_navigation/src/root/get_material_app.dart';
import 'package:provider/provider.dart';

import 'app_theme.dart';
import 'my_shared_preferences.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) => ChangeNotifierProvider(
      create: (context) => ThemeProvider(),
      builder: (context, _) {
        final themeProvider = Provider.of<ThemeProvider>(context);
        return GetMaterialApp(title: 'Corewar', debugShowCheckedModeBanner: false, themeMode: themeProvider.themeMode, theme: AppTheme.lightTheme, darkTheme: AppTheme.darkTheme, home: const NavBar());
      });
}
