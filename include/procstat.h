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

#ifndef PROCSTAT_H_
#define PROCSTAT_H_

#include <unistd.h>

class ProcStat {
 public:
    void init();
    void update();
    float get_percent_cpu();
    float get_percent_idle();

 private:
    size_t previous_idle_time, previous_total_time;
    float percent_cpu, percent_idle;
};

#endif  // PROCSTAT_H_
