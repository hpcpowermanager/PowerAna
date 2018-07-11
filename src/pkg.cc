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

#include <pkg.h>
#include <msr.h>
#include <msr_headers.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>

unsigned int energy_delta(unsigned int after, unsigned int before) {
    if (after > before)
        return after - before;
    else
        return 0x100000000 + after - before;
}

Pkg::Pkg(int pkg_id) {
    this->pkg_id = pkg_id;

    pc_states.push_back(CState("PC2", MSR_PKG_C2_RESIDENCY));
    pc_states.push_back(CState("PC3", MSR_PKG_C3_RESIDENCY));
    pc_states.push_back(CState("PC6", MSR_PKG_C6_RESIDENCY));
    pc_states.push_back(CState("PC7", MSR_PKG_C7_RESIDENCY));
}

int Pkg::get_pkg_id() {
    return pkg_id;
}

void Pkg::init() {
    int fd = open_msr(cores.begin()->get_core_id());

    tsc_before = read_msr(fd, MSR_TSC);
    std::vector<CState>::iterator it_pc;
    for (it_pc = pc_states.begin(); it_pc != pc_states.end(); it_pc++)
        it_pc->init(fd);

    uint64_t msr = read_msr(fd, MSR_RAPL_POWER_UNIT);
    energy_units = 1.0 / (1 << (msr >> 8 & 0x1F));

    pkg_before = read_msr(fd, MSR_PKG_ENERGY_STATUS) & 0xFFFFFFFF;
    pkg_after = 0;
    pkg_energy = 0;

    pp0_before = read_msr(fd, MSR_PP0_ENERGY_STATUS) & 0xFFFFFFFF;
    pp0_after = 0;
    pp0_energy = 0;

    dram_before = read_msr(fd, MSR_DRAM_ENERGY_STATUS) & 0xFFFFFFFF;
    dram_after = 0;
    dram_energy = 0;

    if (fd)
        close_msr(fd);

    std::vector<Core>::iterator it_core;
    for (it_core = cores.begin(); it_core != cores.end(); it_core++)
        it_core->init();
}

void Pkg::update(timeval stamp_delta) {
    int fd;
    double interval = stamp_delta.tv_sec + stamp_delta.tv_usec / 1000000.0;
    fd = open_msr(cores.begin()->get_core_id());

    uint64_t tsc_after = read_msr(fd, MSR_TSC);
    if (tsc_after != tsc_before) {
        std::vector<CState>::iterator it_pc;
        for (it_pc = pc_states.begin(); it_pc != pc_states.end(); it_pc++)
            it_pc->update(fd, tsc_after-tsc_before);
        tsc_before = tsc_after;
    }

    pkg_after = read_msr(fd, MSR_PKG_ENERGY_STATUS) & 0xFFFFFFFF;
    pkg_energy = energy_delta(pkg_after, pkg_before) *
                                     energy_units / interval;
    pkg_energy = roundf(pkg_energy * 100) / 100;

    pp0_after = read_msr(fd, MSR_PP0_ENERGY_STATUS) & 0xFFFFFFFF;
    pp0_energy = energy_delta(pp0_after, pp0_before) *
                                     energy_units / interval;
    pp0_energy = roundf(pp0_energy * 100) / 100;

    dram_after = read_msr(fd, MSR_DRAM_ENERGY_STATUS) & 0xFFFFFFFF;
    dram_energy = energy_delta(dram_after, dram_before) *
                                     energy_units / interval;
    dram_energy = roundf(dram_energy * 100) / 100;

    pkg_before = pkg_after;
    pp0_before = pp0_after;
    dram_before = dram_after;

    if (fd)
        close_msr(fd);

    std::vector<Core>::iterator it_core;
    for (it_core = cores.begin(); it_core != cores.end(); it_core++)
        it_core->update();
}

double Pkg::get_pkg_power() {
    return pkg_energy;
}

double Pkg::get_pp0_power() {
    return pp0_energy;
}

double Pkg::get_dram_power() {
    return dram_energy;
}
