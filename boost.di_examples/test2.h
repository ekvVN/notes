//
// Created by ekvvn on 26.08.17.
//

#ifndef USINGTMP_TEST2_H
#define USINGTMP_TEST2_H

#include <iostream>
#include <boost/di.hpp>

namespace test2 {
    namespace di = boost::di;

    class run {
        static auto test() {
            auto injector = di::make_injector(
                    di::bind<int>().to(2)
            );

            return injector.create<int>();
        }

    public:
        static void main() {
            std::cout << test() << std::endl;
        }
    };
}

#endif //USINGTMP_TEST2_H
