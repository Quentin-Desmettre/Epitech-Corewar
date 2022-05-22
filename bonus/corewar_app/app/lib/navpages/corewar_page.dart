import 'package:corewar_app/network/cancel_queue.dart';
import 'package:corewar_app/network/queue_up.dart';
import 'package:corewar_app/sidebar.dart';
import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

class CorewarPage extends StatefulWidget {
  const CorewarPage({Key? key}) : super(key: key);
  static List<String> listChampion = [""];
  static String valueChoose = "";
  static bool inQueue = false;

  @override
  _CorewarPageSate createState() => _CorewarPageSate();
}

class _CorewarPageSate extends State<CorewarPage> {
  @override
  Widget build(BuildContext context) => Scaffold(
        body: GestureDetector(
          child: Scaffold(
            drawer: const SideBar(),
            body: Stack(children: const [SideBarButton(), CorewarPageWidgets()]),
          ),
          onTap: () {
            FocusScope.of(context).requestFocus(FocusNode());
          },
        ),
      );
}

class CorewarPageWidgets extends StatefulWidget {
  const CorewarPageWidgets({Key? key}) : super(key: key);

  @override
  State<CorewarPageWidgets> createState() => _CorewarPageWidgetsState();
}

class _CorewarPageWidgetsState extends State<CorewarPageWidgets> {
  late Future<String> message;

  Future<String> readString() async {
    final prefs = await SharedPreferences.getInstance();

    final List<String>? items = prefs.getStringList('Champion');

    if (items != null) {
      CorewarPage.listChampion = items;
    } else {
      CorewarPage.listChampion = [""];
    }
    CorewarPage.valueChoose = CorewarPage.listChampion[0];
    return ("Message");
  }

  @override
  void initState() {
    message = readString();
    super.initState();
  }

  void clearPreferences() async {
    final prefs = await SharedPreferences.getInstance();
    final success = await prefs.remove('Champion');
    CorewarPage.listChampion[0] = "";
    CorewarPage.valueChoose = CorewarPage.listChampion.isNotEmpty ? CorewarPage.listChampion[0] : "";
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.only(top: 50),
      child: Column(
        children: [
          const MyCoreImage(),
          Row(mainAxisAlignment: MainAxisAlignment.center, children: [
            Padding(
              padding: const EdgeInsets.only(left: 50, top: 30, bottom: 30),
              child: FutureBuilder<String>(
                  future: message,
                  builder: (BuildContext context, AsyncSnapshot<String> snapshot) {
                    return (DropdownButton(
                        value: CorewarPage.valueChoose,
                        hint: const Text("No Champion"),
                        onChanged: (newValue) {
                          setState(() {
                            CorewarPage.valueChoose = newValue.toString();
                          });
                        },
                        items: CorewarPage.listChampion.map((valueItem) {
                          return DropdownMenuItem(
                            value: valueItem,
                            child: Text(
                              valueItem,
                              softWrap: true,
                            ),
                          );
                        }).toList()));
                  }),
            ),
            Padding(
              padding: const EdgeInsets.only(left: 50),
              child: FlatButton(
                onPressed: () => setState(() {
                  clearPreferences();
                }),
                color: Colors.black,
                child: const Text(
                  "Clear",
                  style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),
                ),
              ),
            ),
          ]),
          Row(mainAxisAlignment: MainAxisAlignment.center, children: const [
              Padding(
                padding: EdgeInsets.only(
                  right: 10,
                ),
                child: PlayButton(),
              ),
              Padding(
                padding: EdgeInsets.only(
                  left: 10,
                ),
                child: CancelButton(),
              ),
            ],
          ),
        ],
      ),
    );
  }
}

class MyCoreImage extends StatelessWidget {
  const MyCoreImage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      width: MediaQuery.of(context).size.width / 1.2,
      height: MediaQuery.of(context).size.height / 1.9,
      child: Column(
        children: [
          Padding(
            padding: const EdgeInsets.only(top: 10),
            child: Image.asset("assets/corewar.png"),
          ),
          const Padding(
            padding: EdgeInsets.symmetric(vertical: 15),
            child: Text(
              "COREWAR",
              style: TextStyle(
                color: Colors.white,
                fontWeight: FontWeight.bold,
                fontSize: 40,
                backgroundColor: Colors.black,
              ),
            ),
          ),
        ],
      ),
    );
  }
}

class PlayButton extends StatelessWidget {
  const PlayButton({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return FlatButton(
      onPressed: () => queueUp(CorewarPage.valueChoose, context),
      color: Colors.black,
      child: const Text(
        "Play",
        style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),
      ),
    );
  }
}

class CancelButton extends StatelessWidget {
  const CancelButton({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return FlatButton(
      onPressed: () => cancelQueue(context),
      color: Colors.black,
      child: const Text(
        "Cancel",
        style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),
      ),
    );
  }
}
