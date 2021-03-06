//
// Created by ekvvn on 26.08.17.
//

#ifndef USINGTMP_TEST5_H
#define USINGTMP_TEST5_H

#include <iostream>
#include <memory>
#include <boost/di.hpp>

namespace test5 {
    namespace di = boost::di;

    struct interface {
        virtual ~interface() noexcept = default;
        virtual int dummy() = 0;
    };
    struct implementation : interface {
        int dummy() override { return 5; }
    };

    auto module = [] {
        // clang-format off
        return di::make_injector(
                di::bind<interface>().to<implementation>()
        );
        // clang-format on
    };

    class run {
        static auto test() {
            auto injector = di::make_injector(module());
            return injector.create<std::unique_ptr<interface>>();
        }

    public:
        static void main() {
            std::cout << test()->dummy() << std::endl;
        }
    };
}


#endif //USINGTMP_TEST5_H
