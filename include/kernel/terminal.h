#ifndef LUMAOS_TERMINAL_H_
#define LUMAOS_TERMINAL_H_

#pragma once

#define EXIT 6384018879
#define REBOOT 6952682532528
#define PWD 193467056
#define SHELL 210688646365
#define LS 5862500
#define CD 5862188
#define TOUCH 210690100968
#define MKDIR 210681637468
#define RM 5862692

void init_terminal();
void execute_command(char *command);

#endif