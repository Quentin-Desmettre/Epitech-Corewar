import 'package:flutter/material.dart';

import 'app_theme.dart';
import 'settings_page.dart';

class SideBar extends StatefulWidget {
  const SideBar({Key? key}) : super(key: key);

  @override
  _SideBarState createState() => _SideBarState();
}

class _SideBarState extends State<SideBar> {
  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Stack(
      children: [
        Align(
          alignment: Alignment.centerLeft,
          child: Stack(
            children: [
              Container(margin: const EdgeInsets.fromLTRB(20, 0, 0, 110), child: const SettingsButton()),
              Container(margin: const EdgeInsets.fromLTRB(20, 110, 0, 0), child: const DarkModeButton()),
            ],
          ),
        )
      ],
    );
  }
}

class SideBarButton extends StatelessWidget {
  const SideBarButton({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Center(
      widthFactor: 0.5,
      child: Padding(
        padding: const EdgeInsets.only(left: 20),
        child: IconButton(
          icon: const Icon(Icons.drag_indicator_rounded, size: 30),
          onPressed: () => {Scaffold.of(context).openDrawer()},
        ),
      ),
    );
  }
}

class SettingsButton extends StatelessWidget {
  const SettingsButton({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return IconButton(
        icon: const Icon(Icons.settings),
        iconSize: 40,
        onPressed: () => {
              Navigator.push(context, MaterialPageRoute(builder: (context) => SettingsPage())),
            });
  }
}
