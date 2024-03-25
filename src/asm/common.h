//          Copyright Nikita Kniazev 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/predef/architecture.h>
#include <boost/predef/other/wordsize.h>
#include <boost/predef/os.h>

// Predef bug https://github.com/boostorg/predef/issues/127
#if BOOST_ARCH_MIPS && !defined(__mips64)
#  undef BOOST_ARCH_WORD_BITS
#  define BOOST_ARCH_WORD_BITS 32
#endif
// Predef bug https://github.com/boostorg/predef/issues/135
#if BOOST_ARCH_RISCV && defined(__riscv_xlen)
#  undef BOOST_ARCH_WORD_BITS
#  define BOOST_ARCH_WORD_BITS __riscv_xlen
#endif

#if defined(BOOST_CONTEXT_ARCH)
// Defined by user
#elif BOOST_ARCH_X86_64
# define BOOST_CONTEXT_ARCH x86_64
#elif BOOST_ARCH_X86_32
# undef i386
# define BOOST_CONTEXT_ARCH i386
#elif BOOST_ARCH_ARM && BOOST_ARCH_WORD_BITS == 64
# define BOOST_CONTEXT_ARCH arm64
#elif BOOST_ARCH_ARM && BOOST_ARCH_WORD_BITS == 32
# define BOOST_CONTEXT_ARCH arm
#elif BOOST_ARCH_MIPS && BOOST_ARCH_WORD_BITS == 64
# define BOOST_CONTEXT_ARCH mips64
#elif BOOST_ARCH_MIPS && BOOST_ARCH_WORD_BITS == 32
# define BOOST_CONTEXT_ARCH mips32
#elif BOOST_ARCH_PPC_64
# define BOOST_CONTEXT_ARCH ppc64
#elif BOOST_ARCH_PPC
# define BOOST_CONTEXT_ARCH ppc32
#elif BOOST_ARCH_RISCV && BOOST_ARCH_WORD_BITS == 64
# define BOOST_CONTEXT_ARCH riscv64
#elif BOOST_ARCH_RISCV && BOOST_ARCH_WORD_BITS == 32
# define BOOST_CONTEXT_ARCH riscv32
#elif BOOST_ARCH_SYS390
# define BOOST_CONTEXT_ARCH s390x
#elif BOOST_ARCH_SPARC && BOOST_ARCH_WORD_BITS == 64
# define BOOST_CONTEXT_ARCH sparc64
#elif BOOST_ARCH_SPARC && BOOST_ARCH_WORD_BITS == 32
# define BOOST_CONTEXT_ARCH sparc32
#elif BOOST_ARCH_LOONGARCH
# define BOOST_CONTEXT_ARCH loongarch64
#else
# error "Unsupported architecture"
#endif

#if defined(BOOST_CONTEXT_ABI)
// Defined by user
#elif defined(BOOST_ARCH_ARM_AVAILABLE)
# define BOOST_CONTEXT_ABI aapcs
#elif defined(BOOST_ARCH_MIPS_AVAILABLE) && BOOST_ARCH_WORD_BITS == 64
# define BOOST_CONTEXT_ABI n64
#elif defined(BOOST_ARCH_MIPS_AVAILABLE) && BOOST_ARCH_WORD_BITS == 32
# define BOOST_CONTEXT_ABI o32
#elif defined(BOOST_OS_WINDOWS_AVAILABLE)
# define BOOST_CONTEXT_ABI ms
#else
# define BOOST_CONTEXT_ABI sysv
#endif

#if defined(BOOST_CONTEXT_BINFMT)
// Defined by user
#elif defined(BOOST_OS_WINDOWS_AVAILABLE)
# define BOOST_CONTEXT_BINFMT pe
#elif defined(BOOST_OS_AIX_AVAILABLE)
# define BOOST_CONTEXT_BINFMT xcoff
#elif defined(BOOST_OS_MACOS_AVAILABLE)
# define BOOST_CONTEXT_BINFMT macho
#else
# define BOOST_CONTEXT_BINFMT elf
#endif

#if defined(BOOST_CONTEXT_ASSEMBLER)
// Defined by user
#elif defined(__GNUC__)
# define BOOST_CONTEXT_ASSEMBLER gas
# define BOOST_CONTEXT_ASM_SUFFIX .S
#elif defined(BOOST_ARCH_ARM_AVAILABLE)
# define BOOST_CONTEXT_ASSEMBLER armasm
# define BOOST_CONTEXT_ASM_SUFFIX .asm
#elif defined(BOOST_OS_WINDOWS_AVAILABLE)
# define BOOST_CONTEXT_ASSEMBLER masm
# define BOOST_CONTEXT_ASM_SUFFIX .asm
#else
# define BOOST_CONTEXT_ASSEMBLER gas
# define BOOST_CONTEXT_ASM_SUFFIX .S
#endif

#include <boost/config/helper_macros.hpp>

#define BOOST_CONTEXT_ASM_INCLUDE(name) \
  BOOST_STRINGIZE(BOOST_JOIN(BOOST_JOIN(BOOST_JOIN(BOOST_JOIN(BOOST_JOIN(BOOST_JOIN(BOOST_JOIN(BOOST_JOIN(BOOST_JOIN( \
    name, _), BOOST_CONTEXT_ARCH), _), BOOST_CONTEXT_ABI), _), BOOST_CONTEXT_BINFMT), _), BOOST_CONTEXT_ASSEMBLER), BOOST_CONTEXT_ASM_SUFFIX))

