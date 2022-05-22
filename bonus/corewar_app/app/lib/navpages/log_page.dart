import 'package:corewar_app/network/cancel_queue.dart';
import 'package:flutter/material.dart';

class LogPage extends StatefulWidget {
  const LogPage({Key? key}) : super(key: key);
  static ValueNotifier<String> log = ValueNotifier("");

  @override
  _LogPageState createState() => _LogPageState();
}

class _LogPageState extends State<LogPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: GestureDetector(
        child: Scaffold(
          appBar: AppBar(
            backgroundColor: Colors.white,
            title: const Text(
              'COREWAR LOG',
              style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold),
            ),
            actions: [
              IconButton(
                  onPressed: () => cancelQueue(context),
                  icon: const Icon(
                    Icons.cancel,
                    color: Colors.deepOrange,
                    size: 30,
                  ))
            ],
          ),
          body: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              Expanded(
                child: Container(
                  color: Colors.black,
                  child: Padding(
                    padding: const EdgeInsets.only(left: 10),
                    child: SingleChildScrollView(
                      child: ValueListenableBuilder(
                          valueListenable: LogPage.log,
                          builder: (context, value, widget) {
                            return Text(
                              value.toString(),
                              style: const TextStyle(color: Colors.white, fontWeight: FontWeight.bold, height: 2),
                            );
                          }),
                    ),
                  ),
                ),
              ),
            ],
          ),
        ),
        onTap: () {
          FocusScope.of(context).requestFocus(FocusNode());
        },
      ),
    );
  }
}
