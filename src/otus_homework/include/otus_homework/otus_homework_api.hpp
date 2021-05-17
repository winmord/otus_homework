#pragma once
// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
#define OTUS_HOMEWORK_HELPER_DLL_IMPORT __declspec(dllimport)
#define OTUS_HOMEWORK_HELPER_DLL_EXPORT __declspec(dllexport)
#define OTUS_HOMEWORK_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define OTUS_HOMEWORK_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define OTUS_HOMEWORK_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define OTUS_HOMEWORK_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define OTUS_HOMEWORK_HELPER_DLL_IMPORT
#define OTUS_HOMEWORK_HELPER_DLL_EXPORT
#define OTUS_HOMEWORK_HELPER_DLL_LOCAL
#endif
#endif

// Now we use the generic helper definitions above to define OTUS_HOMEWORK_API and OTUS_HOMEWORK_LOCAL.
// OTUS_HOMEWORK_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// OTUS_HOMEWORK_LOCAL is used for non-api symbols.

#ifdef OTUS_HOMEWORK_DLL // defined if otus_homework is compiled as a DLL
#ifdef OTUS_HOMEWORK_DLL_EXPORTS // defined if we are building the otus_homework DLL (instead of using it)
#define OTUS_HOMEWORK_API OTUS_HOMEWORK_HELPER_DLL_EXPORT
#else
#define OTUS_HOMEWORK_API OTUS_HOMEWORK_HELPER_DLL_IMPORT
#endif // OTUS_HOMEWORK_DLL_EXPORTS
#define OTUS_HOMEWORK_LOCAL OTUS_HOMEWORK_HELPER_DLL_LOCAL
#else // OTUS_HOMEWORK_DLL is not defined: this means OTUS_HOMEWORK is a static lib.
#define OTUS_HOMEWORK_API
#define OTUS_HOMEWORK_LOCAL
#endif // OTUS_HOMEWORK_DLL

