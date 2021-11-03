#include "MT_Int.h"

int main() {
    Int hello; // default
    std::cout << hello.valid() << '\n';
    hello.set(90);
    std::cout << hello.valid() << '\n';
    std::cout << hello.get() << '\n'; //get

    const Int bye(100);
    std::cout << bye.get() << '\n';

    Int copy_con(bye);
    std::cout << copy_con.get() << '\n';

    Int move_con(std::move(hello));
    std::cout << move_con.get() << '\n';

    Int copy_assign = bye;
    std::cout << copy_assign.get() << '\n';

    Int move_assign = std::move(copy_assign);
    std::cout << move_assign.get() << '\n';



    return 0;
}
