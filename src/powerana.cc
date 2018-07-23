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
#include <cstate.h>

#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <thread>
#include <sstream>

const char sep = ' ';
const int line_width = 113;
const int date_width = 10;
const int time_width = 8;
const int node_width = 8;
const int pcpu_width = 5;
const int pidle_width = 5;
const int pkg_width = 3;
const int pkg_width2 = 44;
const int pkgpwr_width = 6;
const int pp0pwr_width = 6;
const int drampwr_width = 7;
const int core_width = 4;
const int core_width2 = 95;
const int cstate_width = 5;

void do_sleep() {
    sleep(1);
}

void PowerAna::print_counters() {
    struct tm tinfo;
    char date[15], time[15];
    time_t rawtime = stamp_after.tv_sec;
    localtime_r(&rawtime, &tinfo);
    strftime(date, 15, "%Y-%m-%d", &tinfo);
    strftime(time, 15, "%H:%M:%S", &tinfo);

    // Print headers
    std::cout << std::string(line_width, '-') << std::endl \
      << std::setw(date_width) << "Date" \
      << sep << std::setw(time_width) << "Time" \
      << sep << std::setw(node_width) << "Node" \
      << sep << std::setw(pcpu_width) << "CPU%" \
      << sep << std::setw(pidle_width) << "IDLE%" \
      << sep << std::setw(pkg_width) << "Pkg";

    std::vector<CState>::iterator it_pc;
    for (it_pc = node.pkgs.begin()->pc_states.begin(); \
      it_pc != node.pkgs.begin()->pc_states.end(); \
      it_pc++)
        std::cout << sep << std::setw(cstate_width) << it_pc->get_name() + "%";

    std::cout << sep << std::setw(pkgpwr_width) << "PkgPwr" \
      << sep << std::setw(pkgpwr_width) << "Pp0Pwr" \
      << sep << std::setw(pkgpwr_width) << "DramPwr" \
      << sep << std::setw(core_width) << "Core";
    std::vector<CState>::iterator it_cc;
    for (it_cc = node.pkgs.begin()->cores.begin()->cc_states.begin(); \
      it_cc != node.pkgs.begin()->cores.begin()->cc_states.end(); \
      it_cc++)
        std::cout << sep << std::setw(cstate_width) << it_cc->get_name() + "%";
    std::cout << std::endl << std::string(line_width, '-') << std::endl;

    // Print counters
    std::cout << std::setw(date_width) << date \
      << sep << std::setw(time_width) << time \
      << sep << std::setw(node_width) << node.get_node_name() \
      << sep << std::setw(pcpu_width) << node.procstat.get_percent_cpu() \
      << sep << std::setw(pidle_width) << node.procstat.get_percent_idle();

    for (std::vector<Pkg>::iterator it_pkg = node.pkgs.begin(); \
      it_pkg != node.pkgs.end(); \
      it_pkg++) {
        if (it_pkg == node.pkgs.begin())
            std::cout << sep << std::setw(pkg_width) << it_pkg->get_pkg_id();
        else
            std::cout << std::endl << std::setw(pkg_width2) \
              << it_pkg->get_pkg_id();

        for (std::vector<CState>::iterator it_pc = it_pkg->pc_states.begin(); \
          it_pc != it_pkg->pc_states.end(); \
          it_pc++)
            std::cout << sep << std::setw(cstate_width) \
              << it_pc->get_percent_cstate();

        std::cout << sep << std::setw(pkgpwr_width) << it_pkg->get_pkg_power() \
          << sep << std::setw(pp0pwr_width) << it_pkg->get_pp0_power() \
          << sep << std::setw(drampwr_width) << it_pkg->get_dram_power();

        for (std::vector<Core>::iterator it_core = it_pkg->cores.begin(); \
          it_core != it_pkg->cores.end(); \
          it_core++) {
            if (it_core == it_pkg->cores.begin())
                std::cout << sep << std::setw(core_width) \
                  << it_core->get_core_id();
            else
                std::cout << std::endl << std::setw(core_width2) \
                  << it_core->get_core_id();

            for (std::vector<CState>::iterator it_cc \
              = it_core->cc_states.begin(); \
              it_cc != it_core->cc_states.end(); \
              it_cc++)
                std::cout << sep << std::setw(cstate_width) \
                  << it_cc->get_percent_cstate();
        }
    }

    std::cout << std::endl << std::string(line_width, '-') << std::endl;
}

int PowerAna::init() {
    gettimeofday(&stamp_before, NULL);
    node.init();

    loop();
    loop();
    return 0;
}

void PowerAna::update_timestamp() {
    gettimeofday(&stamp_after, NULL);
    timersub(&stamp_after, &stamp_before, &stamp_delta);
    stamp_before = stamp_after;
}

void PowerAna::update_counters() {
    update_timestamp();
    node.update(stamp_delta);
}

int PowerAna::loop() {
    std::thread th(do_sleep);

    update_counters();
    print_counters();

    th.join();
}

void PowerAna::cleanup() {
}
