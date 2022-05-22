import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter/cupertino.dart';
import 'package:path_provider/path_provider.dart';

Future<String> get _localPath async {
  final directory = await getApplicationDocumentsDirectory();

  return directory.path;
}

Future<File> _localFile(String filename) async {
  final path = await _localPath;
  return File('$path/counter.txt');
}

Future<Uint8List> readData(String filename) async {
  final file = await _localFile(filename);
  final Uint8List data = await file.readAsBytes();

  return (data);
}

Future<void> writeData(String filename, String content, FileMode mode) async {
  final file = await _localFile(filename);

  await file.writeAsBytes(content.codeUnits, mode: mode);
}