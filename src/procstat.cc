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

#include <procstat.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>


std::vector<size_t> get_cpu_times() {
    std::ifstream proc_stat("/proc/stat");
    proc_stat.ignore(5, ' ');   // Skip the 'cpu' prefix.
    std::vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time))
        continue;
    return times;
}

int get_cpu_times(size_t &idle_time, size_t &total_time) {
    const std::vector<size_t> cpu_times = get_cpu_times();
    idle_time = cpu_times[3];
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
}

void ProcStat::init() {
    get_cpu_times(previous_idle_time, previous_total_time);
}

void ProcStat::update() {
    size_t idle_time, total_time;

    get_cpu_times(idle_time, total_time);
    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;

    float p_cpu = 100.0 * (1.0 - idle_time_delta / total_time_delta);
    float p_idle = 100.0 * idle_time_delta / total_time_delta;

    percent_cpu = roundf(p_cpu * 100) / 100;
    percent_idle = roundf(p_idle * 100) / 100;

    previous_idle_time = idle_time;
    previous_total_time = total_time;
}

float ProcStat::get_percent_cpu() {
    return percent_cpu;
}

float ProcStat::get_percent_idle() {
    return percent_idle;
}
