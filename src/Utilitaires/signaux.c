/**
 * \file signaux.c
 */
#include "signaux.h"

struct sigaction handle_signal (int signal, void (*handler) (int), int flags)
{
    struct sigaction act;
    struct sigaction old;
    act.sa_handler = handler;
    act.sa_flags = flags;
    CHECK (sigemptyset (&act.sa_mask), "ERREUR SIGEMPTYSET");
    CHECK (sigaction (signal, &act, &old), "ERREUR SIGACTION");
    return old;
}

struct sigaction ignore_signal (int signal, int flags)
{
    return handle_signal (signal, SIG_IGN, flags);
}
