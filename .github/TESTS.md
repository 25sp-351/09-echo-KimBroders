Test default:
    input (Terminal 1):    ./threaded.exe
    input (Terminal 2):    telnet 127.0.0.1 8888
    expected output:
        Binding to port 8888
        accepted connection on 4
        Handling connection on 4
        done with connection 4

Test printing ('-v'):
    input (Terminal 1):    ./threaded.exe -v
    input (Terminal 2):    telnet 127.0.0.1 8888
    expected output:
        Binding to port 8888
        accepted connection on 4
        Handling connection on 4
        hello
        done with connection 4

Test port selection ('-p 4493'):
    input (Terminal 1):    ./threaded.exe -p 4493
    input (Terminal 2):    telnet 127.0.0.1 4493
    expected output:
        Binding to port 4493
        accepted connection on 4
        Handling connection on 4
        done with connection 4

Test port selection and printing ('-p 4493 -v'):
    input (Terminal 1):    ./threaded.exe -p 4493 -v
    input (Terminal 2):    telnet 127.0.0.1 4493
    expected output:
        Binding to port 4493
        accepted connection on 4
        Handling connection on 4
        hello
        done with connection 4

Test printing and port selection ('-v -p 4493'):
    input (Terminal 1):    ./threaded.exe -v -p 4493
    input (Terminal 2):    telnet 127.0.0.1 4493
    expected output:
        Binding to port 4493
        accepted connection on 4
        Handling connection on 4
        hello
        done with connection 4

Test closing a connection.
    input (Terminal 1):    ./threaded.exe
    input (Terminal 2):    
        telnet 127.0.0.1 8888
        hello
        ^]
        close
    expected output:
        Binding to port 8888
        accepted connection on 4
        Handling connection on 4
        done with connection 4

Test opening a connection after closing a previous connection.
    input (Terminal 1):    ./threaded.exe
    input (Terminal 2):    
        telnet 127.0.0.1 8888
        hello
        ^]
        close
        telnet 127.0.0.1 8888
    expected output:
        Binding to port 8888
        accepted connection on 4
        Handling connection on 4
        done with connection 4
        accepted connection on 5
        Handling connection on 5

Test two simultaneous connections.
    input (Terminal 1):    ./threaded.exe
    input (Terminal 2):    telnet 127.0.0.1 8888
    input (Terminal 3):    telnet 127.0.0.1 8888
    input (Terminal 2):    hello
    input (Terminal 3):    how are you?
    input (Terminal 2):
        ^]
        close
    input (Terminal 3):
        ^]
        close
    expected output:
        Binding to port 8888
        accepted connection on 4
        Handling connection on 4
        accepted connection on 5
        Handling connection on 5
        done with connection 4
        done with connection 5