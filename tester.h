#ifndef TESTER_H
#define TESTER_H

#include <cstdlib>
#include <iostream>

#define ASSERT_EQ(x, y)                                                        \
    if ((x) != (y))                                                            \
    {                                                                          \
        std::cerr << "Error: " << #x << " != " << #y << " at " << __FILE__     \
                  << ":" << __LINE__ << std::endl;                             \
        std::exit(EXIT_FAILURE);                                               \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        std::cout << "PASS!" << std::endl;                                     \
    }

#define ASSERT_TRUE(x)                                                         \
    if (!x)                                                                    \
    {                                                                          \
        std::cerr << "Error: " << #x << " != true at " << __FILE__ << ":"      \
                  << __LINE__ << std::endl;                                    \
        std::exit(EXIT_FAILURE);                                               \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        std::cout << "PASS!" << std::endl;                                     \
    }

#endif /* TESTER_H */
