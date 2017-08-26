//
// Created by ekvvn on 26.08.17.
//

#ifndef USINGTMP_TEST1_H
#define USINGTMP_TEST1_H

#include <iostream>
#include <boost/di.hpp>

namespace test1 {
    namespace di = boost::di;

    class run {
        static auto test() {
            auto injector = di::make_injector();
            return injector.create<int>();
        }

    public:
        static void main() {
            std::cout << test() << std::endl;
        }
    };
}

#endif //USINGTMP_TEST1_H
