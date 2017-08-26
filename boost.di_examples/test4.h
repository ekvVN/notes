//
// Created by ekvvn on 26.08.17.
//

#ifndef USINGTMP_TEST4_H
#define USINGTMP_TEST4_H

#include <iostream>
#include <memory>
#include <boost/di.hpp>

namespace test4 {
    namespace di = boost::di;

    struct interface {
        virtual ~interface() noexcept = default;

        virtual int dummy() = 0;
    };

    struct implementation : interface {
        int dummy() override { return 4; }
    };

    class run {
        static auto test() {
            // clang-format off
            auto injector = di::make_injector(
                    di::bind<interface>().to<implementation>()
            );
            // clang-format on

            return injector.create<std::unique_ptr<interface>>();
        }

    public:
        static void main() {
            std::cout << test()->dummy() << std::endl;
        }
    };
}

#endif //USINGTMP_TEST4_H
