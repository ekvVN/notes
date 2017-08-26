//
// Created by ekvvn on 26.08.17.
//

#pragma once

#include <boost/di.hpp>
#include <iostream>

namespace test3 {

    namespace di = boost::di;

    auto my_int = [] {};

    struct c {
        BOOST_DI_INJECT(c, (named = my_int) int i) : i(i) {}

        int i = 0;
    };

    class run {
        static auto test() {
            // clang-format off
            auto injector = di::make_injector(
                    di::bind<int>().named(my_int).to(3)
            );
            // clang-format on

            return injector.create<c>().i;
        }

    public:
        static void main() {
            std::cout << test() << std::endl;
        }
    };

}
