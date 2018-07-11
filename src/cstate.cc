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
 *      Sharda Dixit <sharda@cdac.in>
 * *********************************************************************** */

#include <cstate.h>
#include <msr.h>

#include <cmath>


CState::CState(std::string name, int msr_offset) {
    this->name = name;
    this->msr_offset = msr_offset;
}

void CState::init(int fd) {
    duration_before = read_msr(fd, msr_offset);
}

void CState::update(int fd, uint64_t tsc_delta) {
    uint64_t duration_after = read_msr(fd, msr_offset);
    double cstate = 100.0 * (duration_after - duration_before) / tsc_delta;
    percent_cstate = roundf(cstate * 100) / 100;
    duration_before = duration_after;
}

std::string CState::get_name() {
    return name;
}

double CState::get_percent_cstate() {
    return percent_cstate;
}
