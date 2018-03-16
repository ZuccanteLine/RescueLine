//
// Created by davide on 07/03/18.
//


#include <array>
#include <memory>
#include <sstream>
#include <iostream>
#include <python2.7/Python.h>

#ifndef UART_CPP
#define UART_CPP

using std::cout;
using std::endl;
using std::string;

class UartConnection {
public:
    UartConnection(int baudrate, string device) {
        Py_Initialize();

        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\".\")");

        PyObject *script = PyImport_Import(PyString_FromString("UartPY"));
        PyErr_Print();

        PyObject *dic = PyModule_GetDict(script);
        PyObject *initf = PyDict_GetItemString(dic, "init");

        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, PyString_FromString(("/dev/" + device).c_str()));
        PyTuple_SetItem(args, 1, PyInt_FromLong(baudrate));
        PyTuple_SetItem(args, 2, PyFloat_FromDouble(3));

        PyObject *slave = NULL;
        while (slave == NULL) {
            usleep(5e5);
            slave = PyObject_CallObject(initf, args);
            PyErr_Clear();
        }

        read = PyDict_GetItemString(dic, "read");
        write = PyDict_GetItemString(dic, "write");
        closef = PyDict_GetItemString(dic, "close");
//        lcd_write = PyDict_GetItemString(dic, "lcdWrite");
        PyTuple_SetItem(readargs, 0, slave);
        PyTuple_SetItem(writeargs, 0, slave);
    }

    string _read() {
        string s = PyString_AsString(PyObject_CallObject(read, readargs));
        PyErr_Print();
        return s;
    }

    void _write(string cmd) {

        for(int i=0; i<9; i++) cout << (int)cmd.at(i) << "\t";
        cout << endl;

//        cout << "send: " + cmd << endl;
        PyTuple_SetItem(writeargs, 1, PyByteArray_FromStringAndSize(cmd.c_str(), 9));
//        cout << "sending" << endl;
        PyObject_CallObject(write, writeargs);
//        cout << "sending" << endl;
        PyErr_Print();
//        cout << "sent" << endl;
    }

//    void lcd(string mex) {
//        PyObject_CallObject(lcd_write, PyString_FromString(mex.c_str()));
//    }

    void close() {
        PyObject_CallObject(closef, readargs);
        PyErr_Print();
    }

private:
    PyObject *closef;
    PyObject *read;
    PyObject *write;
//    PyObject *lcd_write;

    PyObject *readargs = PyTuple_New(1);
    PyObject *writeargs = PyTuple_New(2);

//    string findPort() {
//        string list = UartConnection::exec("ls /dev/");
//        stringstream ports(list);
//        string port;
//        string slave32;
//        while (ports >> port) {
//            if (port.find("ACM") != string::npos)
//                slave32 = port;ttyACM0
//        }
//        return slave32;
//    }
//
//    void replace(string *str, char a, char b) {
//        for (int i = 0; i < str->dataSize(); ++i) {
//            if ((*str)[i] == a) (*str)[i] = b;
//        }
//    }
//     static string exec(const char *cmd) {
//        array<char, 128> buffer;
//        string result;
//        shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
//        if (!pipe) throw std::runtime_error("popen() failed!");
//        while (!feof(pipe.get())) {
//            if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
//                result += buffer.data();
//        }
//        return result;
//    }

};

//int main(){
//    UartConnection uartConnection(115200, "ttyACM0");
//    uartConnection._write("ciao");
//    cout << uartConnection._read() << endl;
//}

#endif