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

#include <core.h>
#include <msr.h>
#include <msr_headers.h>


Core::Core(int core_id) {
    this->core_id = core_id;

    cc_states.push_back(CState("CC3", MSR_CORE_C3_RESIDENCY));
    cc_states.push_back(CState("CC6", MSR_CORE_C6_RESIDENCY));
    cc_states.push_back(CState("CC7", MSR_CORE_C7_RESIDENCY));
}

int Core::get_core_id() {
    return core_id;
}

void Core::init() {
    int fd = open_msr(core_id);
    tsc_before = read_msr(fd, MSR_TSC);
    std::vector<CState>::iterator it;
    for (it = cc_states.begin(); it != cc_states.end(); it++)
        it->init(fd);
    if (fd)
        close_msr(fd);
}

void Core::update() {
    int fd = open_msr(core_id);
    uint64_t tsc_after = read_msr(fd, MSR_TSC);
    if (tsc_after == tsc_before)
        return;

    std::vector<CState>::iterator it;
    for (it = cc_states.begin(); it != cc_states.end(); it++)
        it->update(fd, tsc_after-tsc_before);

    tsc_before = tsc_after;
    if (fd)
        close_msr(fd);
}
