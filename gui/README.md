# GUI

This software uses Qt as interface manager.

## Editing

To edit, open a file *.ui* with QtDesigner editor.

## Coverting UI to PY

In order to make Qt interface usable by Python, the *.ui* file must be converted to a *.py* file.

You must have installed **tools master** package for python and then run the following command at folder *gui/qt*:

~~~
pyside-uic -o mainwindow.py mainwindow.ui
~~~

or run bash script *uitopy.sh* at folder *gui/qt*.