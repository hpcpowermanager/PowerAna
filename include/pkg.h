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

#ifndef PKG_H_
#define PKG_H_

#include <core.h>

#include <iostream>
#include <vector>

class Pkg {
 public:
    explicit Pkg(int pkg_id);
    std::vector<Core> cores;
    std::vector<CState> pc_states;
    int get_pkg_id();
    void init();
    void update(timeval stamp_delta);
    double get_pkg_power();
    double get_pp0_power();
    double get_dram_power();

 private:
    int pkg_id;
    double energy_units;
    double pkg_energy, pp0_energy, dram_energy;
    uint64_t pkg_before, pkg_after;
    uint64_t pp0_before, pp0_after;
    uint64_t dram_before, dram_after;
    uint64_t tsc_before;
};

#endif  // PKG_H_
