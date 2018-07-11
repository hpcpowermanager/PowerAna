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

#include <node.h>

#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>


std::string find_hostname() {
    std::string str;
    std::ifstream fp("/proc/sys/kernel/hostname");
    if (fp.is_open()) {
        getline(fp, str);
        fp.close();
        return str;
    } else {
        std::cout << "Unable to open file\n";
        return NULL;
    }
}

int find_pkg_id(int cpu) {
    int pkg_id;
    char path[100];

    snprintf(path, sizeof(path),
        "/sys/devices/system/cpu/cpu%d/topology/physical_package_id",
        cpu);
    std::ifstream fp(path);
    fp >> pkg_id;
    return pkg_id;
}

void Node::find_topology() {
    int ncores = sysconf(_SC_NPROCESSORS_ONLN);
    for (int core_id = 0; core_id < ncores; core_id++) {
        int pkg_id = find_pkg_id(core_id);
        std::vector<Pkg>::iterator it;

        for (it = pkgs.begin(); it != pkgs.end(); it++) {
            if (it->get_pkg_id() == pkg_id) {
                Core new_core = Core(core_id);
                it->cores.push_back(new_core);
                break;
            }
        }
        if (it == pkgs.end()) {
            Pkg new_pkg = Pkg(pkg_id);
            Core new_core = Core(core_id);
            new_pkg.cores.push_back(new_core);
            pkgs.push_back(new_pkg);
        }
    }
}

void Node::init() {
    node_name = find_hostname();
    find_topology();
    procstat.init();
    for (std::vector<Pkg>::iterator it = pkgs.begin(); it != pkgs.end(); it++)
       it->init();
}

std::string Node::get_node_name() {
    return node_name;
}

void Node::update(timeval stamp_delta) {
    procstat.update();
    for (std::vector<Pkg>::iterator it = pkgs.begin(); it != pkgs.end(); it++)
        it->update(stamp_delta);
}
