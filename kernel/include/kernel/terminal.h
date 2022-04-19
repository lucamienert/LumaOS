#ifndef LUMAOS_TERMINAL_H_
#define LUMAOS_TERMINAL_H_

#pragma once

// Commands hashed for switch
#define EXIT 6384018879
#define REBOOT 6952682532528
#define CD 5862188
#define PWD 193467056

void init_terminal();
void execute_command(char *command);

#endif