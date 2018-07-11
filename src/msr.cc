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

#include <msr.h>

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

int open_msr(int core) {
    int fd;
    std::stringstream filename;
    filename << "/dev/cpu/" << core << "/msr";
    fd = open(filename.str().c_str(), O_RDONLY);
    if (fd < 0) {
        if (errno == ENXIO) {
            fprintf(stderr, "rdmsr: No CPU %d\n", core);
            exit(2);
        } else if (errno == EIO) {
            fprintf(stderr, "rdmsr: CPU %d doesn't support MSRs\n", core);
            exit(3);
        } else {
            perror("rdmsr:open");
            fprintf(stderr, "Trying to open %s\n", filename.str().c_str());
            exit(127);
        }
    }
    return fd;
}

uint64_t read_msr(int fd, int msr_offset) {
    uint64_t data;
    unsigned int highbit = 63, lowbit = 0, bits;

    if (pread(fd, &data, sizeof(data), msr_offset) != sizeof(data)) {
        perror("read_msr():pread");
        exit(127);
    }
    bits = highbit-lowbit+1;
    if ( bits < 64 ) {
        data >>= lowbit;
        data &= (1ULL << bits)-1;
    }
    return data;
}

void close_msr(int fd) {
    close(fd);
}
