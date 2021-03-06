#pragma once

#define PROG_MAJOR_VERSION 0
#define PROG_MINOR_VERSION 0
#define PROG_PATCH_VERSION 1

#ifndef TOSTRING
#define _TOSTRING(x) #x
#define TOSTRING(x) _TOSTRING(x)
#endif

#define PROGRAM_VERSION TOSTRING(PROG_MINOR_VERSION) "." TOSTRING(PROG_MINOR_VERSION) "." TOSTRING(PROG_PATCH_VERSION)

