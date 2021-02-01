// The MIT License (MIT)
//
// Copyright (c) 2019-2021 The Raygun Authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#pragma once

#define RAYGUN_XSTR(x) RAYGUN_STR(x)
#define RAYGUN_STR(x) #x

#define RAYGUN_MAKE_VERSION(major, minor, patch) "v" RAYGUN_XSTR(major) "." RAYGUN_XSTR(minor) "." RAYGUN_XSTR(patch)

#ifdef NDEBUG
    #define RAYGUN_BREAK()
#else
    #ifdef _WIN32
        #define RAYGUN_BREAK() __debugbreak()
    #else
        #define RAYGUN_BREAK() ::std::raise(SIGTRAP)
    #endif
#endif

// Uncomment this if you are building Raygun as a shared library.
//#ifdef _WIN32
//    #ifdef RAYGUN_DLL_EXPORT
//        #define RAYGUN_DLL_API __declspec(dllexport)
//    #else
//        #define RAYGUN_DLL_API __declspec(dllimport)
//    #endif
//#endif

#ifndef RAYGUN_DLL_API
    #define RAYGUN_DLL_API
#endif
