import 'package:corewar_app/navpages/asm_page.dart';
import 'package:corewar_app/navpages/corewar_page.dart';
import 'package:corewar_app/navpages/log_page.dart';
import 'package:corewar_app/my_shared_preferences.dart';
import 'package:flutter/material.dart';

class NavBar extends StatefulWidget {
  const NavBar({Key? key}) : super(key: key);

  @override
  _NavBarState createState() => _NavBarState();
}

class _NavBarState extends State<NavBar> {
  List pages = [const CorewarPage(), const Asm_page(), LogPage()];
  int currentIndex = 0;

  void onTap(int index) async {
    setState(() {
      currentIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: pages[currentIndex],
      bottomNavigationBar: BottomNavigationBar(
        onTap: onTap,
        currentIndex: currentIndex,
        type: BottomNavigationBarType.fixed,
        showUnselectedLabels: false,
        items: const [
          BottomNavigationBarItem(label: "Corewar", icon: Icon(Icons.videogame_asset_rounded)),
          BottomNavigationBarItem(label: "ASM", icon: Icon(Icons.build)),
          BottomNavigationBarItem(label: "LOG", icon: Icon(Icons.access_time_outlined)),
        ],
      ),
    );
  }
}
