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

#ifndef CORE_H_
#define CORE_H_

#include <cstate.h>

#include <vector>

class Core {
 public:
    explicit Core(int core_id);
    int get_core_id();
    std::vector<CState> cc_states;
    void init();
    void update();

 private:
    int core_id;
    uint64_t tsc_before;
};

#endif  // CORE_H_
