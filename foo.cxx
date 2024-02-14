module;
#include <string>
#include <iostream>
export module foo;


namespace training {
    export void hello()
    {
        std::cout << "Hello World" << std::endl;
    }

    export int ret0()
    {
        return 0;
    }
}

