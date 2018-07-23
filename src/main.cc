/* **********************************************************************
 * Copyright 2018, C-DAC.
 * All Rights Reserved.
 *
 * PowerAna is a free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PowerAna is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors:
 * 	Sharda Dixit <sharda@cdac.in>
 * *********************************************************************** */

#include <powerana.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <iostream>

int main(int argc, char **argv) {
    PowerAna pa;
    pid_t pid;
    int status;

    if (pa.init() != 0) {
        std::cout << "Error in HPMA Initialization.\n";
        return -1;
    }

    if ((pid = fork()) < 0) {
        std::cout << "Fork error\n";
        exit(-1);
    } else if (pid == 0) {      // Child process
        if (execvp(argv[1], argv+1) < 0) {
            std::cout << "Execvp error.\n";
        }
    } else {                    // Parent process
        while (!waitpid(pid, &status, WNOHANG)) {
            pa.loop();
        }
    }

    pa.cleanup();

    std::cout << "Normal exit.\n";
    return 0;
}
