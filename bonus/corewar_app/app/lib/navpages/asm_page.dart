import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import '../network/compile_file.dart';

class Asm_page extends StatefulWidget {
  const Asm_page({Key? key}) : super(key: key);
  static String message = '';
  static bool isCompiling = false;

  @override
  _Asm_PageState createState() => _Asm_PageState();
}

class _Asm_PageState extends State<Asm_page> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: GestureDetector(
        child: Stack(
          children: [
            const AsmTextField(),
            Positioned(
                bottom: 0,
                left: MediaQuery.of(context).size.width / 7,
                child: Row(
                  children: [
                    FlatButton(
                      onPressed: () => compileButton(AsmTextField.name, AsmTextField.program, Asm_page.isCompiling, context),
                      child: const Text(
                        "Compile",
                        style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      color: Colors.black,
                    ),
                    Padding(
                      child: FlatButton(
                        onPressed: () => setState(() {
                          AsmTextField.name.text = '';
                          AsmTextField.program.text = '';
                        }),
                        child: const Text(
                          "Clear",
                          style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                        color: Colors.black,
                      ),
                      padding: EdgeInsets.only(left: MediaQuery.of(context).size.width / 5),
                    )
                  ],
                )),
          ],
        ),
        onTap: () {
          FocusScope.of(context).requestFocus(FocusNode());
        },
      ),
    );
  }
}

class AsmTextField extends StatefulWidget {
  const AsmTextField({Key? key}) : super(key: key);
  static TextEditingController name = TextEditingController();
  static TextEditingController program = TextEditingController();

  @override
  _AsmTextFieldState createState() => _AsmTextFieldState();
}

class _AsmTextFieldState extends State<AsmTextField> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SingleChildScrollView(
        child: ConstrainedBox(
          constraints: BoxConstraints(
            minWidth: MediaQuery.of(context).size.width,
            minHeight: MediaQuery.of(context).size.height,
          ),
          child: IntrinsicHeight(
            child: Center(
              child: Column(
                mainAxisSize: MainAxisSize.max,
                children: <Widget>[
                  Container(
                      width: 280,
                      height: 125,
                      padding: const EdgeInsetsDirectional.only(top: 60.0),
                      child: TextField(
                        controller: AsmTextField.name,
                        autocorrect: true,
                        decoration: const InputDecoration(hintText: 'Enter Name of file here', border: OutlineInputBorder()),
                        inputFormatters: <TextInputFormatter>[
                          FilteringTextInputFormatter.allow(RegExp("[a-zA-Z]")),
                          LengthLimitingTextInputFormatter(15),
                        ],
                      )),
                  Container(
                      width: MediaQuery.of(context).size.width / 1.2,
                      height: MediaQuery.of(context).size.height / 1.5,
                      padding: const EdgeInsetsDirectional.only(top: 30.0),
                      child: TextField(
                        controller: AsmTextField.program,
                        decoration: const InputDecoration(hintText: 'Enter your prog here', border: OutlineInputBorder()),
                        keyboardType: TextInputType.multiline,
                        maxLines: null,
                      )),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}

void showSnackBar(BuildContext context, String text) {
  final snackBar = SnackBar(
    content: Text(text),
    duration: const Duration(seconds: 2),
  );
  Scaffold.of(context).showSnackBar(snackBar);
}
