//          Copyright Nikita Kniazev 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

extern "C" {
extern void __splitstack_getcontext(void *);
}

int main(int argc, char **)
{
    if (argc < 0) __splitstack_getcontext((void *)0);
    return 0;
}
