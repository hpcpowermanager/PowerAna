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

#ifndef CSTATE_H_
#define CSTATE_H_

#include <iostream>
#include <string>

struct CState {
 public:
    CState(std::string name, int msr_offset);
    void init(int fd);
    void update(int fd, uint64_t tsc_delta);
    std::string get_name();
    double get_percent_cstate();

 private:
    uint64_t duration_before;
    double percent_cstate;
    std::string name;
    int msr_offset;
};

#endif  // CSTATE_H_
